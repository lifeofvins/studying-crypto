from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

N = 1024

keypair = RSA.generate(N)

export_key_material = keypair.export_key(format='PEM', pkcs=8, passphrase='verygoodpassword')

with open("mykey.pem", 'wb') as f:
    f.write(export_key_material)
    f.close() 

with open("mykey.pem", 'rb') as f:
    keypair_from_file = RSA.import_key(f.read(), passphrase='verygoodpassword')
    f.close()

print(str(keypair.p) + " " + str(keypair.q) + " ")
print(str(keypair_from_file.p) + " " + str(keypair_from_file.q) + " ")

public_key = keypair.public_key()

# alice
message = b'my mexxxxx'
rsa_encrypter = PKCS1_OAEP.new(public_key)
rsa_mex = rsa_encrypter.encrypt(message)

# bob
rsa_decrypter = PKCS1_OAEP.new(keypair)
dec_rsa_mex = rsa_decrypter.decrypt(rsa_mex)
print(message.decode())
print(dec_rsa_mex.decode())

