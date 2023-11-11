#!/usr/bin/env python
import os
import sys
import os.path
import time 
import subprocess
args = sys.argv
git_cmd_add  = ["git","add","."]
git_cmd_commit  = ["git","commit","-m","Update"]
git_cmd_push  = ["git","push","origin",args[1]]
subprocess.run(git_cmd_add)
subprocess.run(git_cmd_commit)
subprocess.run(git_cmd_push)
