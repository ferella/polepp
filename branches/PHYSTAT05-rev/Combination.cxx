#include <iostream>
#include "Combination.h"
namespace Combination {
  bool add(std::vector<int> & cnt, int elem, int vmax) {
    if (elem<0) return false;
    if (elem>int(cnt.size())-1) return false;
    cnt[elem]++;
    if (cnt[elem]>vmax) {
      cnt[elem] = 0;
      --elem;
      return add(cnt,elem,vmax);
    }
    return true;
  }

  bool add(std::vector<int> & cnt, int elem, const std::vector<int> & vmax) {
    if (elem<0) return false;
    if (elem>int(cnt.size())-1) return false;
    cnt[elem]++;
    if (cnt[elem]>vmax[elem]) {
      cnt[elem] = 0;
      --elem;
      return add(cnt,elem,vmax);
    }
    return true;
  }

  bool next_vector(std::vector<int> & vec, int vmax) {
    int elem = int(vec.size())-1;
    return add(vec,elem,vmax);
  }

  bool next_vector(std::vector<int> & vec, const std::vector<int> & vmax) {
    int elem = int(vec.size())-1;
    return add(vec,elem,vmax);
  }
};