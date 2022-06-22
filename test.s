.section .text
jmp %label
xor r1,r1
.skip 3
ldr r1,%label
or r1,r1
label:
.end
