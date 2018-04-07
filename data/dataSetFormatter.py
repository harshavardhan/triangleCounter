import sys

if(len(sys.argv) != 2):
    print("Usage : python3 dataSetFormatter.py <filename>")
    sys.exit()

firstLine = True
dicti_rev = {}
counter = 0
newFile  = open(sys.argv[1]+"updated", "w")
with open(sys.argv[1], "r") as ins:
    for line in ins:
        if(firstLine):
            firstLine = False
            temp = line.split()
            n = int(temp[0])
            m = int(temp[1])
            newFile.write(str(n)+" "+str(m)+"\n")
        else:
            temp = line.split()
            n1 = int(temp[0])
            n2 = int(temp[1])
            if(dicti_rev.get(n1) is None):
                dicti_rev[n1] = counter
                counter += 1
            if(dicti_rev.get(n2) is None):
                dicti_rev[n2] = counter
                counter += 1
            newFile.write(str(dicti_rev[n1])+" "+str(dicti_rev[n2])+"\n")

newFile.close()
