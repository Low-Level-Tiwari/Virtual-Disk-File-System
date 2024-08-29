src=./src/
lib=./lib/

all: object libr test

object: $(src)encoder.c $(src)decoder.c
	gcc -c $(src)encoder.c -o $(lib)encoder.o
	gcc -c $(src)decoder.c -o $(lib)decoder.o

libr: $(lib)encoder.o $(lib)decoder.o
	ar -rcs $(lib)ecdc.a $(lib)encoder.o
	ar -rcs $(lib)ecdc.a $(lib)decoder.o

test: $(lib)ecdc.a vdCreate.c vdAdd.c
	gcc -o vdCreate vdCreate.c $(lib)ecdc.a -lm
	gcc -o vdAdd vdAdd.c $(lib)ecdc.a -lm
	gcc -o vdls vdls.c $(lib)/ecdc.a -lm
	gcc -o vdGet vdGet.c $(lib)/ecdc.a -lm
	gcc -o vdDelete vdDelete.c $(lib)/ecdc.a -lm
	./vdCreate vdisk 1024
	./vdAdd vdisk file 25
	./vdAdd vdisk context 336
	./vdAdd vdisk file2 18
	./vdAdd vdisk context 336
	./vdAdd vdisk file3 207
	./vdls vdisk
clean:
	rm -f $(lib)*.a $(lib)*.o vdCreate vdAdd vdls vdGet vdDelete vdDefrag
