from os import getrandom
from Cryptodome.Cipher import ChaCha20
from Cryptodome.Random import get_random_bytes
import base64

key = get_random_bytes(32)
cipher = ChaCha20.new(key=key)

plaintext = b'Ciao amore mio bello!'
ciphertext = cipher.encrypt(plaintext=plaintext)

nonceb64 = base64.b64encode(cipher.nonce)
ciphertextb64 = base64.b64encode(ciphertext)

print("Key: " + str(key))
print("Encrypted message: " + ciphertextb64.decode("utf-8"))
print("Generated nonce: " + nonceb64.decode("utf-8"))

# then the receiver gets the encrypted message
# WARNING: remember to pass the nonce to the initialization function
cipher_dec = ChaCha20.new(key=key, nonce=base64.b64decode(nonceb64))
decrypted = cipher_dec.decrypt(base64.b64decode(ciphertextb64))
print("The dectypted string is: " + decrypted.decode())
