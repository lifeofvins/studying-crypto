import base64
import json
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

key = get_random_bytes(32)
cipher = AES.new(key, AES.MODE_GCM)

auth_only_data = b'this is the part to authenticate / header'
confidential_data = b'this needs to be encrypted'

cipher.update(auth_only_data)
ciphertext, tag = cipher.encrypt_and_digest(confidential_data)

keys = ['ciphertext', 'tag', 'header', 'nonce']
data = [base64.b64encode(ciphertext).decode(),
        base64.b64encode(tag).decode(),
        auth_only_data.decode(),
        base64.b64encode(cipher.nonce).decode()
        ]

packed_data = json.dumps(dict(zip(keys, data)))
print(packed_data)
