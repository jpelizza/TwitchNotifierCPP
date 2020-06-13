CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -g -lcurl -ljsoncpp 

SRC :=  $(shell find src -name "*.cpp")
SRCNAME = $(notdir $(SRC))
SRCOBJ = $(SRCNAME:%.cpp=%.o)


all: main
	@ echo "> done :)"
	@ echo "> run \"./bin/bot"

main: $(SRCOBJ)
	@ echo "> Compiling: project"
	@g++ $(CXXFLAGS) -o bin/bot $(addprefix obj/,$(SRCOBJ)) `pkg-config --cflags --libs giomm-2.4` $(LDFLAGS)

$(SRCOBJ): $(SRC)
	@ echo "> Compiling: "$(@:%.o=%.cpp)
	@g++ $(CXXFLAGS) -o obj/$@ -c $(filter %/$(@:%.o=%.cpp), $^) `pkg-config --cflags --libs giomm-2.4` $(LDFLAGS)

.PHONY: clean
clean:
	rm -f obj/*.o bin/bot