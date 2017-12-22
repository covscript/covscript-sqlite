@mkdir build
@cd build
@mkdir imports
@gcc -I ..\include -fPIC -s -O3 -c ..\sqlite3.c
@g++ -std=c++11 -I ..\include -shared -static -fPIC -s -O3 ..\sqlite.cpp .\sqlite3.o -o .\imports\sqlite.cse
@del sqlite3.o