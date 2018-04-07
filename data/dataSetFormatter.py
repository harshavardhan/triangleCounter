import sys

if(len(sys.argv) != 2):
    print("Usage : python3 dataSetFormatter.py <filename>")
    sys.exit()

firstLine = True
dicti_rev = {}
pair_map = {}
counter = 0
newFile  = open(sys.argv[1]+"updated", "w")
lineCounter = 1
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
            if(dicti_rev[n1] < dicti_rev[n2]):
                low = dicti_rev[n1]
                high = dicti_rev[n2]
            # elif(dicti_rev[n1] == dicti_rev[n2]):
            #     print("Self edges in a node, inconsistent dataset")
            #     print(lineCounter)
            #     sys.exit()
            else:
                low = dicti_rev[n2]
                high = dicti_rev[n1]

            if pair_map.get((low, high)) is None:
                newFile.write(str(low)+" "+str(high)+"\n")
                pair_map[(low, high)] = 1
        lineCounter += 1
newFile.close()
