TITLE Assignment 2

; Author: Logan Saso
; Assembly Language 271 Assignment 3                Date: 2/11/2018
; Description: Accepts negative numbers until a positive is entered, then prints the average.

INCLUDE Irvine32.inc

LOWER_BOUND			EQU		-100

.data

userName		BYTE	33 DUP(0) ; to be entered
intro			BYTE	"Hi, my name is Logan and we'll taking some input and computing an average.", 0
namePrompt		BYTE	"What is your name? ", 0
goodbye			BYTE	"Thanks for running this assignment ", 0
noNumbers		BYTE	"Looks like you didn't input any numbers. Oh well!", 0

description		BYTE	"This program will accept input (-100, -1) inclusive and once you input a positive number, will print an average.", 0

numPrompt		BYTE	"Insert a number between (-100, -1) inclusive: ", 0

upperBound		SDWORD	-1
currentValue	SDWORD  0
numNums			DWORD	0

numNumbsMessage	BYTE	"You entered this many numbers: ", 0
currValMessage	BYTE	"The current value is: ", 0
averageMessage	BYTE	"The average is: ", 0



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

; start looping

mainLoop: 
	
	; get number
	mov		edx, OFFSET numPrompt
	call	WriteString
	call	ReadInt

	;validate upper
	cmp		eax, upperBound
	jg		invalidNumber

	;validate lower
	cmp		eax, LOWER_BOUND
	jl		invalidNumber

	;if both valid, add value and restart
	add		numNums, 1
	add		currentValue, eax
	mov		eax, 0
	jmp		mainLoop

invalidNumber:

	;check to see if numbers were entered and skip noNumber if there was
	cmp		currentValue, 0
	jne		someNumbers
	
	mov		edx, OFFSET noNumbers
	call	WriteString
	call	CrLf
	jmp		noNumsJump


someNumbers:
	
	;print numNumbers
	mov		edx, OFFSET numNumbsMessage
	call	WriteString
	mov		eax, numNums
	call	WriteDec
	call	CrLf

	;print sum
	mov		edx, OFFSET currValMessage
	call	WriteString
	mov		eax, currentValue
	call	WriteInt
	call	CrLf

	;do division for average
	mov		edx, 0
	mov		eax, currentValue
	cdq
	mov		ecx, numNums
	idiv	ecx
	
	;print division - eax is already setup
	mov		edx, OFFSET averageMessage
	call	WriteString
	call	WriteInt
	call	CrLf

noNumsJump:

; say goodbye

	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	call	CrLf


	call	ReadString
	exit	; exit to operating system
main ENDP

END main
