#ifndef MEDIAOBJECT_H
#define MEDIAOBJECT_H

#include <string>
#include <iostream>
#include "Playable.h"
#include "NonPlayable.h"
#include "Visual.h"
#include "NonVisual.h"

// Abstract base class for all media objects
class MediaObject {
protected:
    std::string name;       // Name of the media object
    std::string otherInfo;  // Additional info (e.g., description)

public:
    // Constructor initializes common attributes
    MediaObject(const std::string& n, const std::string& other);
    virtual ~MediaObject() = default;

    // Return the type of media ("text", "image", "audio", "video")
    virtual std::string getType() const = 0;

    // Return true if media is playable (audio/video), false otherwise
    virtual bool isPlayable() const = 0;

    // Display media details (simulated display/playback)
    virtual void display() const = 0;

    // Get the name of the media object
    std::string getName() const;
};

// Text class: non-visual, non-playable
class Text : public MediaObject, public NonPlayable, public NonVisual {
public:
    // Constructor: name and content description
    Text(const std::string& name, const std::string& otherInfo);

    std::string getType() const override; // Returns "text"
    bool isPlayable() const override;      // Non-playable => false
    void display() const override;         // Print text info
};

// Image class: visual, non-playable
class Image : public MediaObject, public NonPlayable, public Visual {
private:
    std::string dimensionInfo; // Dimensions of the image

public:
    // Constructor: name, dimensions, and description
    Image(const std::string& name, const std::string& dimensionInfo, const std::string& otherInfo);

    std::string getType() const override; // Returns "image"
    bool isPlayable() const override;      // Non-playable => false
    void display() const override;         // Print image info
};

// Audio class: non-visual, playable
class Audio : public MediaObject, public Playable, public NonVisual {
private:
    std::string duration; // Duration of the audio clip

public:
    // Constructor: name, duration, and description
    Audio(const std::string& name, const std::string& duration, const std::string& otherInfo);

    std::string getType() const override; // Returns "audio"
    bool isPlayable() const override;      // Playable => true
    void display() const override;         // Simulated playback info
};

// Video class: visual, playable
class Video : public MediaObject, public Playable, public Visual {
private:
    std::string duration; // Duration of the video clip

public:
    // Constructor: name, duration, and description
    Video(const std::string& name, const std::string& duration, const std::string& otherInfo);

    std::string getType() const override; // Returns "video"
    bool isPlayable() const override;      // Playable => true
    void display() const override;         // Simulated playback info
};

#endif // MEDIAOBJECT_H
