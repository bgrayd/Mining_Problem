import random, subprocess, copy, threading, time
from Queue import PriorityQueue


k = 6
iterationsPerType = 10
MaxAmountToChange = 0.5
zeroMaxAmount = 10
ThreadsToRunAtOnce = 3
totalOuterIterations = 500


#p=subprocess.Popen(["..\Debug\Mining_Problem.exe",str(a),str(b)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#r,s = parseOut(p.stdout.readline())

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

class weight():
    def __init__(self,value = 0, a=-1,b=100,c=100,d=100,e=100):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.e = e
        self.value = value
        self.r = 0
        self.s = 0
        
    def varsToChage(self):
        return ['a','b','c','d','e']

    def __lt__(self, other):
        return self.value < other.value

class searchThread():
    def __init__(self, baseWeight, pq, iD):
        self.baseWeight = baseWeight
        self.pq = pq
        self.iD = iD

    def run(self):
        # originalWeight = self.baseWeight

        for currentVar in self.baseWeight.varsToChage():
            currentWeight = copy.deepcopy(self.baseWeight)
            valuesToTry = []
            originalValue = getattr(currentWeight, currentVar)
            adjustBy = random.randint(0,100)/100.0 * MaxAmountToChange
            if originalValue == 0:
                valuesToTry.append(adjustBy * zeroMaxAmount)
                valuesToTry.append(-adjustBy * zeroMaxAmount)
            else:
                valuesToTry.append(originalValue + originalValue*adjustBy)
                valuesToTry.append(originalValue - originalValue*adjustBy)
                valuesToTry.append(-(originalValue + originalValue*adjustBy))
                valuesToTry.append(-(originalValue - originalValue*adjustBy))

            for currValue in valuesToTry:
                currentWeight.__dict__[currentVar] = currValue
                if currentWeight.a == 0:
                    currentWeight.a = 0.0000000000000000000000000001
                p=subprocess.Popen(["..\Release\Mining_Problem.exe",str(currentWeight.a),str(currentWeight.b),str(currentWeight.c),str(currentWeight.d),str(currentWeight.e)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
                r,s = parseOut(p.stdout.readline())
                
                valueBeingMaxed = r + 1000 * s
                
                thisWeight = copy.deepcopy(currentWeight)
                thisWeight.r = r
                thisWeight.s = s
                thisWeight.value = 90000 - valueBeingMaxed
                self.pq.put(((90000 - valueBeingMaxed), copy.deepcopy(thisWeight)))

            print str(self.iD) + " finished variable "+str(currentVar)
        print str(self.iD) + " finished a beam"
                


pq = PriorityQueue()
#baseBeamThread = threading.Thread(target=searchThread(weight(), pq, '-1').run)
#baseBeamThread.start()
#baseBeamThread.join()

for each in range(k - 2):
    a = random.uniform(-20, 20)
    b = random.uniform(-20, 20) * 64
    c = random.uniform(-20, 20)
    d = random.uniform(-20, 20)
    e = random.uniform(-20, 20)
    pq.put((90000, weight(90000, a,b,c,d,e)))
    #pq.put((90000, weight(90000, -1,10000,1,0.5,0.25)))
    
# a = random.uniform(0, 200)
# b = random.uniform(0, 200)
# c = random.uniform(0, 200)
# d = random.uniform(0, 200)
# e = random.uniform(0, 200)
# pq.put((90000, weight(90000, a,b,c,d,e)))

# a = random.uniform(0, 200)
# b = random.uniform(-200, 0)
# c = random.uniform(-200, 0)
# d = random.uniform(-200, 0)
# e = random.uniform(-200, 0)
pq.put((90000, weight(90000, 1, 0, 0, 0, 0)))
pq.put((90000, weight(90000, -1, 1000, 0, 0, 0)))
    
#pq.put((90000, weight(90000, 1,10,10,10,10)))
#pq.put((90000, weight(90000,-1,100,10,10,10)))

for each in range(iterationsPerType):
   print "Iteration: "+str(each+1)
   threads = []
   beams = []
   firstValue = None
   allSame = True
   for i in range(k):
       value,temp = pq.get()
       #print value
       print(str(90000-value)+"  a:"+str(temp.a)+"  b:"+str( temp.b)+"   c:" + str(temp.c)+"   d:"+str( temp.d) + "   e:"+str( temp.e))
       beams.append((value,temp))
       if(firstValue == None):
          firstValue = value
       elif(firstValue != value):
          allSame = False
          
   if(not allSame):
       for i in range(1, k):
           a = random.uniform(-1, 100)
           b = random.uniform(-1, 100)* 64
           c = random.uniform(-1, 100)
           d = random.uniform(-1, 100)
           e = random.uniform(-1, 100)
           beams[i] = (90000, weight(90000, a,b,c,d,e))
   else:
       a = random.uniform(-40, 40)
       b = random.uniform(-40, 40)* 64
       c = random.uniform(-40, 40)
       d = random.uniform(-40, 40)
       e = random.uniform(-40, 40)
       beams[k-1] = (90000, weight(90000, a,b,c,d,e))
   pq = PriorityQueue()
   for thrd in range(k):
       while True:
           if threading.activeCount() <= (ThreadsToRunAtOnce):
               value,nextWeight = beams.pop()
               pq.put((value, nextWeight))
               threads.append(threading.Thread(target=searchThread(nextWeight, pq, str(thrd)).run))
               threads[thrd].start()
               break
           time.sleep(5)
   for thrd in threads:
       thrd.join()

for each in range(k):
    value,nextWeight = pq.get()
    print "Special found:"+str(nextWeight.s)+"   out of:"+str(nextWeight.r)
    print("a:"+str(nextWeight.a)+"  b:"+str( nextWeight.b)+"   c:" + str(nextWeight.c)+"   d:"+str( nextWeight.d) + "   e:"+str( nextWeight.e))
    print("\t")
