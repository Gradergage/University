	org	8100h
ADCON	equ	D8h
ADDAT	equ	D9h
DAPR	equ	dah
U:	equ 	40h	;напряжение с датчика
					
adc_read:			;процедура опроса датчиков
	mov a,#5		;пятый канал
	anl a,#00001111b	;сброс старших бит
	setb acc.2		;непрерывный режим
	anl ADCON,#E0h
	orl ADCON,a

	mov DAPR,#0h	;задание диапазона
	lcall adc_delay	;задержка
	mov a,ADDAT	;сохранение в аккумулятор
	mov U,a
	ret

adc_delay:
	push 0		;выдержка паузы
	mov r0,#20	;для преобразования
	djnz r0,$		;в АЦП
	pop 0
	ret
