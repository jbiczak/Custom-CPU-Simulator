; cmp_test.asm
; Tests CMP by comparing pairs of registers and storing results

LOAD R1 10
LOAD R2 20

CMP R0 R1 R2     ; R0 = -1 because R1 < R2
STORE R0 100     ; Memory[100] should be -1

CMP R0 R2 R1     ; R0 = 1 because R2 > R1
STORE R0 101     ; Memory[101] should be 1

CMP R0 R1 R1     ; R0 = 0 because R1 == R1
STORE R0 102     ; Memory[102] should be 0

HALT