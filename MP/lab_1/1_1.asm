	org 	8400h 		; начальный адрес
	mov 	a, #0Ah		; A
	mov 	r5, a		; A
	mov 	r6, #08h		; B
	mov 	r7, #05h		; C

	subb 	a, r7		; A - C
	mov 	b, r6		; запись в регистр В - r6
	mul 	a, b		; (A-C)*B
	subb 	a, #10h		;  -10h
	mov 	b, r5		; запись в регистр В - r5
	div 	a, b		; A - целая часть, B - остаток
	mov 	2Dh, A
	mov 	2Eh, B
	ret 