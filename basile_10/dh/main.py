from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.hazmat.primitives.constant_time import bytes_eq
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.hashes import SHA256

# gen parameters: generator and modulus
g = 2
param = dh.generate_parameters(generator=g, key_size=1024)

# server: alice generates the private part: x
server_prik = param.generate_private_key()
x = server_prik.private_numbers().x
# print(server_prik.parameters().parameter_numbers().g)
# print(server_prik.parameters().parameter_numbers().p)
# print(server_prik.parameters().parameter_numbers().q)
# print(server_prik.private_numbers().x)


server_pubk = server_prik.public_key()
# print(server_pubk.public_numbers().y)
# y = g^x mod p -- also computable with pow(g,x,p)
y = server_pubk.public_numbers().y

client_prik = param.generate_private_key()
client_pubk = client_prik.public_key()

server_secret = server_prik.exchange(client_pubk)
client_secret = client_prik.exchange(server_pubk)

if bytes_eq(client_secret, server_secret):
    print("same secrets")
else:
    print("different secrets")

s_key = HKDF(algorithm=SHA256(), length=16, salt=None, info=server_secret).derive(b'')
print("$ server key > " + str(s_key))

c_key = HKDF(algorithm=SHA256(), length=16, salt=None, info=client_secret).derive(b'')
print("$ client key > " + str(c_key))

if bytes_eq(c_key, s_key):
    print("same keys")
else:
    print("different keys")

