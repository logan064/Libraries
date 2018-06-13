#OBJS holds object files
OBJS = integer.o real.o string.o da.o cda.o stack.o queue.o bst.o driver.o
#OOPTS has flags to create object files
OOPTS = -Wall -Wextra -g -c
#LOPTS has flags to create executable
LOPTS = -Wall -Wextra -g

all:	driver

driver:	$(OBJS)
	gcc $(LOPTS) -o driver $(OBJS)

driver.o:	integer.h driver.c
	gcc $(OOPTS) driver.c

#start of dependencies
integer.o:	integer.h integer.c
	gcc $(OOPTS) integer.c

real.o:	real.h real.c
	gcc $(OOPTS) real.c

string.o:	string.h string.c
	gcc $(OOPTS) string.c

da.o:	da.h da.c
	gcc $(OOPTS) da.c

cda.o:	cda.h cda.c
	gcc $(OOPTS) cda.c

stack.o:	da.h stack.h stack.c
	gcc $(OOPTS) stack.c

queue.o:	cda.h queue.h queue.c
	gcc $(OOPTS) queue.c

bst.o:	queue.h bst.h bst.c
	gcc $(OOPTS) bst.c

#cleans the old .o files and the old .exe
clean:
	rm -f $(OBJS) driver

#runs the executable
test:	driver
	./driver
