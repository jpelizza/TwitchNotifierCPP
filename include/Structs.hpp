#ifndef STRUCTS
#define STRUCTS

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
struct curlJsonInfoFetchTeam{
    CURL *curl;
    std::string readBuffer;
    Json::CharReaderBuilder rBuilder;
    Json::Value root;
    JSONCPP_STRING errs;
    struct curl_slist* headers;
};

struct liveChannelInfo{
    std::string userName;
    std::string userId;
    std::string gameId;
    std::string startedAt;
    std::string title;
    bool notified = false;
    bool stillStreaming = true;
};

#endif //STRUCTS