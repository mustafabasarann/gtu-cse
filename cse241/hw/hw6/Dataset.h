#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include "MediaObject.h"
#include "Observer.h"

// Dataset holds all media objects and notifies observers upon changes
class Dataset {
private:
    std::vector<MediaObject*> items;   // Stored media objects
    std::vector<Observer*> observers;  // Registered observers

public:
    // Constructor & Destructor
    Dataset();
    ~Dataset();

    // Add a media object to dataset and notify observers
    void add(MediaObject* obj);

    // Remove a media object from dataset and notify observers
    void remove(MediaObject* obj);

    // Register an observer; also immediately notifies with existing items
    void registerObserver(Observer* obs);

    // Unregister an observer; no further updates will be sent
    void unregisterObserver(Observer* obs);

private:
    // Internal helper to notify all observers of addition/removal
    void notify(MediaObject* obj, bool added);
};

#endif // DATASET_H
