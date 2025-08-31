#include "MediaObject.h"

// Constructor: initialize name and otherInfo
MediaObject::MediaObject(const std::string& n, const std::string& other)
    : name(n), otherInfo(other) {}

// Return media object name
std::string MediaObject::getName() const {
    return name;
}

// ----- Text Implementation -----

// Constructor: call base MediaObject with name, otherInfo
Text::Text(const std::string& name, const std::string& otherInfo)
    : MediaObject(name, otherInfo) {}

// Return type identifier
std::string Text::getType() const {
    return "text";
}

// Text is not playable
bool Text::isPlayable() const {
    return false;
}

// Display text information
void Text::display() const {
    std::cout << "Text: " << name << " - " << otherInfo << std::endl;
}

// ----- Image Implementation -----

// Constructor: initialize name, dimensions, and description
Image::Image(const std::string& name, const std::string& dimensionInfo, const std::string& otherInfo)
    : MediaObject(name, otherInfo), dimensionInfo(dimensionInfo) {}

// Return type identifier
std::string Image::getType() const {
    return "image";
}

// Image is not playable
bool Image::isPlayable() const {
    return false;
}

// Display image information
void Image::display() const {
    std::cout << "Image: " << name << " - Dimensions: " << dimensionInfo
              << " - " << otherInfo << std::endl;
}

// ----- Audio Implementation -----

// Constructor: initialize name, duration, and description
Audio::Audio(const std::string& name, const std::string& duration, const std::string& otherInfo)
    : MediaObject(name, otherInfo), duration(duration) {}

// Return type identifier
std::string Audio::getType() const {
    return "audio";
}

// Audio is playable
bool Audio::isPlayable() const {
    return true;
}

// Simulate audio playback by displaying info
void Audio::display() const {
    std::cout << "Audio: " << name << " - Duration: " << duration
              << " - " << otherInfo << std::endl;
}

// ----- Video Implementation -----

// Constructor: initialize name, duration, and description
Video::Video(const std::string& name, const std::string& duration, const std::string& otherInfo)
    : MediaObject(name, otherInfo), duration(duration) {}

// Return type identifier
std::string Video::getType() const {
    return "video";
}

// Video is playable
bool Video::isPlayable() const {
    return true;
}

// Simulate video playback by displaying info
void Video::display() const {
    std::cout << "Video: " << name << " - Duration: " << duration
              << " - " << otherInfo << std::endl;
}
