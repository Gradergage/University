	org 	8100h
    	mov 	r0, #50h 	; ��������
  	mov 	r1, #50h	; ������� �����
  	mov 	r2, #60h 	; ������� �����
    	inc 	r0    
cycle:    
    	dec 	r0  
			
    	mov 	b, r0	;�������� 1 �������
    	mov 	a, r1
    	div 	ab
    	mov 	r3, b
    	cjne 	r3, #00h, cycle

    	mov 	b, r0	;�������� 2 �������
    	mov 	a, r2
    	div 	ab
    	mov 	r3, b

    	cjne 	r3, #00h, cycle

            	ret