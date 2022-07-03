.section .text
.word GAGA
.word 1000
GAGA:

ldr r0, %GAGA

ldr r1, r2
ldr r2, [r1 + GAGA]
ldr r6, $0
pop r4
pop r5
halt
