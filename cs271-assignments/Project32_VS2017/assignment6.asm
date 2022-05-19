TITLE Assignment 2

; Author: Logan Saso
; Assembly Language 271 Assignment 6                Date: 3/18/2018
; Description: Takes 10 unsigned positive integars and prints them, their sum, and their average.

INCLUDE Irvine32.inc

; largest 32 bit uint is 4294967295
MAX_CHAR	EQU		10




.data

introText		BYTE	"Hi, my name is Logan and we'll taking 10 unsigned positive 32bit integars and doing some math with them.", 0
goodbyeText		BYTE	"Thanks for running this assignment!", 0

description		BYTE	"This program will print a specified number of composite numbers.", 0
numPrompt		BYTE	"Please enter an unsigned 32bit number: ", 0
invalidNumStr	BYTE	"That is not a valid 32-bit number! Try again.", 0

; an array of 10, 4-byte (32-bit) segments of memory
array			DWORD	10	DUP(?)

numSpacing		BYTE	"  ", 0
arrayLabel		BYTE	"The array is: ", 0
averageText		BYTE	"The average is: ", 0
sumText			BYTE	"The sum is: ", 0

singleNumString	BYTE	11	DUP(0)
correctOrderStr	BYTE	11	DUP(0)
singleNum		DWORD	?
didCarry		DWORD	?

displayString MACRO stringOffset 

	push	edx

	mov		edx, stringOffset
	call	WriteString

	pop		edx

ENDM

getString MACRO	destinationAddress

	pushad
	mov		edx, destinationAddress
	mov		ecx, MAX_CHAR

	call	ReadString

	popad

ENDM

.code
main PROC

	push	OFFSET introText
	call	intro
	call	CrLf

	push	OFFSET invalidNumStr
	push	OFFSET didCarry
	push	OFFSET singleNum
	push	OFFSET singleNumString
	push	OFFSET numPrompt
	push	OFFSET array 
	call	fillArray 

	call	CrLf
	

	displayString OFFSET arrayLabel
	push	OFFSET numSpacing
	push	OFFSET correctOrderStr
	push	OFFSET singleNumString
	push	OFFSET array
	call	printArray
	call	CrLf

	displayString OFFSET sumText
	push	OFFSET correctOrderStr
	push	OFFSET singleNumString
	push	OFFSET array
	call	printSum
	call	CrLf

	displayString OFFSET averageText
	push	OFFSET correctOrderStr
	push	OFFSET singleNumString
	push	OFFSET array
	call	printAverage
	call	CrLf


	exit
main ENDP

intro PROC
	
	push	ebp
	mov		ebp, esp
				
	displayString [ebp + 8]

	pop		ebp

	ret		4
intro ENDP


; +8:  array
; +12: numPrompt
; +16: singleNumString
; +20: singleNum
; +24: didCarry
; +28: invalidNumStr
fillArray PROC

	push	ebp
	mov		ebp, esp

	pushad
	
	;our array start
	mov		eax, [ebp + 8]
	mov		edx, [ebp + 12]

	;we only want 10 numbers
	mov		ecx, 10
	
loadStart:


	displayString	edx
	push	[ebp + 24]
	push	[ebp + 20]
	push	[ebp + 16]
	call	readVal 

	mov		ebx, [ebp + 24]
	mov		ebx, [ebx]
	cmp		ebx, 1
	jne		didntCarry

	add		ecx, 1
	
	displayString [ebp + 28]
	call	CrLf

	jmp		endCarryCheck
	didntCarry:


	push ebx
	push ecx
	push edx

	push eax
	

	mov		eax, 4
	mul		ecx
	mov		ecx, eax
	sub		ecx, 4

	pop eax

	mov		ebx, [ebp + 20]
	mov		ebx, [ebx]
	
	push	eax
	add		eax, ecx
	mov		[eax], ebx
	pop		eax

	pop edx
	pop ecx
	pop ebx


	endCarryCheck:
	
	loop	loadStart
loadEnd:

	popad

	pop		ebp
	ret		24

fillArray ENDP

; +8: singleNumString
; +12: singleNum
; +16: didCarry
readVal PROC
	push	ebp
	mov		ebp, esp

	pushad

	getString [ebp + 8]

	push	  [ebp + 16]
	push	  [ebp + 12]
	push 	  [ebp + 8]
	call	  convertToNum

	popad
	pop		ebp
	
	ret		12
