//
//  main.cpp
//  strategy pattern
//
//  Created by AK on 24/12/2022.
//

#include <iostream>
#include <memory>

using namespace std;

class ExecutionStrategy {
public:
  virtual int execute(int,int) = 0;
};

class ESAdd : public ExecutionStrategy {
  int execute(int a, int b) override {
    return a+b;
  }
};

class ESSub : public ExecutionStrategy {
  int execute(int a, int b) override {
    return a-b;
  }
};

class ESMul : public ExecutionStrategy {
  int execute(int a, int b) override {
    return a*b;
  }
};

class CalcContext {
private:
  ExecutionStrategy* es_;
public:
  void setCalcStrategy(ExecutionStrategy* es) {
    es_ = es;
  }
  int executeStrategy(int a, int b) {
    return es_->execute(a,b);
  }
};


int main(int argc, const char * argv[]) {
  unique_ptr<CalcContext> cc(new CalcContext);
  cc->setCalcStrategy(new ESMul);
  cout << "Set to ESMul yields : " << cc->executeStrategy(2, 3) << endl;
  cc->setCalcStrategy(new ESAdd);
  cout << "Set to ESMul yields : " << cc->executeStrategy(2, 3) << endl;
  return 0;
}
