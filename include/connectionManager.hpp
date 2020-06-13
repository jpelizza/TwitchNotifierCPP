#ifndef CONNMANAGER
#define CONNMANAGER

#include <iostream>
#include <json/json.h>
#include <curl/curl.h>
#include <vector>
#include <glibmm-2.4/glibmm.h>
#include <giomm-2.4/giomm.h>
#include <fstream>

struct liveChannelInfo{
    std::string userName;
    std::string userId;
    std::string gameId;
    std::string startedAt;
    std::string title;
    bool notified = false;
    bool stillStreaming = true;
};

class connectionManager{
    public:
    std::string imgPath;
    std::string Oauth;
    std::string userID;
    std::string clientID;
    std::vector<std::string> followID;
    std::vector<struct liveChannelInfo> liveChannel;
    std::vector<struct liveChannelInfo> liveChannelNotified;
    

    connectionManager(std::string,std::string);
    void updateClientID();
    void updateFollowers();
    void updateLiveChannels();
    void updateToNotify();
    void notify(struct liveChannelInfo);

    void downloadFollowsProfileImages();
};
#endif

