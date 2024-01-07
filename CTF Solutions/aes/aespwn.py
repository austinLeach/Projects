from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import base64
# from secret import flag

KEY_LEN = 2
BS = 16
iv =  b'\x1d\xf4\x9b\xc5\x0b\xc2\x43\x2b\xd3\x36\xb4\x60\x9f\x21\x04\xf7'
ct = b'\xa4\x0c\x65\x02\x43\x6e\x3a\x21\xdd\x63\xc1\x55\x3e\x48\x16\x96\x7a\x75\xdf\xc0\xc7\xb9\x03\x28\xf0\x0a\xf9\x3f\x00\x94\xed\x62'

for i in range(0xff):
    for j in range(0xff):
        pair = bytearray([i,j])
        key = pad(pair, BS)
        cipher = AES.new(key, AES.MODE_CBC, iv)
        plaintext = cipher.decrypt(ct)
        try:
            print(plaintext.decode())
        except:
            asdf = 0
        

# ct = cipher.encrypt(pad(flag, 16))

# print(f"key = {key.hex()}")
# print(f"iv = {iv.hex()}")

# Output:
# iv = 1df49bc50bc2432bd336b4609f2104f7
# ct = a40c6502436e3a21dd63c1553e4816967a75dfc0c7b90328f00af93f0094ed62