//
// Created by miri on 23.1.2020.
//

#include "SearcherObjectAdapter.h"
#include <iostream>

using namespace std;

/**
 *
 * @param problem
 * @return
 */
string SearcherObjectAdapter::solve(SearchableMatrix *problem) {
  return solutionConvertToString(this->m_searcher->search(problem));
}

/**
 *
 * @return
 */
SearcherObjectAdapter *SearcherObjectAdapter::deepCopy() {
  return new SearcherObjectAdapter(this->m_searcher->deepCopy());
}

/**
 *
 * @param solution_vector
 * @return
 */
string SearcherObjectAdapter::solutionConvertToString(vector<State<Point> *> solution_vector) {
  // format: Down (12) ,Down (13) ,Right (18)
  string string_solution = "";
  //auto iterator_from_initial_state = solution_vector.end();
  for (vector<State<Point> *>::reverse_iterator
           iterator_from_initial_state = solution_vector.rbegin();
       iterator_from_initial_state != solution_vector.rend();
       ++iterator_from_initial_state) {
    if ((*iterator_from_initial_state)->getCameFrom() == nullptr) {
      continue;
    }
    // take every state from initial state and add it to the string!
    int cost = (*iterator_from_initial_state)->getCost();
    string direction;
    int prev_i =
        (*iterator_from_initial_state)->getCameFrom()->getState().first;
    int prev_j =
        (*iterator_from_initial_state)->getCameFrom()->getState().second;
    int curr_i = (*iterator_from_initial_state)->getState().first;
    int curr_j = (*iterator_from_initial_state)->getState().second;
    if (prev_i < curr_i) {
      direction = "Down";
    } else if (prev_i > curr_i) {
      direction = "Up";
    } else if (prev_j > curr_j) {
      direction = "Left";
    } else {
      direction = "Right";
    }
    string_solution =
        string_solution + direction + "(" + to_string(cost) + ")"", ";
  }
  // delete last comma
  string_solution.erase(string_solution.end() - 2);
  return string_solution;
}
