#ifndef BACKLOOP
#define BACKLOOP

#include "Structs.hpp"
#include "../include/FileManager.hpp"
#include "../include/ConnectionManager.hpp"
#include "../include/TrayNoti.hpp"
#include <qt5/QtCore/QThread>

class BackLoop : public QThread{
    private:
    
    public:
    TrayNoti *tn;
    void run();
    BackLoop(TrayNoti *tn);
};

#endif