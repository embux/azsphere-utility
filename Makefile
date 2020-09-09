INCDIR=-I./inc 
LIBS=-lpthread 
CFLAGS=-Wall -DSQLITE_THREADSAFE=2 -DRTU_MULTI_THREAD=1
OBJS=obj/azUtility.o obj/ATCommand.o obj/serialcommu.o
AZSPHERE_EXE=bin/azutility

all: $(AZSPHERE_EXE)
	$(CC) $(OBJS) -o $(AZSPHERE_EXE) $(LIBS)

$(AZSPHERE_EXE): $(OBJS)


obj/%.o : src/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $(INCDIR) $< -o $@ 

clean:
	rm -f obj/* bin/*
