#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Observer.h"
#include "MediaObject.h"

// Player observes dataset and maintains a playlist of playable objects
class Player : public Observer {
private:
    std::string name;                 // Identifier for this player
    std::vector<MediaObject*> playList; // List of playable items
    int currentIndex;                 // Index of currently playing item

public:
    // Constructor sets player name and initializes index
    Player(const std::string& n);

    // Called by Dataset when a media object is added/removed
    void update(MediaObject* obj, bool added) override;

    // Display all items in the playlist
    void show_list() const;

    // Return pointer to current media object; nullptr if empty
    MediaObject* currently_playing() const;

    // Move to next item; if type specified, skip to next of that type
    void next(const std::string& type = "");

    // Move to previous item; if type specified, skip to previous of that type
    void previous(const std::string& type = "");
};

#endif // PLAYER_H
