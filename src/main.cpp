#include <iostream>
#include "../include/fileManager.hpp"
#include "../include/connectionManager.hpp"
#include <unistd.h>

int main(int argc, char *argv[]){
    fileManager fm;
    fm.startup();
    connectionManager cm(fm.getOauth(),fm.path);
    cm.downloadFollowsProfileImages();
    while(true){
        cm.updateFollowers();
        cm.updateLiveChannels();
        cm.updateToNotify();
        sleep(60);
    }
}