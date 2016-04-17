import subprocess

p=subprocess.Popen(["..\Debug\Mining_Problem.exe","-1","4","3","2","1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

print(p.stdout.readline())
raw_input()