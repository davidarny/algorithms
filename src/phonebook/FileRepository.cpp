#include "FileRepository.h"

std::string FileRepository::mMasterFilePath = "master.txt"; // NOLINT(cert-err58-cpp)
std::string FileRepository::mSlaveFilePath = "slave.txt"; // NOLINT(cert-err58-cpp)

std::string FileRepository::getMasterFilePath()
{
    return mMasterFilePath;
}

std::string FileRepository::getSlaveFilePath()
{
    return mSlaveFilePath;
}

void FileRepository::overrideMasterFilePath(const std::string& path)
{
    if (path.empty()) {
        return;
        ;
    }
    std::string copy(path); // NOLINT(performance-unnecessary-copy-initialization)
    mMasterFilePath = copy;
}

void FileRepository::overrideSlaveFilePath(const std::string& path)
{
    if (path.empty()) {
        return;
    }
    std::string copy(path); // NOLINT(performance-unnecessary-copy-initialization)
    mSlaveFilePath = copy;
}
