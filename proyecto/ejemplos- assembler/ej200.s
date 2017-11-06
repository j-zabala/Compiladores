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

	movl	%edi, -4(%rbp)

	movl	%esi, -8(%rbp)

	movl	%edx, -12(%rbp)

	movl	%ecx, -16(%rbp)

	movl	%r8d, -20(%rbp)

	movl	%r9d, -24(%rbp)

	movl	-4(%rbp), %edx

	movl	-8(%rbp), %eax
	addl	%eax, %edx

	movl	-12(%rbp), %eax
	addl	%eax, %edx

	movl	-16(%rbp), %eax
	addl	%eax, %edx

	movl	-20(%rbp), %eax
	addl	%eax, %edx

	movl	-24(%rbp), %eax
	addl	%eax, %edx

	movl	16(%rbp), %eax
	addl	%eax, %edx

	movl	24(%rbp), %eax
	addl	%eax, %edx

	movl	32(%rbp), %eax
	addl	%edx, %eax

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	inc, .-inc
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
	subq	$48, %rsp
	movl	$2, -44(%rbp)
	movl	$20, -40(%rbp)
	movl	$40, -36(%rbp)
	movl	$33, -32(%rbp)
	movl	$15, -28(%rbp)
	movl	$22, -24(%rbp)
	movl	$9, -20(%rbp)
	movl	$11, -16(%rbp)
	movl	$1, -12(%rbp)
	movl	$22, -8(%rbp)


	movl	-24(%rbp), %r9d
	movl	-28(%rbp), %r8d
	movl	-32(%rbp), %ecx
	movl	-36(%rbp), %edx
	movl	-40(%rbp), %esi

	movl	-44(%rbp), %eax

	movl	-8(%rbp), %edi
	pushq	%rdi

	movl	-12(%rbp), %edi
	pushq	%rdi

	movl	-16(%rbp), %edi
	pushq	%rdi

	movl	-20(%rbp), %edi
	pushq	%rdi

	movl	%eax, %edi

	call	inc
	addq	$32, %rsp
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -44(%rbp)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
