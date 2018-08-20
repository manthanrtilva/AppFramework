/// File: Application.h
/// Author : Manthan R. Tilva
/// Date : 08/08/2018
/// Brief :

#ifndef AppFramework_Core_Application_h_
#define AppFramework_Core_Application_h_

#include <memory>

namespace AppFramework {
namespace Core {
class Application : public std::enable_shared_from_this<Application>{
  Application(int argc,char** argv);
public:
  static std::shared_ptr<Application> getInstance();
  ~Application();
  virtual bool configure() = 0;
  virtual void run() = 0;
protected:
};
inline std::shared_ptr<Application> getInstance() {

}
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_Application_h_
