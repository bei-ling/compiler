#!/bin/bash
# compile
rm -r ../build
if [ ! -d "./build" ]; then
    mkdir ../build
fi
cd ../build
cmake ..
make

# time trace
# cd ../build/src/CMakeFiles/c_compiler.dir
# file_count=0

# echo "$ json file:"
# du -h *.json

# for file_name in $(ls *.json)
# do
#     json_file[file_count]=$file_name
#     file_count=$(expr $file_count + 1)
# done
# json_path=../build/src/CMakeFiles/c_compiler.dir
# cd ../../../../.vscode
# pwd

# if [ $file_count -eq 1 ]; then
#     python time_trace.py $json_path/${json_file[0]}
# else
#     python time_trace.py $json_path/${json_file[0]} $json_path/${json_file[1]} $json_path/${json_file[2]}
# fi
# echo "$ generate combined.json:"
# du -h combined.json
# run
# cd ../build/src/
# ./c_compiler