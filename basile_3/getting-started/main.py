from Cryptodome.Random import get_random_bytes
from base64 import b64encode

random = get_random_bytes(16)
print(b64encode(random))