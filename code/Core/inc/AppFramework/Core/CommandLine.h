/// File: CommandLine.h
/// Author : Manthan R. Tilva
/// Date : 08/08/2018
/// Brief :

#ifndef AppFramework_Core_CommandLine_h_
#define AppFramework_Core_CommandLine_h_

#include <memory>
#include <string>
#include <unordered_map>

#include "AppFramework/Core/Socket.h"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace AppFramework {
namespace Core {
class CommandLine {
  class ArgBase {
  public:
    ArgBase(const std::string &arg, const std::string &description, bool hasVaule, bool isRequired, bool hasDefault)
        : mStrArgName{arg}, mStrArgDesc{description}, mBHasValue{hasVaule}, mBIsRequired{isRequired}, mBHasDefault{
                                                                                                          hasDefault} {}
    const std::string mStrArgName;
    const std::string mStrArgDesc;
    bool mBHasValue;
    const bool mBIsRequired;
    const bool mBHasDefault;
    bool mBIsHandled{false};
    virtual void parse(const std::string& strValue) = 0;
    virtual std::string print_value() const = 0;
  };
  template <typename T>
  class ArgumentWithValue : public ArgBase {
  public:
    ArgumentWithValue(const std::string &arg, const std::string &description, bool isRequired, bool hasDefault)
        : ArgBase(arg, description, true, isRequired, hasDefault) {
          if(std::is_same<T,bool>::value){
            mBHasValue = false;
          }
        }
    T oValue = T();
    virtual void parse(const std::string& strValue) {
      oValue = CommandLine::parse(strValue,oValue);
    }
    virtual std::string print_value() const override { return ""; }
    std::function<void(const std::string &arg, const T &value)> mOCallback;
  };

public:
  CommandLine(int argc, char **argv) : mStrAppName{argv[0]} {
    for (int index = 1; index < argc; ++index) {
      mVecArgumnet.push_back(argv[index]);
    }
    addHelp();
  }
  template <typename T>
  void addRequired(const std::string &name, const std::string &description) {
      auto &arg = std::unique_ptr<ArgumentWithValue<T>>(new ArgumentWithValue<T>(name, description, true, false));
      mMapStrUPtrBase["-" + name] = std::unique_ptr<ArgBase>(std::move(arg));
  }
  template <typename T>
  void addOptional(const std::string &name, const std::string &description) {
      auto &arg = std::unique_ptr<ArgumentWithValue<T>>(new ArgumentWithValue<T>(name, description, false, false));
      mMapStrUPtrBase["-" + name] = std::unique_ptr<ArgBase>(std::move(arg));
  }
  template <typename T>
  void addDefault(const std::string &name, const std::string &description,const T& value) {
      auto &arg = std::unique_ptr<ArgumentWithValue<T>>(new ArgumentWithValue<T>(name, description, false, false));
      arg->oValue = value;
      mMapStrUPtrBase["-" + name] = std::unique_ptr<ArgBase>(std::move(arg));
  }
  template<typename T>
  T get(const std::string& name){
    for (auto &base : mMapStrUPtrBase) {
      if (base.second->mStrArgName.compare(name) == 0) {
        auto cmd = dynamic_cast<ArgumentWithValue<T> *>(base.second.get());
        return cmd->oValue;
      }
    }
    std::runtime_error("Invalid argument:"+name);
  }
  bool run() {
    for (std::size_t index = 0; index < mVecArgumnet.size(); ++index) {
      const auto &arg = mVecArgumnet[index];
      auto &cmdBase = mMapStrUPtrBase.find(arg);
      if (cmdBase != std::end(mMapStrUPtrBase)) {
        if(!cmdBase->second->mBHasValue){
          cmdBase->second->parse("");
        }
        else {
          if (index + 1 >= mVecArgumnet.size() || mVecArgumnet[index + 1].compare(0, 1, "-") == 0) {
            throw std::runtime_error("Argument '" + cmdBase->second->mStrArgName + "' required value");
          }
          else {
            cmdBase->second->parse(mVecArgumnet[index + 1]);
            ++index;
          }
        }
        cmdBase->second->mBIsHandled = true;
      } else {
        throw std::runtime_error("Invalid argument '" + arg + "'");
      }
    }
    for (const auto &base : mMapStrUPtrBase) {
      if (base.second->mBIsHandled == false && base.second->mBIsRequired == true) {
        throw std::runtime_error(base.second->mStrArgName + " is required but not provided");
      }
    }
    return true;
  }

private:
  static int parse(const std::string& strValue,const int& value){
    return std::stoi(strValue);
  }
  static double parse(const std::string& strValue,const double& value){
    return std::stod(strValue);
  }
  static long double parse(const std::string& strValue,const long double& value){
    return std::stold(strValue);
  }
  static float parse(const std::string& strValue,const float& value){
    return std::stof(strValue);
  }
  static bool parse(const std::string& strValue,const bool& value){
    return true;
  }
  void addHelp() {
    const auto &it = std::find_if(std::begin(mMapStrUPtrBase), std::end(mMapStrUPtrBase),
                                  [](decltype(mMapStrUPtrBase)::const_reference ref) {
                                    if (ref.second->mStrArgName.compare("h") == 0)
                                      return true;
                                    return false;
                                  });
    if (it == std::end(mMapStrUPtrBase)) {
      auto &arg = std::unique_ptr<ArgumentWithValue<bool>>(new ArgumentWithValue<bool>("h", "print this help", false, false));
      arg->mOCallback = [this](const std::string &name,const bool &value) {
        usage();
        std::exit(0);
      };
      mMapStrUPtrBase["-h"] = std::unique_ptr<ArgBase>(std::move(arg));
    }
  }
  void usage() {
    std::cout << mStrAppName << " usage:" << std::endl;
    for (const auto &arg : mMapStrUPtrBase) {
      std::cout << "\t-" << arg.second->mStrArgName << "\t: " << arg.second->mStrArgDesc;
      if (arg.second->mBIsRequired) {
        std::cout << " [Required] ";
      } else {
        std::cout << " [Optional] ";
      }
      if (arg.second->mBHasDefault) {
        std::cout << " [Default:"
                  << "] ";
      }
      std::cout << std::endl;
    }
  }
private:
  const std::string mStrAppName;
  std::vector<std::string> mVecArgumnet;
  std::map<std::string, std::unique_ptr<ArgBase>> mMapStrUPtrBase;
};
} // namespace Core
} // namespace AppFramework
#endif // AppFramework_Core_CommandLine_h_
