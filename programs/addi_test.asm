; addi_test.asm
; Same count-to-5 loop as loop_test.asm but using ADDI instead of a dedicated increment register

LOAD R1 0        ; R1 = counter
LOAD R2 5        ; R2 = target value (R2 is now free from holding the constant 1)

LOOP:
ADDI R1 1        ; R1 = R1 + 1
BNE R1 R2 LOOP

STORE R1 120
HALT