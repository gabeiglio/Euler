
euler:
	clang src/Token.h src/Lexer.c src/Codebuffer.c src/ConstantBuffer.c src/Hashmap.c src/Parser.c src/Debug.c src/VM.c src/main.c && ./a.out

tests:
	clang src/Token.h src/Lexer.c src/Codebuffer.c src/ConstantBuffer.c src/Hashmap.c src/Parser.c src/Debug.c src/VM.c test/utest.h test/main.c  && ./a.out

clean:
	rm a.out
