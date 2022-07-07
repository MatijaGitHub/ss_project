ASSEMBLER=./asembler
LINKER=./linker
EMULATOR=./emulator

${ASSEMBLER} -o test.o ./resenje/tests/test.s
${ASSEMBLER} -o test2.o ./resenje/tests/test2.s
${LINKER} -hex -o program.hex test.o test2.o
${EMULATOR} program.hex