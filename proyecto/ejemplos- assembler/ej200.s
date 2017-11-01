	.file	"ej200.c"
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

	pushq	%rbp

	movq	%rsp, %rbp


	subq	$32, %rsp

	movl	$2, -20(%rbp)
	movl	$20, -16(%rbp)
	movl	$40, -12(%rbp)
	movl	$33, -8(%rbp)
	movl	$15, -4(%rbp)

	movl	-16(%rbp), %eax
	leal	2(%rax), %edx

	movl	-12(%rbp), %eax

	addl	%eax, %edx


	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
	movl	%eax, %edi
	call	inc
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %eax
	leave

	ret

.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
