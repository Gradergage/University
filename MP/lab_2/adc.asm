	org 8100h
U1:	equ 40h		;���������� � �������
					
U1_read:	push 0		;��������� ������ ��������
	mov r0,#0		;����� ��������
	lcall adc_switch	;������
	mov 0DAh,#0h	;������� ���������
	lcall adc_delay	;��������
	mov U1,0D9h	;���������� � U1
	pop 0
	ret

adc_switch:
	mov a,0D8h	;��������� ���:
	anl a,#11111000b	;�����������
	orl  a,#00001000b	;��������������
	orl a,r0		;����� ������
	mov 0D8h,a
	ret

adc_delay:
	push 0		;�������� �����
	mov r0,#20	;��� ��������������
	djnz r0,$		;� ���
	pop 0
	ret
