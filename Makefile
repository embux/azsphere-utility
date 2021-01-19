INCDIR=-I./inc/x86_64/
INCDIR_WIN=-I./inc/Win/
LIBS=-lpthread 
LDLIBS=-lmingw32
CFLAGS=-Wall -DSQLITE_THREADSAFE=2 -DRTU_MULTI_THREAD=1
CFLAGS_WIN=-Wall -Wextra -lmingw32 -lm
CC_WIN32=i686-w64-mingw32-gcc
CC_WIN64=x86_64-w64-mingw32-gcc
CC_ARM=arm-linux-gnueabihf-gcc
OBJS=obj/x86_64/azUtility.o obj/x86_64/ATCommand.o obj/x86_64/serialcommu.o
OBJS_ARM=obj/ARM/azUtility.o obj/ARM/ATCommand.o obj/ARM/serialcommu.o
OBJS_WIN32=obj/win32/azUtility.o obj/win32/ATCommand.o obj/win32/serialcommu_win.o
OBJS_WIN64=obj/win64/azUtility.o obj/win64/ATCommand.o obj/win64/serialcommu_win.o
AZSPHERE_X86_64_EXE=bin/x86_64/azutility
AZSPHERE_3A1_EXE=bin/ARM/azutility
AZSPHERE_win64_EXE=bin/win64/azutility.exe
AZSPHERE_win32_EXE=bin/win32/azutility.exe

x86_64: $(AZSPHERE_X86_64_EXE)
	$(CC) $(OBJS) -o $(AZSPHERE_X86_64_EXE) $(LIBS)

win32: $(AZSPHERE_win32_EXE)
	$(CC_WIN32) $(OBJS_WIN32) -o $(AZSPHERE_win32_EXE)

win64: $(AZSPHERE_win64_EXE)
	$(CC_WIN64) $(OBJS_WIN64) -o $(AZSPHERE_win64_EXE)

ARM: $(AZSPHERE_3A1_EXE)
	$(CC_ARM) $(OBJS_ARM) -o $(AZSPHERE_3A1_EXE) $(LIBS)

$(AZSPHERE_X86_64_EXE): $(OBJS)

$(AZSPHERE_win32_EXE): $(OBJS_WIN32)

$(AZSPHERE_win64_EXE): $(OBJS_WIN64)

$(AZSPHERE_3A1_EXE): $(OBJS_ARM)

obj/x86_64/%.o : src/x86_64/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $(INCDIR) $< -o $@ 

obj/win32/%.o : src/Win/%.c
	$(CC_WIN32) -c $(CFLAGS_WIN) $(INCLUDES) $(INCDIR_WIN) $< -o $@ 

obj/win64/%.o : src/Win/%.c
	$(CC_WIN64) -c $(CFLAGS_WIN) $(INCLUDES) $(INCDIR_WIN) $< -o $@ 

obj/ARM/%.o : src/ARM/%.c
	$(CC_ARM) -c $(CFLAGS) $(INCLUDES) $(INCDIR) $< -o $@

clean:
	rm -f obj/x86_64/* bin/x86_64/*
	rm -f obj/win64/* bin/win64/*
	rm -f obj/win32/* bin/win32/*
	rm -f obj/ARM/* bin/ARM/*
