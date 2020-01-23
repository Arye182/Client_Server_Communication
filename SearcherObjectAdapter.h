//
// Created by miri on 23.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SEARCHEROBJECTADAPTER_H_
#define CLIENT_SERVER_COMMUNICATION__SEARCHEROBJECTADAPTER_H_

#include "Solver.h"
#include "SearchableMatrix.h"
#include "Searcher.h"
class SearcherObjectAdapter: Solver<SearchableMatrix*,string> {
  Searcher<Point>* m_searcher;
 public:
  virtual string solve(SearchableMatrix* problem) override ;
  string solutionConvertToString (vector<State<Point>*> solution_vector);
};
#endif //CLIENT_SERVER_COMMUNICATION__SEARCHEROBJECTADAPTER_H_
