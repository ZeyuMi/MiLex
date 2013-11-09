OBJS = lex.o lexReader.o preprocessor.o nfaConstructor.o dfaConstructor.o dfaOptimizer.o programGenerator.o\
	    buffer.o error.o stringUtil.o stack.o graph.o dfaStateTable.o dfaTransTable.o

CFLAGS= -g

MiLex : $(OBJS)
	cc -g $(OBJS) -o MiLex

.PHONY : clean
clean:
	rm MiLex $(OBJS)
