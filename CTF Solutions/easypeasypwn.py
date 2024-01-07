from pwn import *
io = remote("mercury.picoctf.net", 36981)

encflag = b'\x00' * 32
payload=b'\x00' * 49968

io.sendline(payload)
io.sendline(encflag)
io.interactive()