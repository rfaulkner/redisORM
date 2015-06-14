# redisORM

Simple wrapper around the C hiredis library

Setup & usage
-------------

Ensure that you LD_LIBRARY_PATH is set:

    export LD_LIBRARY_PATH=/usr/local/lib

Install hiredis:

	$ git clone git://github.com/antirez/hiredis.git
	$ cd Hiredis
	$ make && make install

Build object code linking hiredis:

   	$ g++ -std=c++0x -o redisORM.o /usr/lib/libhiredis.a -c redisORM.c

You can include redisORM in your project with:

	#include "redisORM.h"

Link into your project:

	$ g++ -std=c++0x myproj.c -o out ./redisORM.o
