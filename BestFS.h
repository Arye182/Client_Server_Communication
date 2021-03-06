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
  vector<State<T> *> closed;
  vector<State<T> *> solution;

 public:
  /**
   * comparator for priority queue - by cost.
   */
  class myComparator {
   public:
    int operator()(State<T> *p1, State<T> *p2) {
      return p1->getCost() > p2->getCost();
    }
  };

  /**
 * deep copy implementation for Bestfs.
 * @return
 */
  virtual BestFS<T> *deepCopy() override {
    BestFS<T> *copy = new BestFS<T>();
    return copy;
  }

  /**
   * the algorithm.
   * @param searchable_obj
   * @return the solution (in vector of states)
   */
  vector<State<T> *> search(Searchable<T> *searchable_obj) {
    SearchableMatrix *m = dynamic_cast<SearchableMatrix *>(searchable_obj);
    priority_queue<State<T> *, vector<State<T> *>, myComparator> open;
    vector<State<T> *> open_vector;
    State<T> *n;
    vector<State<T> *> successors;
    solution.clear();
    // a priority queue of states to be evaluated
    open.push(searchable_obj->getInitialState());
    open_vector.push_back(searchable_obj->getInitialState());
    // a set of states already evaluated
    closed.clear();
    // while OPEN is not empty
    while (!open.empty()) {
      // Remove the best node from OPEN
      n = open.top();
      open.pop();
      this->nodes_evaluated_counter++;
      auto best_open_vector = find(open_vector.begin(), open_vector.end(), n);
      open_vector.erase(best_open_vector);
      // add(n,CLOSED) // so we won’t check n again
      closed.push_back(n);
      // If n is the goal state,
      if (searchable_obj->getGoalState()->getState() == n->getState()) {
        // backtrace path to n (through recorded parents) and return path.
        State<T> *iterator = n;
        return m->backTracePath(iterator);
      }
      // Create n's successors.
      successors = searchable_obj->getAllPossibleStates(n);
      // For each successor s do:
      for (State<T> *s : successors) {
        bool s_is_in_open = false;
        bool s_is_in_closed = false;
        for (State<T> *state_in_open : open_vector) {
          if (state_in_open->getState() == s->getState()) {
            s_is_in_open = true;
          }
        }
        for (State<T> *state_in_close : this->closed) {
          if (state_in_close->getState() == s->getState()) {
            s_is_in_closed = true;
          }
        }
        if (s_is_in_closed) {
          continue;
        }
        if (!(s_is_in_open)) {
          // If s is not in CLOSED and s is not in OPEN:
          // update that we came to s from n
          s->setCameFrom(n);
          s->setCost(n->getCost() + s->getCost());
          // add(s,OPEN)
          open.push(s);
          open_vector.push_back(s);
        } else {
          // If there is a better path - update cost
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
   * getter
   * @return nodes evaluated
   */
  int getNumberOfNodesEvaluated() override {
    return this->nodes_evaluated_counter;
  }
};

#endif //CLIENT_SERVER_COMMUNICATION__BESTFS_H_
