from Crypto.Hash import SHA256

# init
hash_gen = SHA256.new()

# update
with open("./main.py", "rb") as f:
    hash_gen.update(f.read(1024))

print(hash_gen.hexdigest())
print(hash_gen.digest())