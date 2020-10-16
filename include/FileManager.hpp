#ifndef FILEMANAGER
#define FILEMANAGER

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

class FileManager{
    public:
    //to do use std::string(getlogin()), por algum motivo bugado, olhar com calma
    std::string path = "/home/mechakitty/.ICATNotifier/";

    void startup();
    void createFolder();
    void createFiles();
    std::string getOauth();
};

#endif