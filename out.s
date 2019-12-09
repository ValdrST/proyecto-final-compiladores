	mult label1,
	MFHI 0
	sll 0,0,16
	MFLO 0
	add ,,
	move label1,(null)
	mult label1,
	MFHI 0
	sll 0,0,16
	MFLO 0
	move $v1,label1
	jr $ra
:
:
