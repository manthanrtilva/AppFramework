/// File: SocketException.h
/// Author : Manthan R. Tilva
/// Date : 30/07/2018
/// Brief :

#ifndef AppFramework_Core_SocketException_h_
#define AppFramework_Core_SocketException_h_

#include <stdexcept>
#include "AppFramework/Core/Exception.h"

namespace AppFramework {
namespace Core {
class SocketException : public Exception {
public:
  explicit SocketException(const std::string &msg)
      : Exception(msg) {}
};
class InvalidSocketConnection : public SocketException {
public:
  InvalidSocketConnection(const std::string &from, const std::string &to)
      : SocketException("Can't connect from '"+from+"' socket to '"+to+"' socket") {}
};
class NullSocket : public SocketException {
public:
  NullSocket()
      : SocketException("Null socket") {}
};
class SocketAlreadyConnected : public SocketException {
public:
  SocketAlreadyConnected()
      : SocketException("Socket already connected") {}
};
class SocketNotConnected : public SocketException {
public:
  SocketNotConnected()
      : SocketException("Socket not connected") {}
};
class CannotSendData : public SocketException {
public:
  CannotSendData(const std::string& name,const std::string& type)
      : SocketException("Can't send data on '"+name+"' socket with direction '"+type+"'.") {}
};
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_SocketException_h_