readVal	ENDP

; +8 numString
; +12 numDest
; +16 didCarry
convertToNum PROC
	push	ebp
	mov		ebp, esp

	pushad

	

	mov		esi, [ebp + 8]
	mov		ecx, [ebp + 16]
	push	edx
	mov		edx, 0
	mov		[ecx], edx
	pop		edx

	cld
	xor		edx, edx
	xor		eax, eax

nextDigit:
	;we have to multiply each digit by another factor of 10. This moves the entire number "over one" and makes room for the next digit
	push	eax
	mov		eax, 10
	mul		edx
	mov		edx, eax
	pop		eax
	;check to see that our multiplication didn't just unsigned overflow
	jc		invalidNumber

	;load the first byte from esi into al	
	lodsb

	;Check for our null terminator
	cmp		al, 0
	je		noMoreDigits

	;In ascii, the numbers start at the 48th index. This converts char to number
	sub		al, 48
	;If we are left with a value greater than 10, they put in a non-numeric character
	cmp		al, 10
	jge		invalidNumber
	
	;We should not have a negative number here ever, but let's check anyways
	cmp		al, 0
	jl		invalidNumber
	
	;Add our number to our total. 
	add		edx, eax
	;check to see that our addition didn't just unsigned overflow
	jc		invalidNumber

	jmp		nextDigit

invalidNumber:
	push	edx
	mov		edx, 1
	mov		[ecx], edx
	pop		edx

noMoreDigits: 

	mov		ecx, [ebp + 12]

	mov		eax, edx
	xor		edx, edx

	push	ecx
	mov		ecx, 10
	div		ecx
	pop		ecx

	mov		[ecx], eax

	popad
	
	pop		ebp
	ret		12
convertToNum ENDP


; +8 array
; +12 singleNumString
; +16 correctOrderStr
; +20 numSpacing
printArray PROC
	push	ebp
	mov		ebp, esp
	pushad
	
	mov		esi, [ebp + 8]
	mov		ecx, 10

	startPrint:

		mov		eax, [esi]
		
		push	[ebp + 16]
		push	[ebp + 12]
		push	eax
		call	writeVal

		displayString [ebp + 20]

		add		esi, 4


		loop	startPrint
	

	popad
	pop		ebp
	ret		12

printArray ENDP

; +8 array
; +12 singleNumString
; +16 correctOrderStr
printSum	PROC
	push	ebp
	mov		ebp, esp
	pushad


	mov		esi, [ebp + 8]
	mov		ecx, 10
	xor		edx, edx
	startAdd:

		mov		eax, [esi]
		add		edx, eax
		add		esi, 4

		loop	startAdd

	mov		eax, edx
	push	[ebp + 16]
	push	[ebp + 12]
	push	eax
	call	writeVal

	popad
	pop		ebp
	ret		12
printSum	ENDP

; +8 array
; +12 singleNumString
printAverage PROC

	push	ebp
	mov		ebp, esp
	pushad


	mov		esi, [ebp + 8]
	mov		ecx, 10
	xor		edx, edx
	startAdd:

		mov		eax, [esi]
		add		edx, eax
		add		esi, 4

		loop	startAdd

	mov		eax, edx
	xor		edx, edx
	mov		ecx, 10
	div		ecx
	
	push	[ebp + 16]
	push	[ebp + 12]
	push	eax
	call	writeVal

	popad
	pop		ebp
	ret		12

printAverage ENDP

; +8 val
; +12 singleNumString
; +16 correctOrderStr
writeVal PROC
	push	ebp
	mov		ebp, esp
	pushad
	
	mov		ecx, 11
	mov		edi, [ebp + 12]
	
fillZero:
	xor		edx, edx
	mov		[edi], edx
	inc		edi
	loop	fillZero







	mov		ecx, 10
	mov		edi, [ebp + 12]
	mov		eax, [ebp + 8]
	add		edi, ecx
	mov		ebx, 10

load:
	xor		edx, edx
	div		ebx
	add		dl, 48
	;edx (dl) now contains the char representation of the far right number
	
	mov		[edi], dl
	dec		edi
	loop	load
		

	displayString edi

	popad
	pop		ebp
	ret		12
writeVal ENDP

END main

