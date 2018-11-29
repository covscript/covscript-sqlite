@mkdir build
@cd build
@mkdir imports
@gcc -I ..\include -fPIC -s -O3 -c ..\sqlite3.c
@g++ -std=c++11 -I%CS_DEV_PATH%\include -I..\include -shared -static -fPIC -s -O3 ..\sqlite.cpp .\sqlite3.o -o .\imports\sqlite.cse -L%CS_DEV_PATH%\lib -lcovscript
@del sqlite3.o