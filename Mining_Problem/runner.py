import subprocess

#p=subprocess.Popen(["..\Debug\Mining_Problem.exe","-1","4","3","2","1"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

#print(p.stdout.readline())
#raw_input()

def parseOut(output):
	output = output.decode('ascii')
	strValues = []
	strValues = output.split('~')
	runs = 0
	special = 0
	for each in strValues:
		if each == '':
			continue
		value = int(each)
		runs += int(value/1000)
		special += int(value%1000)
	return runs, special

As = [each/10.0 for each in range(-10,1)]
Bs = [each/10.0 for each in range(0,11)]

As.append(0.5)
As.append(1)
Bs.append(-1)
Bs.append(-0.5)

for a in As:
	for b in Bs:
		p=subprocess.Popen(["..\Debug\Mining_Problem.exe",str(a),str(b)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		r,s = parseOut(p.stdout.readline())
		print("a:"+str(a) +"  b:"+str(b)+"  r:"+str(r)+"   s:"+str(s))
raw_input()