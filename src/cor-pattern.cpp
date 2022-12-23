//
//  main.cpp
//  cor_pattern (Chain of Responsibility)
//
//  Created by AK on 20/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <regex>

using namespace std;

class StringValidator {
public:
  virtual StringValidator* setNext(StringValidator* next_validator) = 0;
  virtual ~StringValidator() {};
  virtual string validate(string str) = 0;
};

class BaseValidator : public StringValidator {
private:
  string id_ = "BaseValidator";
protected:
  StringValidator* next = nullptr;
public:
  ~BaseValidator() { delete next; };
  StringValidator* setNext(StringValidator* next_validator) override {
    next = next_validator;
    return next_validator;
  }
  virtual string validate(string str) override {
    if (next) {
      return next->validate(str);
    }
    return " Validation Succeeded.";
  }
};

class NotEmptyValidator : public BaseValidator {
private:
  string id_ = "NotEmptyValidator";
public:
  string validate(string str) override {
    cout << id_;
    if (str.empty()) {
      return " Cannot be empty.";
    }
    cout << "->";
    return BaseValidator::validate(str);
  }
};

class LengthValidator : public BaseValidator {
private:
  int min_len_;
  string id_ = "LengthValidator";
public:
  LengthValidator(int min_len) : min_len_(min_len) {}
  string validate(string str) override {
    cout << id_;
    if (str.length() < min_len_) {
      return " Characters must be more than" + to_string(min_len_);
    }
    return BaseValidator::validate(str);
  }
};

class RegexValidator : public BaseValidator {
private:
  string re_;
  string id_ = "RegexValidator";
public:
  RegexValidator(string re) : re_(re) {};
  string validate(string str) override {
    cout << id_;
    if (!regex_match(str, regex(re_))) {
      return " Value doesn't match pattern.";
    }
    return BaseValidator::validate(str);
  }
};

void ValidateEmail(string str) {
  auto re = "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";
  BaseValidator* ev = new BaseValidator;
  // NotEmptyValidator->RegexValidatorValidation (->) BaseValidator:"Validation Succeeded."
  ev->setNext(new NotEmptyValidator)->setNext(new RegexValidator(re));
  cout << ">> " << str << " : " << ev->validate(str) << "\n--\n";
  delete ev;
}


int main(int argc, const char * argv[]) {
  BaseValidator* ev = new BaseValidator;
  vector<string> email_addresses {"","axe","axe@barn.co.uk"};
  for (auto& ea : email_addresses) {
    ValidateEmail(ea);
  }
  return 0;
}

// OUTPUT
//>>  : NotEmptyValidator Cannot be empty.
//--
//>> axe : NotEmptyValidator->RegexValidator Value doesn't match pattern.
//--
//>> axe@barn.co.uk : NotEmptyValidator->RegexValidator Validation Succeeded.
//--
//Program ended with exit code: 0
