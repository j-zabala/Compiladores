	.file	"ej20.c"
	.comm	a,4,4
	.comm	b,4,4
	.text
	.globl	inc
	.type	inc, @function
inc:
.LFB0:

	pushq	%rbp

	movq	%rsp, %rbp

	movl	%edi, -20(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -4(%rbp)
	movl	-20(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp

	ret

.LFE0:
	.size	inc, .-inc
	.globl	main
	.type	main, @function


main:
.LFB1:
//////////////////////////
	pushq	%rbp                      siempre lo hacemos, tambien podemos usar el enter

	movq	%rsp, %rbp

	subq	$16, %rsp                   pide de 16 para 4 o menos var, si son 5 pide 32...
////////////////////////////


	movl	$2, -4(%rbp)
	movl	$2, a(%rip)
	movl	a(%rip), %eax
	movl	%eax, %edi

	call	inc

	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax

	leave

	ret

.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
