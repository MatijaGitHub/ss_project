/usr/bin/lex ./resenje/misc/lexer.l 
/usr/bin/bison ./resenje/misc/parser.y
g++ ./resenje/src/cpp/*  ./resenje/misc/cpp/* ./resenje/misc/FlexAndBison/* ./resenje/misc/main.cpp -o exec