//
// Created by arye on 23/01/2020.
//

#include "MyMatrixCacheManager.h"

/**
 * this method saves a solution ina file.
 * @param problem
 * @param solution
 */
void MyMatrixCacheManager::insertSolution(string problem, string solution) {
  auto hashed = this->hasher(problem);
  string key = to_string(hashed);
  fstream problem_to_insert_file;
  problem_to_insert_file<< problem << endl;
  problem_to_insert_file << solution <<endl;
}
/**
 * this method search if there is a solution exists, if so it returns it as a
 * string. if not it returns an empty string.
 * @param problem
 * @return
 */
string MyMatrixCacheManager::findSolution(string problem) {
  auto hashed = this->hasher(problem);
  string key = to_string(hashed);
  fstream problem_to_search_file;
  problem_to_search_file.open("key");
  if (problem_to_search_file) {
    string solution_from_file;
    string problem_from_file;
    getline(problem_to_search_file, problem_from_file);
    getline(problem_to_search_file, solution_from_file);
    problem_to_search_file.close();
    return solution_from_file;
  } else {
    return "";
  }
}
