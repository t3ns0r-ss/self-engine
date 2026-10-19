// A podcast app. The member declarations say who owns what.
#pragma once
#include <memory>
#include <string>
#include <vector>

class Episode {
public:
    explicit Episode(std::string title) : title_(std::move(title)) {}
    const std::string& title() const { return title_; }
private:
    std::string title_;
};
class Library {
public:
    const Episode& add(std::string title) { episodes_.push_back(std::make_unique<Episode>(std::move(title))); return *episodes_.back(); }
private:
    std::vector<std::unique_ptr<Episode>> episodes_;
};
class Playlist {
public:
    void queue(const Episode& e) { queue_.push_back(&e); }
    std::size_t size() const { return queue_.size(); }
private:
    std::vector<const Episode*> queue_;
};
class Speaker {
public:
    void play(const std::string&) {}
};
class Player {
public:
    explicit Player(const Playlist& playlist) : playlist_(&playlist) {}
private:
    Speaker speaker_;
    const Playlist* playlist_;
};
class App {
public:
    App() : player_(playlist_) {}
private:
    Library library_;
    Playlist playlist_;
    Player player_;
};
