/*
 *  main.c
 *
 *  Handles the interface to redis
 *
 *  Created by Ryan Faulkner on 2015-06-13
 */

#ifdef _redisorm_h_
#define _redirsorm_h_

#include <iostream>
#include <string>
#include <vector>

#include "hiredis/hiredis.h"

#define REDISHOST "127.0.0.1"
#define REDISPORT 6379
#define REDISDB "myredisdb"


using namespace std;


/**
 *  Defines interface to redis server
 */
class RedisHandler {

    std::string host;
    int port;

    redisContext *context;

public:
    RedisHandler() { this->host = REDISHOST; this->port = REDISPORT; }
    RedisHandler(std::string host, int port) { this->host = host; this->port = port; }

    void connect();

    void write(std::string, std::string);
    void writeHashMap(std::string, std::string, std::string);
    void incrementHashMap(std::string, std::string, int);
    void incrementKey(std::string, int);
    void decrementKey(std::string, int);
    void deleteKey(std::string);

    bool exists(std::string);

    std::string read(std::string);
    std::string readHashMap(std::string, std::string);
    std::vector<std::string> keys(std::string);
};

#endif

