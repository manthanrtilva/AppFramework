
/// File: Socket.h
/// Author : Manthan R. Tilva
/// Date : 30/07/2018
/// Brief : Declaration to Socket class

#ifndef AppFramework_Core_Socket_h_
#define AppFramework_Core_Socket_h_

#include "AppFramework/Core/DataFragment.h"
#include "AppFramework/Core/SocketException.h"
#include "AppFramework/Core/Common.h"

#include <any>
#include <cstdint>
#include <list>
#include <memory>
#include <string>

#include <iostream>

namespace AppFramework {
namespace Core {
// class Component;
class CLASS_API Socket : public std::enable_shared_from_this<Socket> {
public:
  class EventHandler {
  public:
    enum EventType { CONNECT, DISCONNECT, RECIEVED, SENT };
    virtual void onEvent(EventType type, const std::weak_ptr<Socket>& wpFrom,  const std::weak_ptr<Socket>& wpTo, std::uint8_t dataType, std::any pData) = 0;
  };
  enum FlowDirection { IN_DIRECTION, OUT_DIRECTION, UNKNOWN_DIRECTION };
  typedef FlowDirection Direction;
  Direction getDirection() const;
  ~Socket();
  void connect(std::weak_ptr<Socket> wPtrSocket);
  void disconnect(std::weak_ptr<Socket> wPtrSocket);
  void addListner(std::shared_ptr<EventHandler> sPtrHandler);
  void removeListner(std::shared_ptr<EventHandler> sPtrHandler);
  bool isConnected();
  template <typename T>
  void sendData(std::shared_ptr<DataFragment<T>> sPtrData);
  template <typename T>
  void onDataEvent(EventHandler::EventType type, std::weak_ptr<Socket> sPtrTo,
                   std::shared_ptr<DataFragment<T>> sPtrData);
  std::string getName() const;
  std::uint8_t getDataType() const;
  static std::shared_ptr<Socket> create(const std::string &name, std::uint8_t type,
                                        Direction dir = Direction::UNKNOWN_DIRECTION);

private:
  void disconnectAll();
  Socket(const std::string &name, std::uint8_t type, Direction dir)
      : mStrName{name}, mUIntDataType{type}, mFlowDirection{dir} {}
  std::string getDirectionString() const;

private:
  Direction mFlowDirection{Direction::UNKNOWN_DIRECTION};
  std::list<std::weak_ptr<Socket>> mListConnectedSocket;
  std::list<std::weak_ptr<EventHandler>> mListEventHandler;
  std::string mStrName;
  std::uint8_t mUIntDataType;
};
inline std::string Socket::getName() const { return mStrName; }
inline std::uint8_t Socket::getDataType() const { return mUIntDataType;}
inline Socket::Direction Socket::getDirection() const { return mFlowDirection; }
inline std::string Socket::getDirectionString() const{
  switch (mFlowDirection) {
  case FlowDirection::IN_DIRECTION:
    return "IN_DIRECTION";
    break;
  case FlowDirection::OUT_DIRECTION:
    return "OUT_DIRECTION";
    break;
  case FlowDirection::UNKNOWN_DIRECTION:
    return "UNKNOWN_DIRECTION";
    break;
  }
  return "";
}
template <typename T>
void Socket::sendData(std::shared_ptr<DataFragment<T>> sPtrData) {
  if (getDirection() == FlowDirection::OUT_DIRECTION) {
    if (isConnected()) {
      for (auto &&wPtrSocket : mListConnectedSocket) {
        if (wPtrSocket.expired() == false) {
          auto sPtrSocket = wPtrSocket.lock();
          sPtrSocket->onDataEvent(EventHandler::EventType::RECIEVED, shared_from_this(), sPtrData);
        }
      }
    }
    onDataEvent(EventHandler::EventType::SENT, shared_from_this(), sPtrData);
  } else {
    throw CannotSendData(mStrName, getDirectionString());
  }
}
template <typename T>
void Socket::onDataEvent(EventHandler::EventType type, std::weak_ptr<Socket> wPtrFrom,
                         std::shared_ptr<DataFragment<T>> sPtrData) {
  if (!mListEventHandler.empty()) {
    for (auto &wPtrEventHandler : mListEventHandler) {
      if (wPtrEventHandler.expired() == false) {
        auto sPtrEventHandler = wPtrEventHandler.lock();
        sPtrEventHandler->onEvent(type,wPtrFrom,shared_from_this(),mUIntDataType,std::any(sPtrData));
      }
    }
  }
}
template <>
inline void Socket::onDataEvent<void>(EventHandler::EventType type, std::weak_ptr<Socket> wPtrFrom,
                         std::shared_ptr<DataFragment<void>> sPtrData) {
  if (!mListEventHandler.empty()) {
    for (auto &wPtrEventHandler : mListEventHandler) {
      if (wPtrEventHandler.expired() == false) {
        auto sPtrEventHandler = wPtrEventHandler.lock();
        sPtrEventHandler->onEvent(type,wPtrFrom,shared_from_this(),0,std::any());
      }
    }
  }
}
} // namespace Core
} // namespace AppFramework

#endif // AppFramework_Core_Socket_h_
