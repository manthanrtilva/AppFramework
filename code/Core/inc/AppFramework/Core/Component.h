/// File: Component.h
/// Author : Manthan R. Tilva
/// Date : 02/08/2018
/// Brief :

#ifndef AppFramework_Core_Component_h_
#define AppFramework_Core_Component_h_

#include <memory>
#include <string>
#include <unordered_map>

#include "AppFramework/Core/Socket.h"

namespace AppFramework {
namespace Core {
class Component {
public:
  enum State {
    INIT,
    CONFIGURE,
    RUN,
    // PAUSE,
    // RESUME,
    STOP
  };
  // typename<template T>
  template <typename T>
  static std::shared_ptr<Component> create(const std::string& name);
  State getState();
  void setState(State oState);
  std::string getName() const;
  // std::shared_ptr<Socket> getSocket(const std::string &name, std::uint8_t type) const;
  // void doPause();
  // void doResume();
protected:
  explicit Component(const std::string &name);
  // std::shared_ptr<Socket> createSocket(const std::string &name, std::uint8_t type, Socket::Direction dir);
  virtual void doConfigureImpl() = 0;
  virtual void doRunImpl() = 0;
  virtual void doStopImpl() = 0;
  // virtual void doPauseImpl() = 0;
  // virtual void doResumeImpl() = 0;
private:
  void doConfigure();
  void doRun();
  void doStop();
private:
  std::string mStrName;
  State mState{State::INIT};
  std::unordered_map<std::string, std::shared_ptr<Socket>> mUMapSockets;
};
template <typename T>
std::shared_ptr<Component> Component::create(const std::string& name) {
  return std::make_shared<T>(name);
}
inline std::string Component::getName() const { return mStrName; }
inline Component::State Component::getState(){
  return mState;
}
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_Component_h_
