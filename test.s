.global sym1, sym2, sym3
.section .text

.global sym4
.extern sym5

testLabel2: .ascii "Hi\n"
testLabel: .word 1,2,3
sym1:
.end
.section .data
.skip 5
testLabel3:
.word 12
push r0
pop r0
ldr r0 , 1321
halt
.end
