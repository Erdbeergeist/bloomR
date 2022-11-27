#include <Rcpp.h>
#include "MurmurHash3.h"
using namespace Rcpp;

// [[Rcpp::export]]
void murmurhash(std::string key, uint64_t seed){
  
  uint64_t hash_otpt[2]= {0};
  
  std::string *data = &key;
  
  MurmurHash3_x64_128(&key, key.length(), seed, hash_otpt);
  
  std::cout<<*hash_otpt<<std::endl;
  
}

