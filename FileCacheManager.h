//
// Created by miri on 21.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_

#include "CacheManager.h"
#include <string>

using namespace std;

/**
 * this is for part 2 of the ex.4
 *
 * @tparam Problem
 * @tparam Solution
 */
template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
 public:
  FileCacheManager() = default;
  void insertSolution(Problem problem, Solution solution) {}
  Solution findSolution(Problem problem) override {
    return "not found";
  }
};

#endif //CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
