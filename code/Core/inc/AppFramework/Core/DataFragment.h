
/// File: DataFragment.h
/// Author : Manthan R. Tilva
/// Date : 30/07/2018
/// Brief : Declaration to DataFragment class

#ifndef AppFramework_Core_DataFragment_h_
#define AppFramework_Core_DataFragment_h_

#include <cstdint>
#include <memory>

namespace AppFramework {
namespace Core {
template <typename T>
class DataFragment : public std::enable_shared_from_this<DataFragment<T>>{
  DataFragment() {};
public:
  using element_type = T;
  static std::shared_ptr<DataFragment<T>> create();
  // DataFragment();
  // ~DataFragment();
  void updateData(T *pData);
  void updateData(T oData);
  void updateData(std::shared_ptr<T> pData);
  std::shared_ptr<T> getData();

private:
  std::shared_ptr<T> mSPtrData{nullptr};
};
template <typename T>
std::shared_ptr<DataFragment<T>> DataFragment<T>::create() {
  return std::shared_ptr<DataFragment<T>>(new DataFragment<T>());
  // auto p = new DataFragment<T>();
  // std::shared_ptr<DataFragment<T>> tt = std::shared_ptr<DataFragment<T>>(p);
  // return nullptr;
}
template <typename T>
void DataFragment<T>::updateData(T *pData) {
  mSPtrData = std::shared_ptr<T>(pData);
  pData = nullptr;
}
template <typename T>
void DataFragment<T>::updateData(T oData) {
  mSPtrData = std::make_shared<T>(std::move(oData));
  // pData = nullptr;
}
template <typename T>
void DataFragment<T>::updateData(std::shared_ptr<T> pData) {
  mSPtrData = pData;
}
template <typename T>
std::shared_ptr<T> DataFragment<T>::getData() {
  return mSPtrData;
}
} // namespace Core
} // namespace AppFramework

#endif // AppFramework_Core_DataFragment_h_
