.section .text
.word label,3,6
jmp %label
xor r1,r1
.section .data
.skip 3
label:
.skip 1
ldr r1,%label
or r1,r1

.end
