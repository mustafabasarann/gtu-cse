#ifndef OBSERVER_H
#define OBSERVER_H

#include "MediaObject.h"

// Observer interface for receiving dataset updates
class Observer {
public:
    virtual ~Observer() = default;

    // Update is called when a media object is added or removed.
    // 'added' true => added, false => removed.
    virtual void update(MediaObject* obj, bool added) = 0;
};

#endif // OBSERVER_H
