OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := lib/x64/libLeap.so -Wl,-rpath,x64
  else
    LEAP_LIBRARY := lib/x86/libLeap.so -Wl,-rpath,x86
  endif
else
  # OS X
  LEAP_LIBRARY := ../lib/libLeap.dylib
endif

OPENGL_LIBRARY = -lglut -lGLU -lGL

test: test.cpp
	$(CXX) -Wall -g -I../include test.cpp -o test.out $(OPENGL_LIBRARY) $(LEAP_LIBRARY)

clean:
	rm -rf test.out
