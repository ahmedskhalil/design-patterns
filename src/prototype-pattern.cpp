//
//  main.cpp
//  prototype pattern
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

enum class ShapeType {Rectangle, Circle};

class Shape2D {
protected:
  string shape_name_;
  float x_, y_;
public:
  virtual ~Shape2D() {};
  Shape2D() = default;
  Shape2D(string shape_name) : shape_name_(shape_name) {}
  virtual Shape2D* clone() const = 0;
  virtual void set(float x, float y) {
    x_ = x;
    y_ = y;
  }
};

class Rectangle : public Shape2D {
private:
  float x_, y_;
public:
  Rectangle(string shape_name, float x, float y) : Shape2D(shape_name), x_(x), y_(y) {}
  Shape2D* clone() const override {
    return new Rectangle(*this);
  }
};

class Circle : public Shape2D {
private:
  float x_, y_;
public:
  Circle(string shape_name, float x, float y) : Shape2D(shape_name), x_(x), y_(y) {}
  Shape2D* clone() const override {
    return new Circle(*this);
  }
};

class App {
private:
  unordered_map<ShapeType, Shape2D*> shapes_;
public:
  App() {
    shapes_[ShapeType::Rectangle] = new Rectangle("rect_1", 20.0f, 15.0f);
    shapes_[ShapeType::Circle] = new Circle("circ_1", 10.0f, 25.0f);
  }
  ~App() {
    delete shapes_[ShapeType::Rectangle];
    delete shapes_[ShapeType::Circle];
  }
  Shape2D* createShape(ShapeType type) {
    if (type == ShapeType::Rectangle)
      cout << "creating a rectangle\n";
    if (type == ShapeType::Circle)
      cout << "creating a circle\n";
    return shapes_[type]->clone();
  }
};

void runner(App& app) {
  Shape2D* shape = app.createShape(ShapeType::Circle);
  shape->set(20.0f, 5.0f);
  shape = app.createShape(ShapeType::Rectangle);
  shape->set(10.0f, 25.0f);
  delete shape;
}

int main(int argc, const char * argv[]) {
  unique_ptr<App> app(new App);
  runner(*app);
  return 0;
}
