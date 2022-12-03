SRCS=point_manage.c
TARG=point_manage
CC=gcc
OPTS=-Wall -O
all: $(TARG)
$(TARG): $(SRCS)
	$(CC) -o $(TARG) $(SRCS)
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(TARG)
