	org 	8400h 		; ��������� �����
	mov 	a, #0Ah		; A
	mov 	r5, a		; A
	mov 	r6, #08h		; B
	mov 	r7, #05h		; C

	subb 	a, r7		; A - C
	mov 	b, r6		; ������ � ������� � - r6
	mul 	a, b		; (A-C)*B
	subb 	a, #10h		;  -10h
	mov 	b, r5		; ������ � ������� � - r5
	div 	a, b		; A - ����� �����, B - �������
	mov 	2Dh, A
	mov 	2Eh, B
	ret 