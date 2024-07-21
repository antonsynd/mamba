from typing import Mapping, Optional


class SymbolAlreadyDefinedException(Exception):
    pass


class ScopeBase:
    def __init__(self, name: str) -> None:
        self._name: str = name
        self._symbols: Mapping[str, str] = dict()

    def name(self) -> str:
        return self._name

    def symbols(self) -> Mapping[str, str]:
        return self._symbols

    def define_symbol(self, name: str) -> None:
        if self.has_symbol(name=name):
            raise SymbolAlreadyDefinedException(f"Symbol {name} already defined.")

    def has_symbol(self, name: str, decltype: Optional[str] = None) -> bool:
        if decltype:
            return name in self._symbols and self._symbols[name] == decltype

        return name in self._symbols


class RootScope(ScopeBase):
    def __init__(self) -> None:
        super().__init__(name="root")


class Scope(ScopeBase):
    def __init__(self, name: str, parent: ScopeBase) -> None:
        super().__init__(name=name)

        self._parent: ScopeBase = parent

    def has_symbol(self, name: str, decltype: Optional[str] = None) -> bool:
        current_has_symbol: bool = super().has_symbol(name, decltype)

        if current_has_symbol:
            return True

        return self._parent.has_symbol(name, decltype=decltype)
