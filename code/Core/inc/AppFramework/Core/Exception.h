/// File: Exception.h
/// Author : Manthan R. Tilva
/// Date : 30/07/2018
/// Brief :

#ifndef AppFramework_Core_Exception_h_
#define AppFramework_Core_Exception_h_

#include <stdexcept>

namespace AppFramework {
namespace Core {
class Exception : public std::runtime_error {
public:
  explicit Exception(const std::string &msg)
      : std::runtime_error(msg) {}
};
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_Exception_h_
