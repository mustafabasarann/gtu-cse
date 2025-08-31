#include "Viewer.h"
#include <iostream>

// Constructor: initialize name and set current index to 0
Viewer::Viewer(const std::string& n) : name(n), currentIndex(0) {}

// Update view list when a non-playable media object is added or removed
void Viewer::update(MediaObject* obj, bool added) {
    if (!obj->isPlayable()) {
        if (added) {
            // Add new non-playable object to view list
            viewList.push_back(obj);
        } else {
            // Remove the object if found
            for (auto it = viewList.begin(); it != viewList.end(); ++it) {
                if (*it == obj) {
                    int idx = it - viewList.begin();
                    viewList.erase(it);
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

// Display the view list content
void Viewer::show_list() const {
    std::cout << "Viewer [" << name << "] ViewList:" << std::endl;
    for (auto* obj : viewList) {
        std::cout << "- " << obj->getName() << " (" << obj->getType() << ")" << std::endl;
    }
}

// Return currently selected media object
MediaObject* Viewer::currently_viewing() const {
    if (viewList.empty()) {
        return nullptr; // No items
    }
    if (currentIndex < 0 || currentIndex >= static_cast<int>(viewList.size())) {
        return nullptr; // Invalid index
    }
    return viewList[currentIndex];
}

// Advance to the next item; optionally filter by type ("text"/"image")
void Viewer::next(const std::string& type) {
    if (viewList.empty()) return; // Nothing to advance

    int start = currentIndex + 1;
    int n = viewList.size();
    for (int i = 0; i < n; ++i) {
        int idx = (start + i) % n;
        if (type.empty() || viewList[idx]->getType() == type) {
            currentIndex = idx;
            return;
        }
    }
}

// Move to the previous item; optionally filter by type
void Viewer::previous(const std::string& type) {
    if (viewList.empty()) return; // Nothing to move

    int n = viewList.size();
    for (int i = 1; i <= n; ++i) {
        int idx = (currentIndex - i + n) % n;
        if (type.empty() || viewList[idx]->getType() == type) {
            currentIndex = idx;
            return;
        }
    }
}
