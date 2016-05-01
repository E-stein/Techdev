vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

CC = gcc
CFLAGS = -g -Wall -Wextra
IFLAGS = -Iinclude
EXE = main
CFILES = $(wildcard $(CPATH)/*.c)
OBJFILES = $(patsubst $(CPATH)/%.c, $(OPATH)/%.o,$(CFILES))
OPATH = obj
CPATH = src
BPATH = bin

$(EXE) : lib/libjeu.a
	$(CC) -Llib -ljeu -o $@
	mv $@ $(BPATH)

$(OPATH)/%.o : $(CPATH)/%.c
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

lib/libjeu.a : $(OBJFILES) 
	ar -crv $@ $^
	ranlib $@

clean :
	rm $(OPATH)/* $(BPATH)/* 

# DO NOT DELETE

src/grille.o: include/grille.h /usr/include/stdlib.h /usr/include/features.h
src/grille.o: /usr/include/stdc-predef.h /usr/include/alloca.h
src/grille.o: /usr/include/stdio.h /usr/include/libio.h
src/grille.o: /usr/include/_G_config.h /usr/include/wchar.h
src/grille.o: /usr/include/assert.h
src/io.o: include/io.h /usr/include/stdio.h /usr/include/features.h
src/io.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/io.o: /usr/include/_G_config.h /usr/include/wchar.h include/grille.h
src/io.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/assert.h
src/io.o: include/jeu.h
src/jeu.o: include/jeu.h include/grille.h /usr/include/stdlib.h
src/jeu.o: /usr/include/features.h /usr/include/stdc-predef.h
src/jeu.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
src/jeu.o: /usr/include/_G_config.h /usr/include/wchar.h
src/jeu.o: /usr/include/assert.h
src/main.o: /usr/include/stdio.h /usr/include/features.h
src/main.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/main.o: /usr/include/_G_config.h /usr/include/wchar.h include/grille.h
src/main.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/assert.h
src/main.o: include/io.h include/jeu.h
