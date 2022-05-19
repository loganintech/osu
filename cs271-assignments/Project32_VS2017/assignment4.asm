TITLE Assignment 2

; Author: Logan Saso
; Assembly Language 271 Assignment 4                Date: 2/18/2018
; Description: Takes a number as input and prints that number of composite values.

INCLUDE Irvine32.inc

LOWER_BOUND		EQU		1
UPPER_BOUND		EQU		400z

.data

userName		BYTE	33 DUP(0) ; to be entered
introText		BYTE	"Hi, my name is Logan and we'll taking an input and showing composite numbers.", 0
namePrompt		BYTE	"What is your name? ", 0
goodbyeText		BYTE	"Thanks for running this assignment ", 0

description		BYTE	"This program will print a specified number of composite numbers.", 0

numPrompt		BYTE	"Insert a number between (1, 400) inclusive: ", 0

numToPrint		DWORD	?
thisIsComposite DWORD	0 ;0 for false, 1 for true

numSpacing		BYTE	"     ", 0
checkingNum		DWORD	?

.code
main PROC

	call	intro
	call	getUserData
	call	showComposites
	call	goodbye


	exit
main ENDP

intro PROC
	
	mov		edx, OFFSET introText
	call	WriteString
	call	CrLf

	ret
intro ENDP

getUserData	PROC

	;get user's name
	mov		edx, OFFSET namePrompt
	call	WriteString
	mov		edx, OFFSET userName
	mov		ecx, 32
	call	ReadString

	numberGet:

	;get number
	mov		edx, OFFSET numPrompt
	call	WriteString
	call	ReadInt

	;validate number
	call	validate
	cmp		ebx, 1
	je		numberGet

	mov		numToPrint, eax

	ret
getUserData ENDP

validate PROC

	;validate upper
	cmp		eax, UPPER_BOUND
	jg		invalid

	;validate lower
	cmp		eax, LOWER_BOUND
	jl		invalid
	
	xor		ebx, ebx
	ret

	invalid:
	mov		ebx, 1
	ret

validate ENDP

showComposites PROC

	mov		ecx, numToPrint
	sub		ecx, 1 ;This adjusts for the addition, which runs because we don't want to dec our counter unless it prints something
	mov		eax, 2 ;This will store what we are dividing. Our starting composite, if you will

	composShowStart:

		cmp		thisIsComposite, 0
		je		addOneToECX
	afterAdd:
		pushad
		call	isComposite
		popad

		cmp		thisIsComposite, 1
		jne		notFoundComposite

	foundComposite:
		call	WriteDec

		pushad
		mov		eax, ecx	;move number printed to be divided
		xor		edx, edx	;clear sign
		mov		ebx, 5		;because we can't divide by an immediate value
		div		ebx 
		cmp		edx, 0		;see if the division is even

		jne		spaces

		call	CrLf
		jmp		noSpaces

		spaces:
		mov		edx, OFFSET numSpacing
		call	WriteString

		noSpaces:

		popad

	notFoundComposite:

		inc		eax

	loop	composShowStart

	call	CrLf
	ret


	addOneToEcx:
		
		inc ecx
		jmp afterAdd

showComposites ENDP


isComposite	PROC
	;eax stores value to check
	;edx must be cleared for division
	;we're going to divide by 2, then 3 and add 2 each time until the number is met. If it divides by any of those it's composite
	mov		checkingNum, eax
	xor		edx, edx
	mov		ecx, 2

	;do the loop once at div 2
	cmp		ecx, eax
	jge		isntCompositeVal

	div		ecx
	cmp		edx, 0
	je		isCompositeVal

	inc		ecx
	;now ecx is 3

	divLoop:

	mov		eax, checkingNum
	xor		edx, edx
	;if they are the same or ecx is greater we haven't found a composite
	cmp		ecx, eax
	jge		isntCompositeVal

	div		ecx
	cmp		edx, 0
	je		isCompositeVal

	add		ecx, 2
	jmp		divLoop


	isCompositeVal:
	mov		thisIsComposite, 1
	ret

	isntCompositeVal:
	mov		thisIsComposite, 0
	ret

isComposite ENDP

goodbye PROC

	mov		edx, OFFSET goodbyeText
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	call	CrLf

	ret

goodbye ENDP

END main
