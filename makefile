
OBJS := obj/main.o obj/box.o obj/containerbox.o obj/mdatbox.o obj/mpegparserexception.o\
	obj/mpegparser.o obj/tinystr.o obj/tinyxml.o obj/tinyxmlerror.o obj/tinyxmlparser.o 

mpegparser : ${OBJS}
	g++ -std=c++11 -o bin/mpegparser ${OBJS}

obj/%.o : %.cpp
	g++ -c -std=c++11 $< -o $@

linecount:
	wc -l *.cpp *.h makefile

clean :
	rm -f obj/* bin/* rm *~


