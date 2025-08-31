#include "Dataset.h"
#include "Player.h"
#include "Viewer.h"
#include "MediaObject.h"
#include <iostream>

// Main function demonstrating the usage of Dataset, Player, and Viewer
int main() {
    // Create the dataset which holds all media objects
    Dataset* ds = new Dataset();

    // Create two players and two viewers as observers
    Player* p1 = new Player("Player1");
    Player* p2 = new Player("Player2");
    Viewer* v1 = new Viewer("Viewer1");
    Viewer* v2 = new Viewer("Viewer2");

    // Register observers to the dataset
    ds->registerObserver(p1);
    ds->registerObserver(p2);
    ds->registerObserver(v1);
    ds->registerObserver(v2);

    // Add various media objects to the dataset
    ds->add(new Image("image1", "1920x1080", "Landscape Photo"));
    ds->add(new Image("image2", "800x600", "Portrait Photo"));
    ds->add(new Audio("audio1", "3:45", "Podcast Episode"));
    ds->add(new Video("video1", "10:00", "Tutorial Video"));
    ds->add(new Text("text1", "Chapter 1: Introduction"));

    // Show current playlists and view lists
    p1->show_list();
    v1->show_list();

    // Display currently playing for player 1
    MediaObject* playObj = p1->currently_playing();
    if (playObj) {
        std::cout << "Player1 is currently playing: ";
        playObj->display();
    }

    // Display currently viewing for viewer 1
    MediaObject* viewObj = v1->currently_viewing();
    if (viewObj) {
        std::cout << "Viewer1 is currently viewing: ";
        viewObj->display();
    }

    // Remove currently playing object from dataset and observe updates
    if (playObj) {
        ds->remove(playObj);
    }

    // Show updated playlist for player 1 after removal
    p1->show_list();

    // Clean up: unregister observers and delete them
    ds->unregisterObserver(p1);
    ds->unregisterObserver(p2);
    ds->unregisterObserver(v1);
    ds->unregisterObserver(v2);

    delete p1;
    delete p2;
    delete v1;
    delete v2;
    delete ds; // Dataset destructor will free remaining media objects

    return 0;
}
