//
//  main.cpp
//  memento pattern
//
//  Created by AK on 25/12/2022.
//

#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Memento {
public:
  virtual ~Memento() {}
  virtual string getName() const = 0;
  virtual string getDate() const = 0;
  virtual string getState() const = 0;
};

class concreteMemento : public Memento {
private:
  string state_;
  string date_;
public:
  concreteMemento(string state) : state_(state) {
    state_ = state;
    time_t now = time(0);
    date_ = ctime(&now);
    date_.pop_back();
  }
  string getName() const override {
    return date_ + "/" + state_;
  }
  string getDate() const override {
    return date_;
  }
  string getState() const override {
    return state_;
  }
};

class Originator { // aka. InitialState
private:
  string state_;
  string generateRandomString(int len=10) {
    const char an[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    int str_len = sizeof(an)-1;
    string rand_str;
    for (int i=0; i<len; i++) {
      rand_str += an[rand() % str_len];
    }
    return rand_str;
  }
public:
  Originator(string state) : state_(state) {
    cout << "Originator: initial state : " << state_ << endl;
  }
  void processData() {
    cout << "Originator: processing data.." << endl;
    state_ = generateRandomString(5);
    cout << "Originator: new state : " << state_ << endl;
  }
  Memento* save() {
    return new concreteMemento(state_);
  }
  void restore(Memento* memento) {
    state_ = memento->getState();
    cout << "Originator: state changed to : " << state_ << endl;
  }
};

class CareTaker {
private:
  vector<Memento*> mementos_;
  Originator* originator_;
public:
  CareTaker(Originator* originator) : originator_(originator) {}
  ~CareTaker() { for (auto& m : mementos_) delete m; }
  void backup() {
    cout << "CareTaker: saving original state" << endl;
    mementos_.push_back(originator_->save()); // new concreteMemento(state_)
  }
  void undo() {
    if (!mementos_.size()) return;
    Memento* memento = mementos_.back();
    mementos_.pop_back();
    cout << "CareTaker: reverting to state : " << memento->getName() << endl;
    try {
      originator_->restore(memento);
    } catch (...) {
      this->undo();
    }
  }
  void listPastStates() const {
    cout << "CareTaker: list of mementos:" << endl;
    for (Memento* m : mementos_) {
      cout << m->getName() << endl;
    }
  }
};

void run() {
  unique_ptr<Originator> orig(new Originator("AppStart-Reaady"));
  unique_ptr<CareTaker> ct(new CareTaker(orig.get()));
  ct->backup(); // add to memento-list
  orig->processData(); // create new state:user-action
  ct->backup();
  orig->processData();
  ct->backup();
  orig->processData();
  ct->backup();
  orig->processData();
  ct->listPastStates();
  cout << "Undoing.." << endl;
  ct->undo();
  ct->listPastStates();
}


int main(int argc, const char * argv[]) {
  run();
  return 0;
}

// OUTPUT
// Originator: initial state : AppStart-Reaady
// CareTaker: saving original state
// Originator: processing data..
// Originator: new state : 5PN2q
// CareTaker: saving original state
// Originator: processing data..
// Originator: new state : mWqBl
// CareTaker: saving original state
// Originator: processing data..
// Originator: new state : Q9wQj
// CareTaker: saving original state
// Originator: processing data..
// Originator: new state : 99nsQ
// CareTaker: list of mementos:
// Wed Dec 28 14:37:06 2022/AppStart-Reaady
// Wed Dec 28 14:37:06 2022/5PN2q
// Wed Dec 28 14:37:06 2022/mWqBl
// Wed Dec 28 14:37:06 2022/Q9wQj
// Undoing..
// CareTaker: reverting to state : Wed Dec 28 14:37:06 2022/Q9wQj
// Originator: state changed to : Q9wQj
// CareTaker: list of mementos:
// Wed Dec 28 14:37:06 2022/AppStart-Reaady
// Wed Dec 28 14:37:06 2022/5PN2q
// Wed Dec 28 14:37:06 2022/mWqBl
