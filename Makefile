SRCS=point_manager.c
TARG=point_manager
CC=gcc
OPTS=-Wall -O
all: $(TARG)
$(TARG): $(SRCS)
	$(CC) -o $(TARG) $(SRCS)
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(TARG)
