CC =gcc

CFLAGS =-Wall -Wextra -Werror

EXE =fp

OBJS =main.o utils.o logger.o house.o room.o evidence.o ghost.o hunter.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) -lpthread

main:   main.c
	$(CC) $(CFLAGS) -c main.c

utils:  utils.c
	$(CC) $(CFLAGS) -c utils.c

logger: logger.c
	$(CC) $(CFLAGS) -c logger.c

house:  house.c
	$(CC) $(CFLAGS) -c house.c

room:   room.
	$(CC) $(CFLAGS) -c room.c

evidence: evidence.c
	$(CC) $(CFLAGS) -c evidence.c

ghost:    ghost.c
	$(CC) $(CFLAGS) -c ghost.c

hunter:   hunter.c
	$(CC) $(CFLAGS) -c hunter.c

clean:
	rm -f $(OBJS) $(EXE)
