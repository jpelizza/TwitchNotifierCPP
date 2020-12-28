#ifndef CONNMANAGER
#define CONNMANAGER

#include <iostream>
#include <sstream>

//#include <jsoncpp/json/json.h>
#include <json/json.h>
#include <curl/curl.h>
#include <vector>
#include <fstream>
#include "Structs.hpp"

class ConnectionManager{
    public:
    std::string imgPath;
    std::string Oauth;
    std::string userID;
    std::string clientID;
    std::vector<std::string> followID;
    std::vector<struct liveChannelInfo> liveChannel;
    std::vector<struct liveChannelInfo> liveChannelNotified;
    

    ConnectionManager(std::string,std::string);
    void updateClientID();
    void updateFollowers();
    void updateLiveChannels();

    void downloadFollowsProfileImages();
};
#endif

