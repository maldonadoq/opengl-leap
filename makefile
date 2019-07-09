LEAP_LIBRARY := -L"/usr/lib" lib/x64/libLeap.so -Wl,-rpath,lib/x64
LEAP_INCLUDE := -I"include"
OPENGL_LIBRARY = -lglut -lGLU -lGL

test: test.cpp
	$(CXX) $(LEAP_INCLUDE) test.cpp -o test.out $(OPENGL_LIBRARY) $(LEAP_LIBRARY)

clean:
	rm -rf *.out
