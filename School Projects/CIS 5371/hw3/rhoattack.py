#!/bin/python3
# Austin Leach
import hashlib
import random
import string

def myHash(input):
    sha256 = hashlib.sha256()
    sha256.update(input.encode())
    fullHash = sha256.hexdigest()
    # print(fullHash)
    return fullHash

found = 0
# generate a random string of length 64
x = ''.join(random.choice(string.ascii_letters+string.digits) for i in range(0, 4))
print("initial x0: ",x)

# tortoise and hare start at same position
# first 32 bits is equivalent to first 4 characters
tortoise = myHash(x) 
hare = tortoise
tortoise2 = ''
for i in range(0, 2**20):
    # print("tortoise: ", tortoise) 
    # print("hare    : ", hare)
    previousTortoise = tortoise
    tortoise = myHash(tortoise)[:4]
    hare = myHash(hare)[:4]
    # print("hare    : ", hare)
    previousHare = hare
    hare = myHash(hare)[:4]
    # compare first 4 characters of each to see if there is a collision
    if (tortoise == hare):
        print("A collision has been found for Tortoise and Hare race")
        print(tortoise, hare)
        found = 1
        tortoiseHash = myHash(previousTortoise)
        hareHash = myHash(previousHare)
        tortoise2 = hare
        break
tortoise = myHash(x)
for i in range(0,2**20):
    previousTortoise = tortoise
    tortoise = myHash(tortoise)[:4]
    previousTortoise2 = tortoise2
    tortoise2 = myHash(tortoise2)[:4]
    if (tortoise == tortoise2 and previousTortoise != previousTortoise2):
        print("A collision has been found for Tortoise and Tortoise race")
        print(tortoise, tortoise2)
        print("x : ", previousTortoise)
        print("x': ", previousTortoise2)
        tortoiseHash = myHash(previousTortoise)
        tortoise2Hash = myHash(previousTortoise2)
        print("x  full SHA-256: ", tortoiseHash)
        print("x' full SHA-256: ", tortoise2Hash)
        break

if not found:
    print("No collision found with starting x: ", x)