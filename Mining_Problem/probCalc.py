file = open("input.txt",'r')

YgY = 0
NgY = 0
YgN = 0
NgN = 0

totalYgY = 0.0
totalNgY = 0.0
totalYgN = 0.0
totalNgN = 0.0

for each in range(0,1000):
	YgY = 0.0
	NgY = 0.0
	YgN = 0.0
	NgN = 0.0
	map={}
	for i in range(0,8):
		curLine = file.readline()
		for j in range(0,8):
			map[(i,j)]=int(curLine[j])
	file.readline()
	
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
				if(map[(x,y)] == 1):
					Ygx += 1
				else:
					Ngx += 1
			#right
			if(i!=7):
				x=i+1
				y=j
				if(map[(x,y)] == 1):
					Ygx += 1
				else:
					Ngx += 1
			#up
			if(j!=0):
				x=i
				y=j-1
				if(map[(x,y)] == 1):
					Ygx += 1
				else:
					Ngx += 1
			#down
			if(j!=7):
				x=i
				y=j+1
				if(map[(x,y)] == 1):
					Ygx += 1
				else:
					Ngx += 1
					
			if(map[(x,y)] == 1):
				YgY += Ygx
				NgY += Ngx
			else:
				YgN += Ygx
				NgN += Ngx
				
	print(YgY/(YgY+NgY))
	print(YgN/(YgN+NgN))
	totalYgY = YgY
	totalNgY = NgY
	totalYgN = YgN
	totalNgN = NgN
print(" ")
print(totalYgY/(totalYgY+totalNgY))
print(totalYgN/(totalYgN+totalNgN))
raw_input()
