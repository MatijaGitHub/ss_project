.section .text
.global sym1, sym2, sym3
.global sym4
.extern sym5
testLabel2: .ascii "Hi\n"
testLabel: .word 1,2,3
.end
.section .data
.skip 5
testLabel3:
.word 12
or r1,r2
xor r3,r4
.end
