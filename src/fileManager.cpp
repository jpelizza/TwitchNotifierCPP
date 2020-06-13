#include "../include/fileManager.hpp"

void fileManager::startup(){
    createFolder();
    createFiles();
    return;
}

void fileManager::createFolder(){
    mkdir(this->path.c_str(),0777);
    mkdir((this->path + "imgs").c_str(),0777);
    return;
}

void fileManager::createFiles(){
    std::string fileName[3] = {"Account.txt","Follows.txt","AccountFollows.txt"};
    std::fstream file;
    std::ifstream fileExists;
    for (unsigned long i=0;i<sizeof(fileName)/sizeof(fileName[0]);i++){
        fileExists.open(path + fileName[i]);
        if(!fileExists.good()){
            file.open(path + fileName[i],std::fstream::out);
            file.close();
        }
    }
    return;
}

std::string fileManager::getOauth(){
    std::string line;
    std::ifstream account((this->path)+"Account.txt");
    std::getline(account,line);
    /*TODO
    ADD CHAR COUNT TO CHECK IF VALID AOUTH RIGHT AWAY*/
    if(line == "") {
        std::cout << "getOauth error, file blank\n";
    }
    return line;
}
