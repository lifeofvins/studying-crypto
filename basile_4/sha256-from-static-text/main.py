from Crypto.Hash import SHA256

# init
hash_gen = SHA256.new(b'zero part')

# update
hash_gen.update(b'first part')
hash_gen.update(b'second part')
hash_gen.update(b'third part')
hash_gen.update(b'fourth part')
hash_gen.update(b'fifth part')
hash_gen.update(b'sixth and last part')

print(hash_gen.hexdigest())
print(hash_gen.digest())