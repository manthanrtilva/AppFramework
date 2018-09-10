
#include "AppFramework/Core/Component.h"

#include <boost/config.hpp>
#include <boost/dll/alias.hpp>

using AppFramework::Core::Component;
#define __FUNC__ __FUNCTION__

class Comp1 : public Component {
public:
  Comp1(const std::string &str) : Component(str) {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl;
  }
  ~Comp1(){
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl;
  }
protected:
  virtual void doConfigureImpl() override {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl;
  }
  virtual void doRunImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }
  virtual void doStopImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }
};

BOOST_DLL_ALIAS(
    AppFramework::Core::identity(Component::create<Comp1>),
    create_component
)
