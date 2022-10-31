from factordb.factordb import FactorDB
from Crypto.Util.number import getPrime

n_len = 31

p1 = getPrime(n_len)
p2 = getPrime(n_len)

n = p1 * p2

fdb = FactorDB(n)
fdb.connect()