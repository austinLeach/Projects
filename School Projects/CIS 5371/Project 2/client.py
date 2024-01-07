#!/usr/bin/python3           # This is client.py file
# Austin Leach
# 31536, 31537
import socket

portPrompt = "Port Number: "
portNumber = int(input(portPrompt))

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("128.186.120.191", portNumber))

message = ''
paddingBytesNumber = 15
decryptingBlock = 0
numberOfBytesInCipherText = 0
prePaddingToReachFullBlock = 0
paddingText = 'aa'

print("Calculating if there is fragmentary data")
# figure out if there is fragmentary data or not
for i in range(0, 16):
    data = '-e ' + paddingText * i
    s.send(data.encode())
    x = s.recv(1024).decode()
    x = x.replace(" ","")
    # take output from server and extract # of encryption bytes
    splitIntoArray = x.split()
    if (i == 0):
        numberOfBytesInCipherText = splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[0]
        # print(numberOfBytesInCipherText + " " + splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[0])
    else:
        # print(numberOfBytesInCipherText + " " + splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[0])
        if (numberOfBytesInCipherText < splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[0]):
            #padding made it add another block
            if (i < 15):
                prePaddingToReachFullBlock = i
                paddingBytesNumber = paddingBytesNumber - i
                print(str(i-1) + " is the number of bytes of padding needed to make it a full block")
                break
        elif(i == 15):
                print("no pre-padding needed to make it a full block")


try:
    while True:
        # construct new encryption query for no padding(unless it is fragmentary, then make it a full block)
        data = '-e ' + paddingText * prePaddingToReachFullBlock
        s.send(data.encode())
        x = s.recv(1024).decode()
        x = x.replace(" ","")
        # take output from server and split it into each part for calculations
        splitIntoArray = x.split()
        numberOfBytesInCipherText = splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[0]
        cipherText = splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[1]
        iv = splitIntoArray[1].split("IV:b'")[1].split("'")[0]
        # print (numberOfBytesInCipherText + "\n" + cipherText + "\n" + iv)

        numberOfBlocks = int(numberOfBytesInCipherText) / 16
        cipherTextBlocks = []
        # ciphertext is in hex so 2 characters is 1 byte so every 32 characters is a 16 byte block
        for i in range(0, len(cipherText), 32):
            cipherTextBlocks.append(cipherText[i:i+32])
        # print(cipherTextBlocks)
        
        # writing hex as padding to need 2 letters to represent one byte of padding
        # construct new encryption query for padding in order to move last byte of message
        data = '-e ' + paddingText * prePaddingToReachFullBlock + paddingText * paddingBytesNumber
        s.send(data.encode())
        x = s.recv(1024).decode()
        x = x.replace(" ","")
        # take output from server and split it into each part for calculations
        splitIntoArray = x.split()
        cipherText = splitIntoArray[0].split("b'Encryption:")[1].split('\\n')[1]
        ivForPadding = splitIntoArray[1].split("IV:b'")[1].split("'")[0]
        # print (numberOfBytesInCipherText + "\n" + cipherText + "\n" + ivForPadding)

        cipherTextBlocksPaddedQuery = []
        for i in range(0, len(cipherText), 32):
            cipherTextBlocksPaddedQuery.append(cipherText[i:i+32])
        # print(cipherTextBlocksPaddedQuery)

        # construct attack for decryption query
        attack = ''
        if (paddingBytesNumber > 0):
            for i in range(0, len(cipherTextBlocks)-1):
                attack = attack + cipherTextBlocks[i]
            attack = attack + cipherTextBlocksPaddedQuery[decryptingBlock]
        # for no padding added
        elif (paddingBytesNumber == 0):
            for i in range(0, len(cipherTextBlocks)-1):
                attack = attack + cipherTextBlocks[i]
            attack = attack + cipherTextBlocks[decryptingBlock]
        # print(attack)
        # use iv from original c0 and not from b0
        attack = "-V " + attack + " " + iv
        s.send(attack.encode())
        x = s.recv(1024).decode()
        # print(x) will be either Invalid or Valid
        # example c0,c1,c2,c3,b1
        # result is lastByte(c3) ^ lastByte(b0) ^ lastByte of V which will always be 15
        if (x == 'Valid' and paddingBytesNumber > 0):
            # convert hex to int for xor operation
            lastByteOfTag = int(cipherTextBlocks[int(numberOfBlocks)-2][-2:], 16)
            lastOfBeforeDecryptionBlock = 0
            # use the block before the current decryption block for the xor
            if (decryptingBlock == 0):
                lastOfBeforeDecryptionBlock = int(ivForPadding[-2:], 16)
            else:
                lastOfBeforeDecryptionBlock = int(cipherTextBlocksPaddedQuery[decryptingBlock-1][-2:], 16)
            padding = 15
            # print(cipherTextBlocks[int(numberOfBlocks)-2][-2:])
            # print(ivForPadding[-2:])
            # print(padding)
            result = lastByteOfTag ^ lastOfBeforeDecryptionBlock ^ padding
            # convert result int back into ascii
            result = chr(result)
            # print(result)
            message = message + result
            print(message)
            paddingBytesNumber = paddingBytesNumber - 1
            

        # for -e with no padding needed
        # example c0,c1,c2,c3,c1
        # result is lastByte(c3) ^ lastByte(iv) ^ 15
        elif (x == 'Valid' and paddingBytesNumber == 0):
            # convert hex to int for xor operation
            lastByteOfTag = int(cipherTextBlocks[int(numberOfBlocks)-2][-2:], 16)
            lastOfBeforeDecryptionBlock = 0
            if (decryptingBlock == 0):
                lastOfBeforeDecryptionBlock = int(iv[-2:], 16)
            else:
                lastOfBeforeDecryptionBlock = int(cipherTextBlocks[decryptingBlock-1][-2:], 16)
            padding = 15
            result = lastByteOfTag ^ lastOfBeforeDecryptionBlock ^ padding
            # convert result int back into ascii
            result = chr(result)
            # print(result)
            # print(cipherTextBlocks[3][-2:])
            # print(iv[-2:])
            message = message + result
            print(message)
            # print(paddingBytesNumber)
            decryptingBlock = decryptingBlock + 1
            paddingBytesNumber = 15
            # -1 because 0 based and -1 because do not need to go past tag block
            if (decryptingBlock == numberOfBlocks - 2):
                break
            

except KeyboardInterrupt:
    s.close()
