SRC_FILES := $(wildcard *.cpp)
COMMON_SRC_FILES := ../Common/$(wildcard *.cpp)
CXXFLAGS := -w -std=c++11 -O3 -s
DEBUG_CXXFLAGS := -Wall -g -std=c++11
CHECK_CXXFLAGS := -Wall -std=c++11 -fsyntax-only -Werror

#i don't know if this works
ifeq (a,$(shell echo "a"))
#Use Unix style command variables
APP_NAME := lolCompiler
else
#Use Windows style command variables
APP_NAME := lolCompiler.exe
endif


debug: $(SRC_FILES)
	mkdir -p ../bin/Debug
	g++ $(DEBUG_CXXFLAGS) $(SRC_FILES) -o $(APP_NAME)
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
