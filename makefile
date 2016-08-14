

main : obj/main.o obj/box.o obj/containerbox.o obj/mdatbox.o obj/mpegparser.o obj/mpegparserexception.o 
	g++ -std=c++11 -o bin/main obj/main.o obj/box.o obj/containerbox.o obj/mdatbox.o obj/mpegparser.o obj/mpegparserexception.o 

obj/%.o : %.cpp
	g++ -c -std=c++11 $< -o $@

linecount:
	wc -l *.cpp *.h makefile

clean :
	rm -f obj/* bin/* rm *~

