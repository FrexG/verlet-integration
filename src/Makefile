CC := clang 
CFLAGS := -Wall `pkg-config --cflags raylib` -g

LIBS := `pkg-config --libs --cflags raylib` -lm 

SRC := main.c
VERLET := verlet.c
OBJS := main.o
MAIN := main

all: $(MAIN)

$(MAIN):$(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(VERLET) $(OBJS) $(LIBS) 

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(MAIN) 
