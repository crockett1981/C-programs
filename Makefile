SRC = contacts/main.c
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

clean:
	rm -f $(BIN)

.PHONY: all clean
