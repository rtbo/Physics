
import sys
import os
import argparse
import json
from jinja2 import Environment

def complete_dim(dim):
    pass

if __name__ == '__main__':

    ap = argparse.ArgumentParser(description="Derived units code generator")
    ap.add_argument("--input", nargs='?', type=argparse.FileType('r'),
            default=sys.stdin, help="Input template to be used")
    ap.add_argument("--output", nargs='?', type=argparse.FileType('w'),
            default=sys.stdout, help="Output file")
    args = ap.parse_args()

    dir_path = os.path.dirname(os.path.realpath(__file__))
    datafile = os.path.join(dir_path, "DerivedDims.json")

    print(datafile)

    with open(datafile, "r") as df:
        derived_dims = json.load(df)

    for dim in derived_dims:
        complete_dim(dim)

    tplt = Environment(trim_blocks=True).from_string(args.input.read())
    args.output.write(tplt.render(dims=derived_dims))
