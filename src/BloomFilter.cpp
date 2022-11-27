#include <Rcpp.h>
#include "BloomFilter.h"

// [[Rcpp::plugins("cpp11")]]

using namespace Rcpp;


BloomFilter::BloomFilter(uint64_t size, uint8_t n_hashes, uint64_t seed){
  BloomFilter::size = size;
  BloomFilter::n_hashes = n_hashes;
  BloomFilter::seed = seed;
  
  BloomFilter::bits = std::vector<bool> (size);
}

std::array<uint64_t, 2> BloomFilter::hashValue(void *data, std::size_t len){
  std::array<uint64_t, 2> hash;
  MurmurHash3_x64_128(data, len, BloomFilter::seed, hash.data());
  
  return hash;
}

uint64_t BloomFilter::ith_hash(uint64_t i, uint64_t hash_0, uint64_t hash_1){
  return (hash_0 + hash_1 * i ) % BloomFilter::size;  
}

void BloomFilter::insert(std::string data){
  auto hashed = hashValue(&data, data.length());
  std::cout<<*hashed.data()<<std::endl;
  
  for (int i = 0; i < BloomFilter::n_hashes; i++){
    BloomFilter::bits[BloomFilter::ith_hash(i, hashed[0], hashed[1])] = true;
  }
}

bool BloomFilter::check(std::string data){
  auto hashed = hashValue(&data, data.length());
  
  for (int i = 0; i < BloomFilter::n_hashes; i++){
    if(!BloomFilter::bits[BloomFilter::ith_hash(i, hashed[0], hashed[1])]) {
      return false;
    }
  }
  
  return true;
}

RCPP_MODULE(BloomFilter){
  class_<BloomFilter>("BloomFilter")
  
  .constructor<uint64_t, uint8_t, uint64_t>()
  
  .field("size", &BloomFilter::size)
  .field("n_hashes", &BloomFilter::n_hashes)
  .field("seed", &BloomFilter::seed)
  
  .method("insert", &BloomFilter::insert)
  .method("check", &BloomFilter::check)
  ;
}