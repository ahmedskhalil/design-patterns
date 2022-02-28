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
  virtual std::unique_ptr<UIButton> createUIButton() const = 0;
};

class WindowsUIDialog : public UIDialog {
public:
  std::unique_ptr<UIButton> createUIButton() const override {
    return std::make_unique<WindowsUIButton>();
  }
};

class macOSUIDialog : public UIDialog {
public:
  std::unique_ptr<UIButton> createUIButton() const override {
    return std::make_unique<macOSUIButton>();
  }
};

class Application {
//  UIDialog dialog_;
  const std::string os_;
  
public:
  Application(const std::string& os) : os_(os) {};
  
  void initialise() {
    if (os_ == "Windows") {
      new WindowsUIDialog();
    } else if (os_ == "macOS") {
      new macOSUIDialog();
    } else {
      std::cout << "Unknown OS\n";
    }
  }
  
  
};



int main(int argc, const char * argv[]) {
  
  return 0;
}
