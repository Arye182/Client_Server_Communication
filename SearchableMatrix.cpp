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

SearchableMatrix::SearchableMatrix(const SearchableMatrix* copy){
  this->matrix = copy->matrix;
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
  Point current_point = other_state->getState();
  int i = current_point.first;
  int j = current_point.second;
  double current_cost = other_state->getCost();
  int upper_bound = -1;
  int bottom_bound = this->matrix->getRowsNum();
  int left_bound = -1;
  int right_bound = this->matrix->getColumnsNum();

  // down --- (i+1 , j)
  if (i + 1 < bottom_bound) {
  Point possible_point_down = Point(i + 1, j);
  Point possible_state_down = this->matrix->getMatrixStateData()
  [i + 1][j]->getState();
  double
      pos_cost_down = this->matrix->getMatrixStateData()[i + 1][j]->getCost();
  // check boundaries and infinity
  if (pos_cost_down != -1 && possible_state_down.first < bottom_bound) {
    State<Point> *pos_state = new State<Point>(possible_point_down);
    pos_state->setCost(pos_cost_down);
    possible_states.push_back(pos_state);
  }
}

  // right --- (i , j+1)
  if (j+1 < right_bound) {
    Point possible_point_right = Point(i, j + 1);
    Point possible_state_right =
        this->matrix->getMatrixStateData()[i][j + 1]->getState();
    double pos_cost_right =
        this->matrix->getMatrixStateData()[i][j + 1]->getCost();
    // check boundaries and infinity
    if (pos_cost_right != -1 && possible_state_right.second < right_bound) {
      State<Point> *pos_state = new State<Point>(possible_point_right);
      pos_state->setCost(pos_cost_right);
      possible_states.push_back(pos_state);
    }
  }

  // up --- (i-1 , j)
  if (i != 0) {
    Point possible_point_up = Point(i - 1, j);
    Point possible_state_up = this->matrix->getMatrixStateData()
    [i - 1][j]->getState();
    double
        pos_cost_up = this->matrix->getMatrixStateData()[i - 1][j]->getCost();
    // check boundaries and infinity
    if (pos_cost_up != -1 && possible_state_up.first > upper_bound) {
      State<Point> *pos_state = new State<Point>(possible_point_up);
     pos_state->setCost(pos_cost_up);
      possible_states.push_back(pos_state);
    }
  }

  // left --- (i , j-1)
  if (j != 0) {
    Point possible_point_left = Point(i, j - 1);
    Point possible_state_left =
        this->matrix->getMatrixStateData()[i][j - 1]->getState();
    double
        pos_cost_left = this->matrix->getMatrixStateData()[i][j - 1]->getCost();
    // check boundaries and infinity
    if (pos_cost_left != -1 && possible_state_left.second > left_bound) {
      State<Point> *pos_state = new State<Point>(possible_point_left);
      pos_state->setCost(pos_cost_left);
      possible_states.push_back(pos_state);
    }
  }

  return possible_states;
}
Matrix *SearchableMatrix::getMatrix() {
  return this->matrix;
}
vector<State<Point> *> SearchableMatrix::backTracePath(State<Point> *goal_to_backtrace) {
  State<Point>* iterator = goal_to_backtrace;
  while(iterator->getCameFrom() != nullptr){
    this->solution.push_back(iterator);
    iterator = iterator->getCameFrom();
  }
  this->solution.push_back(iterator);
  return this->solution;
}




