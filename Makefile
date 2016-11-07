# Makefile for gtkmm_fbsetbg

BIN = fbsetbg-gtkmm

SOURCES = src/main.cpp src/signals.cpp src/setbgapp.cpp src/directory.cpp src/command.cpp

OBJS = build/main.o build/signals.o build/setbgapp.o build/directory.o build/command.o

CC = g++

CFLAGS = -std=c++11 `pkg-config --cflags gtkmm-3.0`

LIBS   = `pkg-config --cflags --libs gtkmm-3.0`

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LIBS)

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(BIN) $(OBJS)

