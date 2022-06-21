.section .text
jmp label
xor r1,r1
.word 5
ldr r1,label
label:
or r1,r1
.end
