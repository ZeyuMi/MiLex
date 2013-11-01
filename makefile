OBJS = driver.o token.o

lex : $(OBJS)
	cc -g $(OBJS) -o lex

driver.o : token.h token.c driver.c
	cc -g -c token.c mem.c driver.c
token.o : token.h token.c
	cc -g -c  token.c

.PHONY : clean
clean:
	rm lex $(OBJS)
