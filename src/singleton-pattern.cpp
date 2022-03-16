//
//  main.cpp
//  singleton pattern
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

class Database {
private:
  static Database* database_;
  static mutex mutex_;
protected:
  Database(const string path) : path_(path) {}
  ~Database() {}
  string path_;
public:
  Database(Database& database) = delete;
  Database(Database&& database) = delete;
  void operator=(const Database&) = delete;
  static Database* getInstance(const string& path);
  string getID() const { return path_; }
};

Database* Database::database_{nullptr};
mutex Database::mutex_;

Database* Database::getInstance(const string& path) {
  lock_guard<mutex> lock(mutex_);
  if (database_ == nullptr) {
    database_ = new Database(path);
  }
  return database_;
}

void createSingletonA() {
  this_thread::sleep_for(chrono::milliseconds(500));
  Database* db_singleton = Database::getInstance("DB1");
  cout << db_singleton->getID() << endl;
}

void createSingletonB() {
  this_thread::sleep_for(chrono::milliseconds(500));
  Database* db_singleton = Database::getInstance("DB2");
  cout << db_singleton->getID() << endl;
}


int main(int argc, const char * argv[]) {
  thread t1(createSingletonA);
  thread t2(createSingletonB);
  t1.join();
  t2.join();
  return 0;
}
