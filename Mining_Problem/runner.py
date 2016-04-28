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

As = [-1, -0.5, -0.001, 0]#[each/10.0 for each in range(-10,1)]
Bs = [each*10 for each in range(0,11)]

As.append(0.5)
As.append(1)
Bs.append(-1)
Bs.append(-0.5)

out1 = open("total.csv","w")
out2 = open("special.csv","w")
out1.write(",")
out2.write(",")
for each in As:
	out1.write(str(each)+',')
	out2.write(str(each)+',')
out1.write("\n")
out2.write("\n")

special = {}
total = {}

for a in As:
	for b in Bs:
		p=subprocess.Popen(["..\Debug\Mining_Problem.exe",str(a),str(b)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		r,s = parseOut(p.stdout.readline())
		special[(a,b)] = s
		total[(a,b)] = r
		print("a:"+str(a) +"  b:"+str(b)+"  r:"+str(r)+"   s:"+str(s))
		
for b in Bs:
	out1.write(str(b)+',')
	out2.write(str(b)+',')
	for a in As:
		out1.write(str(total[(a,b)])+',')
		out2.write(str(special[(a,b)])+',')
	out1.write("\n")
	out2.write("\n")

out1.close()
out2.close()
raw_input()
