#include <iostream>
#include <stdexcept>
#include "catalog.h"

int main(int /* argc */, char* /* argv */[]) {
    try {
        // Create catalog with output.txt for logging
        Catalog catalog("output.txt");
        
        // Process data file
        catalog.processDataFile("data.txt");
        
        // Process commands file
        catalog.processCommandsFile("commands.txt");
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}