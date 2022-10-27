import base64
from email.mime import base
import json
from struct import unpack
from Crypto.Random import get_random_bytes
from Crypto.Hash import HMAC, SHA512

msg = b'message to be signed'
key = get_random_bytes(16)

# init
hmac_gen = HMAC.new(digestmod=SHA512, key=key)

# update
hmac_gen.update(msg)

print(hmac_gen.hexdigest())

# pack data into JSON object
# MAC; original_message

mac = base64.b64encode(hmac_gen.digest()).decode()
pckd_data = json.dumps({"message": msg.decode(), "MAC": mac})

print(pckd_data)


# at receiver side
unpckd_data = json.loads(pckd_data)
print(unpckd_data['message'])
print(unpckd_data['MAC'])

# verification
hmac_verifier = HMAC.new(key=key, digestmod=SHA512)
hmac_verifier.update(unpckd_data['message'].encode())
print(hmac_verifier.hexdigest())

# but better...
try:
    hmac_verifier.verify(base64.b64decode(unpckd_data['MAC']))
except ValueError:
    print("MAC verification failed -> problems")
else:
    print("MAC verification success -> ok")


# change the received MAC: bytearray
# bytes are unmodifiable, so it's needed to use
# the bytearray class -> it'll be b64decoded then when
# passed to the verifier
modified_MAC = bytearray(base64.b64decode(unpckd_data['MAC']))
modified_MAC[0] += 1

try:
    hmac_verifier.verify(base64.b64decode(modified_MAC))
except ValueError:
    print("MAC verification failed -> ok")
else:
    print("MAC verification success -> problems")