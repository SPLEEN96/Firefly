project_dir	=$(shell pwd)

flags		=-g

src_dir		=./Src
all_files	= $(src_dir)/Firefly/*.cpp $(src_dir)/Sandbox/*.cpp

output_dir	=./Output
output_name	=Engine.o

all:
	gcc -lstdc++ -lglfw -lGL -lGLEW  $(all_files)  $(flags)  -o $(output_dir)/$(output_name)
