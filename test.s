.section .text
.word label,3,6
jmp %label
xor r1,r1
.skip 3
label:
and r1,r1
ldr r1,%label
or r1,r1

.end
