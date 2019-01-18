LIBRARY		=-lstdc++ -lglfw -lGL -lGLEW 
INCLUDE		=-I./Lib/spdlog/include/ #-I/another/path
FLAGS		=-g

src_dir		=./Src
all_files	= $(src_dir)/Firefly/*.cpp $(src_dir)/Sandbox/*.cpp

output_dir	=./Output
output_name	=Engine.o

all:
	gcc  $(LIBRARY) $(INCLUDE) $(all_files)  $(FLAGS)  -o $(output_dir)/$(output_name)
