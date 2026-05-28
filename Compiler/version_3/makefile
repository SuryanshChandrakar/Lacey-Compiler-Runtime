bps3_to_am1: compiler.cpp lexer.cpp
	g++ -O3 -o bps3_to_am1 compiler.cpp
	# lexer.cpp is included by compiler.cpp

lexer.cpp: lexer.l
	flex -o lexer.cpp lexer.l

compiler.cpp: compiler.yy
	bison -o compiler.cpp compiler.yy

clean:
	rm -f bps3_to_am1 compiler.cpp lexer.cpp
