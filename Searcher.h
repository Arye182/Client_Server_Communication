//
// Created by arye on 20/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SEARCHER_H_
#define CLIENT_SERVER_COMMUNICATION__SEARCHER_H_

#include "Searchable.h"
#include "State.h"


template<class T>
class Searcher {

 public:
  virtual std::vector<State<T>*> search(Searchable<T> *searchable_obj) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;

};

#endif //CLIENT_SERVER_COMMUNICATION__SEARCHER_H_
