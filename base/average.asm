;###########################################
;#										   #
;#	+ Created By: Marcos alves             #
;#									       #
;#	+ Created Date: April 20th, 2016       #
;#									       #
;#	+ Last Modified: May 27th, 2016	   	   #
;#									  	   #
;#	+ Title: average.asm			       #
;#									       #
;#	+ Email: marcos.alves@cc.ci.ufpb.br    #
;#										   #
;###########################################


; >>>> MACROS de saída leitura e escrita <<<<

%macro read 2
	mov 	ecx, %1
	mov 	eax, 3		 
	mov 	ebx, 0		 
	mov 	edx, %2		 
	int 	80h        
%endmacro

%macro write 2
	mov 	eax, 4
	mov 	ebx, 1
	mov 	ecx, %1
	mov 	edx, %2
	int 	80h
%endmacro

; >>>> segmento de dados inicializados <<<<

SECTION .data
	flag 	db  0 ; 0 FALSE 1 TRUE
	msg1	db	0xa,"+ Digite a quantidade de pontos na 1º prova (0-100): " , 0x0
	len1	equ	$ -msg1
	msg2	db	0xa,"+ Digite a quantidade de pontos na 2º prova (0-100): ", 0x0
	len2	equ	$ -msg2
	msg3	db	0xa,"+ Digite a quantidade de pontos na 3º prova (0-100): ", 0x0
	len3	equ $ -msg3
	msg4 	db 	0xa, " >>>>>>>>>>>>>>>>>> Situação Escolar <<<<<<<<<<<<<<<<<<<< ", 0xa
	len4 	equ $ -msg4
	msg5 	db  0xa,0xa,"# Seu Nível: ", 0x0
	len5 	equ $ -msg5
	msg6 	db 	0xa, "           **** ERROR: NOTA(S) INVÁLIDA(S) !!! ****", 0xa
	len6    equ $ -msg6
	msg7 	db  0xa, 0xa,"# Situação: APROVADO", 0xa
	len7	equ $ -msg7
	msg8 	db  0xa, 0xa,"# Situação: REPROVADO", 0xa
	len8	equ $ -msg8
	msg9 	db 	0xa, 0xa, "# Situação: PROVA FINAL", 0xa
	len9	equ $ -msg9
	msg10 	db  0xa, "           **** CUIDADO VOCÊ ESTÁ NA FINAL ****", 0xa
	len10	equ $ -msg10
	msg11 	db 	0xa, "+ Digite a quantidade de pontos na prova final (0-100): ", 0x0
	len11	equ $ -msg11
	msg12 	db 	0xa, 0xa, "@AUTOR: MARCOS ALVES", 0xa
	len12 	equ $ -msg12
	msg13 	db 	0xa, "# Sua Média: ", 0x0
	len13 	equ $ -msg13
	msg14	db 	0xa, "(*) Para ser aprovado você precisava tirar: ", 0x0
	len14 	equ $ -msg14

; >>>> segmento de dados NÃO inicializados <<<<
	
SECTION .bss 
	buffer 	resb 	1
	class 	resb 	1
	prev	resb 	4
	final 	resb	4
	mean	resb	4
	score1	resb	4
	score2	resb	4
	score3	resb	4
	
; >>>> labels do programa, inicialização código <<<<

SECTION .text
   global _start

; @função principal

_start:	
	push 	ebp
	mov 	ebp, esp
	
	write	msg4, len4

	write	msg1, len1
	read 	score1, 4

	write	msg2, len2
	read 	score2, 4	

	write	msg3, len3
	read 	score3, 4

	call 	calcmean

	cmp 	byte[flag], 1
	je 		.exit	

	write 	msg13, len13
	mov 	esi, [mean]
	call 	inttostr

	call 	level

.exit:
	write 	msg12, len12
	pop 	ebp
	mov		eax, 1       
   	int		80h    
   	ret

; @calculando a media

calcmean:
	push 	ebp
	push 	esi
	push 	ebx
	push 	edx

	lea		esi, [score1]
	call 	strtoint
	mov  	[score1], eax

	lea		esi, [score2]
    call 	strtoint
	mov 	[score2], eax

	lea		esi, [score3]
    call 	strtoint
	mov 	[score3], eax

	cmp 	dword[score1], 100
	ja 		.error
	cmp 	dword[score2], 100
	ja 		.error
	cmp 	dword[score3], 100
	ja 		.error

	xor 	eax, eax
	add 	eax, [score1]
	add 	eax, [score2]
	add 	eax, [score3]

	xor 	edx, edx
	mov 	ebx, 3
	div     ebx

	mov 	[mean], eax
	jmp 	.endmean

