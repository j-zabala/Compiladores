	.file	"ej.c"
	.comm	a,4,4    se declara variable global
	.comm	b,4,4
	.text
	.globl	main
	.type	main, @function

main:
.LFB0:                 ------------

	pushq	%rbp

	movq	%rsp, %rbp
                                	estas 2 anteriores (tambien falta la resta que no esta por q no hay variables local) se puede remplazar por el enter


	movl	$2, a(%rip) (es asi pq llama a las variable global a y abajo la b)
	movl	$3, b(%rip)
	nop

	popq	%rbp     se puede reemplazar por el leave

	ret

.LFE0:         -------------------
	.size	main, .-main
