	org	8100h
ADCON	equ	D8h
ADDAT	equ	D9h
DAPR	equ	dah
U:	equ 	40h	;���������� � �������
					
adc_read:			;��������� ������ ��������
	mov a,#5		;����� �����
	anl a,#00001111b	;����� ������� ���
	setb acc.2		;����������� �����
	anl ADCON,#E0h
	orl ADCON,a

	mov DAPR,#0h	;������� ���������
	lcall adc_delay	;��������
	mov a,ADDAT	;���������� � �����������
	mov U,a
	ret

adc_delay:
	push 0		;�������� �����
	mov r0,#20	;��� ��������������
	djnz r0,$		;� ���
	pop 0
	ret
