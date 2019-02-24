#!/bin/bash
SHADERS_PATH="./Src/Rendering/Shaders"
VERT_NAME=$1.vert
FRAG_NAME=$1.frag

echo rm $SHADERS_PATH/$1.*.spv
./Lib/vulkan/x86_64/bin/glslangValidator -V $SHADERS_PATH/$VERT_NAME -o $SHADERS_PATH/$VERT_NAME.spv
./Lib/vulkan/x86_64/bin/glslangValidator -V $SHADERS_PATH/$FRAG_NAME -o $SHADERS_PATH/$FRAG_NAME.spv