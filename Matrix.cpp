//
// Created by arye on 20/01/2020.
//

#include "Matrix.h"


/**
 *
 * @param data_to_lex
 */
Matrix::Matrix(vector<string> data_to_lex) {
  this->matrix_string_data = data_to_lex;
  this->buildMatrix();
  this->rows = data_to_lex.size()-3;
}

/**
 *
 */
void Matrix::buildMatrix() {
  vector<vector<State<Point>*>> matrix_data_on_build;
  // iterate all the string vectors...
  for (int i = 0; i < this->matrix_string_data.size(); i++ ) {
    string row = this->matrix_string_data[i];
    vector<State<Point>*> matrix_row;
    int k = 0, j = 0, size;
    string::size_type r;
    double value;
    //string name;
    size = row.size();
    r = row.find(',');

    // start state
    if (i == this->matrix_string_data.size()-3 ) {
      vector<int> v;
      while (r != string::npos) {
        int signal = stod(row.substr(k, r));
        v.push_back(signal);
        k = r + 1;
        r = row.find(',', k);
      }
      if (k < size) {
        int signal = stod(row.substr(k, r));
        v.push_back(signal);
      }
      State<Point>* start_state = new State<Point>(Point(v[0],v[1]));
      this->begin_state = start_state;
      continue;
    }

    // end state
    if (i == this->matrix_string_data.size()-2){
      vector<int> v;
      while (r != string::npos) {
        int signal = stod(row.substr(k, r));
        v.push_back(signal);
        k = r + 1;
        r = row.find(',', k);
      }
      if (k < size) {
        int signal = stod(row.substr(k, r));
        v.push_back(signal);
      }
      State<Point>* end_state = new State<Point>(Point(v[0],v[1]));
      this->goal_state = end_state;
      break;
    }

    // lex every string to matrix data
    while (r != string::npos) {
      value = stod(row.substr(k, r));
      State<Point>* matrix_element = new State<Point>(Point(i,j));
      matrix_element->setCost(value);
      matrix_row.push_back(matrix_element);
      k = r + 1;
      r = row.find(',', k);
      j++;
    }
    // update the columns
    this->columns = j+1;
    // last element in the row
    if (k < size) {
      value = stod(row.substr(k, size));
      State<Point>* matrix_element = new State<Point>(Point(i,j));
      matrix_element->setCost(value);
      matrix_row.push_back(matrix_element);
    }
    j=0;

    // update the matrix row in the matrix data structure
    matrix_data_on_build.push_back(matrix_row);
  }
  this->matrix_state_data = matrix_data_on_build;
}

/**
 *
 * @return
 */
int Matrix::getRowsNum() {
  return this->rows;
}

/**
 *
 * @return
 */
int Matrix::getColumnsNum() {
  return this->columns;
}

/**
 *
 * @return
 */
vector<vector<State<Point> *>> Matrix::getMatrixStateData() {
  return this->matrix_state_data;
}

/**
 *
 * @return
 */
State<Point> *Matrix::getBeginState() {
  return this->begin_state;
}

/**
 *
 * @return
 */
State<Point> *Matrix::getGoalState() {
  return this->goal_state;
}


