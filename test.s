
.extern label
.section .text
.word label,3,6
label1:
.section .data
loop:
ldr r2, [r4 + loop]
.end
