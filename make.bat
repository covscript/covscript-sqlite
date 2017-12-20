@mkdir build
@cd build
@mkdir imports
@g++ -std=c++11 -I ..\include -shared -static -fPIC -s -O3 ..\sqlite.cpp -o .\imports\sqlite.cse