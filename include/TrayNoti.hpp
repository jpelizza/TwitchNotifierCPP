#ifndef TRAYNOTIFIER
#define TRAYNOTIFIER

//arch
#include <qt/QtWidgets/QApplication>
#include <qt/QtWidgets/QPushButton>
#include <qt/QtWidgets/QSystemTrayIcon>
#include <qt/QtWidgets/QMenu>
#include <qt/QtWidgets/QActionGroup>
#include <qt/QtWidgets/QMessageBox>
#include <qt/QtCore/QSize>
#include <qt/QtCore/QObject>
#include <qt/QtCore/QTimer>
#include <qt/QtCore/QSignalMapper>
#include <qt/QtGui/QWindow>
#include <qt/QtGui/QScreen>
#include <qt/QtGui/QIcon>

//Qt5 includes
/*
debian
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
*/
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
    std::string iconPath;
    std::string color[6] = {"W","D","L","G","B","T"};
    std::string states[11] = {"common","1","2","3","4","5","6","7","8","9","plus"};
    int notiColor = 1;
    int notiPoint = 0;
    int state = 10;
    std::string auxString;
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
    int getTrayContextMenuActionsListSize();
};

#endif
//TRAYNOTIFIER