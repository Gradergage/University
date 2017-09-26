	org 8100h

	setb 00h		;a
	setb 01h		;b
	setb 02h		;c
	setb 03h		;d
	
	mov c, 00h
	cpl c
	anl c, /01h		;-a^-b
	mov 05h,c
	
	mov c, 02h
	anl c, /03h		;c^-d
	mov 06h,c
	
	mov c,03h
	anl c,/02h		;-c^d
	
	orl c,06h		;c xor d
	
	orl c,05h		;res
	mov 2Eh,#00h
	mov 70h,c		;сохранение
	ret

