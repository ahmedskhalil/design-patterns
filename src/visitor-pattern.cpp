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
#include <thread>
#include <chrono>

using namespace std;

class Point;
class Circle;
class Square;
class Rectangle;
class Octagon;

class Visitor {
public:
  virtual void visitPoint(const Point* point) const = 0;
  virtual void visitCircle(const Circle* circle) const = 0;
  virtual void visitSquare(const Square* square) const = 0;
  virtual void visitRectangle(const Rectangle* rectangle) const = 0;
  virtual void visitOctagon(const Octagon* octagon) const = 0;
};

class Shape {
public:
  virtual ~Shape() {};
  virtual void accept(Visitor* visitor) const = 0;
};

class Point : public Shape {
public:
  void accept(Visitor* visitor) const override {
    visitor->visitPoint(this);
  }
  
  void printDescription() const {
    cout << ">> this is a Point\n";
  }
};

class Circle : public Shape {
public:
  void accept(Visitor* visitor) const override {
    visitor->visitCircle(this);
  }
  
  void printDescription() const {
    cout << ">> this is a Circle\n";
  }
};

class Square : public Shape {
public:
  void accept(Visitor* visitor) const override {
    visitor->visitSquare(this);
  }
  
  void printDescription() const {
    cout << ">> this is a Square\n";
  }
};

class Rectangle : public Shape {
public:
  void accept(Visitor* visitor) const override {
    visitor->visitRectangle(this);
  }
  
  void printDescription() const {
    cout << ">> this is a Rectangle\n";
  }
};

class Octagon : public Shape {
public:
  void accept(Visitor* visitor) const override {
    visitor->visitOctagon(this);
  }
  
  void printDescription() const {
    cout << ">> this is an Octagon\n";
  }
};

class FileExporter : public Visitor {
public:
  virtual void visitPoint(const Point* point) const override {
    point->printDescription();
  }
  virtual void visitCircle(const Circle* circle) const override {
    circle->printDescription();
    
  }
  virtual void visitSquare(const Square* square) const override {
    square->printDescription();
  }
  virtual void visitRectangle(const Rectangle* rectangle) const override {
    rectangle->printDescription();
  }
  virtual void visitOctagon(const Octagon* octagon) const override {
    octagon->printDescription();
  }
};


int main(int argc, const char * argv[]) {
  
  std::array<const Shape*, 5> shapes = { new Point, new Circle, new Square, new Rectangle, new Octagon};
  FileExporter* file_explorer = new FileExporter;
  
  for (const Shape* shape: shapes) {
    shape->accept(file_explorer);
  }
  
  for (const Shape* shape : shapes) {
    delete shape;
  }
  delete file_explorer;
  
  return 0;
}
