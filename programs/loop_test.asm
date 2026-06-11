; loop_test.asm
; Counts from 0 to 5 using a loop, stores final value in Memory[120]

LOAD R1 0
LOAD R2 1
LOAD R3 5

ADD R1 R1 R2
BNE R1 R3 3

STORE R1 120
HALT