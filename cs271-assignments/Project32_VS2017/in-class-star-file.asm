TITLE Program Template     (template.asm)

; Author:
; Course / Project ID                 Date:
; Description:

INCLUDE Irvine32.inc

; (insert constant definitions here)

.data

star	BYTE	"*", 0

outerLoopCounter	DWORD	1
innerLoopCounter	DWORD	1


; (insert variable definitions here)

.code
main PROC

; (insert executable instructions here)

outerLoop:
innerLoop:

	mov		eax, innerLoopCounter
	cmp		eax, outerLoopCounter
	jle		printNumber


printStar:
	mov		edx, OFFSET star
	call	WriteString
	jmp		afterPrint

printNumber:
	mov		edx, innerLoopCounter
	call	WriteDec

afterPrint:
	
	mov		eax, innerLoopCounter
	add		eax, 1
	mov		innerLoopCounter, eax
	cmp		eax, 6
	je		endInner
	jmp		innerLoop
endInner:

	call	CrLf

	mov		eax, outerLoopCounter
	add		eax, 1
	mov		outerLoopCounter, eax
	cmp		eax, 6
	je		endOuter

	mov		innerLoopCounter, 1
	jmp		outerLoop
endOuter:
67
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)


END main
