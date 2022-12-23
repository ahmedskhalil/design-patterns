//
//  main.cpp
//  state pattern
//
//  Created by AK on 23/12/2022.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

class PlotContext;
class PlotState {
protected:
  PlotContext* context_;
public:
  virtual ~PlotState() {};
  void setContext(PlotContext* ctx) {
    this->context_ = ctx;
  }
  virtual void handleScroll() = 0;
  virtual void handleClick() = 0;
};

class PlotContext {
private:
  PlotState* state_;
public:
  PlotContext(PlotState* state) : state_(nullptr) {
    this->transitionTo(state);
  }
  ~PlotContext() { delete state_; };
  void transitionTo(PlotState* state) {
    cout << "Context : Transition to " << typeid(*state).name() << endl;
    if (state_ != nullptr) delete state_;
    state_ = state;
    state_->setContext(this);
  }
  void requestA() { state_->handleClick(); }
  void requestB() { state_->handleScroll(); }
};

class ModifiableState : public PlotState {
public:
  void handleClick() override;
  void handleScroll() override {
    cout << "ModifiableState : scrolling ..\n";
  }
};

class LockedState : public PlotState {
public:
  void handleClick() override {
    cout << "LockedState : click has no effect!\n";
    cout << "LockedState is transitioning to ModifiableState\n";
    context_->transitionTo(new ModifiableState);
  }
  void handleScroll() override {
    cout << "LockedState : scrolling has no effect!\n";
  }
};

void ModifiableState::handleClick() {
  cout << "ModifiableState : moving cursor ..\n";
  cout << "ModifiableState is transitioning to LockedState\n";
  context_->transitionTo(new LockedState);
}

// ctx->request[ABC](state[ABC]->handle())
int main(int argc, const char * argv[]) {
  unique_ptr<PlotContext> ctx(new PlotContext(new ModifiableState));
  ctx->requestA();
  ctx->requestB();
  return 0;
}

// OUTPUT
// Context : Transition to 15ModifiableState
// ModifiableState : moving cursor ..
// ModifiableState is transitioning to LockedState
// Context : Transition to 11LockedState
// LockedState : scrolling has no effect!
