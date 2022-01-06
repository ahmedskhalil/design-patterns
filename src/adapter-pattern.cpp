//
//  main.cpp
//  observer_pattern
//
//  Created by AK on 29/12/2021.
//

#include <iostream>
#include <list>
#include <string>
#include <array>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

class BNCSocket {
public:
  virtual ~BNCSocket() = default;
  
  virtual string request() const {
    return "BNC Specs : xx xx xx\n";
  }
};

class TNCSocket {
public:
  string specificRequest() const {
    return "987 654 321 0";
  }
};

class TNCtoBNC : public BNCSocket {
private:
  TNCSocket* tnc_socket_;
public:
  TNCtoBNC(TNCSocket* adaptee) : tnc_socket_(adaptee) {}
  string request() const override {
    string id = this->tnc_socket_->specificRequest();
    reverse(id.begin(), id.end());
    return "Adapter correct ID : " + id;
  }
};

void testRun(const BNCSocket* bnc_socket) {
  cout << bnc_socket->request();
}

int main(int argc, const char * argv[]) {
  unique_ptr<BNCSocket> bnc_socket(new BNCSocket);
  testRun(bnc_socket.get());
  
  unique_ptr<TNCtoBNC> tnc_bnc(new TNCtoBNC(new TNCSocket));
  cout << "Adaptee : " << tnc_bnc->request() << endl;
  
  return 0;
}
