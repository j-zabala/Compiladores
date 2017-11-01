	.file	"ej2.c"
	.comm	a,4,4
	.comm	b,4,4
	.text

	.globl	inc
	.type	inc, @function

inc:
.LFB0:

	pushq	%rbp

	movq	%rsp, %rbp

	movl	%edi, -4(%rbp)         mueve el primero al segundo (moveleft)

	movl	-4(%rbp), %eax
	addl	$1, %eax                // va haciendo la suma


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

	movl	$2, a(%rip)

	movl	a(%rip), %eax  //mueve el parametro en el edi
	movl	%eax, %edi


	call	inc          // llama a la funcion


	movl	%eax, b(%rip)   // a b le guarda lo que hay en el eax (donde estaria el resultado de inc (a))
	movl	b(%rip), %eax


	popq	%rbp

	ret

.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
