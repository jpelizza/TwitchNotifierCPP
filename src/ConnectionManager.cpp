#include "../include/ConnectionManager.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void cjInit(struct curlJsonInfoFetchTeam* cj){
    cj->headers = NULL;
    cj->curl = curl_easy_init();
}

void cjAct(struct curlJsonInfoFetchTeam* cj, std::vector<std::string> headers, std::string uri){
    for(auto header = headers.begin(); header!=headers.end();header++){
        cj->headers = curl_slist_append(cj->headers, (*header).c_str());
        curl_easy_setopt(cj->curl, CURLOPT_HTTPHEADER, cj->headers);
    }
    curl_easy_setopt(cj->curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(cj->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(cj->curl, CURLOPT_WRITEDATA, &cj->readBuffer);
    curl_easy_perform(cj->curl);
    curl_easy_cleanup(cj->curl);
}

ConnectionManager::ConnectionManager(std::string Oauth, std::string path){
    this->Oauth = Oauth;
    this->imgPath = path + "imgs/";
    this->updateClientID();
    this->updateFollowers();
    this->updateLiveChannels();
};

void ConnectionManager::updateClientID(){
    struct curlJsonInfoFetchTeam *cj = new curlJsonInfoFetchTeam;
    cjInit(cj);
    if(cj->curl) {
        std::vector<std::string> headers;
        headers.emplace_back(("Authorization: OAuth " + this->Oauth).c_str());
        cjAct(cj,headers,"https://id.twitch.tv/oauth2/validate");
        std::stringstream s(cj->readBuffer);
        Json::parseFromStream(cj->rBuilder, s, &cj->root, &cj->errs);
        this->clientID= cj->root.get("client_id",cj->root).asString();
        this->userID = cj->root.get("user_id",cj->root).asString();
        //free memory
        free(cj);
    }
    std::cout << "B\n";

}

void ConnectionManager::updateFollowers(){
    struct curlJsonInfoFetchTeam *cj = new curlJsonInfoFetchTeam;
    cjInit(cj);

    if(cj->curl) {
        std::vector<std::string> headers;
        headers.emplace_back(("Authorization: Bearer " + this->Oauth).c_str());
        headers.emplace_back(("Client-ID: " + this->clientID).c_str());

        cjAct(cj,headers,"https://api.twitch.tv/helix/users/follows?from_id=" + this->userID);

        std::stringstream s(cj->readBuffer);
        Json::parseFromStream(cj->rBuilder, s, &cj->root, &cj->errs);
        Json::Value data = cj->root["data"];
        this->followID.clear();
        for ( unsigned int index = 0; index < data.size(); ++index ) {
            this->followID.push_back( data[index].get("to_id",data[index]).asString() );
        }
        //free memory
        free(cj);
    }
}

void ConnectionManager::updateLiveChannels(){
    struct curlJsonInfoFetchTeam *cj = new curlJsonInfoFetchTeam;
    cjInit(cj);

    if(cj->curl) {
        std::string uri = "https://api.twitch.tv/helix/streams?";
        for(auto index = followID.begin(); index!=followID.end() ;index++){
            uri += ("user_id="+(*index)+"&");
        }
        std::vector<std::string> headers;
        headers.emplace_back(("Authorization: Bearer " + this->Oauth).c_str());
        headers.emplace_back(("Client-ID: " + this->clientID).c_str());

        cjAct(cj,headers, uri);

        struct liveChannelInfo auxInfo;
        std::stringstream s(cj->readBuffer);
        Json::parseFromStream(cj->rBuilder, s, &cj->root, &cj->errs);
        Json::Value data = cj->root["data"];
        int auxInt = 0;
        for(auto it = this->liveChannel.begin(); it!= this->liveChannel.end();it++){
            (*it).stillStreaming = false;
        }

        for ( unsigned int index = 0; index < data.size(); index++ ){
            auxInfo.userName = data[index].get("user_name",data[index]).asString();
            auxInfo.userId = data[index].get("user_id",data[index]).asString();
            auxInfo.gameId = data[index].get("game_id",data[index]).asString();
            auxInfo.title = data[index].get("title",data[index]).asString();
            auxInfo.startedAt = data[index].get("started_at",data[index]).asString();

            auxInt = 0;
            bool auxBool = false;
            for(auto it = this->liveChannel.begin(); it!= this->liveChannel.end();it++,auxInt++){
                if(!(*it).userId.compare(auxInfo.userId)){
                    auxBool = true;
                    (*it).stillStreaming=true;
                    //causing bug?
                    if((*it).startedAt.compare(auxInfo.startedAt)){
                        auxBool = false;
                        this->liveChannel.erase(this->liveChannel.begin()+auxInt);
                        it--;
                    }
                }
            }
            if(!auxBool){
                this->liveChannel.push_back(auxInfo);
            }
        }
        auxInt=0;
        for(auto it = this->liveChannel.begin(); it!= this->liveChannel.end();it++,auxInt++){
            if((*it).stillStreaming==false){
                this->liveChannel.erase(this->liveChannel.begin()+auxInt);
                it--;
            }
        }
    }
}



void ConnectionManager::downloadFollowsProfileImages(){
    std::vector<std::string> imageLinkVector;
    {
        CURL *curl;
        std::string readBuffer;
        Json::CharReaderBuilder rBuilder;
        Json::Value root;
        JSONCPP_STRING errs;
        struct curl_slist* headers = NULL;
        curl = curl_easy_init();
        if(curl) {
            std::string uri = "https://api.twitch.tv/helix/users?";
            for(auto index = followID.begin(); index!=followID.end() ;index++){
                uri += ("id="+(*index)+"&");
            }
            headers = curl_slist_append(headers, ("Authorization: Bearer " + this->Oauth).c_str() );
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            headers = curl_slist_append(headers, ("Client-ID: " + this->clientID).c_str() );
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            std::stringstream s(readBuffer);
            Json::parseFromStream(rBuilder, s, &root, &errs);
            Json::Value data = root["data"];
            for ( unsigned int index = 0; index < data.size(); ++index ){
                imageLinkVector.push_back(data[index].get("profile_image_url",data[index]).asString());
            }
        }
    }
    //image download
    auto index = followID.begin();
    for(std::vector<std::string>::iterator link = imageLinkVector.begin(); link!=imageLinkVector.end();index++,link++)
    {
        CURL *image;
        FILE *fp;
        image = curl_easy_init();
        
        if(image){
            fp = fopen( (this->imgPath + (*index) + ".png").c_str(), "wb");
            if( fp == NULL ) std::cout << "File cannot be opened";
            curl_easy_setopt(image, CURLOPT_URL, (*link).c_str());
            curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
            curl_easy_perform(image);
            curl_easy_cleanup(image);
        }
        fclose(fp);
    }
}
