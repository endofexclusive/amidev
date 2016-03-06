; This is the crt code for any program.

	section	".text", code
	public	_start
	cnop	0,4

_start:
	; Lower interrupt priority level.
	;move.w	#$2000, sr
	;move.w	#$0000, sr

	; Set stack pointer if defined by linker.
	move.l	#__stack, d0
	beq	.keep_sp
	move.l	d0, sp
.keep_sp:

	;; Create a stack frame.
	link	a6, #-8

	; .data section should already be loaded
        ; Clear .bss section, PC relative.
.clear_bss:
	lea	__bss_start(pc), a0
        move.l  a0, a1
        move.l  #__bss_size, d0
        add.l   d0, a1
	bra	.clear_bss_first
.clear_bss_loop:
	move.l	#0, (a0)+
.clear_bss_first:
	cmp.l	a0, a1
	bne	.clear_bss_loop

        lea     $dff000, a5
	bsr	main

	trap	#1

