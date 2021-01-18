f = open("pow_two.txt","w")

for i in range(2000):
	f.write("\"" + str(1<<i) + "\",")
f.close()