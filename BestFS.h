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
class BestFS : public Searcher<T> {

 private:
  int nodes_evaluated_counter = 0;
  //priority_queue<State<T>*> open;
  vector<State<T>*> closed;
  vector<State<T>*> solution;



 public:

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
  vector<State<T>*> search(Searchable<T> *searchable_obj) {
    priority_queue <State<Point>*, vector<State<Point>*>, myComparator> open;
    vector<State<Point>*> open_vector;
    State<Point>* n;
    vector<State<Point>*> successors;
    solution.clear();
    // OPEN = [initial state] // a priority queue of states to be evaluated
    open.push(searchable_obj->getInitialState());
    open_vector.push_back(searchable_obj->getInitialState());
    // CLOSED = [] // a set of states already evaluated
    closed.clear();
    // while OPEN is not empty
    while (!open.empty()) {
      // 1. n  dequeue(OPEN) // Remove the best node from OPEN
      n = open.top();
      open.pop();
      auto best_open_vector = find(open_vector.begin(), open_vector.end(), n);
      open_vector.erase(best_open_vector);
      // 2. add(n,CLOSED) // so we won’t check n again
      closed.push_back(n);
      // 3. If n is the goal state,
      if (searchable_obj->getGoalState()->getState() == n->getState()) {
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
        bool s_is_in_open = false;
        bool s_is_in_closed = false;
        for (State<Point>* state_in_open : open_vector) {
          if (state_in_open->getState() == s->getState()) {
            s_is_in_open = true;
          }
        }
        for (State<Point>* state_in_close : this->closed) {
          if (state_in_close->getState() == s->getState()) {
            s_is_in_closed = true;
          }
        }
        if (s_is_in_closed) {
          continue;
        }
        if (!(s_is_in_open)) {
        // a. If s is not in CLOSED and s is not in OPEN:
          // i. update that we came to s from n
          s->setCameFrom(n);
          s->setCost(n->getCost() + s->getCost());
          // ii. add(s,OPEN)
          open.push(s);
          open_vector.push_back(s);
        } else {

          // If there is a better path - update cost
          SearchableMatrix
              *m = dynamic_cast<SearchableMatrix *>(searchable_obj);
          double s_original_cost = m->getMatrix()->getMatrixStateData()
          [s->getState().first][s->getState().second]->getCost();
          double cost = n->getCost() + s_original_cost;
          if (cost < s->getCost()) {
            s->setCost(cost);
            // If it's a new path
            if (s->getCameFrom() != n) {
              s->setCameFrom(n);
              // It's the same path as before - remove the node and insert back to update priority
            } else {
              auto succ_open_vector =
                  find(open_vector.begin(), open_vector.end(),
                       s);
              open_vector.erase(succ_open_vector);
              open.push(s);
            }
          }
        }
      }
    }
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
