#!/usr/bin/env python3
import sys
import os
import subprocess

def exec(args):
    return subprocess.check_output(args).decode("utf-8")

def list_filter(function, items):
    return list(filter(function, items))

def get_git_root():
    return exec(["git", "rev-parse", "--show-toplevel"]).strip()

def get_git_files():
    return exec(["git", "ls-files"]).splitlines()

def clang_format(files):
    return subprocess.call(["clang-format", "-i", "-style=Chromium"] + files)

def match_file(file):
    return file.endswith(".cpp") or file.endswith(".hpp")

def main():
    os.chdir(get_git_root())
    clang_format(
        list_filter(
            match_file,
            get_git_files()
        )
    )

if __name__ == "__main__":
    sys.exit(main())