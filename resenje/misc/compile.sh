/usr/bin/lex ./resenje/misc/lexer.l 
/usr/bin/bison ./resenje/misc/parser.y
g++ -g -pthread ./resenje/cpp/*  ./resenje/misc/cpp/* ./resenje/misc/FlexAndBison/* ./resenje/misc/mainAssembler.cpp -o assembler
/usr/bin/lex ./resenje/misc/lexer.l 
/usr/bin/bison ./resenje/misc/parser.y
g++ -g -pthread ./resenje/cpp/*  ./resenje/misc/cpp/* ./resenje/misc/FlexAndBison/* ./resenje/misc/mainLinker.cpp -o linker
/usr/bin/lex ./resenje/misc/lexer.l 
/usr/bin/bison ./resenje/misc/parser.y
g++ -g -pthread ./resenje/cpp/*  ./resenje/misc/cpp/* ./resenje/misc/FlexAndBison/* ./resenje/misc/mainEmulator.cpp -o emulator