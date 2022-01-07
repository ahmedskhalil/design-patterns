//
//  main.cpp
//  builder_pattern
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

class UIWidget {
public:
  vector<string> components_;
  void listComponents() const {
    cout << "UIWidget components: ";
    for (size_t i = 0; i < components_.size(); i++) {
      if (components_[i] == components_.back()) {
        cout << components_[i];
      } else {
        cout << components_[i] << ", ";
      }
    }
    cout << endl;
  }
};

class Builder {
public:
  virtual ~Builder(){}
  virtual void addButton() const = 0;
  virtual void addSlider() const = 0;
  virtual void addTextField() const = 0;
  virtual void add2DPlot() const = 0;
};

class FloatingWidgetBuilder : public Builder {
private:
  UIWidget* ui_widget_;
public:
  FloatingWidgetBuilder() {
    this->reset();
  }
  ~FloatingWidgetBuilder() {
    delete ui_widget_;
  }
  void reset() {
    this->ui_widget_ = new UIWidget();
  }
  
  void addButton() const override {
    this->ui_widget_->components_.push_back("UIButton");
  }
  void addSlider() const override {
    this->ui_widget_->components_.push_back("UISlider");
  }
  void addTextField() const override {
    this->ui_widget_->components_.push_back("UITextField");
  }
  void add2DPlot() const override {
    this->ui_widget_->components_.push_back("UI2DPlot");
  }
  
  UIWidget* getWidget() {
    UIWidget* ui_widget = this->ui_widget_;
    this->reset();
    return ui_widget;
  }
};

class FloatingWidgetDirector {
private:
  Builder* fwidget_builder;
public:
  void setBuilder(Builder* builder) {
    this->fwidget_builder = builder;
  }
  
  void buildMinimalFloatingWidget() {
    this->fwidget_builder->addTextField();
  }
  
  void buildFullFloatingWidget() {
    this->fwidget_builder->addButton();
    this->fwidget_builder->addTextField();
    this->fwidget_builder->addSlider();
    this->fwidget_builder->add2DPlot();
  }
};

void testRun(FloatingWidgetDirector& director) {
  unique_ptr<FloatingWidgetBuilder> builder = make_unique<FloatingWidgetBuilder>();
  director.setBuilder(builder.get());
  
  director.buildMinimalFloatingWidget();
  auto* ui_widget = builder->getWidget();
  ui_widget->listComponents();
  delete ui_widget;
  
  director.buildFullFloatingWidget();
  ui_widget = builder->getWidget();
  ui_widget->listComponents();
  delete ui_widget;
}


int main(int argc, const char * argv[]) {
  unique_ptr<FloatingWidgetDirector> director = make_unique<FloatingWidgetDirector>();
  testRun(*director);
  
  return 0;
}
