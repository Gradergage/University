	org	8100h
ADCON	equ	D8h
ADDAT	equ	D9h
DAPR	equ	dah
P5:	equ F8h

U:	equ 	50h	;���������� � �������
					
adc_read:			;��������� ������ ��������
	mov a,#5		;����� �����
	anl a,#00001111b	;����� ������� ���
	setb acc.2		;����������� �����
	anl ADCON,#E0h
	orl ADCON,a

	mov DAPR,#B4h	;������� ���������
	lcall adc_delay	;��������
	mov a,ADDAT	;���������� � �����������
	mov U,a
	jmp adc_read

adc_delay:
	push 0		;�������� �����
	mov r0,#20	;��� ��������������
	djnz r0,$		;� ���
	pop 0


num:	equ	040h
num2:	equ	041h
num3:	equ	042h

klav_end:	mov a,U
	mov b,#Ah
	div AB
	mov num3,b
	mov b,#Ah
	div AB
	mov num2,b
	add a, #30h
	mov num,a

	mov a, num3
	add a,#30h
	mov num3, a
	
	mov a, num2
	add a,#30h
	mov num2, a
	
end:	
	indic:	clr P1.2
	mov r4,#38h		; ��������� 8-������� ������ ������ � ��� � ������� ����� �����
	lcall ind_wr
	mov r4,#0Ch		; ����������� ������ ��� ��������
	lcall ind_wr
	mov r4,#80h		; ����������� ������ ��� ��������
	lcall ind_wr

	mov dptr, #FFD0h		;����� ������� ������, ��� �������� ��������� ������
	setb P1.2

wr_str1:	movx a,@dptr		
	mov r4,a
	lcall ind_wr	; ������ ������ � ���
	inc dptr
	mov a,dpl		
	cjne a,#DCh,wr_str1	; �������� ��������� 1-� ������
	
	mov a, num
	;movx a,@dptr
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl

	mov a, num2
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl

	mov a, num3
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl

	mov a, #65h
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl

	mov a, #e3h,
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl

	clr P1.2
	mov r4,#C0h	; ������� ��� ��������� 1-� ������ ������ ������
	lcall ind_wr	
	setb P1.2
	ret
;wr_str2:	movx a,@dptr

	;cjne a,#0F8h,wr_str2
	;ret

ind_wr:	mov P5,r4		; �������� � ���� P5 ������������ � ��� ����������
	setb P1.3			; ��������� ������� E
	clr P1.0			; R/W=0 (������)
	lcall delay
	clr P1.3			; ����� ������� E
	lcall delay
	setb P1.3			; ��������� ������� E
	ret

delay:	mov r3, #7
m9:	djnz r3, m9	
	ret
	
	org FFD0h
	

str1:	db 48h,61h,BEh,70h,C7h,B6h,65h,BDh,B8h,65h,3Ah,20h

