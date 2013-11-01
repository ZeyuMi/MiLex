OBJS = driver.o token.o mem.o

lex : $(OBJS)
	cc -g $(OBJS) -o lex

driver.o : token.h token.c mem.h mem.c driver.c
	cc -g -c token.c mem.c driver.c
token.o : token.h token.c
	cc -g -c  token.c
mem.o : mem.h mem.c
	cc -g -c mem.c

.PHONY : clean
clean:
	rm lex $(OBJS)
