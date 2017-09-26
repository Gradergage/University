	org 8100h
map_start:	equ 30h		;начало области хранени€ карты клавиатуры
P4:	equ E8h
P5:	equ F8h

klav:			;чтение карты в пам€ть ћ 
	mov a,#7fh	;подготовка "бегущего нул€"
	mov r0,#map_start	;адрес начала карты 
			;состо€ни€ клавиатуры
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
end:	
	ret
