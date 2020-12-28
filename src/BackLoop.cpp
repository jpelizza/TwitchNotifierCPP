#include "../include/BackLoop.hpp"


BackLoop::BackLoop(TrayNoti *tn){
    this->tn = tn;
}

void BackLoop::run(){
    FileManager fm;
    fm.startup();
    ConnectionManager cm(fm.getOauth(),fm.path);
    std::cout << std::endl;
    cm.downloadFollowsProfileImages();
    while(true){
        cm.updateFollowers();
        cm.updateLiveChannels();
        tn->addToActionList(cm.liveChannel);

        tn->addToMenu();
        
        
        sleep(3);
        tn->cleanMenu(cm.liveChannel);
    }
}