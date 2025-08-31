CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp catalog.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = exceptions.h field.h entry.h catalog.h
TARGET = catalog

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean