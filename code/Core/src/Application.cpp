/// File: Application.cpp
/// Author : Manthan R. Tilva
/// Date : 08/08/2018
/// Brief :

namespace AppFramework {
namespace Core {
Application::Application(int argc, char **argv) {}
std::shared_ptr<Application> Application::getInstance(int argc=0,char** argv=nullptr) {
  std::shared_ptr<Application> staticSPtrApp;
  if(staticSPtrApp == nullptr){
    if(argv == 0 && argv == nullptr){
      std::runtime_error("Application not created yet.");
    }
    staticSPtrApp = std::make_shared<Application>(argc,argv);
  }
  return staticSPtrApp;
}
Application::~Application() {}
void Application::run() {}
} // namespace Core
} // namespace AppFramework
