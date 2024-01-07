#! /bin/python3
# Austin Leach

warAndPeace = open("war-and-peace.txt", "r")

bigrams = {}
totalBigrams = 0

for line in warAndPeace:
    line = line.strip()
    for i in range(0, len(line)):
        if i == len(line)-1:
            bigram = line[i] + " "
        else:
            bigram = line[i] + line[i+1]
        if bigram in bigrams:
            bigrams[bigram] += 1
        else:
            bigrams[bigram] = 1
        totalBigrams += 1

warAndPeace.close()

bigramsFile = open("bigrams.txt", "w")
for bigram in bigrams:
    bigrams[bigram] = bigrams[bigram]/totalBigrams

    # \t to use as a delimiter later
    bigramFrequency = bigram + "\t" + str(bigrams[bigram]) + "\n"

    bigramsFile.write(bigramFrequency)

bigramsFile.close()
