#ifndef PLAYABLE_H
#define PLAYABLE_H

// Interface for playable media types
class Playable {
public:
    virtual ~Playable() = default;
    // Marker interface, actual playback behavior simulated via MediaObject::display()
};

#endif // PLAYABLE_H
