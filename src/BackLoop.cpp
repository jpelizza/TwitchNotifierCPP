#include "../include/BackLoop.hpp"


BackLoop::BackLoop(TrayNoti *tn){
    this->tn = tn;
}

void BackLoop::run(){
    FileManager fm;
    fm.startup();
    ConnectionManager cm(fm.getOauth(),fm.path);
    cm.downloadFollowsProfileImages();
    while(true){
        cm.updateFollowers();
        cm.updateLiveChannels();
        tn->addToActionList(cm.liveChannel);
        tn->addToMenu();
        /*TrayIcon AddToActionList*/
        /*TrayIcon AddToMenu*/
        //Depricated cm.updateToNotify();
        sleep(5);
        tn->cleanMenu(cm.liveChannel);
    }
}