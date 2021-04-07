
rm -r ./build
mkdir ./build
cd ./build
time cmake ..
make
cd src
./c_compiler