//
// Created by arye on 21/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__BFS_H_
#define CLIENT_SERVER_COMMUNICATION__BFS_H_

#include "Searcher.h"
#include "Searchable.h"
#include "SearchableMatrix.h"
#include <string>
#include <queue>

using namespace std;

template<class T>
class BFS : public Searcher<T> {

 private:
  int nodes_evaluated_counter = 0;

 public:
  /**
   *
   * @param searchable_obj
   * @return
   */
  vector<State<T>*> search(Searchable<T> *searchable_obj) {
    SearchableMatrix *m = dynamic_cast<SearchableMatrix *>(searchable_obj);
    // our stack for dfs algorithm
    queue<State<T> *> bfs_queue;
    // list of possible neighbours
    vector<State<T>*> successors;
    // list of visited
    vector<State<T>*> visited;
    // start state and goal state
    State<T> *start_state = searchable_obj->getInitialState();
    State<T> *goal_state = searchable_obj->getGoalState();
    //push the first state to the stack and mark it visited
    start_state->setCameFrom(nullptr);
    start_state->setIsVisited(true);
    bfs_queue.push(start_state);
    visited.push_back(start_state);
    this->nodes_evaluated_counter++;
    // loop
    while (!bfs_queue.empty()) {
      // pop the next vertex to work on
      State<T>* element = bfs_queue.front();
      bfs_queue.pop();

      for (State<T>* v1 : visited) {
        if (v1->getState() == element->getState()) {
          element->setIsVisited(true);
        }
        if (v1->getState() == goal_state->getState()) {
          return m->backTracePath(v1);
        }
      }


      if (!element->getIsVisited()) {
        element->setIsVisited(true);
        visited.push_back(element);
      }
      this->nodes_evaluated_counter++;
      successors = searchable_obj->getAllPossibleStates(element);
      for (State<T>* s : successors){
        for (State<T>* v : visited) {
          if (v->getState() == s->getState()) {
            s->setIsVisited(true);
          }
        }
        if (!s->getIsVisited()) {
          s->setCameFrom(element);
          s->setCost(element->getCost() + s->getCost());
          s->setIsVisited(true);
          bfs_queue.push(s);
          visited.push_back(s);
        }
        // 3. If n is the goal state,
        if (goal_state->getState() == s->getState()) {
          // backtrace path to n (through recorded parents) and return path.
          return m->backTracePath(s);
        }
      }
    }
    for (State<T>* v : visited) {
      if (v->getState() == goal_state->getState()) {
        return m->backTracePath(v);
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

#endif //CLIENT_SERVER_COMMUNICATION__BFS_H_
