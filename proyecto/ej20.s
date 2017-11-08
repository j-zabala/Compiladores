	.file	"ej20.c"
	.comm	a,4,4
	.comm	b,4,4
	.text
	.globl	inc
	.type	inc, @function
inc:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -4(%rbp)
	movl	-20(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	inc, .-inc
	.section	.rodata

.LC0:
	.string	"la funcion devuelve: %i"

	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$2, -4(%rbp)
	movl	$2, a(%rip)
	movl	a(%rip), %eax
	movl	%eax, %edi
	call	inc
	movl	%eax, -4(%rbp)





	movl	-4(%rbp), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf




	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
