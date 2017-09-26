	org 8100h
U1:	equ 40h		;напряжение с датчика
					
U1_read:	push 0		;процедура опроса датчиков
	mov r0,#0		;выбор нулевого
	lcall adc_switch	;канала
	mov 0DAh,#0h	;задание диапазона
	lcall adc_delay	;задержка
	mov U1,0D9h	;сохранение в U1
	pop 0
	ret

adc_switch:
	mov a,0D8h	;настройка АЦП:
	anl a,#11111000b	;непрерывное
	orl  a,#00001000b	;преобразование
	orl a,r0		;выбор канала
	mov 0D8h,a
	ret

adc_delay:
	push 0		;выдержка паузы
	mov r0,#20	;для преобразования
	djnz r0,$		;в АЦП
	pop 0
	ret
