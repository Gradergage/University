	org 	8100h	
	mov   	r3, #20h 	; Y
  	mov 	r1, #40h  	; address counter (X)

step1:  	mov  	@r1,03h 	; 20h-18h
  	inc  	r1

	dec	r3

 	mov  	A,r3
  	subb  	A,#18h
  	jnz  	step1
	
step2:  	mov  	@r1,03h	;18h-28h
  	inc  	r1

	inc	r3
	
 	mov  	A,r3
  	subb  	A,#28h
  	jnz  	step2	

step3:  	mov  	@r1,03h	;28h-20h
  	inc  	r1

	dec	r3
	
 	mov  	A,r3
  	subb  	A,#1Fh
  	jnz  	step3

  	ret