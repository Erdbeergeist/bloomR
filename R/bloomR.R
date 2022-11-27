library(Rcpp)

sourceCpp('src/murmurhash.cpp')
sourceCpp('src/BloomFilter.cpp')

murmurhash("Nora", 255)

BF <- new(BloomFilter, size = 5000, n_hashes = 2, seed = 255)

BF$insert('Nora')
BF$insert("Lukas")
BF$check("Nora")
BF$check('Lukas')
BF$check('Annika')
