from random import randint
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Cryptodome.Util.Padding import pad
from base64 import b64encode, b64decode


def shortkey8_enc(key, message, iv):
    cipher = AES.new(key.to_bytes(16, 'big'), AES.MODE_CBC, iv)
    return cipher.encrypt(pad(message, AES.block_size))

def shortkey8_dec(key, message, iv):
    cipher = AES.new(key.to_bytes(16, 'big'), AES.MODE_CBC, iv)
    return cipher.decrypt(message)

def double8_enc(key1, key2, message, iv):
    cipher1 = AES.new(key1.to_bytes(16, 'big'), AES.MODE_CBC, iv)
    cipher2 = AES.new(key2.to_bytes(16, 'big'), AES.MODE_CBC, iv)
    return cipher2.encrypt(cipher1.encrypt(pad(message, AES.block_size)))

if __name__ == '__main__':
    MAX_KEY = 2**8
    k1 = randint(0,MAX_KEY)
    k2 = randint(0,MAX_KEY)
    iv = get_random_bytes(AES.block_size)
    plaintext = b'this is the plaintext...'
    ciphertext = double8_enc(k1, k2, plaintext, iv)

    # let's now build the dictionary from the plaintext
    intermediate_dict = dict()
    
    # from plaintext to the intermediate artifact
    for i in range(MAX_KEY):
        intermediate_enc = shortkey8_enc(i, plaintext, iv)
        intermediate_dict[intermediate_enc] = i
    
    # completed on the encryption side

    ####################################

    # the other direction now

    for i in range(MAX_KEY):
        intermediate_dec = shortkey8_dec(i, ciphertext, iv)

        if intermediate_dec in intermediate_dict:
            print("Candidate keys found!")
            print("key1: " + str(intermediate_dict[intermediate_dec]))
            print("key2: " + str(i))
