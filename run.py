from subprocess import call
import os

files = sorted(["tests/" + f for f in os.listdir('tests') if os.path.isfile("tests/" + f) and f.endswith(".lang")])

for f in files:
    newf = f + ".s"
    call("echo " + f + ":", shell=True)
    assembly = call("./lang < " + f + " > " + newf, shell=True)
    if not (assembly == 0):
        call("rm -f " + newf, shell=True)
        continue
    compiled = call("gcc -m32 -o tests/exec tester.c " + newf, shell=True)
    call("rm " + newf, shell=True)
    if not (compiled == 0):
        continue
    ran = call("tests/exec", shell=True)
    if not (ran == 0):
    	call("echo Program exited with an error.", shell=True)
    call("rm tests/exec", shell=True)