.error:
	write	msg6, len6
	mov 	byte[flag], 1

.endmean:
	pop 	ebx
	pop 	edx
	pop 	esi
	pop 	ebp
	ret


finalexam:	
	push 	ebp
	push 	ebx
	push 	edx
	push 	eax

	write 	msg10, len10 	
	write 	msg11, len11
	read 	final, 4

	lea 	esi, [final]
	call 	strtoint
	mov 	[final], eax

	xor 	eax, eax
	xor 	edx, edx

	mov 	ebx, 6
	mov 	eax, [mean]

	imul 	eax, ebx
	mov 	ebx, eax
	mov 	eax, 500
	sub 	eax, ebx
	mov 	ebx, 4
	div 	ebx

	mov 	[prev], eax

	cmp 	dword[final], eax
	jae 	.aproved
	
	write 	msg8, len8
	jmp 	.endexam

.aproved:
	write 	msg7, len7

.endexam:
	pop 	eax
	pop 	edx
	pop 	ebx
	pop 	ebp
	ret 

; @classificando a nota e verifica se foi p/ final 

level:
	push 	ebp
	
	cmp 	dword[mean], 90
	jae 	.lA
	cmp 	dword[mean], 80 
	jae 	.lB
	cmp 	dword[mean], 70 
	jae 	.lC
	cmp 	dword[mean], 60 
	jae 	.lD
	cmp 	dword[mean], 40
	jae 	.lE
	cmp 	dword[mean], 39 
	jbe 	.lF

.lA:
	; Conceito A   90-100 	APROVADO
	write 	msg7, len7
	mov 	byte[class], 'A'
	jmp 	.endlevel

.lB:
	; Conceito B	80-89	APROVADO
	write 	msg7, len7
	mov 	byte[class], 'B'
	jmp 	.endlevel

.lC:
	; Conceito C 	70-79	APROVADO
	write 	msg7, len7
	mov 	byte[class], 'C'
	jmp 	.endlevel

.lD:
	; Conceito D 	60-69	FINAL
	write 	msg9, len9
	call 	finalexam
	write 	msg14, len14
	mov 	esi, [prev]
	call 	inttostr
	mov 	byte[class], 'D'
	jmp 	.endlevel

.lE:
	; Conceito E 	40-59	FINAL
	write 	msg9, len9
	call 	finalexam
	write 	msg14, len14
	mov 	esi, [prev]
	call 	inttostr
	mov 	byte[class], 'E'
	jmp 	.endlevel

.lF:
	; Conceito F 	0-39	REPROVADO
	write 	msg8, len8
	mov 	byte[class], 'F'
	
.endlevel:
	write 	msg5, len5
	write 	class, 1
	pop 	ebp
	ret

; @convertendo string em inteiro

strtoint:
	push 	ebp
	push 	edx
	push 	ebx
	push 	esi

	mov 	ebx, 10
	xor 	eax, eax

.nextch:
 	xor 	edx, edx
 	mov 	dl, byte[esi]

	cmp 	dl, 30H
	jb 		.endch
	cmp 	dl, 39H
	ja 		.endch

	sub  	dl, 30H
	imul 	eax, ebx
	add 	eax, edx
	
	inc 	esi
	jmp 	.nextch

.endch:
	pop 	ebx
	pop 	esi
	pop 	edx
	pop 	ebp
	ret

; @converte string para inteiro 

inttostr:
	push 	ebp
	push 	edx
	push 	ebx
	push 	edi
	push 	esi
	push 	eax

	mov 	eax, esi
	xor 	esi, esi

.first:
	xor 	edx, edx
	mov 	ebx, 100
	div 	ebx
	inc 	esi
	jmp 	.print

.second:
	xor 	edx, edx
	mov 	ebx, 10
	div 	ebx
	inc 	esi
	jmp 	.print

.third:
	inc 	esi

.print:
	add 	eax, 30H
	mov 	[buffer], eax
	xor 	eax, eax
	mov 	edi, edx
	write 	buffer, 1
	mov 	eax, edi

	cmp 	esi, 1
	je 		.second
	cmp 	esi, 2
	je 		.third

endint:
	pop 	eax
	pop 	esi
 	pop 	ebx
 	pop 	edi
	pop 	edx
	pop 	ebp
	ret
