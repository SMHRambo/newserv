#include <string>

#include <phosg/Arguments.hh>

class PathManager {
    public:
        static std::shared_ptr<PathManager> getInstance() {
            static std::shared_ptr<PathManager> instance{new PathManager};
            return instance;
        }

        void setPath(Arguments& args);
        std::string getSystemPath();
        std::string getConfigPath();
        void setSystemPath(Arguments& args);
        void setConfigPath(Arguments& args);

    private:
        std::string SystemPath;
        std::string ConfigPath;

    private:
        PathManager();

    public:
        PathManager(PathManager const&)     = delete;
        void operator=(PathManager const&)  = delete;
};
