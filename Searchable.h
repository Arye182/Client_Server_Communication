//
// Created by arye on 19/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_
#define CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_

#include <vector>
#include "State.h"

using namespace std;

template <class T>
class Searchable {
 public:
  virtual State<T> *getInitialState() = 0;
  virtual State<T> *getGoalState() = 0;
  virtual bool isGoalState(State<T>*  other_state) = 0;
  virtual vector<State<T>*> getAllPossibleStates(State<T>*  other_state) = 0;

};


#endif //CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_
