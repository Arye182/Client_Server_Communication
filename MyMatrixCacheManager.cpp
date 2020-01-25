//
// Created by arye on 23/01/2020.
//

#include "MyMatrixCacheManager.h"

MyMatrixCacheManager::MyMatrixCacheManager(const MyMatrixCacheManager* copy_m_cm) {
  this->hasher = copy_m_cm->hasher;
}
/**
 * this method saves a solution ina file.
 * @param problem
 * @param solution
 */
void MyMatrixCacheManager::insertSolution(string problem, string solution) {
  auto hashed = this->hasher(problem);
  string key = to_string(hashed)+".txt";
  fstream problem_to_insert_file;
  cout << key << endl;
  lock_cache.try_lock();
  problem_to_insert_file.open(key, ios:: out );
  if (!problem_to_insert_file) {
    cerr << "could not open file of solution" << endl;
  }
  problem_to_insert_file << solution <<endl;
  problem_to_insert_file.close();
  lock_cache.unlock();
}
/**
 * this method search if there is a solution exists, if so it returns it as a
 * string. if not it returns an empty string.
 * @param problem
 * @return
 */
string MyMatrixCacheManager::findSolution(string problem) {
  lock_cache.try_lock();
  auto hashed = this->hasher(problem);
  string key = to_string(hashed)+".txt";
  fstream problem_to_search_file;
  problem_to_search_file.open(key);
  if (problem_to_search_file) {
    string solution_from_file;
    //string problem_from_file;
    //getline(problem_to_search_file, problem_from_file);
    getline(problem_to_search_file, solution_from_file);
    problem_to_search_file.close();
    lock_cache.unlock();
    return solution_from_file;
  } else {
    if (problem_to_search_file.is_open()) {
      problem_to_search_file.close();
    }
    lock_cache.unlock();
    return "";

  }
}

