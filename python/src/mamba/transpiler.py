import ast
import io
import sys

from typing import Optional


def transpile(module: ast.Module) -> str:
    buffer = io.StringIO()

    transpiler = Transpiler(buffer=buffer, module=module)
    transpiler.transpile()

    return buffer.getvalue()


class SymbolAlreadyDefinedException(Exception):
    pass


class EmptyScopePopException(Exception):
    pass


class Scope:
    def __init__(self, parent: "Optional[Scope]" = None) -> None:
        self._symbols: "set[str]" = set()
        self._parent: Optional[Scope] = parent

    def define_symbol(self, name: str) -> None:
        if self.has_symbol(name=name):
            raise SymbolAlreadyDefinedException(f"Symbol {name} already defined.")

    def has_symbol(self, name: str) -> bool:
        if name in self._symbols:
            return True

        if self._parent:
            return self._parent.has_symbol(name=name)

        return False


class Transpiler:
    mamba_type_to_cpp: "dict[str, str]" = {
        "bool": "mamba::Boolean",
        "float": "mamba::Double",
        "int": "mamba::Integer",
        "str": "mamba::String",
        "list": "mamba::List",
        "tuple": "mamba::Tuple",
    }

    def __init__(self, buffer: io.StringIO, module: ast.Module) -> None:
        self._module: ast.Module = module
        self._buffer: io.StringIO = buffer
        self._root_scope: Scope = Scope()
        self._non_root_scopes: "list[Scope]" = []

    def transpile(self) -> None:
        self.emit_header()

        for i in self._module.body:
            i_type = type(i)
            if i_type is ast.AnnAssign:
                self.emit_ann_assign(buffer=self._buffer, ann_assign=i)
            elif i_type is ast.Expr:
                self.emit_expr(buffer=self._buffer, expr=i)
            else:
                print(f"Unsupported type {i_type}", flush=True, file=sys.stderr)
                continue

            self._buffer.write("\n")

        self.emit_footer()

    def emit_header(self) -> None:
        self._buffer.write(
            """#include "mamba/mamba.hpp"

using namespace mamba;

int main() {
"""
        )

    def emit_footer(self) -> None:
        self._buffer.write("}\n")

    def translate_mamba_type_to_cpp(self, annotation: ast.Name) -> str:
        return self.mamba_type_to_cpp[annotation.id]

    def current_scope(self) -> Scope:
        if self._non_root_scopes:
            return self._non_root_scopes[-1]

        return self._root_scope

    def pop_scope(self) -> None:
        if self._non_root_scopes:
            self._non_root_scopes.pop()

        raise EmptyScopePopException("Attempted to pop scope when scope list is empty")

    def push_scope(self) -> Scope:
        parent: Scope = self._root_scope

        if self._non_root_scopes:
            parent: Scope = self._non_root_scopes[-1]

        self._non_root_scopes.append(Scope(parent=parent))

    def emit_ann_assign(self, buffer: io.StringIO, ann_assign: ast.AnnAssign) -> None:
        symbol_name: str = ann_assign.target.id
        symbol_type: str = self.translate_mamba_type_to_cpp(
            annotation=ann_assign.annotation
        )

        if self.current_scope().has_symbol(symbol_name):
            # Make sure value is Constant
            buffer.write(f'{symbol_name} = "{ann_assign.value.value}";')
        else:
            buffer.write(f'{symbol_type} {symbol_name} = "{ann_assign.value.value}";')

    def emit_expr(self, buffer: io.StringIO, expr: ast.Expr) -> None:
        call: ast.Call = expr.value
        func_name: str = call.func.id
        args: "list[ast.Name]" = call.args

        buffer.write(f"{func_name}({args[0].id});")
