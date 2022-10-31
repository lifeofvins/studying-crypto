from Crypto.Util.number import getPrime
from math import gcd

N = 2048  # length of my prime numbers

p1 = getPrime(N)
p2 = getPrime(N)

n = p1 * p2
phi = (p1-1)*(p2-1)

e = 65537

# check gcd(e, phi) == 1
if gcd(e, phi) != 1:
    raise ValueError
    exit(-1)

d = pow(e, -1, phi)

pub_key = (e, n)
pri_key = (d, n)

msg = b'yumino ti amo!!!'
int_message = int.from_bytes(msg, byteorder='big')

if int_message >= n:
    raise ValueError
    exit(-2)

enc = pow(int_message, e, n)
dec = pow(enc, d, n)
print("> enc: " + str(enc))
print("> dec: " + dec.to_bytes(2 * N, byteorder='big').decode())
