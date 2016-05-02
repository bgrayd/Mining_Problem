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
Bs = [each*100 for each in range(-10,1)]

#As.append(0.5)
#As.append(1)
#Bs.append(-1)
#Bs.append(-0.5)

out1 = open("total.csv","w")
out2 = open("special.csv","w")
out3 = open("special_avg.csv","w")
out1.write(",")
out2.write(",")
out3.write(",")
special = {}
total = {}

for a in As:
	for b in Bs:
		p=subprocess.Popen(["..\Release\Mining_Problem.exe",str(a),str(b)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		r,s = parseOut(p.stdout.readline())
		special[(a,b)] = s
		total[(a,b)] = r
		print("a:"+str(a) +"  b:"+str(b)+"  r:"+str(r)+"   s:"+str(s))
		
for i in range(0,11):
	out1.write(str(Bs[i])+',')
	out2.write(str(Bs[i])+',')
	out3.write(str(Bs[i])+',')
	out1.write(str(As[i])+',')
	out2.write(str(As[i])+',')
	out3.write(str(As[i])+',')
	for a in As:
		out1.write(str(total[(a,b)])+',')
		out2.write(str(special[(a,b)])+',')
		out3.write(str((64.0 * special[(a,b)])/total[(a,b)])+',')
	out1.write("\n")
	out2.write("\n")
	out3.write("\n")


out1.close()
out2.close()
out3.close()
#raw_input()
