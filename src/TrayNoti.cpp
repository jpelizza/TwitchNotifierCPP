#include "../include/TrayNoti.hpp"
#include "../include/FileManager.hpp"
#include "../include/ConnectionManager.hpp"

TrayNoti::TrayNoti(int screenX, int screenY){
    this->screenX = screenX;
    this->screenY = screenY;
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    trayIcon        = new QSystemTrayIcon();
    trayContextMenu = new QMenu();
    timer           = new QTimer();
    icon            = new QIcon();

    setTrayIcon(iconPath);
    trayIcon->setContextMenu(trayContextMenu);
}

TrayNoti::TrayNoti(std::string iconPath){
    
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    trayIcon        = new QSystemTrayIcon();
    trayContextMenu = new QMenu();
    timer           = new QTimer();
    icon            = new QIcon();

    std::cout << trayContextMenu->thread() << std::endl;
    setTrayIcon(iconPath);
    this->iconPath = iconPath;
    trayIcon->setContextMenu(trayContextMenu);
}


void TrayNoti::addToActionList(std::vector<struct liveChannelInfo> lciVec){
    QAction *action = new QAction();
    QSignalMapper* signalMapper = new QSignalMapper();

    for(auto vecPointer = lciVec.begin(); vecPointer!=lciVec.end(); vecPointer++){
        action->setIcon(QIcon((iconPath+(*vecPointer).userId+".png").c_str()));
        action->setText((*vecPointer).userName.c_str());
        action->setData(dataN++);
        this->auxString = (*(vecPointer)).userName;
        QObject::connect(action,&QAction::triggered,this,[this](){TrayNoti::trayOpenLink(auxString);});
        actionVec.push_back(action);
        action = new QAction();
    }

}

void TrayNoti::addToMenu(){
    
    for(auto vecPointer = actionVec.begin(); vecPointer != actionVec.end();vecPointer++){
        trayContextMenu->addAction(*(vecPointer));
    }

    std::cout << actionVec.size() << " " << trayContextMenu->actions().count() << std::endl;
    this->actionVec.clear();
}

void TrayNoti::cleanMenu(std::vector<struct liveChannelInfo> lciVec){
    bool aux = false;
    auto trayPointer = trayContextMenu->actions().begin();
    for(int i = 0 ; i<trayContextMenu->actions().size() ; i++,trayPointer++ ){
        for(auto it = lciVec.begin(); it!= lciVec.end(); it++){
            std::cout << trayContextMenu->actions().size()  << std::endl;
            if(!(*it).userName.compare((*trayPointer)->text().toStdString())){
                aux = true;
            }
        }
        if(!aux){
            trayContextMenu->removeAction(trayContextMenu->actions().first());
        }
        aux = false;
    }
}

void TrayNoti::trayOpenLink(std::string chanName){
    system(("midori https://twitch.tv/"+chanName).c_str());
}

void TrayNoti::changeIcon(std::string newIconName){
    QIcon swapIcon;
    swapIcon.addFile(newIconName.c_str(),QSize(22,22));
    trayIcon->setIcon(swapIcon);
}


void TrayNoti::setTrayIcon(std::string path){
    this->icon->addFile("18.png",QSize(22,22));
    trayIcon->setIcon(*icon);
    trayIcon->show();
}

//DEPRICATED

void TrayNoti::checkNotifications(){
    
    QMessageBox* msgbox = new QMessageBox(QMessageBox::NoIcon,NULL,"",
    QMessageBox::StandardButton::NoButton,
    NULL,Qt::Popup | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowDoesNotAcceptFocus);
    msgbox->setStyleSheet("QMessageBox{messagebox-text-interaction-flags: 5}");
    msgbox->setTextInteractionFlags(Qt::NoTextInteraction);
    /*remove "okay" button*/
    //msgbox->setStandardButtons(0);
    //size.scale(screenX,screenY,Qt::KeepAspectRatio);
    QObject::connect(timer, SIGNAL(timeout()), msgbox, SLOT(close()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
    timer->start(2500);

    msgbox->setText("<div align='justified'><div style='display: flex'><img src='39322714.png' width='80' height='80'></div><div align='right'>Suicidio online</div></div>");



    msgbox->move(QPoint(this->screenX -(250),25));
    msgbox->setWindowOpacity(0.90);
    msgbox->setMinimumSize(QSize(600, 600));
    msgbox->raise();
    msgbox->open();
}