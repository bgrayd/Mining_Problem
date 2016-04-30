'''
Created on Feb 8, 2016

@author: Brandon
'''

import numpy

elements = ['0', '1']
prob = [0.9, 0.1]

map_file = open('input.txt', 'w')
runningTally = 0
count = 0
#for l in xrange(100):
while count < 500:
    map = {}

    for i in xrange(8): #row
        for j in xrange(8): #column
            try:
                if map[str(i),str(j)]:
                    pass
            except:
                if numpy.random.choice(elements, p=prob) == '0':
                    map[str(i),str(j)] = 0
                    prob = [0.9, 0.1]
                else:
                    map[str(i),str(j)] = 1
                    prob[0] = prob[0]/2
                    prob[1] = 1 - prob[0]
                    try:
                        if map[str(i-1),str(j)]:
                            if numpy.random.choice(elements, p=prob) == '1':
                                map[str(i-1),str(j)] = 1
                    except:
                        pass
                    try:
                        if map[str(i+1),str(j)]:
                            if numpy.random.choice(elements, p=prob) == '1':
                                map[str(i-1),str(j)] = 1
                    except:
                        pass
                    try:
                        if map[str(i),str(j-1)]:
                            if numpy.random.choice(elements, p=prob) == '1':
                                map[str(i-1),str(j)] = 1
                    except:
                        pass
                    try:
                        if map[str(i),str(j+1)]:
                            if numpy.random.choice(elements, p=prob) == '1':
                                map[str(i-1),str(j)] = 1
                    except:
                        pass
                prob = [0.9, 0.1]

    tally = 0
    for i in xrange(8): #row
        for j in xrange(8): #column
            tally += map[str(i),str(j)]
    if (tally < 6) or (tally > 10):
        continue
    print(map)
    count+=1
    runningTally += tally
    # export map
    for i in xrange(8): #row
        for j in xrange(8): #column
            map_file.write(str(map[str(i),str(j)]))
        map_file.write('\n')
        
    YgY = 0.0
    NgY = 0.0
    YgN = 0.0
    NgN = 0.0
        
    for i in range(0,8):
        for j in range(0,8):
            Ygx = 0
            Ngx = 0
            x=i
            y=j
            #left
            if(i!=0):
                x = i-1
                y=j
                if(map[str(x),str(y)] == 1):
                    Ygx += 1
                else:
                    Ngx += 1
            #right
            if(i!=7):
                x=i+1
                y=j
                if(map[str(x),str(y)] == 1):
                    Ygx += 1
                else:
                    Ngx += 1
            #up
            if(j!=0):
                x=i
                y=j-1
                if(map[str(x),str(y)] == 1):
                    Ygx += 1
                else:
                    Ngx += 1
            #down
            if(j!=7):
                x=i
                y=j+1
                if(map[str(x),str(y)] == 1):
                    Ygx += 1
                else:
                    Ngx += 1
                    
            if(map[str(x),str(y)] == 1):
                YgY += Ygx
                NgY += Ngx
            else:
                YgN += Ygx
                NgN += Ngx
                
    map_file.write(str(YgY/(YgY+NgY))+'\n')
    map_file.write(str(YgN/(YgN+NgN))+'\n')
    
    map_file.write("\n")
map_file.close()
print(runningTally/(count+1.0))