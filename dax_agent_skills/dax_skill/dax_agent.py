#!/usr/bin/env python3
"""
DAX Agent entrypoint for Bionic Skill
"""
import sys
import subprocess
import os

DAX_AGENT_EXE = "C:/Users/thoma/OneDrive/Desktop/New folder (7)/weaveformer/dax-cpp/build/Release/dax_agent.exe"
DAX_BIONIC_EXE = "C:/Users/thoma/OneDrive/Desktop/New folder (7)/weaveformer/dax-cpp/build/Release/dax_bionic.exe"

def run(cmd, args):
    exe = DAX_AGENT_EXE if "dax_agent" in cmd else DAX_BIONIC_EXE
    full_cmd = [exe] + args
    result = subprocess.run(full_cmd, capture_output=True, text=True)
    print(result.stdout)
    if result.stderr:
        print(result.stderr, file=sys.stderr)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: dax_agent <command> [args]")
        sys.exit(1)
    cmd = sys.argv[1]
    run(cmd, sys.argv[2:])
