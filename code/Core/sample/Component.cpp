

#include "AppFramework/Core/Component.h"

#include <string>
#define __FUNC__ __FUNCTION__
int main(int argc, char const *argv[]) {
  using AppFramework::Core::Component;
  class Comp1 : public Component {
  public:
    Comp1(const std::string &str) : Component(str) {}

  protected:
    virtual void doConfigureImpl() override {
      std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl;
    }
    virtual void doRunImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }
    virtual void doStopImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNC__ << std::endl; }
  };
  std::string str;
  class cc {

  };
  auto oComp1 = Component::create<Comp1>("");
  oComp1->setState(Component::State::CONFIGURE);
  oComp1->setState(Component::State::RUN);
  oComp1->setState(Component::State::STOP);
  return 0;
}
