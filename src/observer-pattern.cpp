//
//  main.cpp
//  observer_pattern
//
//  Created by AK on 29/12/2021.
//

#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class IObserver {
public:
  virtual ~IObserver() {};
  virtual void update(const string& message_from_subject) = 0;
};

class ISubject {
public:
  virtual ~ISubject() {};
  virtual void attach(IObserver* observer) = 0;
  virtual void detach(IObserver* observer) = 0;
  virtual void notify() = 0;
};

class Subject : public ISubject {
public:
  virtual ~Subject() { cout << "bye i was an object\n"; }
  void attach(IObserver* observer) override {
    observer_list_.push_back(observer);
  }
  void detach(IObserver* observer) override {
    observer_list_.remove(observer);
  }
  void notify() override {
    list<IObserver*>::iterator observer_list_iterator = observer_list_.begin();
    while (observer_list_iterator != observer_list_.end()) {
      (*observer_list_iterator)->update(message_);
      ++observer_list_iterator;
    }
    cout << ">> there are " << observer_list_.size() << " observer(s) in the list\n";
  }
  void pushMessage (string message="blank") {
    this->message_ = message;
    notify();
  }
  
private:
  list<IObserver*> observer_list_;
  string message_;
  string name_;
};

class Observer : public IObserver {
public:
  Observer(Subject& subject, string name) : subject_(subject), name_(name) {
    this->subject_.attach(this);
    cout << "this is " << name << " # " << ++Observer::static_number_ << "\n";
    this->number_ = Observer::static_number_;
  }
  virtual ~Observer() { cout << "[ " << name_ << " ] is dead\n"; }
  void update(const string& message_from_subject) {
    message_from_subject_ = message_from_subject;
    cout << ">> observer " << name_ << " # " << this->number_
        << " - NEW MESSAGE : " << this->message_from_subject_ << "\n";
  }
  void removeFromList() {
    subject_.detach(this);
    cout << ">> observer #" << this->number_ << " REMOVED!\n\n";
  }
  
private:
  Subject& subject_;
  string message_from_subject_;
  string name_;
  static int static_number_;
  int number_;
};

int Observer::static_number_ = 0;
// Observer


void testRun() {
  Subject* region_east_topic = new Subject;
  Subject* region_west_topic = new Subject;
  Subject* region_south_topic = new Subject;
  Subject* region_southwest_topic = new Subject;
  Subject* region_central_topic = new Subject;
  
  Observer* region_east_office = new Observer(*region_east_topic, "RE_OFFICE");
  Observer* region_west_office = new Observer(*region_west_topic, "RW_OFFICE");
  Observer* region_south_office = new Observer(*region_south_topic, "RS_OFFICE");
  Observer* region_central_office;
  Observer* region_southwest_office;
  
  chrono::seconds sleep_for(5);
  region_east_topic->pushMessage("RE: Current population : 608,660");
//  region_west_office->removeFromList();
  this_thread::sleep_for(sleep_for);
  
  region_southwest_office = new Observer(*region_southwest_topic, "RSW");
  region_southwest_topic->pushMessage("RS: Current population : 818,259");
  this_thread::sleep_for(sleep_for);

  region_central_office = new Observer(*region_central_topic, "RC");
  region_central_topic->pushMessage("RC: Current population : 37,015");
  this_thread::sleep_for(sleep_for);
  
  //removed
  region_west_topic->pushMessage("RW: Current population : 737,015");
  this_thread::sleep_for(sleep_for);

  region_south_office = new Observer(*region_south_topic, "RS");
  region_south_topic->pushMessage("RS: Current population : 818,259");
  this_thread::sleep_for(sleep_for);
}

int main(int argc, const char * argv[]) {
  testRun();
  return 0;
}
