asm; arithmetic_test.asm
; Basic arithmetic: loads two values, adds and subtracts them

LOAD R1 10
LOAD R2 5

ADD R3 R1 R2
STORE R3 100

SUB R3 R1 R2
STORE R3 101

HALT