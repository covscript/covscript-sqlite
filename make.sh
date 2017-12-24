mkdir -p build
cd build
mkdir -p imports
gcc -I ../include -fPIC -s -O3 -c ../sqlite3.c
g++ -std=c++11 -I ../include -shared -fPIC -s -O3 ../sqlite.cpp ./sqlite3.o -o ./imports/sqlite.cse
rm sqlite3.o