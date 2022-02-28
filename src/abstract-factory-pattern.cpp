//
//  main.cpp
//  abstract-factory pattern
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
  virtual ~UIButton(){};
  virtual void draw() const = 0;
};

class WindowsUIButton : public UIButton {
  void draw() const override {
    cout << "Drawing Windows UI Button\n";
  }
};

class macOSUIButton : public UIButton {
  void draw() const override {
    cout << "Drawing macOS UI Button\n";
  }
};

class UICheckbox {
public:
  virtual ~UICheckbox(){};
  virtual void draw() const = 0;
};

class WindowsUICheckbox : public UICheckbox {
  void draw() const override {
    cout << "Drawing Windows UI Checkbox\n";
  }
};

class macOSUICheckbox : public UICheckbox {
  void draw() const override {
    cout << "Drawing macOS UI Checkbox\n";
  }
};

class GUI {
public:
  virtual void createUIButton() const = 0;
  virtual void createCheckBox() const = 0;
};

class WindowsGUI : public GUI {
public:
  void createUIButton() const override {
    cout << "Creating a Windows GUI UI Button\n";
  }
  void createCheckBox() const override {
    cout << "Creating a Windows GUI UI Checkbox\n";
  }
};

class macOSGUI : public GUI {
public:
  void createUIButton() const override {
    cout << "Creating a macOS GUI UI Button\n";
  }
  void createCheckBox() const override {
    cout << "Creating a macOS GUI UI Checkbox\n";
  }
};

class GUIFactory {
public:
  virtual macOSGUI* createmacOSGUI() const = 0;
  virtual WindowsGUI* createWindowsGUI() const = 0;
};

class WindowsGUIFactory : public GUIFactory {
public:
  WindowsGUI* createWindowsGUI() const override {
    return new WindowsGUI();
  }
  macOSGUI* createmacOSGUI() const override {
    return new macOSGUI();
  }
};

class macOSGUIFactory : public GUIFactory {
public:
  WindowsGUI* createWindowsGUI() const override {
    return new WindowsGUI();
  }
  macOSGUI* createmacOSGUI() const override {
    return new macOSGUI();
  }
};

void App(const GUIFactory& gui_factory) {
  unique_ptr<WindowsGUI> win_gui(gui_factory.createWindowsGUI());
  win_gui->createCheckBox();
  win_gui->createUIButton();
}

int main(int argc, const char * argv[]) {
  unique_ptr<WindowsGUIFactory> win_gui(new WindowsGUIFactory);
  App(*win_gui);
  unique_ptr<macOSGUIFactory> macos_gui(new macOSGUIFactory);
  App(*macos_gui);
  
  return 0;
}
