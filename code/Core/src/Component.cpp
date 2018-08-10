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
      switch (oState) {
        case State::STOP:
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
  doConfigureImpl();
  mState = State::CONFIGURE;
}
void Component::doRun() {
  doRunImpl();
  mState = State::RUN;
}
void Component::doStop() {
  doStopImpl();
  mState = State::STOP;
}

} // namespace Core
} // namespace AppFramework
