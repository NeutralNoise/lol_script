#COMMON_SRC_FILES := ../Common/optcodes.cpp
SRC_FILES := $(wildcard *.cpp)
COMMON_SRC_FILES := fetch/fetch.cpp fetch/fetch_cmp.cpp fetch/fetch_jmp.cpp fetch/fetch_math.cpp fetch/fetch_mov.cpp fetch/fetch_stack.cpp
CXXFLAGS := -w -std=c++11 -O3 -s
DEBUG_CXXFLAGS := -Wall -g -std=c++11
CHECK_CXXFLAGS := -Wall -std=c++11 -fsyntax-only -Werror

#i don't know if this works
ifeq (a,$(shell echo "a"))
#Use Unix style command variables
APP_NAME := lolVM
else
#Use Windows style command variables
APP_NAME := lolVM.exe
endif

debug: $(SRC_FILES) $(COMMON_SRC_FILES)
	mkdir -p ../bin/Debug
	g++ $(DEBUG_CXXFLAGS) $(SRC_FILES) $(COMMON_SRC_FILES) -o $(APP_NAME)
	mv $(APP_NAME) ../bin/Debug

check:
	g++ $(CHECK_CXXFLAGS) $(SRC_FILES)

release: $(SRC_FILES)
	mkdir -p ../bin/Release
	#mkdir -p ../bin
	g++ $(CXXFLAGS) $(SRC_FILES) -o $(APP_NAME)
	mv $(APP_NAME) ../bin/Release

clean:
	rm -f -r ../bin
	rm -f $(APP_NAME)
