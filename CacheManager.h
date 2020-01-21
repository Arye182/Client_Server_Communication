//
// Created by miri on 21.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__CACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__CACHEMANAGER_H_
template <typename Problem, typename Solution>
class CacheManager{
 public:
  virtual void insertSolution(Problem problem, Solution solution) = 0;
  virtual Solution findSolution(Problem problem) = 0;
};
#endif //CLIENT_SERVER_COMMUNICATION__CACHEMANAGER_H_
