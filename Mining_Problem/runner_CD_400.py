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

As = [each*1.0 for each in range(-15,10)]#[-1, -0.5, -0.001,0.01, 0.1, 1]#
Bs = [each*1.0 for each in range(-15,10)]#[-2, -1, 0, 10, 50, 100, 1000]#

#As.append(0.5)
#As.append(1)
#Bs.append(-1)
#Bs.append(-0.5)

out1 = open("total_CD_400.csv","w")
out2 = open("special_CD_400.csv","w")
out3 = open("special_avg_CD_400.csv","w")
out1.write(",")
out2.write(",")
out3.write(",")
for each in As:
	out1.write(str(each)+',')
	out2.write(str(each)+',')
	out3.write(str(each)+',')
out1.write("\n")
out2.write("\n")
out3.write("\n")
special = {}
total = {}

for a in As:
	for b in Bs:
		p=subprocess.Popen(["..\Release\Mining_Problem_400.exe", str(-1), str(10), str(a),str(b), str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		r,s = parseOut(p.stdout.readline())
		special[(a,b)] = s
		total[(a,b)] = r
		print("a:"+str(a) +"  b:"+str(b)+"  r:"+str(r)+"   s:"+str(s))
		
for b in Bs:
	out1.write(str(b)+',')
	out2.write(str(b)+',')
	out3.write(str(b)+',')
	for a in As:
		out1.write(str(total[(a,b)])+',')
		out2.write(str(special[(a,b)])+',')
		out3.write(str((64.0 * special[(a,b)])/total[(a,b)])+',')
	out1.write("\n")
	out2.write("\n")
	out3.write("\n")
    
#p=subprocess.Popen(["..\Release\Mining_Problem.exe",str(-0.41124953772),str(0.45),str(0), str(-4.842), str(0)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#r,s = parseOut(p.stdout.readline())
#print("a:"+str(a) +"  b:"+str(b)+"  r:"+str(r)+"   s:"+str(s))


out1.close()
out2.close()
out3.close()
raw_input()
