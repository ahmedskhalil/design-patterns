//
//  main.cpp
//  factorymethod_pattern
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

class UIButton {
public:
  virtual ~UIButton() {};
  virtual void render() const = 0;
  virtual void onClick() const = 0;
};

class WindowsUIButton : public UIButton {
public:
  void render() const override {
    cout << ">> rendering WindowsUIButton style button\n";
  }
  void onClick() const override {
    cout << ">> WindowsUIButton : click captured";
  }
};

class macOSUIButton : public UIButton {
public:
  void render() const override {
    cout << ">> rendering macOSUIButton style button\n";
  }
  void onClick() const override {
    cout << ">> macOSUIButton : click captured";
  }
};

class UIDialog {
public:
  virtual ~UIDialog() {};
  virtual string createUIButton() const = 0;
};

class WindowsUIDialog : public UIDialog {
public:
  string createUIButton() const override {
    
  }
};



int main(int argc, const char * argv[]) {
  
  return 0;
}
