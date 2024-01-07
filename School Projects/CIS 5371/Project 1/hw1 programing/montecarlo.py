#! /bin/python3
# Austin Leach

import math
import string
import random

def swap(string, pos1, pos2):
    stringlist = list(string)
    temp = stringlist[pos1]
    stringlist[pos1] = stringlist[pos2]
    stringlist[pos2] = temp
    string = "".join(stringlist)
    return string

def decrypt(decryptedText, cipherText, key, alphabet):
    for line in cipherText:
        newline = ""
        for i in range(0, len(line)):
            # find where the current character is in the key
            indexInKey = key.find(line[i])
            # index is -1 if it is a non alphabetic character like " " or ","
            if (indexInKey == -1):
                newline += line[i]
                continue
            # replace current character with substitution of alphabet index with key
            newline += alphabet[indexInKey]
        decryptedText.append(newline)
    return decryptedText


bigramsFile = open("bigrams.txt", "r")

englishBigrams = {}

# get bigrams and compute log of frequency
for line in bigramsFile:
    line = line.strip("\n")
    # \t is delimiter in bigrams.txt
    line =  line.split("\t")
    englishBigrams[line[0]] = math.log(float(line[1]))
    # print (line[0],englishBigrams[line[0]])

bigramsFile.close()

inputFile = open("input.txt", "r")

alphabet = string.ascii_lowercase
key = string.ascii_lowercase
# random key to start with 
for i in range(0, len(key)):
    randomIndex = random.randrange(26)
    key = swap(key, i, randomIndex)

# make inputFile into array
cipherText = []
for line in inputFile:
    line = line.strip("\n")
    cipherText.append(line)

# large initial bad score since random key will be bad
score = -10000000000

counter = 0
bestDecryptedText = []
for i in range(0,10000):
    roundKey = swap(key, random.randrange(26), random.randrange(26))

    decryptedText = []
    decryptedText = decrypt(decryptedText, cipherText, roundKey, alphabet)
    
    # calculate new bigrams and compare them to english ones to make a score
    roundScore = 0
    for line in decryptedText:
        for i in range(0, len(line)):
            if i == len(line)-1:
                bigram = line[i] + " "
            else:
                bigram = line[i] + line[i+1]
            if bigram in englishBigrams:
                roundScore += englishBigrams[bigram]
            # bigram is not an english bigram so give it a bad score
            else:
                roundScore += -10000
    # print(roundScore, score)
    
    # score closer to zero is better
    if (roundScore > score):
        score = roundScore
        key = roundKey
        bestDecryptedText = decryptedText
    
    # if lower randomly decide to go anyways
    else:
        probability = 1/(2**(abs(score)-abs(roundScore))+1)
        randomFloat = random.random()
        if (probability < randomFloat):
            score = roundScore
            key = roundKey
    counter +=1 
    print(*bestDecryptedText, sep="\n")   
    print("Iteration", counter, "Best key is:", key)

outputFile = open("output.txt", "w")

keyOutput = "Encryption key: " + key
outputFile.write(keyOutput)
outputFile.write("\n\n")
outputFile.write("Plaintext:")
outputFile.write("\n\n")

for line in bestDecryptedText:
    line = line + "\n"
    outputFile.write(line)

outputFile.close()
