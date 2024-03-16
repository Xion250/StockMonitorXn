import os
from subprocess import run

clangdir_stdout = run(["whereis", "clang++"], capture_output=True).stdout.decode("utf-8")
clangdir = clangdir_stdout.split()[1]

projectdir_stdout = run("pwd", capture_output=True).stdout.decode("utf-8")
projectdir = projectdir_stdout[0:len(projectdir_stdout)-len("/quick actions/")]

args = " -std=c++17 -stdlib=libc++ "
cmd = clangdir + args + "-g " + projectdir + "/src/*.cpp -o " + projectdir + "/bin/main"

os.system(cmd)
