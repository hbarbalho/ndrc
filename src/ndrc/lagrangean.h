#include <iostream>
#ifndef LAGRANGEAN_H_
#define LAGRANGEAN_H_

namespace ndrc {

template <class Solution, class Comparator>
class Lagrangean {
 public:
  using solution_type = Solution;
  using comparator_type = Comparator;

 private:
  solution_type (*solve_subproblem_func_)(const int64_t&);
  comparator_type comparator_;

  solution_type solve_subproblem(const int64_t& it) {
    std::cout << "Call solve subproblem" << std::endl;
    return solve_subproblem_func_(it);
  }

 public:
  Lagrangean(){

  }

  void add_subproblem_callback(solution_type (*solve_subproblem_func)(const int64_t&)) {
    solve_subproblem_func_ = solve_subproblem_func;
  }

  void run() {
    solution_type best_sol;
    for (int64_t it = 0; it < 5; ++it) {
      std::cout << "Iteration " << it << std::endl;
      solution_type sol = solve_subproblem(it);
      std::cout << "Solution " << sol << std::endl;
      if (it == 0 || comparator_.compare(sol,best_sol))
        best_sol = sol;
      std::cout << "--------------------------" << std::endl;
    }
    std::cout << "Best sol:" << best_sol << std::endl;
  }
};
}  // namespace ndrc

#endif