	org	8100h
ADCON	equ	D8h
ADDAT	equ	D9h
DAPR	equ	dah
P5:	equ F8h

U:	equ 	50h	;напряжение с датчика
					
adc_read:			;процедура опроса датчиков
	mov a,#5		;пятый канал
	anl a,#00001111b	;сброс старших бит
	setb acc.2		;непрерывный режим
	anl ADCON,#E0h
	orl ADCON,a

	mov DAPR,#B4h	;задание диапазона
	lcall adc_delay	;задержка
	mov a,ADDAT	;сохранение в аккумулятор
	mov U,a
	jmp adc_read

adc_delay:
	push 0		;выдержка паузы
	mov r0,#20	;для преобразования
	djnz r0,$		;в АЦП
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
	mov r4,#38h		; Установка 8-битного режима обмена с ЖКИ с выводом обеих строк
	lcall ind_wr
	mov r4,#0Ch		; Отображение экрана без курсоров
	lcall ind_wr
	mov r4,#80h		; Отображение экрана без курсоров
	lcall ind_wr

	mov dptr, #FFD0h		;Адрес внешней памяти, где хранится выводимые строки
	setb P1.2

wr_str1:	movx a,@dptr		
	mov r4,a
	lcall ind_wr	; Запись данных в ЖКИ
	inc dptr
	mov a,dpl		
	cjne a,#DCh,wr_str1	; проверка окончания 1-й строки
	
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
	mov r4,#C0h	; Команда для адресации 1-й ячейки второй строки
	lcall ind_wr	
	setb P1.2
	ret
;wr_str2:	movx a,@dptr

	;cjne a,#0F8h,wr_str2
	;ret

ind_wr:	mov P5,r4		; Загрузка в порт P5 записываемой в ЖКИ информации
	setb P1.3			; Установка сигнала E
	clr P1.0			; R/W=0 (запись)
	lcall delay
	clr P1.3			; Сброс сигнала E
	lcall delay
	setb P1.3			; Установка сигнала E
	ret

delay:	mov r3, #7
m9:	djnz r3, m9	
	ret
	
	org FFD0h
	

str1:	db 48h,61h,BEh,70h,C7h,B6h,65h,BDh,B8h,65h,3Ah,20h

