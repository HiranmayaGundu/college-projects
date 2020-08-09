file = open("insert2.txt",'r')
insert2 = list()
for line in file:
	  insert2.append(float(line));
file.close()
print("Insert 2 min is " + str(min(insert2)) + " max is " + str(max(insert2))+ " avg is " + str(sum(insert2)/len(insert2)))

file = open("insert3.txt",'r')
insert3 = list()
for line in file:
	  insert3.append(float(line));
file.close()
print("Insert 3 min is " + str(min(insert3)) + " max is " + str(max(insert3))+ " avg is " + str(sum(insert3)/len(insert3)))



file = open("insert 1.5.txt",'r')
insert15 = list()
for line in file:
	  insert15.append(float(line));
file.close()
print("Insert 1.5 min is " + str(min(insert15)) + " max is " + str(max(insert15))+ " avg is " + str(sum(insert15)/len(insert15)))



file = open("insert 1.25.txt",'r')
insert125 = list()
for line in file:
	  insert125.append(float(line));
file.close()
print("Insert 1.25 min is " + str(min(insert125)) + " max is " + str(max(insert125))+ " avg is " + str(sum(insert125)/len(insert125)))



file = open("insert 1.75.txt",'r')
insert175 = list()
for line in file:
	  insert175.append(float(line));
file.close()
print("Insert 1.75 min is " + str(min(insert175)) + " max is "  + str(max(insert175))+ " avg is " + str(sum(insert175)/len(insert175)))



file = open("pop .5.txt",'r')
pop5 = list()
for line in file:
	  pop5.append(float(line));
file.close()
print("pop 0.5 min is " + str(min(pop5)) + " max is " + str(max(pop5))+ " avg is " + str(sum(pop5)/len(pop5)))



file = open("pop .25.txt",'r')
pop25 = list()
for line in file:
	  pop25.append(float(line));
file.close()
print("pop 0.25 min is " + str(min(pop25)) + " max is " + str(max(pop25))+ " avg is " + str(sum(pop25)/len(pop25)))



file = open("pop .75.txt",'r')
pop75 = list()
for line in file:
	  pop75.append(float(line));
file.close()
print("pop 0.75 min is " + str(min(pop75)) + " max is " + str(max(pop75))+ " avg is " + str(sum(pop75)/len(pop75)))


