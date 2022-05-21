CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra
CCP = g++
CPPFLAGS = -std=c++17 -pedantic -Wall

TARGET = tail wordcount wordcount-dynamic wordcount-cpp

all: $(TARGET)

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -c $<

wordcount: libhtab.a wordcount.o io.o
	$(CC) $(CFLAGS) -o wordcount -static wordcount.o io.o -L. -lhtab 

libhtab.a: htab.h htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_foreach.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o htab_struct.o
	ar -rcs libhtab.a $^

wordcount-dynamic: libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.c io.o -L. -lhtab 

libhtab.so: htab.h htab_bucket_count_d.o htab_clear_d.o htab_erase_d.o htab_find_d.o htab_foreach_d.o htab_free_d.o htab_hash_function_d.o htab_init_d.o htab_lookup_add_d.o htab_resize_d.o htab_size_d.o htab_struct_d.o
	$(CC) $(CFLAGS) htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_foreach.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o htab_struct.o -shared -o libhtab.so  		

htab_bucket_count.o: htab_bucket_count.c
	$(CC) -c $(CFLAGS) $^	

htab_clear.o: htab_clear.c
	$(CC) -c $(CFLAGS) $^

htab_erase.o: htab_erase.c
	$(CC) -c $(CFLAGS) $^

htab_find.o: htab_find.c
	$(CC) -c $(CFLAGS) $^	

htab_foreach.o: htab_foreach.c
	$(CC) -c $(CFLAGS) $^

htab_free.o: htab_free.c
	$(CC) -c $(CFLAGS) $^	

htab_hash_function.o: htab_hash_function.c
	$(CC) -c $(CFLAGS) $^

htab_init.o: htab_init.c
	$(CC) -c $(CFLAGS) $^

htab_lookup_add.o: htab_lookup_add.c
	$(CC) -c $(CFLAGS) $^											

htab_resize.o: htab_resize.c
	$(CC) -c $(CFLAGS) $^	

htab_size.o: htab_size.c
	$(CC) -c $(CFLAGS) $^			

htab_struct.o: htab_struct.c
	$(CC) -c $(CFLAGS) $^

htab_bucket_count_d.o: htab_bucket_count.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_clear_d.o: htab_clear.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_erase_d.o: htab_erase.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_find_d.o: htab_find.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_foreach_d.o: htab_foreach.c
	$(CC) -c -fPIC $(CFLAGS) $^

htab_free_d.o: htab_free.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_hash_function_d.o: htab_hash_function.c
	$(CC) -c -fPIC $(CFLAGS) $^

htab_init_d.o: htab_init.c
	$(CC) -c -fPIC $(CFLAGS) $^

htab_lookup_add_d.o: htab_lookup_add.c
	$(CC) -c -fPIC $(CFLAGS) $^											

htab_resize_d.o: htab_resize.c
	$(CC) -c -fPIC $(CFLAGS) $^	

htab_size_d.o: htab_size.c
	$(CC) -c -fPIC $(CFLAGS) $^			

htab_struct_d.o: htab_struct.c
	$(CC) -c -fPIC $(CFLAGS) $^	

io.o: io.c
	$(CC) -c $(CFLAGS) $^	

wordcount.o: wordcount.c
	$(CC) -c $(CFLAGS) $^

wordcount-cpp: wordcount-.cc		
	$(CCP) $(CPPFLAGS) -o wordcount-cpp wordcount-.cc

.PHONY: clean	

clean:
	rm *.o			