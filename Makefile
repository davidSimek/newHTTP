# Project:	newHTTP
# Author:	David Šimek

CFLAGS	= -Wall -Wextra -g

SOURCES := $(wildcard src/*.c)

EXECUTABLE_LINUX := out/run_linux
EXECUTABLE_WINDOWS := out/run_windows.exe

all: linux windows

# build for GNU/LINUX

linux: $(SOURCES)
	gcc -D LINUX $(CFLAGS) -o $(EXECUTABLE_LINUX) $^

# build for WINDOWS

windows: $(SOURCES)
	x86_64-w64-mingw32-gcc -D WINDOWS $(CFLAGS) -o $(EXECUTABLE_WINDOWS) $^ -lws2_32

# debug build for GNU/LINUX

linux_debug: $(SOURCES)
	gcc -g -D LINUX $(CFLAGS) -o $(EXECUTABLE_LINUX) $^

# debug build for WINDOWS

windows_debug: $(SOURCES)
	x86_64-w64-mingw32-gcc -g -D WINDOWS $(CFLAGS) -o $(EXECUTABLE_WINDOWS) $^ -lws2_32

clean:
	rm -f $(EXECUTABLE_LINUX) $(EXECUTABLE_WINDOWS)

