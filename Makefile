#BookCheck :


CC = g++
CFLAGS = -Wall -O3 -c
LFLAGS = -Wall -O3
INCLUDE = -I.
OBJS = main.o Seed.o Map.o ReadingLevel.o ExceptionFile.o TFIDF.o

BookCheck : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o BookCheck

main.o : main.cpp 
	$(CC) main.cpp $(CFLAGS) $(INCLUDE)
	
ExceptionFile.o : ExceptionFile.cpp ExceptionFile.h
	$(CC) ExceptionFile.cpp $(CFLAGS) $(INCLUDE)

Seed.o : Seed.cpp Seed.h
	$(CC) Seed.cpp $(CFLAGS) $(INCLUDE)

Map.o : Map.cpp Map.h
	$(CC) Map.cpp $(CFLAGS) $(INCLUDE)	
	
ReadingLevel.o : ReadingLevel.cpp ReadingLevel.h
	$(CC) ReadingLevel.cpp $(CFLAGS) $(INCLUDE)
	
TFIDF.o : TFIDF.cpp TFIDF.h
	$(CC) TFIDF.cpp $(CFLAGS) $(INCLUDE)
	
clean :
	-rm *.o BookCheck
