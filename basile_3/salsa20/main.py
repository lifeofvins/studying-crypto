from pydoc import plain
from Cryptodome.Cipher import Salsa20
from Cryptodome.Random import get_random_bytes

plaintext1 = b'Mammamia'
plaintext2 = b'chepizza'

key = get_random_bytes(16)

cipher = Salsa20.new(key=key)

ciphertext = cipher.encrypt(plaintext=plaintext1)
ciphertext += cipher.encrypt(plaintext=plaintext2)
nonce = cipher.nonce

cipher_dec = Salsa20.new(key=key, nonce=nonce)
plaintext_dec = cipher_dec.decrypt(ciphertext)

print(plaintext_dec)