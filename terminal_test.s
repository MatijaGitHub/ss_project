.section .text
.word 8,100
.word KEYBOARD,TIMER
ldr r6,$0xFEFE
ldr r1,$0
ldr r3,$4
str r3,0xFF10
LOOP:
ldr r2,$1
add r1,r2
jmp LOOP
END:
halt

.section .keyboard
KEYBOARD:
ldr r2, 0xFF02
ldr r1, $15
cmp r1,r2
jeq END
str r2,0xFF00
iret

TIMER:
ldr r2,$65
str r2,0xFF00
iret

