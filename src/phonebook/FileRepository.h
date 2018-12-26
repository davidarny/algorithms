#ifndef ALGORITHMS_FILEREPOSITORY_H
#define ALGORITHMS_FILEREPOSITORY_H

#include <string>

class FileRepository {
private:
    static std::string mMasterFilePath;
    static std::string mSlaveFilePath;

public:
    static void overrideMasterFilePath(const std::string& path);

    static void overrideSlaveFilePath(const std::string& path);

    static std::string getMasterFilePath();

    static std::string getSlaveFilePath();
};

#endif //ALGORITHMS_FILEREPOSITORY_H
