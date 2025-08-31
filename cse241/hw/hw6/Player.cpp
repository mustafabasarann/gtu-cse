#include "Player.h"
#include <iostream>

// Constructor: initialize name and set current index to 0
Player::Player(const std::string& n) : name(n), currentIndex(0) {}

// Update playlist when a playable media object is added or removed
void Player::update(MediaObject* obj, bool added) {
    if (obj->isPlayable()) {
        if (added) {
            // Add new playable object to playlist
            playList.push_back(obj);
        } else {
            // Remove the object if found
            for (auto it = playList.begin(); it != playList.end(); ++it) {
                if (*it == obj) {
                    int idx = it - playList.begin();
                    playList.erase(it);
                    // Adjust currentIndex if necessary
                    if (idx <= currentIndex && currentIndex > 0) {
                        currentIndex--;
                    }
                    break;
                }
            }
        }
    }
}

// Display the playlist content
void Player::show_list() const {
    std::cout << "Player [" << name << "] PlayList:" << std::endl;
    for (auto* obj : playList) {
        std::cout << "- " << obj->getName() << " (" << obj->getType() << ")" << std::endl;
    }
}

// Return currently selected media object
MediaObject* Player::currently_playing() const {
    if (playList.empty()) {
        return nullptr; // No items
    }
    if (currentIndex < 0 || currentIndex >= static_cast<int>(playList.size())) {
        return nullptr; // Invalid index
    }
    return playList[currentIndex];
}

// Advance to the next item; optionally filter by type ("audio"/"video")
void Player::next(const std::string& type) {
    if (playList.empty()) return; // Nothing to advance

    int start = currentIndex + 1;
    int n = playList.size();
    for (int i = 0; i < n; ++i) {
        int idx = (start + i) % n;
        if (type.empty() || playList[idx]->getType() == type) {
            currentIndex = idx;
            return;
        }
    }
}

// Move to the previous item; optionally filter by type
void Player::previous(const std::string& type) {
    if (playList.empty()) return; // Nothing to move

    int n = playList.size();
    for (int i = 1; i <= n; ++i) {
        int idx = (currentIndex - i + n) % n;
        if (type.empty() || playList[idx]->getType() == type) {
            currentIndex = idx;
            return;
        }
    }
}
