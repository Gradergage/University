	org 	8100h
    	mov 	r0, #50h 	; делитель
  	mov 	r1, #50h	; меньшее число
  	mov 	r2, #60h 	; большее число
    	inc 	r0    
cycle:    
    	dec 	r0  
			
    	mov 	b, r0	;проверка 1 деления
    	mov 	a, r1
    	div 	ab
    	mov 	r3, b
    	cjne 	r3, #00h, cycle

    	mov 	b, r0	;проверка 2 деления
    	mov 	a, r2
    	div 	ab
    	mov 	r3, b

    	cjne 	r3, #00h, cycle

            	ret