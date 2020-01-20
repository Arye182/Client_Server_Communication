//
// Created by arye on 20/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__BESTFS_H_
#define CLIENT_SERVER_COMMUNICATION__BESTFS_H_



#include "Searcher.h"
#include "Searchable.h"

#include "SearchableMatrix.h"
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

template<class T>
class BestFirstSearch : public Searcher<T> {

 private:
 int nodes_evaluated_counter = 0;
 //priority_queue<State<T>*> open;
 vector<State<T>*> closed;
 vector<State<T>*> solution;



 public:
  BestFirstSearch<T>(){

 }

  class myComparator {
   public:
    int operator() (State<Point>* p1,  State<Point>* p2)
    {
      return p1->getCost() > p2->getCost();
    }
  };

  /**
   *
   * @param searchable_obj
   * @return
   */
  vector<State<T>*> search(Searchable<T> *searchable_obj) override {
    priority_queue <State<Point>*, vector<State<Point>*>, myComparator> open;
    vector<State<Point>*> open_vector;
    State<Point>* n;
    vector<State<Point>*> successors;
    solution.clear();
    // OPEN = [initial state] // a priority queue of states to be evaluated
    open.push(searchable_obj->getGoalState());
    open_vector.push_back(searchable_obj->getGoalState());
    // CLOSED = [] // a set of states already evaluated
    closed.clear();
    // while OPEN is not empty
    while (!open.empty()) {
      // 1. n  dequeue(OPEN) // Remove the best node from OPEN
      n = open.pop();
      auto best_open_vector = find(open_vector.begin(), open_vector.end(), n);
      open_vector.erase(best_open_vector);
      // 2. add(n,CLOSED) // so we won’t check n again
      closed.push_back(n);
      // 3. If n is the goal state,
      if (searchable_obj->isGoalState(n->getState())) {
        // backtrace path to n (through recorded parents) and return path.
        State<Point>* iterator = n;
        while(iterator != searchable_obj->getInitialState()){
          this->solution.push_back(iterator);
          iterator = iterator->getCameFrom();
        }
        return this->solution;
      }
      // 4. Create n's successors.
      successors = searchable_obj->getAllPossibleStates(n);
      // 5. For each successor s do:
      for (State<Point>* s : successors) {
        bool s_is_in_open = find(open_vector.begin(), open_vector.end(), s)
            != open_vector.end();
        bool s_is_in_closed = find(this->closed.begin(), this->closed.end(), s)
            != this->closed.end();
        // a. If s is not in CLOSED and s is not in OPEN:
        if( !(s_is_in_closed) && !(s_is_in_open)) {
          // i. update that we came to s from n
          s->setCameFrom(n);
          s->setCost(n->getCost() + s->getCost());
          // ii. add(s,OPEN)
          open.push(s);
          open_vector.push_back(s);
        } else {
          // b. Otherwise, if this new path is better than previous one
          if (n->getCost() > n->getCost()+s->getCost()) {
            // i. If it is not in OPEN add it to OPEN.
            if(!(s_is_in_open)) {
              open.push(s);
              open_vector.push_back(s);
            } else {
              // ii. Otherwise, adjust its priority in OPEN
              s->setCameFrom(n);
              s->setCost(n->getCost() + s->getCost());
            }
          }
        }
      }
    }
    // done
    return this->solution;
 }

 /**
  *
  * @return
  */
  int getNumberOfNodesEvaluated() override {
   return this->nodes_evaluated_counter;
 }
};

#endif //CLIENT_SERVER_COMMUNICATION__BESTFS_H_
