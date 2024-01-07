import hashlib
import base64

username = 'FRASER'

statickey1 = 'picoCTF{1n_7h3_|<3y_of_'
statickey2 = '}'

key = ''

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[4]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[5]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[3]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[6]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[2]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[7]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[1]

key += hashlib.sha256(username.encode('utf-8')).hexdigest()[8]

print(statickey1 + key + statickey2)