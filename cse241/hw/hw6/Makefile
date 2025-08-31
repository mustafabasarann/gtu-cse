CXX = g++
CXXFLAGS = -std=c++11 -Wall

# List of object files
OBJS = MediaObject.o Observer.o Player.o Viewer.o Dataset.o main.o

# Default target to build the application
all: app

# Link all object files into executable 'app'
app: $(OBJS)
	$(CXX) $(CXXFLAGS) -o app $(OBJS)

# Compile MediaObject.cpp
MediaObject.o: MediaObject.cpp MediaObject.h Playable.h NonPlayable.h Visual.h NonVisual.h
	$(CXX) $(CXXFLAGS) -c MediaObject.cpp

# Compile Observer.cpp
Observer.o: Observer.cpp Observer.h MediaObject.h
	$(CXX) $(CXXFLAGS) -c Observer.cpp

# Compile Player.cpp
Player.o: Player.cpp Player.h Observer.h MediaObject.h
	$(CXX) $(CXXFLAGS) -c Player.cpp

# Compile Viewer.cpp
Viewer.o: Viewer.cpp Viewer.h Observer.h MediaObject.h
	$(CXX) $(CXXFLAGS) -c Viewer.cpp

# Compile Dataset.cpp
Dataset.o: Dataset.cpp Dataset.h Observer.h MediaObject.h
	$(CXX) $(CXXFLAGS) -c Dataset.cpp

# Compile main.cpp
main.o: main.cpp MediaObject.h Player.h Viewer.h Dataset.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean up generated files
clean:
	rm -f *.o app
