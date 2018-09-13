/// File: Component.h
/// Author : Manthan R. Tilva
/// Date : 02/08/2018
/// Brief :

#ifndef AppFramework_Core_Component_h_
#define AppFramework_Core_Component_h_

#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

#include "AppFramework/Core/Property.h"
#include "AppFramework/Core/Socket.h"
#include "AppFramework/Core/Common.h"

#include <boost/dll/alias.hpp>

#include <iostream>

namespace AppFramework {
namespace Core {
class CLASS_API Component : public Property {
public:
  enum State { INIT, CONFIGURE, RUN, STOP };
  typedef std::shared_ptr<Component>(component_create_t)(const std::string &);
  template <typename T>
  static std::shared_ptr<Component> create(const std::string &name);
  State getState();
  void setState(State oState);
  std::string getName() const;
  std::weak_ptr<Socket> getSocket(const std::string &name, std::uint8_t type, Socket::Direction dir) {
    const auto& sock = mUMapSockets.find(name);
    if (sock != std::end(mUMapSockets)) {
      if(sock->second->getDataType() == type && sock->second->getDirection() == dir){
        return sock->second;
      }
    }
    return std::weak_ptr<Socket>();
  }

protected:
  explicit Component(const std::string &name);
  std::weak_ptr<Socket> addSocket(const std::string &name, std::uint8_t type,
                                    Socket::Direction dir = Socket::Direction::UNKNOWN_DIRECTION) {
    if (mUMapSockets.find(name) == std::end(mUMapSockets)) {
      mUMapSockets[name] = std::move(Socket::create(name, type, dir));
      return mUMapSockets[name];
    }
    return std::weak_ptr<Socket>();
  }
  virtual void doConfigureImpl() = 0;
  virtual void doRunImpl() = 0;
  virtual void doStopImpl() = 0;

private:
  void doConfigure();
  void doRun();
  void doStop();
  void doStopImplWrap();

private:
  std::string mStrName;
  State mState{State::INIT};
  std::unordered_map<std::string, std::shared_ptr<Socket>> mUMapSockets;
  std::thread mRunThread;
};
template <typename T>
std::shared_ptr<Component> Component::create(const std::string &name) {
  return std::make_shared<T>(name);
}
inline std::string Component::getName() const { return mStrName; }
inline Component::State Component::getState() { return mState; }
template <class F>
F identity(F f) {
  return std::move(f);
}
} // namespace Core
} // namespace AppFramework

#if MSVC
#define CREATE_COMPONENT(comp) BOOST_DLL_ALIAS(               \
    AppFramework::Core::identity(Component::create<comp>),   \
    create_component                                          \
)
#else
#define CREATE_COMPONENT(comp) BOOST_DLL_ALIAS(               \
    Component::create<comp>, create_component                 \
)
#endif
#endif // AppFramework_Core_Component_h_
