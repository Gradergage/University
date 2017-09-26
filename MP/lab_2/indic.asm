	org 8400h
P5: 	equ F8h
P4:	equ E8h
;P1:	equ 90h

indic:	clr P1.0
	mov r4,#38h		; ��������� 8-������� ������ ������ � ��� � ������� ����� �����
	lcall ind_wr
	mov r4,#0Ch		; ����������� ������ ��� ��������
	lcall ind_wr
	mov r4,#80h		; ����������� ������ ��� ��������
	lcall ind_wr

	mov dptr, #FFD0h		;����� ������� ������, ��� �������� ��������� ������
	setb P1.0

wr_str1:	movx a,@dptr		
	mov r4,a
	lcall ind_wr	; ������ ������ � ���
	inc dptr
	mov a,dpl		
	cjne a,#E4h,wr_str1	; �������� ��������� 1-� ������
	
	clr P1.0
	mov r4,#C0h	; ������� ��� ��������� 1-� ������ ������ ������
	lcall ind_wr	
	setb P1.0

wr_str2:	movx a,@dptr
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl
	cjne a,#0F8h,wr_str2
	ret

ind_wr:	mov P5,r4		; �������� � ���� P5 ������������ � ��� ����������
	setb P1.3			; ��������� ������� E
	clr P1.2			; R/W=0 (������)
	lcall delay
	clr P1.3			; ����� ������� E
	lcall delay
	setb P1.3			; ��������� ������� E
	ret

delay:	mov r3, #7
m1:	djnz r3, m1	
	ret
	
	org FFD0h

str1:	db 48h,41h,A3h,41h,54h,41h,20h,4Bh,A7h,41h,42h,A5h,ACh,41h,3Ah,20h
str2:	db 43h,41h,a1h,41h,e0h, 45h,45h,42h,41h,20h,a5h,20h,a8h,4fh,4bh,41h,54h,a5h,a7h,4fh