//
// Created by arye on 20/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__MATRIX_H_
#define CLIENT_SERVER_COMMUNICATION__MATRIX_H_

#include <utility>
#include <vector>
#include <string>
#include "State.h"

using namespace std;
using Point = pair<int, int>;


class Matrix {
  
 private:
  int rows; // number of rows of the matrix
  int columns; // number of columns of the matrix
  vector<vector<State<Point>*>> matrix_state_data; // with points
  vector<vector<string>> matrix_string_data;
  State<Point>* begin_state;
  State<Point>* goal_state;
  
 public:
  Matrix(vector<vector<string>> matrix_data_to_lex_from_server);
  void buildMatrix();
  
};

#endif //CLIENT_SERVER_COMMUNICATION__MATRIX_H_
