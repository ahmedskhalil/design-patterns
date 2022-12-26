//
//  main.cpp
//  mediator pattern
//
//  Created by AK on 25/12/2022.
//

#include <iostream>
#include <memory>

using namespace std;

class UIComponent;
class Mediator {
public:
  virtual void notify(UIComponent*, string) const = 0;
};
class UIComponent {
protected:
  Mediator* mediator_;
public:
  UIComponent(Mediator* mediator=nullptr) : mediator_(mediator) {}
  void setMediator(Mediator* mediator) { mediator_ = mediator; }
  virtual ~UIComponent() = default;
};
class UIButton : public UIComponent {
public:
  void RunB1() {
    cout << "UIButton runs B1\n";
    mediator_->notify(this, "B1");
  }
  void RunB2() {
    cout << "UIButton runs B2\n";
    mediator_->notify(this, "B2");
  }
};
class UITextbox : public UIComponent {
public:
  void RunT1() {
    cout << "UITextbox runs T1\n";
    mediator_->notify(this, "T1");
  }
  void RunT2() {
    cout << "UITextbox runs T2\n";
    mediator_->notify(this, "T2");
  }
};
class UICheckbox : public UIComponent {
public:
  void RunC1() {
    cout << "UICheckbox runs C1\n";
    mediator_->notify(this, "C1");
  }
  void RunC2() {
    cout << "UICheckbox runs C2\n";
    mediator_->notify(this, "C2");
  }
};
class AuthenticationDialog : public Mediator {
private:
  UIButton* uibutton_;
  UITextbox* uitextbox_;
  UICheckbox* uicheckbox_;
public:
  AuthenticationDialog(UIButton* uib, UITextbox* uit, UICheckbox* uic) :
  uibutton_(uib), uitextbox_(uit), uicheckbox_(uic) {
    uibutton_->setMediator(this);
    uitextbox_->setMediator(this);
    uicheckbox_->setMediator(this);
  }
  void notify(UIComponent* uic_sender, string event) const override {
    if (dynamic_cast<UIButton*>(uic_sender) && event == "BTC2") {
      uibutton_->RunB2();
      uitextbox_->RunT2();
      uicheckbox_->RunC2();
    }
    if (event == "BC1") {
      uibutton_->RunB1();
      uicheckbox_->RunC1();
    }
  }
};

void run() {
  unique_ptr<UIButton> uib(new UIButton);
  unique_ptr<UITextbox> uit(new UITextbox);
  unique_ptr<UICheckbox> uic(new UICheckbox);
  unique_ptr<AuthenticationDialog> ad(new AuthenticationDialog(uib.get(),uit.get(),uic.get()));
  ad->notify(uib.get(), "BTC2");
}


int main(int argc, const char * argv[]) {
  run();
  return 0;
}

// OUTPUT
// UIButton runs B2
// UITextbox runs T2
// UICheckbox runs C2
