#include <iostream>
#include "ndrc/lagrangean.h"
#include <stdlib.h>
#include <time.h>

class Solution {
 public:
  int64_t cost_;
  int64_t id_;
  bool operator<(const Solution& sol) const {
    if (this->cost_ < sol.cost_)
      return true;
    else if (this->cost_ > sol.cost_)
      return false;
    else if (this->id_ < sol.id_)
      return true;
    else
      return false;
  }

  friend std::ostream& operator<<(std::ostream& strm, const Solution& sol) {
    return strm << sol.id_ << " = " << sol.cost_;
  }
};

template <class Solution>
class Comparator {
 public:
  using solution_type = Solution;
  bool compare(const solution_type& new_sol, const solution_type& old_sol) {
    return new_sol < old_sol;
  }
};

using solution_type = Solution;
using compare_type = Comparator<solution_type>;
using lagrangean_type = ndrc::Lagrangean<solution_type, compare_type>;

solution_type solve_subproblem(const int64_t& it) {
  std::cout << "My subproblem " << it << std::endl;
  solution_type sol;
  sol.cost_ = std::rand() % 50;
  sol.id_ = std::rand() % 10000;
  return sol;
}

int main(int argc, char* argv[]) {
  std::srand(time(NULL));
  lagrangean_type lag;
  lag.add_subproblem_callback(solve_subproblem);
  lag.run();
}