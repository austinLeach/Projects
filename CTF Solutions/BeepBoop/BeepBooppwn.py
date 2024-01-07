
file = open("BeepBoop", "r")

beepBoop = file.readline()
print (beepBoop)

beepBoopList = beepBoop.split(" ")
print(beepBoopList)

result = ""
for thing in beepBoopList:
    if (thing == "beep"):
        result += "0"
    else:
        result += "1"

print(result)

#fha{rkgrezvangr-rkgrezvangr-rkgrezvangr} shift by 13
#sun{exterminate-exterminate-exterminate}