#! /usr/bin/env python

# Copyright (C) 2017 Remi Thebault
# All rights reserved.
#
# This program and its source code are distributed under the
# terms of the BSD-style license, that can be found in the
# License.txt file at project root.


import sys
import argparse
import json
from jinja2 import Environment


def titleStr(s):
    # return a copy of the string s with first character uppercased,
    # and all other characters untouched
    if len(s) == 0:
        return s;
    ts = s[0].upper()
    if len(s) > 1:
        ts = ts + s[1:]
    return ts

def completeItem(item):
    item["titleName"] = titleStr(item["name"])
    item["titleDefaultUnit"] = titleStr(item["defaultUnit"])
    for u in item["units"]:
        u["titleName"] = titleStr(u["name"])
        if not "litName" in u:
            u["litName"] = u["name"]
        if not "wcharSeq" in u:
            u["wcharSeq"] = u["name"]


if __name__ == '__main__':

    ap = argparse.ArgumentParser(description="Physics code generator")
    ap.add_argument("--datafile", default="PhysicsData.json",
            help="Path to the 'PhysicsData.json' file")
    ap.add_argument("--print-items", dest="print_items", action="store_true", default=False,
            help="print the list of items (one per line) and exit")
    ap.add_argument("--mode", choices=["glob", "item"],
            help="Generation mode: 'glob' for files that take all items as input,"+
             "'item' for files that deal with one item (in such case, --item is required")
    ap.add_argument("--item", help="The physical quantity to generate code for")
    ap.add_argument("--input", nargs='?', type=argparse.FileType('r'),
            default=sys.stdin, help="Input template to be used")
    ap.add_argument("--output", nargs='?', type=argparse.FileType('w'),
            default=sys.stdout, help="Output file")
    args = ap.parse_args()

    with open(args.datafile, "r") as datafile:
        physicsItems = json.load(datafile)

    if args.print_items:
        for item in physicsItems:
            args.output.write(item["name"] + "\n")
        sys.exit(0)

    tplt = Environment(trim_blocks=True).from_string(args.input.read())

    if args.mode == 'glob':
        for pi in physicsItems:
            completeItem(pi)
        args.output.write(tplt.render(items=physicsItems))
    else:
        item = [pi for pi in physicsItems if pi["name"] == args.item][0]
        completeItem(item)
        args.output.write(tplt.render(item=item))
