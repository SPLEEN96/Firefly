#Resources: 
#https://stackoverflow.com/questions/40288915/makefile-compiling-every-time
#############CHEAT SHEET##################
#$@ name of the target
#$^ all items in dependency list
#$< dependency of the object (first item in dependency list)
#-MD -MP automatically generates dependency files (.d) (has to be included in makefile)
#all: main.cpp --> target: dependencies
#############CHEAT SHEET##################

COMPILER		:=gcc
OUTPUT			:=Engine.out
INCLUDES		:=-I./Lib/spdlog/include/ -I./Src
FLAGS			:=-g -Wall
LFLAGS			:=-lstdc++ -lglfw -lGL -lGLEW
SOURCES			:=$(wildcard ./Src/Firefly/*.cpp)
OBJS			:=$(SOURCES:.cpp=.o)

src_dir		:=./Src/Firefly
output_dir	:=./Output


#Compiles everything without cleanup
default: $(OUTPUT)
#Compiles everything and clean
fresh: $(OUTPUT) clean
#Removes all .o and .d files
clean: 
	rm -f $(OBJS) $(OBJS:.o=.d)


#Links and Compiles Objects into Executable
$(OUTPUT): $(OBJS)
	$(COMPILER) $(FLAGS) $(LFLAGS) $^ -o $(output_dir)/$@
	
#Compiles every SourceFiles into Objects with pattern rule
$(OBJS): %.o: %.cpp
	$(COMPILER) $(INCLUDES) $(FLAGS) $(LFLAGS) -MD -MP -c $< -o $@



-include $(OBJS:.o=.d) #replaces the .o by .d