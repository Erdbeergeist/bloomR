#include <Rcpp.h>
#include "BloomFilter.h"

// [[Rcpp::plugins("cpp11")]]

using namespace Rcpp;


BloomFilter::BloomFilter(uint64_t size, uint8_t n_hashes, uint64_t seed = 1337){
  BloomFilter::size = size;
  BloomFilter::n_hashes = n_hashes;
  BloomFilter::seed = seed;
  
  BloomFilter::bits = std::vector<bool> (size);
}

BloomFilter::BloomFilter(uint64_t num_elements, double epsilon, uint64_t seed = 1337){
  BloomFilter::seed = seed;
  BloomFilter::size = ceil(-(double)num_elements * log2(epsilon) / log(2));
  BloomFilter::n_hashes = ceil(-log2(epsilon));
  BloomFilter::bits = std::vector<bool> (BloomFilter::size);
  
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

double BloomFilter::check_fill_rate(){
  double ret = 0;
  for (int i = 0; i < BloomFilter::bits.size(); i++){
    ret += BloomFilter::bits[i];
  }
  return ret/BloomFilter::bits.size();
}


/*
 * Validators for Constructors
 */

/*
 *  Validate size, n_hases, seed
 *           uint64_t, uint8_t, uint64_t
 */
bool validate_sns(SEXP* args, int nargs)
{ return TYPEOF(args[0]) == INTSXP && 
         TYPEOF(args[1]) == INTSXP &&
         TYPEOF(args[2]) == INTSXP; }


/*
 *  Validate num_elements, epsilon, seed
 *           uint64_t, double,  uint64_t
 */
bool validate_nes(SEXP* args, int nargs)
{ 
  return TYPEOF(args[0]) == INTSXP && 
         TYPEOF(args[1]) == REALSXP &&
         TYPEOF(args[2]) == INTSXP; }

RCPP_MODULE(BloomFilter){
  class_<BloomFilter>("BloomFilter")
  
  .constructor<uint64_t, uint8_t, uint64_t>(
    "size, n_hashes, seed constructor",
    validate_sns)
  
  .constructor<uint64_t, double, uint64_t>(
    "num_elements, epsilon, seed constructor",
    validate_nes)
  
  .field("size", &BloomFilter::size)
  .field("n_hashes", &BloomFilter::n_hashes)
  .field("seed", &BloomFilter::seed)
  
  .method("insert", &BloomFilter::insert)
  .method("check", &BloomFilter::check)
  .method("check_fill_rate", &BloomFilter::check_fill_rate)
  ;
}