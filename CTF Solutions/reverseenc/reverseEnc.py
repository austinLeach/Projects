enc = open("enc").read()
flag = ""
for i in range (0, len(enc)):
    char1 = chr((ord(enc[i]) >> 8))
    char2 = chr(enc[i].encode('utf-16be')[-1])
    flag+= char1
    flag+= char2

print(flag)