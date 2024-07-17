#!/usr/bin/env python3
import argparse
import ast

from pathlib import Path
from typing import Optional

from mamba.transpiler import transpile


def main() -> None:
    args = parse_args()

    input_path: Path = args.input
    output_path: Optional[Path] = args.output

    module: ast.Module = ast.parse(source=input_path.read_text(), filename=input_path)

    print(ast.dump(module, indent=4), flush=True)

    result: str = transpile(module=module)

    if not output_path:
        output_path: Path = input_path.with_name(f"{input_path.stem}.py.cpp")

    output_path.write_text(result)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("-i", "--input", type=Path, required=True)
    parser.add_argument("-o", "--output", type=Path, default=None)

    return parser.parse_args()


if __name__ == "__main__":
    main()
