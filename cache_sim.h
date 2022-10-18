#ifndef ONLINE_CACHE_SIMULATOR_CACHE_SIM_H_
#define ONLINE_CACHE_SIMULATOR_CACHE_SIM_H_

#include <iostream>
#include <vector>

#include "absl/time/clock.h"

#ifdef DEBUG_PERF
inline uint8_t _depth = 0;
#define STARTTIME(X) auto X = absl::Now(); _depth++;
#define STOPTIME(X)  \
    _depth--; \
    for (uint8_t _i = 0; _i < _depth; _i++) {std::cout << "\t";} \
    std::cout << #X ": " << absl::Now() - X << std::endl;
#else //DEBUG_PERF
#define STARTTIME(X) 
#define STOPTIME(X)  
#endif //DEBUG_PERF

class CacheSim {
 protected:
  uint64_t access_number = 1;  // simulated timestamp
  size_t memory_usage = 0; // memory usage of the cache sim
 public:
  using SuccessVector = std::vector<uint64_t>;

  CacheSim() = default;
  virtual ~CacheSim() = default;
  /*
   * Perform a memory access upon a given id
   * addr:    the id to access 
   * returns  nothing
   */
  virtual void memory_access(uint64_t addr) = 0;

  virtual SuccessVector get_success_function() = 0;

  void print_success_function() {
    // TODO: This is too verbose for real data.
    std::vector<uint64_t> func = get_success_function();
    for (uint64_t page = 1; page < func.size(); page++)
      std::cout << page << ": " << func[page] << std::endl;
  }
  size_t get_memory_usage() { return memory_usage; }
};

#endif  // ONLINE_CACHE_SIMULATOR_INCLUDE_CACHE_SIM_H_
