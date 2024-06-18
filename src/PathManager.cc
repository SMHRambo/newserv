#include "PathManager.hh"

#include <string.h>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>
#else
#endif // else not __APPLE__
#include <filesystem>

#include <phosg/Arguments.hh>

using namespace std;

PathManager::PathManager() {
    string AppPath;
    
#ifdef __APPLE__
  char buf [PATH_MAX];
  uint32_t bufsize = PATH_MAX;
  if(!_NSGetExecutablePath(buf, &bufsize))
    AppPath = canonical(std::filesystem::path(buf)).parent_path();
#else
    AppPath = canonical(std::filesystem::path("/proc/self/exe")).parent_path();
#endif // else not __APPLE__
    
    SystemPath = AppPath + "/system/";
    ConfigPath = SystemPath + "config.json";
}

string PathManager::getSystemPath() {
    return SystemPath;
}

string PathManager::getConfigPath() {
    return ConfigPath;
}

void PathManager::setPath(Arguments& args) {
    setSystemPath(args);
    setConfigPath(args);
}

void PathManager::setSystemPath(Arguments& args) {
    string system_path = args.get<string>("system");
    if(!system_path.empty()) {
        SystemPath = system_path;
    }
}

void PathManager::setConfigPath(Arguments& args) {
    string config_path = args.get<string>("config");
    if(!config_path.empty()) {
        ConfigPath = config_path;
    }
}
