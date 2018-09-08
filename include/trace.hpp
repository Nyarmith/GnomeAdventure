#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <utility>
#include <queue>
#define ll long long

const char* basename(const char* fullName){
  const char* last = fullName;
  const char* curr = fullName;
  while (*curr != '\0'){
    ++curr;
    if (*curr == '/'){
      last = curr;
    }
  }
  return (last+1);
}

#define LOG_DEBUG(msg) \
  do { \
    std::cerr << basename(__FILE__) << " : " << __LINE__ << " : " << msg << "\n"; \
  } while(0)
