//
// Created by arye on 19/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__STATE_H_
#define CLIENT_SERVER_COMMUNICATION__STATE_H_

template<class T>
class State {

 private:
  T state;
  double cost;
  State<T>* came_from;
  bool is_visited;
  double high_score;


 public:
  /**
   *
   * @param state
   */
  State(T state) {
    this->state = state;
  }

  /**
   *
   * @param s
   * @return
   */
  bool operator == (const State<T> &s) {
    return (s.came_from == came_from
            && s.cost == cost
            && s.state == state);
  }

//  State<T> &operator=(State<T> s) {
//    this->node = s.getState();
//    this->cost = s.getCost();
//    this->come_from = s.getComeFrom();
//    this->is_visited = false;
//    return *this;
//  }

  // getters
  /**
   *
   * @return
   */
  T getState() {
    return this->state;
  }

  /**
   *
   * @return
   */
  double getCost() {
   return this->cost;
  }

  /**
   *
   * @return
   */
  State<T>* getCameFrom() {
    return this->came_from;
  }

  /**
   *
   * @return
   */
  bool getIsVisited() {
    return  this->is_visited;
  }

  /**
   *
   * @return
   */
  double getHighScore() {
   return this->high_score;
  }

  // setters
  /**
   *
   * @param new_state
   */
  void setState (T new_state) {
    this->state = new_state;
  }

  /**
   *
   * @param new_cost
   */
  void setCost (double new_cost) {
    this->cost = new_cost;
  }

  /**
   *
   * @param new_came_from
   */
  void setCameFrom(State<T>* new_came_from){
    this->came_from = new_came_from;
  }

  /**
   *
   * @param new_is_visited
   */
  void setIsVisited(bool new_is_visited) {
    this->is_visited = new_is_visited;
  }

  /**
   *
   * @param new_high_score
   */
  void setHighScore (double new_high_score) {
    this->high_score = new_high_score;
  }
};


#endif //CLIENT_SERVER_COMMUNICATION__STATE_H_
