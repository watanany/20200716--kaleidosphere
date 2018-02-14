CC = g++

LDLIBS = -lglut -lGL -lGLU -lGLEW -lXmu -lX11 -lm

.cpp:
	$(CC) $@.cpp Rect.cpp Framebuffer.cpp $(LDLIBS) -o kaleidscope
