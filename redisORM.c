/*
 *  redisORM.c
 *
 *  Implements the interface for the redis ORM
 *
 *  Created by Ryan Faulkner on 2015-06-13
 */

#include "redisORM.h"

using namespace std;

/** Establishes a connection to a redis instance */
void RedisHandler::connect() { this->context = redisConnect(REDISHOST, REDISPORT); }

/** Writes a key value to redis */
void RedisHandler::write(std::string key, std::string value) {
    redisCommand(this->context, "SET %s %s", key.c_str(), value.c_str());
}

/** Writes a value to redis hash map */
void RedisHandler::writeHashMap(std::string key, std::string hash, std::string value) {
    redisCommand(this->context, "HSET %s %s %s", key.c_str(), hash.c_str(), value.c_str());
}

/** Writes a value to redis hash map */
void RedisHandler::incrementHashMap(std::string key, std::string hash, int value) {
    redisCommand(this->context, "HINCRBY %s %s %s", key.c_str(), hash.c_str(), std::to_string(value).c_str());
}

/** Writes a value to redis hash map */
void RedisHandler::incrementKey(std::string key, int value) {
    redisCommand(this->context, "INCRBY %s %s", key.c_str(), std::to_string(value).c_str());
}

/** Writes a value to redis hash map */
void RedisHandler::decrementKey(std::string key, int value) {
    redisCommand(this->context, "DECRBY %s %s", key.c_str(), std::to_string(value).c_str());
}

/** Read a value from redis given a key */
std::string RedisHandler::read(std::string key) {
    std::string result;
    redisReply *reply = (redisReply*)redisCommand(this->context, "GET %s", key.c_str());
    result = reply->str;
    freeReplyObject(reply);
    return result;
}

/** Read a value from redis given a key */
std::string RedisHandler::readHashMap(std::string key, std::string hash) {
    std::string result;
    redisReply *reply = (redisReply*)redisCommand(this->context, "HGET %s %s", key.c_str(), hash.c_str());
    result = reply->str;
    freeReplyObject(reply);
    return result;
}

/** Read a value from redis given a key */
void RedisHandler::deleteKey(std::string key) {
    std::string result;
    (redisReply*)redisCommand(this->context, "DEL %s", key.c_str());
}

/** Read a value from redis given a key */
bool RedisHandler::exists(std::string key) {
    int result;
    redisReply *reply = (redisReply*)redisCommand(this->context, "EXISTS %s", key.c_str());
    result = reply->integer;
    freeReplyObject(reply);
    return result == 1;
}

/** Read a value from redis given a key pattern */
std::vector<std::string> RedisHandler::keys(std::string pattern) {
    std::vector<string> elems;
    redisReply *reply = (redisReply*)redisCommand(this->context, "KEYS %s", pattern.c_str());

    // Determine if the reply is an array and iterate through elems if so
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (int j = 0; j < reply->elements; j++) {
            elems.push_back(reply->element[j]->str);
        }
    }
    freeReplyObject(reply);
    return elems;
}
