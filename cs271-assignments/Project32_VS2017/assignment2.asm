TITLE Assignment 2

; Author: Logan Saso
; Assembly Language 271 Assignment 2                Date: 1/28/2018
; Description: Prints fibonacci numbers up to a user-specified bound

INCLUDE Irvine32.inc

UPPER_BOUND		EQU		46

.data

userName		BYTE	33 DUP(0) ; to be entered
intro			BYTE	"Hi, my name is Logan and we'll be printing some Fibonacci numbers.", 0
namePrompt		BYTE	"What is your name? ", 0
goodbye			BYTE	"Thanks for running this assignment ", 0

description		BYTE	"This program will be calculating Fibonacci numbers up to a specified target value.", 0

numPrompt		BYTE	"Insert a number between (exclusive) 0 and 47: ", 0
invalidNumInput	BYTE	"I'm sorry, but that is not a number between 1 and 46 inclusive. Try again.", 0

upperBound		DWORD	?

numberSpacing	BYTE	"     ", 0

quotientValue	DWORD	?
loopCounter		DWORD	?

.code
main PROC

; introduction

	mov		edx, OFFSET intro
	call	WriteString
	call	CrLf

; get user name 

	mov		edx, OFFSET namePrompt
	call	WriteString
	mov		edx, OFFSET userName
	mov		ecx, 32
	call	ReadString

; get upper bound and validate

upperBoundLoop:

	mov		edx, OFFSET numPrompt
	call	WriteString
	call	ReadInt
	mov		upperBound, eax

	cmp		eax, UPPER_BOUND
	jg		invalidInput

	cmp		eax, 0
	jle		invalidInput

	jmp		loopEnd

invalidInput:

	mov		edx, OFFSET invalidNumInput
	call	WriteString
	call	CrLf
	jmp		upperBoundLoop

loopEnd:

; debug

	;mov		eax, upperBound
	;call	WriteDec
	;call	CrLf

; write Fibonacci numbers

	;first we need to calculate the quotient of dividing by 5 so when it matches we can print a newline
	mov		edx, 0
	mov		eax, upperBound
	mov		ecx, 5
	div		ecx

	;This is an if statement to adjust the quotient up one so that it prints 5 properly, but also doesn't print on the first line
	cmp		edx, 4
	je		setZero
	
	add		edx, 1
	jmp		noZero

setZero:
	mov		edx, 0

noZero:
	mov		quotientValue, edx
	

	;now setup our loop
	mov		eax, 1
	mov		ebx, 0
	mov		ecx, upperBound


fibLoopStart:
	
	add		eax, ebx
	call	WriteDec			;Print our fib value

	mov		edx, OFFSET numberSpacing ;Prepare our WriteString spacing
	call	WriteString ;Writes the spaces we moved into edx above

	mov		edi, ebx
	mov		ebx, eax			;swap half our numbers for a second. EDI still holds what eax will be 

	; This section does a division to see if the quotient matches what we looked for earlier
	mov		edx, 0				;clear before division
	mov		eax, ecx			;divisor
	mov		loopCounter, ecx	;store our progress
	mov		ecx, 5
	div		ecx
	cmp		edx, quotientValue
	jne		noNewline

	call	CrLf

	noNewline: 

	;now we restore loop conditions
	mov		ecx, loopCounter	;restore loopcounter
	mov		eax, edi			;set eax to fib value

	noNewLineBlock:

	loop	fibLoopStart
	call	CrLf

; say goodbye

	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	call	CrLf


	exit	; exit to operating system
main ENDP

END main
