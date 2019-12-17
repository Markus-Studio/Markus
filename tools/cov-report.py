#!/usr/bin/env python3
import sys
import os
import subprocess

def get_git_root():
    return subprocess.check_output(
        ["git", "rev-parse", "--show-toplevel"]
    ).decode("utf-8").strip()

def exec(command, env=None):
    subprocess.Popen(command, env=env).wait()

def build():
    exec(["cmake", ".", "-DBUILD_BINARY=OFF", "-DBUILD_TESTS=ON", "-DBUILD_FOR_COVERAGE=ON"])
    exec(["make"])

def exec_save(command, file):
    f = open(file, "w")
    subprocess.call(command, stdout=f)

def generateReport():
    env = os.environ.copy()
    env["LLVM_PROFILE_FILE"] = "/tmp/markus.profraw"
    exec(["./bin/markus-test"], env=env)
    exec(["llvm-profdata", "merge", "-sparse", "/tmp/markus.profraw", "-o", "/tmp/markus.profdata"])
    exec_save(["llvm-cov", "show", "./bin/markus-test", "-instr-profile=/tmp/markus.profdata", "-format=html"], "coverage-report.html")
    exec(["llvm-cov", "report", "./bin/markus-test", "-instr-profile=/tmp/markus.profdata"])

def main():
    os.chdir(get_git_root())
    build()
    generateReport()
    print("A full report was saved to coverage-report.html")

if __name__ == "__main__":
    sys.exit(main())