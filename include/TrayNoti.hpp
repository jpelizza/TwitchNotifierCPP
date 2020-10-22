#ifndef TRAYNOTIFIER
#define TRAYNOTIFIER

//Qt5 includes
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QSystemTrayIcon>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QActionGroup>
#include <qt5/QtWidgets/QMessageBox>
#include <qt5/QtCore/QSize>
#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QTimer>
#include <qt5/QtCore/QSignalMapper>
#include <qt5/QtGui/QWindow>
#include <qt5/QtGui/QScreen>
#include <qt5/QtGui/QIcon>


//regular includes
#include <string>
#include <iostream>
#include <vector>
#include "Structs.hpp"

class TrayNoti : public QObject{

    private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayContextMenu;
    QTimer *timer;
    QIcon *icon;
    std::vector<QAction*> actionVec;
    
    void setTrayIcon(std::string path);
    int screenX, screenY;
    int dataN = 1;


    public:
    std::string iconPath = "18.png";
    std::string gayness[5] = {"Default","L","G","B","T"};
    std::string states[11] = {"common","1","2","3","4","5","6","7","8","9","+"};
    int gaynessPoint = 0;
    int NotiPoint = 4;
    std::string auxString;
    int state = 0;
    TrayNoti(int screenX, int screenY);
    TrayNoti(std::string iconPath);
    void addToActionList(std::vector<struct liveChannelInfo> lciVec);
    void addToMenu();
    void cleanMenu(std::vector<struct liveChannelInfo> lciVec);
    void checkNotifications();
    static void trayOpenLink(std::string chanName);
    void notiIcon();
    void changeIcon(int newIconState);
    void loop();
    void changeIconPath();
    void setIconState(int newIconState);
    std::vector<QAction*> getActionVec();
};

#endif
//TRAYNOTIFIER