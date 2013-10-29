OBJS = driver.o token.o

lex : $(OBJS)
	cc -g $(OBJS) -o lex

driver.o : token.h token.c driver.c
token.o : token.h token.c

.PHONY : clean
clean:
	rm lex $(OBJS)
