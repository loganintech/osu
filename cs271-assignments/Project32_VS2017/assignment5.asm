TITLE Assignment 2

; Author: Logan Saso
; Assembly Language 271 Assignment 5                Date: 3/4/2018
; Description: Takes a variable and builds an array of random numbers, sorts those numbers, and prints the median.

INCLUDE Irvine32.inc

MIN		EQU		10
MAX		EQU		200
LO		EQU		100
HI		EQU		999

.data

introText		BYTE	"Hi, my name is Logan and we'll taking an input making a random number array, then sorting it.", 0
goodbyeText		BYTE	"Thanks for running this assignment!", 0

description		BYTE	"This program will print a specified number of composite numbers.", 0
instructions	BYTE	"Please input how many elements should be generated [10, 200] inclusive: ", 0

numPrompt		BYTE	"Insert a number between (1, 400) inclusive: ", 0

request			DWORD	?

array			DWORD	MAX	DUP(?)

arrayName		BYTE	"Random Numbers, Unsorted", 0
arraySorted		BYTE	"Random Numbers, Sorted", 0

numSpacing		BYTE	"   ", 0
median			BYTE	"The median is: ", 0

.code
main PROC

	call	Randomize

	call	intro

	call	CrLf


	;void getUserData(int* reference)
	push	OFFSET request 
	call	getUserData 

	call	CrLf
	
	;void fillArray(int size, int* array)
	push	request
	push	OFFSET array
	call	fillArray

	;void printList(char* numSpacing, int* array, int request, char* arrayName)
	push	OFFSET numSpacing
	push	OFFSET array
	push	request
	push	OFFSET arrayName
	call	printList


	push	OFFSET array
	push	request
	call	sortList

	;Visual sepparation between our lists
	call	CrLf
	call	CrLf

	;same as before, but now the list is sorted
	push	OFFSET numSpacing
	push	OFFSET array
	push	request
	push	OFFSET arraySorted
	call	printList

	;visual spacing
	call	CrLf
	call	CrLf

	push	OFFSET median
	push	OFFSET array
	push	request
	call	printMedian


	exit
main ENDP

intro PROC
	
	mov		edx, OFFSET introText
	call	WriteString
	call	CrLf

	ret	
intro ENDP

getUserData	PROC

	push	ebp
	mov		ebp, esp 

	numberGet: 

	;get how many elements to use
	mov		edx, OFFSET instructions
	call	WriteString
	call	ReadInt ;reads a number into EAX

	;validate number

	;validate upper
	cmp		eax, MAX
	jg		numberGet

	;validate lower
	cmp		eax, MIN
	jl		numberGet
	
	mov		ebx, [ebp + 8]
	mov		[ebx], eax
	pop		ebp

	ret		4
getUserData ENDP


; +8:  listLocation
; +12: listSize
fillArray PROC

	push	ebp
	mov		ebp, esp


	mov		ecx, [ebp + 12]
	mov		esi, [ebp + 8]
	mov		edx, 0


	setNumberLoop:
		mov		ebx, esi
		add		ebx, edx		

		;get our random number
		mov		eax, HI - LO + 1
		call	RandomRange
		add		eax, LO

		;move our random number to our array variable
		mov		[ebx], eax
	
		add		edx, 4
		loop	setNumberLoop

	pop		ebp
	ret		8

fillArray ENDP


; +8:  listNameString
; +12: listSize
; +16: listLocation
; +20: numSpacing
printList PROC

	push	ebp
	mov		ebp, esp

	;get our variables in some registers
	mov		esi, [ebp + 16]
	mov		ecx, [ebp + 12]

	mov		edx, [ebp + 8]
	call	WriteString
	
	xor		edx, edx

	printLoop:
	
		;store some values
		push	eax
		push	edx
		push	ecx		


		;newline every 10th number
		xor		edx, edx	
		mov		eax, ecx
		mov		ecx, 10
		div		ecx
	
		cmp		edx, 0
		jne		noSpacing

		call	CrLf		

		noSpacing:
		
		;pop said values
		pop		ecx
		pop		edx
		pop		eax
		
		;get our number
		mov		eax, [esi + edx]
		call	WriteDec
		
		;print some spacing
		push	edx
		mov		edx, [ebp + 20]
		call	WriteString
		pop		edx

		add		edx, 4
		loop	printLoop
	
	pop		ebp
	ret		12

printList ENDP

; +8:  listSize
; +12: listLocation
sortList PROC
	
	push	ebp
	mov		ebp, esp

;	int ecx = ;
;	int edx;
;	for(i = 0; i < listSize - 1; i++) {
;	    for(j = 0; j < listSize - i - 1; j++) {
;
;			if(listLocation[j] > listLocation[j + 1]) {
;			    swap(&listLocation[j], &listLocation[j + 1])		
;	        }
;		}
;	}

	mov		esi, [ebp + 12]

	mov		eax, [ebp + 8]
	sub		eax, 1

	;setting this up as I
	xor		ecx, ecx


	outerLoop:
	
	;is ecx larger than [ebp + 8] - 1
	;if it is, we're sorted
	;otherwise continue
	
	cmp		ecx, eax
	jge		endOuter

	;setting this up as j
	xor		edx, edx

		innerLoop: 

		;is edx larger than [ebp + 8] - ecx - 1
		;if it is, go to end of this loop
		;otherwise, continue
	
		mov		ebx, eax
		sub		ebx, ecx
		cmp		edx, ebx
		jge		endInner


		;reset ebx to base of array
		mov		ebx, esi	
		;push eax to store val
		push	eax
		;setup eax for mul
		mov		eax, edx
		
		push	edx
		push	ecx
		mov		ecx, 4
		mul		ecx
		pop		ecx
		pop		edx
		;add our bytes offset to our base array offset
		add		ebx, eax
		
		;return eax to former glory
		pop		eax
		
		;push our other offset to the stack		
		push	ebx
		add		ebx, 4
		push	ebx		
		;swap-em
		call	checkAndSwap


		add		edx, 1
		jmp		innerLoop
		;end inner loop
		endInner: 
	
	add		ecx, 1
	jmp		outerLoop
	;end outer loop
	endOuter: 

	pop		ebp
	ret		8
sortList ENDP

; +8:  right
; +12: left
checkAndSwap PROC

	push	ebp
	mov		ebp, esp

	;int temp = *left;
	;*left = *right;
	;*right = temp

	pushad

	mov		eax, [ebp+12]
	mov		eax, [eax]
	;now eax stores the value of the left side
	
	mov		ebx, [ebp+8]
	mov		ebx, [ebx]
	;now ebx stores the value of the right side

	cmp		ebx, eax
	jle		noSwap

	mov		ecx, [ebp+12]
	mov		[ecx], ebx
	;set the value of the left to the right

	mov		edx, [ebp+8]
	mov		[edx], eax
	;set the value of the right to the left

	noSwap:

	popad

	pop		ebp
	ret		8

checkAndSwap ENDP


; +8: listSize
; +12: array
; +16: medianText
printMedian	PROC

	push	ebp
	mov		ebp, esp

	mov		eax, [ebp + 8]
	xor		edx, edx
	mov		ecx, 2
	div		ecx
	;eax now stores the halfway point index

	mov		ecx, 4
	mul		ecx
	;eax now stores the halfway point address offset
	
	mov		edx, [ebp + 16]
	call	WriteString

	;get our array address
	mov		esi, [ebp + 12]
	;get the address of the median
	add		esi, eax
	mov		eax, esi
	;dereference that value
	mov		eax, [eax]
	;print that value
	call	WriteDec

	pop ebp
	ret

printMedian ENDP

END main
