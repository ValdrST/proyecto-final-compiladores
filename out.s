	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	nop
	move label6,0
	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	nop
	move $v1,label6
	jr $ra
	move label6,0
	mult label6,
	MFHI 0
	sll 0,0,16
	MFLO 0
	move $v1,label6
	jr $ra
:
:
:
:
