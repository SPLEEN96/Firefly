project_dir	=$(shell pwd)

flags		=-g
src_dir		=./Src
output_dir	=./Output
output_name	=Engine.o

all:
	gcc -lstdc++ -lglfw -lGL -lGLEW  $(src_dir)/*.cpp  $(flags)  -o $(output_dir)/$(output_name)
