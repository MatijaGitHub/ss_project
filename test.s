.section .text
.word GAGA
.word 1000
GAGA:
ldr r0,$16
ldr r1,$1
shl r1,r0
halt
