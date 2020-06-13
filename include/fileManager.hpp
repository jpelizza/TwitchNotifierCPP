#ifndef FILEMANAGER
#define FILEMANAGER

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

class fileManager{
    public:
    std::string path = "/home/" + std::string(getlogin()) + "/.ICATNotifier/";

    void startup();
    void createFolder();
    void createFiles();
    std::string getOauth();
};

#endif