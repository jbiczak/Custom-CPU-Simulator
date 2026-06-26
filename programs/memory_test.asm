; memory_test.asm
; Tests MOV and LOADM by storing a value, loading it back,
; copying it to another register, and verifying the result

LOAD R1 42       ; R1 = 42
STORE R1 100     ; Memory[100] = 42

LOADM R2 100     ; R2 = Memory[100] (should be 42)
MOV R3 R2        ; R3 = R2 (should also be 42)

STORE R3 101     ; Memory[101] = 42
HALT