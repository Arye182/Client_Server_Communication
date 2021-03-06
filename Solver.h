//
// Created by miri on 20.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SOLVER_H_
#define CLIENT_SERVER_COMMUNICATION__SOLVER_H_

template<typename Problem, typename Solution>
class Solver {
 public:
  virtual Solver *deepCopy() = 0;
  virtual Solution solve(Problem problem) = 0;
  virtual ~Solver() = default;
};
#endif //CLIENT_SERVER_COMMUNICATION__SOLVER_H_
