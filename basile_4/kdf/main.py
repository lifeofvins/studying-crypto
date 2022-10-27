from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes

password = b'my password easily discoverable'
salt = get_random_bytes(16)
key = scrypt(password=password, salt=salt, key_len=32, N=2**20, r=8, p=1)
print(key.hex())