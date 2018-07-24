/// File: PropertyValue.h
/// Author : Manthan R. Tilva
/// Date : 21/07/2018
/// Brief :

#include "ValueType.h"

#include <type_traits>

#ifndef AppFramework_Core_PropertyValue_h_
#define AppFramework_Core_PropertyValue_h_
namespace AppFramework {
namespace Core {
class PropertyValue {
public:
  PropertyValue(ValueType value) : mType{value} {
    switch (mType) {
    case ValueType::BOOL:
      mPtrData = new bool();
      break;
    case ValueType::INT8:
      mPtrData = new std::int8_t();
      break;
    case ValueType::INT16:
      mPtrData = new std::int16_t();
      break;
    case ValueType::INT32:
      mPtrData = new std::int32_t();
      break;
    case ValueType::INT64:
      mPtrData = new std::int64_t();
      break;
    case ValueType::STRING:
      mPtrData = new std::string();
      break;
    }
  }
  template <typename NativeType> NativeType getValue() {
    validateType<NativeType>();
    NativeType *pValue = static_cast<NativeType *>(mPtrData);
    return *pValue;
  }
  template <typename NativeType> void setValue(NativeType value) {
    validateType<NativeType>();
    NativeType *pValue = static_cast<NativeType *>(mPtrData);
    *pValue = value;
  }
  ValueType mType;

private:
  template <typename NativeType> void validateType() {
    switch (mType) {
    case ValueType::BOOL:
      if (!std::is_same<NativeType, bool>::value) {
        InvalidFunctionCall();
      }
      break;
    case ValueType::INT8:
      if (!std::is_same<NativeType, std::int8_t>::value) {
        InvalidFunctionCall();
      }
      break;
    case ValueType::INT16:
      if (!std::is_same<NativeType, std::int16_t>::value) {
        InvalidFunctionCall();
      }
      break;
    case ValueType::INT32:
      if (!std::is_same<NativeType, std::int32_t>::value) {
        InvalidFunctionCall();
      }
      break;
    case ValueType::INT64:
      if (!std::is_same<NativeType, std::int64_t>::value) {
        InvalidFunctionCall();
      }
      break;
    case ValueType::STRING:
      if (!std::is_same<NativeType, std::string>::value) {
        InvalidFunctionCall();
      }
      break;
    }
  }
  inline void InvalidFunctionCall() {
    throw std::runtime_error("Invalid function call");
  }
  void *mPtrData = nullptr;
};
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_PropertyValue_h_
