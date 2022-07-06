# file: ivt.s

.extern isr_reset, isr_timer, isr_terminal

.section ivt
.word isr_reset
.skip 2 # isr_error
.word isr_terminal
.word isr_timer





.skip 8
.section VOLIMDUPE
.end
