export CC = clang

CFLAGS += -g
CFLAGS += -pedantic -Wall
CFLAGS += -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings \
-Wconversion -Wunreachable-code -Wcast-qual -W -Wformat=2 -Winit-self -Wuninitialized
CFLAGS += -Wcast-align
CPPFLAGS += -fsanitize=address
LDFLAGS  += -fsanitize=address

ifdef DEBUG
# add the debug flag, may need to comment this line when doing make feedback
CPPFLAGS += -DDEBUG
endif

.PHONY: all all-deferred

# list of C files the .o of which shall not be automatically added to OBJS list
EXCLUDE_SRCS = game_server.c game_client.c

SRCS = $(filter-out $(EXCLUDE_SRCS), $(wildcard *.c))

LDLIBS += -lm -lssl -lcrypto

OBJS=$(subst .c,.o,$(SRCS))

all:: all-deferred

game_server: $(OBJS) game_server.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
game_client: $(OBJS) game_client.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

