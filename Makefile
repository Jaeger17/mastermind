# build flags
CFLAGS += -Wall -Wextra -Wpedantic -Wwrite-strings -Wfloat-equal 

mastermind:

.PHONY: debug
debug: mastermind

clean:
	$(RM) mastermind *.o
