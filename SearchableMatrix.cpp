//
// Created by arye on 20/01/2020.
//

#include "SearchableMatrix.h"

State<Point> *SearchableMatrix::getInitialState() {
  return nullptr;
}
State<Point> *SearchableMatrix::getGoalState() {
  return nullptr;
}
bool SearchableMatrix::isGoalState(State<Point> *) {
  return false;
}
vector<State<Point> *> SearchableMatrix::getAllPossibleStates(State<Point> *) {
  return vector<State<Point> *>();
}

