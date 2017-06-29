CC = gcc
CFLAGS = -g -lm -std=c99 -Wall -Werror

.PHONY: clean doc

firefox-doc:
	doxygen conf/doxygen.conf
	firefox ./doc/html/index.html
	
doc:
	doxygen conf/doxygen.conf

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

read-file: read-file.o
	$(CC) $(CFLAGS) -o $@ $^

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o $@ $^

conway-naive: conway-naive.o
	$(CC) $(CFLAGS) -o $@ $^

launch-conway-naive: conway-naive
	./conway-naive

generate-animation:
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif

add-files-svn:
	svn add --force ./mainpage.dox ./logo.png src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	rm -f *.o read-file conway-naive write-fact

syntax-check-cell: src/cell.c src/app-cell.c
	$(GCC) $(CFLAGS) -c $<

compile-all: app-conway.o
	$(CC) $(CFLAGS) -o app-conway $^
	
app-conway: app-conway.o
	$(CC) $(CFLAGS) -o $@ $^
	
launch-app-conway: app-conway
	rm -f ./out/*.ppm
	./app-conway
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif
	eog ./out/animation.gif

valgrind-app-conway: app-conway
	rm -f ./out/*.ppm
	valgrind ./app-conway
	
speedy-conway:
	$(CC) -O3 -lm -std=c99 -o speedy-conway ./src/app-conway.c

launch-speedy-conway:
	rm -f ./out/*.ppm
	./speedy-conway
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif
	eog ./out/animation.gif
