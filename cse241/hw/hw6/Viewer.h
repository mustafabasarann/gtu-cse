#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>
#include "Observer.h"
#include "MediaObject.h"

// Viewer observes dataset and maintains a view list of non-playable objects
class Viewer : public Observer {
private:
    std::string name;                  // Identifier for this viewer
    std::vector<MediaObject*> viewList; // List of non-playable items
    int currentIndex;                  // Index of currently viewing item

public:
    // Constructor sets viewer name and initializes index
    Viewer(const std::string& n);

    // Called by Dataset when a media object is added/removed
    void update(MediaObject* obj, bool added) override;

    // Display all items in the view list
    void show_list() const;

    // Return pointer to current media object; nullptr if empty
    MediaObject* currently_viewing() const;

    // Move to next item; if type specified, skip to next of that type
    void next(const std::string& type = "");

    // Move to previous item; if type specified, skip to previous of that type
    void previous(const std::string& type = "");
};

#endif // VIEWER_H
