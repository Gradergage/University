	org 8100h
map_start:	equ 30h		;начало области хранения карты клавиатуры
P4:	equ E8h
P5:	equ F8h

klav:			;чтение карты в память МК
	mov a,#7fh	;подготовка "бегущего нуля"
	mov r0,#map_start	;адрес начала карты 
			;состояния клавиатуры
	orl P4,#f0h

$scan:	mov P1,a	;выдача сигнала в порт 1

	mov @R0,P4	;чтение ответа из порта 1
	inc r0		;в очередную позицию карты
	setb c
	rr a		;подготовка нового опроса
	cjne a,#7fh,$scan

num:	equ	040h	
			
	mov r0,#30h

find_row:	mov a,@r0
	inc r0
	subb a,#ffh
	jz find_row	
	
	cjne r0,#35h,find_button
	mov num,#00h
	sjmp end
	
find_button:
	dec r0
	mov a,@r0
	jnb a.7,m1
	jnb a.6,m2
	jnb a.5,m3
	jnb a.4,m4
m1:	mov r1,#01h
	ljmp find_num
m2:	mov r1,#02h
	ljmp find_num
m3:	mov r1,#03h
	ljmp find_num
m4:	mov r1,#04h
find_num:	mov a,r0
	mov b,#04h
	clr c
	subb a,#30h
	mul ab
	add a,r1
	
klav_end:	
	mov num,a
	;add A, #30h
	;mov num,a	
end:	
	indic:	clr P1.0
	mov r4,#38h		; Установка 8-битного режима обмена с ЖКИ с выводом обеих строк
	lcall ind_wr
	mov r4,#0Ch		; Отображение экрана без курсоров
	lcall ind_wr
	mov r4,#80h		; Отображение экрана без курсоров
	lcall ind_wr

	mov dptr, #FFD0h		;Адрес внешней памяти, где хранится выводимые строки
	setb P1.0

wr_str1:	movx a,@dptr		
	mov r4,a
	lcall ind_wr	; Запись данных в ЖКИ
	inc dptr
	mov a,dpl		
	cjne a,#E4h,wr_str1	; проверка окончания 1-й строки
	
	clr P1.0
	mov r4,#C0h	; Команда для адресации 1-й ячейки второй строки
	lcall ind_wr	
	setb P1.0

wr_str2:	movx a,@dptr
	mov r4,a
	lcall ind_wr
	inc dptr
	mov a,dpl
	cjne a,#0F8h,wr_str2
	ret

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
	

str1:	db 48h,41h,A3h,41h,54h,41h,20h,4Bh,A7h,41h,42h,A5h,ACh,41h,3Ah,20h
str2:	db @40h, 20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h,20h

