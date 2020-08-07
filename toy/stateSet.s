	.arch msp430g2553
	.p2align 1,0
	.text
	.global stateSet
stateSet:
	bit #1, r12	;if(switches &1)
	jnz case2
	mov #1, r12	;switches = 1
	jmp end
case2:
	bit #2, r12	;if(switches &2) 
	jnz case3
	mov #2, r12	;switches=2
	jmp end
case3:
	bit #4, r12	;if(switches&4)
	jnz case4
	mov #3, r12	;switches = 3
	jmp end
case4:
	bit #8, r12	;if(switches &8)
	jnz end
	mov #4, r12	;switches = 4
end:
	pop r0
	
