'''
Created on Feb 8, 2016

@author: Brandon
'''

import numpy

elements = ['0', '1']
prob = [0.9, 0.1]

map_file = open('input.txt', 'w')

count = 0
#for l in xrange(100):
while count < 100:
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
    
    # export map
    for i in xrange(8): #row
        for j in xrange(8): #column
            map_file.write(str(map[str(i),str(j)]))
        map_file.write('\n')
    
    map_file.write("\n")
map_file.close()
