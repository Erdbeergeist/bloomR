# bloomR
Bloom Filter Package for R, with a C++ implementation of a Bloom Filter using murmurhash3 and Kirsch-Mitzenmacher strategy.

For a detailed introduction and review of Bloom Filters and especially the employed strategy to create n hashes see:
https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf

## Usage 
To use the Bloom Filter create an instance and take care to explicitely specify the type of the arguments, this is required for the validator to work its magic and call the correct constructor. A very simple example could look like this:
```
library(bloomR)
library(dplyr)

seed = 1337
set.seed(seed)

data <- as.data.frame(faithful) %>% mutate(id = row_number(), 
                                           name = str_c(eruptions, waiting, id))

train <- data %>% sample_frac(.7)
test <- data %>% anti_join(train, by = 'name')

# Initializing with a desired false positive rate
b <- new(BloomFilter, 
         num_elements = as.integer(190), 
         epsilon = as.numeric(0.02), 
         seed = as.integer(1337))
b$n_hashes
b$size


# Initializing by setting the size and number of hash functions manually
b <- new(BloomFilter, 
         size = as.integer(1000), 
         n_hashes = as.integer(1), 
         seed = as.integer(1337))

b$size

b$check_fill_rate()
map(train$name, b$insert)

b$check_fill_rate()
map(test$name, b$check)
```
