//
// Created by arye on 20/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__SEARCHABLEMATRIX_H_
#define CLIENT_SERVER_COMMUNICATION__SEARCHABLEMATRIX_H_


#include "Matrix.h"
#include "Searchable.h"
#include <algorithm>
#include <string>
#include <list>

using namespace std;

class SearchableMatrix : public Searchable<Point> {

 private:
  Matrix *matrix;
  vector<State<Point>*> solution;

 public:
  SearchableMatrix(Matrix* m);
  SearchableMatrix(const SearchableMatrix* copy);
  State<Point> *getInitialState() override ;
  State<Point> *getGoalState() override ;
  bool isGoalState(State<Point>* other_state) override ;
  vector<State<Point>*> getAllPossibleStates(State<Point>*  other_state) override ;
  Matrix* getMatrix();
  vector<State<Point>*> backTracePath (State<Point>* goal_to_backtrace);
};

#endif //CLIENT_SERVER_COMMUNICATION__SEARCHABLEMATRIX_H_
