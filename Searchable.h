//
// Created by arye on 19/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_
#define CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_

#include <vector>
#include "State.h"


template <class T>
class Searchable {
 public:
  virtual State<T> *getInitialState() const = 0;

  virtual State<T> *getGoalState() const = 0;

  virtual std::vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
};


#endif //CLIENT_SERVER_COMMUNICATION__SEARCHABLE_H_
