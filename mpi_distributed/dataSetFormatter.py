import sys


if(len(sys.argv) != 2):
    print("Usage : python3 dataSetFormatter.py <filename>")
    sys.exit()

firstLine = True
dicti_rev = {}
pair_map = {}
counter = 0
lineCounter = 0
with open(sys.argv[1], "r") as ins:
    for line in ins:
        if(firstLine):
            firstLine = False
            temp = line.split()
            n = int(temp[0])
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
            else:
                low = dicti_rev[n2]
                high = dicti_rev[n1]

            if (pair_map.get((low, high)) is None) and low != high:
                pair_map[(low, high)] = 1
                lineCounter += 1

newFile  = open("modified/"+sys.argv[1][9:], "w")
newFile.write(str(n) + " " + str(lineCounter) + "\n")
for i in sorted(pair_map.keys()):
# for i in pair_map.keys():
    newFile.write(str(i[0]) + " " + str(i[1]) + "\n")
newFile.close()
