#include "Dataset.h"

// Constructor
Dataset::Dataset() {}

// Destructor cleans up allocated media objects
Dataset::~Dataset() {
    for (auto* obj : items) {
        delete obj; // Free memory for each media object
    }
}

// Add media object and notify observers
void Dataset::add(MediaObject* obj) {
    items.push_back(obj);
    notify(obj, true);
}

// Remove media object and notify observers
void Dataset::remove(MediaObject* obj) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == obj) {
            items.erase(it);
            notify(obj, false);
            delete obj; // Free memory
            break;
        }
    }
}

// Register observer and immediately send existing items to it
void Dataset::registerObserver(Observer* obs) {
    observers.push_back(obs);
    for (auto* obj : items) {
        obs->update(obj, true); // Send current items as 'added'
    }
}

// Unregister observer; it will no longer receive updates
void Dataset::unregisterObserver(Observer* obs) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == obs) {
            observers.erase(it);
            break;
        }
    }
}

// Notify all observers about addition/removal of a media object
void Dataset::notify(MediaObject* obj, bool added) {
    for (auto* obs : observers) {
        obs->update(obj, added);
    }
}
