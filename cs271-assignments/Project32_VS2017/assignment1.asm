TITLE Program Template     (assignment1.asm)

; Author: Logan Saso
; Assembly Language 271 Assignment 1                Date: 1/17/2018
; Description: An introduction to the masm progamming language.

INCLUDE Irvine32.inc

.data

userName		BYTE	33 DUP(0) ; to be entered
intro			BYTE	"Hi, my name is logan and we'll do some math.", 0
namePrompt		BYTE	"What is your name? ", 0
goodbye			BYTE	"Thanks for running this assignment ", 0

description		BYTE	"This program will do some math to two numbers which you WILL input now or I'll fry ur motherboard.", 0

numPromptOne	BYTE	"Insert the first number: ", 0
numPromptTwo	BYTE	"Insert the second number: ", 0

addition		BYTE	"The result of adding those two numbers is: ", 0
subtraction		BYTE	"The result of subtracting those two numbers is: ", 0
multiplication	BYTE	"The result of multiplying those two numbers is: ", 0
division		BYTE	"The result of dividing those two numbers is: ", 0
remainder		BYTE	" with a remainder of ", 0

firstNumber		DWORD	?
secondNumber	DWORD	?

addResult		DWORD	?
subResult		DWORD	?
multResult		DWORD	?
divResult		DWORD	?
remainResult	DWORD	?


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

; get first number

	mov		edx, OFFSET numPromptOne
	call	WriteString
	call	ReadInt
	mov		firstNumber, eax

; get second number

	mov		edx, OFFSET numPromptTwo
	call	WriteString
	call	ReadInt
	mov		secondNumber, eax

; calculate and print addition

	mov		edx, OFFSET addition
	call	WriteString

	mov		eax, firstNumber
	add		eax, secondNumber
	mov		addResult, eax
	call	WriteDec
	call	CrLf

; calculate and print subtraction

	mov		edx, OFFSET subtraction
	call	WriteString

	mov		eax, firstNumber
	sub		eax, secondNumber
	mov		subResult, eax
	call	WriteDec
	call	CrLf

; calculate and print multiplication

	mov		edx, OFFSET multiplication
	call	WriteString

	mov		eax, firstNumber
	mul		secondNumber
	mov		multResult, eax
	call	WriteDec
	call	CrLf

; calculate and print division

	mov		edx, OFFSET division
	call	WriteString

	mov		edx, 0
	mov		eax, firstNumber
	mov		ecx, secondNumber
	div		ecx
	mov		divResult, eax
	mov		remainResult, edx
	
	call	WriteDec

; print remainder

	mov		edx, OFFSET remainder
	call	WriteString

	mov		eax, remainResult
	call	WriteDec
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
