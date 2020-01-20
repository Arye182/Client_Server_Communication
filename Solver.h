//
// Created by miri on 20.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SOLVER_H_
#define CLIENT_SERVER_COMMUNICATION__SOLVER_H_

template <typename Problem, typename Solution>
class Solver {
 public:
  virtual Solution solve(Problem problem);
};
#endif //CLIENT_SERVER_COMMUNICATION__SOLVER_H_
