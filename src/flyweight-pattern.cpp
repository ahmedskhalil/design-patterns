//
//  main.cpp
//  flyweight pattern
//
//  Created by AK on 29/12/2021.
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

struct TreeType { // shared state
  string name_;
  string color_;
  string texture_;
  
  TreeType(const string& name, const string& color, const string& texture)
  : name_(name), color_(color), texture_(texture) {}
  friend ostream& operator<<(ostream& os, const TreeType& tt) {
    return os << " " << tt.name_ << ", " << tt.color_ << ", " << tt.texture_;
  }
  void draw(const size_t x, const size_t y) {
    cout << "Drawing " << name_ << ", " << color_ << ", " << texture_ << " at x:" << x << " and y:" << endl;
  }
};

struct Tree { // unique state
  size_t x_;
  size_t y_;
  TreeType tree_type_;
  
  Tree(const size_t& x, const size_t& y, const TreeType& tree_type) : x_(x), y_(y), tree_type_(tree_type) {}
  void draw() { tree_type_.draw(x_, y_); }
};

class TreeTypeFlyWeight {
  TreeType* tree_type_; // shared state
  
public:
  TreeTypeFlyWeight(const TreeType* tree_type) : tree_type_(new TreeType(*tree_type)) {}
  TreeTypeFlyWeight(const TreeTypeFlyWeight& tt_fw) : tree_type_(new TreeType(*tt_fw.tree_type_)) {}
  ~TreeTypeFlyWeight() { delete tree_type_; }
  TreeType* getTreeType() const { return tree_type_; }
  void logTree(const Tree& tree) const {
    cout << "Tree type (shared state) : " << *tree_type_ << " and tree (unique state) : " << &tree
        << " at x: " << tree.x_ << " & y: " << tree.y_ << endl;
  }
};

class TreeFactory {
private:
  unordered_map<string, TreeTypeFlyWeight> treetype_flyweights_;
  string getKey(const TreeType& tree_type) {
    return tree_type.name_ + "-" + tree_type.color_ + "-" + tree_type.texture_;
  }
public:
  TreeFactory(initializer_list<TreeType> tree_types) {
    for (const TreeType& tree_type : tree_types) {
      this->treetype_flyweights_.insert(make_pair<string, TreeTypeFlyWeight>(this->getKey(tree_type), TreeTypeFlyWeight(&tree_type)));
    }
  }
  TreeTypeFlyWeight getTreeTypeFlyWeight(const TreeType& tree_type) {
    auto key = this->getKey(tree_type);
    if (this->treetype_flyweights_.find(key) == this->treetype_flyweights_.end()) {
      cout << "TreeType not found, creating new one..\n";
      this->treetype_flyweights_.insert(make_pair(key, TreeTypeFlyWeight(&tree_type)));
    } else {
      cout << "Reusing existing TreeType\n";
    }
    return treetype_flyweights_.at(key);
  }
  void list_TreeTypeFlyWeights() const {
    size_t count = this->treetype_flyweights_.size();
    cout << "Available TreeTypes : " << count << endl;
    for (pair<string, TreeTypeFlyWeight> tt_fw: this->treetype_flyweights_) {
      cout << tt_fw.first << endl;
    }
  }
};

void addToDrawingSet(TreeFactory& tf, const string& name, const string& color, const string& texture) {
  cout << "Adding TreeType to drawing set -> name : " << name << ", color: " << color << ", texture: " << texture << endl;
  auto fw = tf.getTreeTypeFlyWeight({name, color, texture});
  fw.logTree({124,421,*fw.getTreeType()});
}

int main(int argc, const char * argv[]) {
  unique_ptr<TreeFactory> tf(new TreeFactory({{"JC","G","X"},{"LC","Y","W"},{"TC","R","C"}}));
  tf->list_TreeTypeFlyWeights();
  addToDrawingSet(*tf.get(), "ZC", "B", "E");
  tf->list_TreeTypeFlyWeights();
  return 0;
}

// OUTPUT
// Available TreeTypes : 3
// TC-R-C
// LC-Y-W
// JC-G-X
// Adding TreeType to drawing set -> name : ZC, color: B, texture: E
// TreeType not found, creating new one..
// Tree type (shared state) :  ZC, B, E and tree (unique state) : 0x7ff7bfeff258 at x: 124 & y: 421
// Available TreeTypes : 4
// TC-R-C
// ZC-B-E
// LC-Y-W
// JC-G-X
