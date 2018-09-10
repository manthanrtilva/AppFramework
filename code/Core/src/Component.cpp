/// File: Component.cpp
/// Author : Manthan R. Tilva
/// Date : 03/08/2018
/// Brief :

#include <memory>
#include <unordered_map>

#include "AppFramework/Core/Component.h"

namespace AppFramework {
namespace Core {
Component::Component(const std::string &name) : mStrName{name} {}
void Component::setState(Component::State oState) {
  std::cout << __LINE__ << ":" << __FUNC__ <<":"<<mState<<":"<<oState<< std::endl;
  switch (mState) {
    case State::INIT:
      switch (oState) {
        case State::CONFIGURE:
          doConfigure();
          break;
        case State::RUN:
          doConfigure();
          doRun();
          break;
      }
      break;
    case State::CONFIGURE:
      switch (oState) {
        case State::RUN:
          doRun();
          break;
      }
      break;
    case State::RUN:
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
      switch (oState) {
        case State::STOP:
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
          doStop();
          break;
      }
      break;
    case State::STOP:
      switch (oState) {
        case State::CONFIGURE:
          doConfigure();
          break;
        case State::RUN:
          doRun();
          break;
      }
      break;
  }
}
void Component::doConfigure() {
  mState = State::CONFIGURE;
  doConfigureImpl();
}
void Component::doStopImplWrap() {
  try {
    doRunImpl();
  } catch (std::exception &ex) {
    std::cout << "exception:" << ex.what() << std::endl;
    mState = State::STOP;
  } catch (...) {
    std::cout << "unknown exception" << std::endl;
    mState = State::STOP;
  }
  mState = State::STOP;
}
void Component::doRun() {
  try {
    mState = State::RUN;
    mRunThread = std::thread(&Component::doStopImplWrap,this);
  } catch (std::exception &ex) {
    std::cout << "exception:" << ex.what() << std::endl;
    mState = State::STOP;
  } catch (...) {
    std::cout << "unknown exception" << std::endl;
    mState = State::STOP;
  }
}
void Component::doStop() {
std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  mState = State::STOP;
  doStopImpl();
  mRunThread.join();
}

} // namespace Core
} // namespace AppFramework
