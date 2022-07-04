.section .text
.word 6,100
.word KEYBOARD
ldr r6,$0xFEFE
ldr r1,$0
LOOP:
ldr r2,$1
add r1,r2
jmp LOOP
END:
halt

.section .keyboard
KEYBOARD:
ldr r2, 0xFF02
ldr r1, $10
cmp r1,r2
jeq END
str r2,0xFF00
iret

