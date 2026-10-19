// A chat server.
#pragma once
#include <memory>
#include <string>
#include <vector>

class User {
public:
    explicit User(std::string name) : name_(std::move(name)) {}
private:
    std::string name_;
};
class Message {
public:
    Message(const User& from, std::string text) : from_(&from), text_(std::move(text)) {}
private:
    const User* from_;
    std::string text_;
};
class Room {
public:
    void join(const User& u) { members_.push_back(&u); }
    void post(const User& u, std::string text) { messages_.emplace_back(u, std::move(text)); }
private:
    std::vector<const User*> members_;
    std::vector<Message> messages_;
};
class Connection {
public:
    explicit Connection(const User& user) : user_(&user) {}
private:
    const User* user_;
};
class Server {
public:
    Room& open_room() { rooms_.emplace_back(); return rooms_.back(); }
    void accept(const User& u) { connections_.push_back(std::make_unique<Connection>(u)); }
private:
    std::vector<Room> rooms_;
    std::vector<std::unique_ptr<Connection>> connections_;
};
