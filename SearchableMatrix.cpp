//
// Created by arye on 20/01/2020.
//

#include "SearchableMatrix.h"

/**
 *
 * @param m
 */
SearchableMatrix::SearchableMatrix(Matrix *m) {
  this->matrix = m;
}

/**
 *
 * @return
 */
State<Point> *SearchableMatrix::getInitialState() {
  return this->matrix->getBeginState();
}

/**
 *
 * @return
 */
State<Point> *SearchableMatrix::getGoalState() {
  return this->matrix->getGoalState();
}

/**
 *
 * @param other_state
 * @return
 */
bool SearchableMatrix::isGoalState(State<Point>* other_state) {
  return other_state == this->matrix->getGoalState();
}

/**
 *
 * @param other_state
 * @return
 */
vector<State<Point> *> SearchableMatrix::getAllPossibleStates(State<Point>* other_state) {
  vector<State<Point> *> possible_states;



  return possible_states;
}




