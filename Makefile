# Project:	newHTTP
# Author:	David Šimek

CFLAGS	= -Wall -Wextra -g

SOURCES_LINUX := $(filter-out l_%, $(wildcard src/*.c))  # only use files not prepended by w_
EXECUTABLE_LINUX := out/run_linux

SOURCES_WINDOWS := $(filter-out w_%, $(wildcard src/*.c))  # only use files not prepended by w_
EXECUTABLE_WINDOWS := out/run_windows.exe

all: linux windows

# -----------------------
# | BUILD FOR GNU/LINUX |
# -----------------------

linux: $(SOURCES_LINUX)
	gcc -D LINUX $(CFLAGS) -o $(EXECUTABLE_LINUX) $^


# ---------------------
# | BUILD FOR WINDOWS |
# ---------------------

windows: $(SOURCES_WINDOWS)
	x86_64-w64-mingw32-gcc -D WINDOWS $(CFLAGS) -o $(EXECUTABLE_WINDOWS) $^
clean:
	rm -f $(EXECUTABLE_LINUX) $(EXECUTABLE_WINDOWS)

