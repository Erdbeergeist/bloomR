#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <array>
#include "MurmurHash3.h"

class BloomFilter{
public:
  BloomFilter(uint64_t size, uint8_t n_hashes, uint64_t seed);
 
  void insert(std::string data);
  bool check(std::string data); 
  
  uint64_t size;
  uint64_t n_hashes;
  uint64_t seed;
  
private:
  std::array<uint64_t, 2> hashValue(void *data, std::size_t len);
  uint64_t ith_hash(uint64_t i, uint64_t hash_0, uint64_t hash_1);
  
  std::vector<bool> bits;
};

#endif