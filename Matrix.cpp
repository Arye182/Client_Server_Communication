//
// Created by arye on 20/01/2020.
//

#include "Matrix.h"


/**
 *
 * @param data_to_lex
 */
Matrix::Matrix(vector<vector<string>> data_to_lex) {
  this->matrix_string_data = data_to_lex;
  this->buildMatrix();
}



/**
 *
 */
void Matrix::buildMatrix() {
  vector<vector<State<Point>*>> matrix_data_on_build;
  // iterate all the string vectors...
  // create each time a new state and save it in the vec vec of states


  // update all the fields of the shitty one.
  // the state will include everything.
  // the point is just a field in the state.
  // the state is actually the vertice...


}
