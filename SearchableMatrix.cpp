//
// Created by arye on 20/01/2020.
//

#include "SearchableMatrix.h"

State<Point> *SearchableMatrix::getInitialState() {
  return this->matrix->getBeginState();
}


State<Point> *SearchableMatrix::getGoalState() {
  return this->matrix->getGoalState();
}


bool SearchableMatrix::isGoalState(State<Point>* other_state) {
  return other_state == this->matrix->getGoalState();
}


vector<State<Point> *> SearchableMatrix::getAllPossibleStates(State<Point>* other_state) {
  return vector<State<Point> *>();
}


SearchableMatrix::SearchableMatrix(Matrix *m) {
  this->matrix = m;
}

