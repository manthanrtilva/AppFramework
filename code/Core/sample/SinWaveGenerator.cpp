#include "AppFramework/Core/Component.h"
#include "AppFramework/Core/DataFragment.h"
#include "AppFramework/Core/Socket.h"
#include "SinWaveData.h"

#include <boost/dll/alias.hpp>

#include <cmath>
const double PI = std::acos(-1);

using AppFramework::Core::Component;

class SinWaveGenerator : public Component {
public:
  SinWaveGenerator(const std::string &str) : Component(str) {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl;
    addProperty<double>("maxValue", 5.0);
    addProperty<double>("minValue", -5.0);
    addProperty<double>("period", 10.0);
    addProperty<std::uint32_t>("pollInterval", 1000);
  }
  ~SinWaveGenerator() { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }

protected:
  virtual void doConfigureImpl() override {
    std::cout << __LINE__ << ":" << __FUNC__ << std::endl;
    mUint32PollInterval = getProperty<std::uint32_t>("pollInterval");
    mMetaData.mMaxValue = getProperty<double>("maxValue");
    mMetaData.mMinValue = getProperty<double>("minValue");
    mMetaData.mPeriod = getProperty<double>("period");
    mFMidPoint = (mMetaData.mMaxValue + mMetaData.mMinValue) / 2;
    mFHalfHeight = (mMetaData.mMaxValue - mMetaData.mMinValue) / 2;
    mFMultiplier = 2 * PI / (mMetaData.mPeriod);
    pWPtrSinData = addSocket("SinWaveData",1,AppFramework::Core::Socket::Direction::OUT_DIRECTION);
  }
  virtual void doRunImpl() override {
    if(auto pSPtr = pWPtrSinData.lock()){
      auto metaDataFrag = AppFramework::Core::DataFragment<MetaData>::create();
      metaDataFrag->updateData(mMetaData);
      pSPtr->sendData<MetaData>(metaDataFrag);
    }
    auto sinDataFrag = AppFramework::Core::DataFragment<double>::create();
    while (getState() == Component::State::RUN) {
      auto t = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
      mFCurrentValue = mFMidPoint + mFHalfHeight * std::sin(mFMultiplier * t);
      // std::cout << t << "\t" << mFCurrentValue << std::endl;
      if(auto pSPtr = pWPtrSinData.lock()){
        sinDataFrag->updateData(mFCurrentValue);
        pSPtr->sendData<double>(sinDataFrag);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(mUint32PollInterval));
    }
  }
  virtual void doStopImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }

private:
  std::uint32_t mUint32PollInterval;
  MetaData mMetaData;
  double mFMaxValue;
  double mFMinValue;
  double mFPeriod;
  double mFMidPoint;
  double mFHalfHeight;
  double mFCurrentValue;
  double mFMultiplier;
  std::weak_ptr<AppFramework::Core::Socket> pWPtrSinData = std::weak_ptr<AppFramework::Core::Socket>();
};

BOOST_DLL_ALIAS(AppFramework::Core::identity(Component::create<SinWaveGenerator>), create_component)
