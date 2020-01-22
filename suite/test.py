#!/usr/bin/env python3
import glob
import sys
import os
import subprocess
import difflib


def getCurrentOutput(filename):
    return subprocess.check_output(["../bin/markus-dump", filename]).decode("utf-8")


def check(filename):
  with open(filename + '.dump', 'r') as file:
    expected = file.read().strip().splitlines()
  actual = getCurrentOutput(filename).strip().splitlines()
  ok = expected == actual
  if ok:
    return True
  print("Failed " + filename)
  print("=" * 100)
  for line in difflib.unified_diff(expected, actual, fromfile='Expected', tofile='Actual'):
    print(line.rstrip())
  print("=" * 100)
  return False


def main():
  os.chdir(os.path.dirname(os.path.realpath(__file__)))
  filenames = sorted(glob.glob("*/*.markus"))
  for file in filenames:
    if not check(file):
      return -1
    print("[OK] " + file)
  return 0


if __name__ == "__main__":
    sys.exit(main())
