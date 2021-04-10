#!/bin/bash

# rm -r ../build
# if [ ! -d "./build" ]; then
#     mkdir ../build
# fi

# cd ../build
# time cmake ..
# make

cd ../build/src/CMakeFiles/c_compiler.dir
file_count=0
echo "json file:"
for file_name in $(ls *.json)
do
    echo ' '$file_name
    json_file[file_count]=$file_name
    file_count=$(expr $file_count + 1)
done
json_path=../build/src/CMakeFiles/c_compiler.dir
cd ../../../../.vscode
python time_trace.py $json_path/${json_file[0]} $json_path/${json_file[1]}
# cd src
# ./c_compiler