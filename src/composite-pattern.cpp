//
//  main.cpp
//  composite pattern
//
//  Created by AK on 29/12/2021.
//

#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

class Component {
protected:
  Component* parent_;
public:
  virtual ~ Component() = default;
  void setParent(Component* parent) { parent_ = parent; }
  Component* getParent() const { return parent_; }
  virtual void add(Component* component) {}
  virtual void remove(Component* component) {}
  virtual bool isComposite() const { return false; }
  virtual string getID() const = 0;
};

class SubComponent : public Component {
public:
  string getID() const override { return "SubComponent"; }
};

class Composite : public Component {
protected:
  list<Component*> children_;
public:
  void add(Component* component) override {
    children_.push_back(component);
    component->setParent(this);
  }
  void remove(Component* component) override {
    children_.remove(component);
    component->setParent(nullptr);
  }
  bool isComposite() const override {
    return true;
  }
  string getID() const override {
    string id;
    for (const Component* comp : children_) {
      if (comp == children_.back()) {
        id += comp->getID();
      } else {
        id += comp->getID() + "+";
      }
    }
    return "Branch(" + id + ")";
  }
};

void printStructure(Component* component) {
  cout << "Structure : " << component->getID() << endl;
}


int main(int argc, const char * argv[]) {
  unique_ptr<Component> main_team(new Composite);
  unique_ptr<Component> sub_team1(new Composite);
  unique_ptr<Component> sub_team2(new Composite);
  unique_ptr<Component> member_1(new SubComponent);
  unique_ptr<Component> member_2(new SubComponent);
  unique_ptr<Component> member_3(new SubComponent);
  
  sub_team1->add(member_1.get());
  sub_team1->add(member_2.get());
  sub_team2->add(member_3.get());
  
  main_team->add(sub_team1.get());
  main_team->add(sub_team2.get());
  
  printStructure(main_team.get());
  return 0;
}
