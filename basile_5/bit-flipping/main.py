from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes

plaintext = b'plaintext 123456!!!'

# sender
key = get_random_bytes(32)
cipher = ChaCha20.new(key=key)
ciphertext = cipher.encrypt(plaintext=plaintext) # bytes --> unmodifiable

# the sender has sent the message

#########

# attacker side
index = plaintext.index(b'1')
new_value = b'2'
print(ord(new_value)) # ord returns ascii value

# '1' = 49
# '2' = 50 --> last two bits will change

# build the mask
# a XOR b = c --> a XOR c = b
mask = plaintext[index] ^ ord(new_value)
cipher_array = bytearray(ciphertext)
cipher_array[index] = cipher_array[index] ^ mask

# receiver side
cipher_dec = ChaCha20.new(key=key, nonce=cipher.nonce)
print(cipher_dec.decrypt(cipher_array))
