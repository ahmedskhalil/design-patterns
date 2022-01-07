//
//  main.cpp
//  bridge_pattern
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

class RemoteControl;

class Device {
public:
  virtual ~Device() {}
  virtual bool isEnabled() const = 0;
  virtual void enable() = 0;
  virtual void disable() = 0;
  virtual float getVolume() const = 0;
  virtual void setVolume(float) = 0;
  virtual int getChannel() const = 0;
  virtual void setChannel(int) = 0;
};

class RemoteControl {
protected:
  Device* device_;
public:
  virtual ~RemoteControl() {}
  RemoteControl(Device* device) : device_(device) {}
  
  void togglePower() const {
    if (device_->isEnabled()) {
      device_->disable();
    } else {
      device_->enable();
    }
  }
  virtual void volumeDown() const {
    device_->setVolume(device_->getVolume()-10);
  }
  virtual void volumeUp() const {
    device_->setVolume(device_->getVolume()+10);
  }
  virtual void channelDown() const {
    device_->setChannel(device_->getChannel()-10);
  }
  virtual void channelUp() const {
    device_->setChannel(device_->getChannel()+10);
  }
};

class TV : public Device {
private:
  bool is_enabled_ = false;
  float volume_ = 0.0f;
  int channel_ = 0;
  
  bool isEnabled() const override {
    return is_enabled_;
  }
  void enable() override {
    cout << ">> TV is enabled\n";
    is_enabled_ = true;
  }
  void disable() override {
    cout << ">> TV is disabled\n";
    is_enabled_ = false;
  }
  float getVolume() const override {
    return volume_;
  }
  void setVolume(float volume) override {
    volume_ = volume;
    cout << ">> TV : volume is " << volume_ << endl;
  }
  int getChannel() const override {
    return channel_;
  }
  void setChannel(int channel) override {
    channel_ = channel;
    cout << ">> TV : channel is " << channel_ << endl;
  }
};

class Radio : public Device {
private:
  bool is_enabled_ = false;
  float volume_ = 0.0f;
  int channel_ = 0;
  
  bool isEnabled() const override {
    return is_enabled_;
  }
  void enable() override {
    cout << ">> Radio is enabled\n";
    is_enabled_ = true;
  }
  void disable() override {
    cout << ">> Radio is disabled\n";
    is_enabled_ = false;
  }
  float getVolume() const override {
    return volume_;
  }
  void setVolume(float volume) override {
    volume_ = volume;
    cout << ">> Radio : volume is " << volume_ << endl;
  }
  int getChannel() const override {
    return channel_;
  }
  void setChannel(int channel) override {
    channel_ = channel;
    cout << ">> Radio : channel is " << channel_ << endl;
  }
};

int main(int argc, const char * argv[]) {
  unique_ptr<TV> tv(new TV);
  unique_ptr<RemoteControl> tv_remote(new RemoteControl(tv.get()));
  tv_remote->togglePower();
  tv_remote->volumeUp();
  
  unique_ptr<Radio> radio(new Radio);
  unique_ptr<RemoteControl> radio_remote(new RemoteControl(radio.get()));
  radio_remote->togglePower();
  radio_remote->volumeUp();
  return 0;
}
