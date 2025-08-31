CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp Robot.cpp Humanic.cpp OptimusPrime.cpp RoboCop.cpp Roomba.cpp Bulldozer.cpp Kamikaze.cpp Simulation.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = PA4

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
main.o: main.cpp Simulation.h Constants.h
Robot.o: Robot.cpp Robot.h Constants.h
Humanic.o: Humanic.cpp Humanic.h Robot.h Constants.h
OptimusPrime.o: OptimusPrime.cpp OptimusPrime.h Humanic.h Robot.h Constants.h
RoboCop.o: RoboCop.cpp RoboCop.h Humanic.h Robot.h Constants.h
Roomba.o: Roomba.cpp Roomba.h Robot.h Constants.h
Bulldozer.o: Bulldozer.cpp Bulldozer.h Robot.h Constants.h
Kamikaze.o: Kamikaze.cpp Kamikaze.h Robot.h Constants.h
Simulation.o: Simulation.cpp Simulation.h Robot.h OptimusPrime.h RoboCop.h Roomba.h Bulldozer.h Kamikaze.h Constants.h

clean:
	rm -f $(OBJS) $(EXEC)