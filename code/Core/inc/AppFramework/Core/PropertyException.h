/// File: PropertyException.h
/// Author : Manthan R. Tilva
/// Date : 21/07/2018
/// Brief :

#ifndef AppFramework_Core_PropertyException_h_
#define AppFramework_Core_PropertyException_h_

#include <stdexcept>

namespace AppFramework {
namespace Core {
class PropertyException : public std::runtime_error {
public:
  explicit PropertyException(const std::string &msg)
      : std::runtime_error(msg) {}
};
class PropertyNotAdded : public PropertyException {
public:
  PropertyNotAdded(const std::string &name, const std::string &type)
      : PropertyException("Property '" + name + "' of type '" + type +
                          "' is not added") {}
};
class PropertyAlreadyAdded : public PropertyException {
public:
  PropertyAlreadyAdded(const std::string &name, const std::string &type)
      : PropertyException("Property '" + name + "' of type '" + type +
                          "' is already added") {}
};
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_PropertyException_h_
