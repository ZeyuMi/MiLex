OBJS = lex.o lexReader.o preprocessor.o nfaConstructor.o dfaConstructor.o dfaOptimizer.o programGenerator.o lexWriter.o buffer.o

CFLAGS= -g

MiLex : $(OBJS)
	cc -g $(OBJS) -o MiLex

.PHONY : clean
clean:
	rm MiLex $(OBJS)
