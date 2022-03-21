//
//  main.cpp
//  decorator pattern
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
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;

class DataSource {
public:
  virtual ~DataSource() {}
  virtual void write_data(const string& data) const = 0;
  virtual string read_data() const = 0;
};

class FileDataSource : public DataSource {
  filesystem::path filepath_;
public:
  FileDataSource(filesystem::path filepath) : filepath_(filepath) {}
  void write_data(const string& data) const override {
    ofstream data_file;
    data_file.open(filepath_, ios::out | ios::app);
    if (data_file.is_open()) {
      data_file << data;
    } else {
      cout << "could not write to file\n";
    }
    data_file.close();
  }
  string read_data() const override {
    ifstream file_stream(filepath_.string());
    stringstream file_stream_buffer;
    file_stream_buffer << file_stream.rdbuf();
    return file_stream_buffer.str();
  }
};
class DataSourceDecorator : public DataSource {
protected:
  DataSource* data_source_;
public:
  DataSourceDecorator(DataSource* data_source) : data_source_(data_source) {}
  void write_data(const string& data) const override {
    data_source_->write_data(data);
  }
  string read_data() const override {
    return data_source_->read_data();
  }
};
class EncryptDecorator : public DataSourceDecorator {
public:
  EncryptDecorator(DataSource* data_source) : DataSourceDecorator(data_source) {}
  void write_data(const string& data) const override {
    DataSourceDecorator::write_data(data);
  }
  string read_data() const override {
    return "ENCRYPTED_" + DataSourceDecorator::read_data();
  }
};
class DecryptDecorator : public DataSourceDecorator {
public:
  DecryptDecorator(DataSource* data_source) : DataSourceDecorator(data_source) {}
  void write_data(const string& data) const override {
    DataSourceDecorator::write_data(data);
  }
  string read_data() const override {
    return "DECRYPTED_" + DataSourceDecorator::read_data();
  }
};

void runner(DataSource* data_source) {
  cout << "DATA: " << data_source->read_data() << endl;
}

int main(int argc, const char * argv[]) {
  filesystem::path datafile("/path/to/txt/file");
  auto file_data_source = make_unique<FileDataSource>(datafile);
  runner(file_data_source.get());
  
  auto encryptor = make_unique<EncryptDecorator>(file_data_source.get());
  runner(encryptor.get());
  
  auto decryptor = make_unique<DecryptDecorator>(file_data_source.get());
  runner(decryptor.get());

  return 0;
}
