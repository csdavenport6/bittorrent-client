# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Define header and source directories
INCLUDEDIR = include
SRCDIR = src

# Define target output
TARGET = bittorrent_client

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

# Default target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# To obtain object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDEDIR) -c $< -o $@

# To remove generated files
clean:
	rm -f $(TARGET) $(SRCDIR)/*.o

# Dependencies
$(SRDDIR)/main.o: $(INCLUDEDIR)/bencode.h
$(SRCDIR)/BEncodingParser.o: $(INCLUDEDIR)/bencode.h
