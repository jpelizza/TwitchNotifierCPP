#include <iostream>
#include <unistd.h>
#include <thread>
#include "../include/FileManager.hpp"
#include "../include/ConnectionManager.hpp"
#include "../include/TrayNoti.hpp"
#include "../include/BackLoop.hpp"

int main(int argc, char *argv[]){

    QApplication app (argc, argv);

    TrayNoti *tn = new TrayNoti("/home/mechakitty/.ICATNotifier/imgs/");
    BackLoop *backThread = new BackLoop(tn);
    backThread->start();

    if(tn==NULL){
        std::cout << "There was a problem creating a trayIcon\n";
    }

    return app.exec();
    
}
