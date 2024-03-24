IO8255 equ 0270h
IO8255in equ 0270h
IO8255out equ 0271h
IO8255ctl equ 0273h6

_stack segment stack
	dw 100 dup(?)
_stack ends

_data segment
_data ends

code segment
assume cs:code, ds:_data, ss:_stack
start proc near
	mov ax, _data
	mov ds, ax
	mov dx, IO8255ctl
	mov al, 10010000B
	out dx, al

input:
	mov dx, IO8255in
	in ax, dx
	and ax, 00ffh
	cmp ax, 0
	jz q1
	cmp ax, 00ffh
	jz q2
	
	mov dx, IO8255out
	not ax
	out dx, ax
	jmp input
q1:
	mov ax, 007fh
	mov dx, IO8255out
gogo:
	call delay
	out dx, ax
	rol al, 1
	cmp ax, 007fh
	jne gogo
	jmp input
q2:
	mov ax, 00feh
	mov dx, IO8255out
gogo2:
	call delay
	out dx, ax
	ror al, 1
	cmp ax, 00feh
	jne gogo2
	jmp input
	
delay proc
	xor cx, cx
	loop $
	ret
delay endp

start endp
code ends
end start
