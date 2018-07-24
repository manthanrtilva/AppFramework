/// File: ValueType.h
/// Author : Manthan R. Tilva
/// Date : 23/07/2018
/// Brief :
#ifndef AppFramework_Core_ValueType_h_
#define AppFramework_Core_ValueType_h_
namespace AppFramework {
namespace Core {

enum ValueType {
  BOOL, //bool
  INT8, //std::int8_t
  INT16, //std::int16_t
  INT32, //std::int32_t
  INT64, //std::int64_t
  STRING //std::string
};

} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_ValueType_h_
