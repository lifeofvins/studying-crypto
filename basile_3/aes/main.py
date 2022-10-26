from Cryptodome.Cipher import AES
from Cryptodome.Random import get_random_bytes
from Cryptodome.Util.Padding import pad

key = get_random_bytes(32)

cipher = AES.new(key=key, mode=AES.MODE_CBC) # no IV so it'll be automatically generated
plaintext = b'Ciao amore'

# we have to pad the plaintext up to the block size
padded_plaintext = pad(plaintext, AES.block_size)
ciphertext = cipher.encrypt(plaintext=padded_plaintext)

print(ciphertext)

