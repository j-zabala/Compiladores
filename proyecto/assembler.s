  .comm res,8 
  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $64,$0
  movq $0,-16(%rbp) 
  movq -16(%rbp), %rax 
  movq %rax, res(%rip) 
  movq $6,-40(%rbp) 
  movq	-40(%rbp),%rdi 
  call inc 
  movq	%rax, -32(%rbp)  
  movq $102,-48(%rbp) 
  movq	-48(%rbp),%rsi 
  movq	-32(%rbp),%rdi 
  call resto 
  movq	%rax, -24(%rbp)  
  movq -24(%rbp), %rax 
  movq %rax, -8(%rbp) 
  movq $1,-56(%rbp) 
  movq	-56(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-56(%rbp), %rax 
  jmp endmetodo0
  endmetodo0:
  leave
  ret 
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	resto
  .type	resto, @function
resto:
.LFB1:
  enter $112,$0
  movq  %rdi,-8(%rbp) 
  movq  %rsi,-16(%rbp) 
  movq $3,-32(%rbp) 
  movq $2,-40(%rbp) 
  movq	-32(%rbp), %rax 
  imul	-40(%rbp), %rax 
  movq	 %rax,-48(%rbp) 
  movq	 $0,-56(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-48(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB2.L 
  movq	 $1,-56(%rbp) 
LAB2.L: 
  cmp $1,-56(%rbp)  
  jne LAB0ELSE 
  movq	-8(%rbp), %rax 
  imul	$-1, %rax 
  movq	 %rax,-64(%rbp) 
  movq $3,-72(%rbp) 
  movq	$0, %rdx 
  movq	-64(%rbp), %rax 
  movq -72(%rbp),%rbx 
  cqo
  idiv %rbx 
  movq	 %rdx,-80(%rbp) 
  movq -80(%rbp), %rax 
  movq %rax, -24(%rbp) 
  jmp LAB1ENDIF 
LAB0ELSE: 
  movq $2,-88(%rbp) 
  movq	-8(%rbp), %rax 
  add	-88(%rbp), %rax 
  movq	 %rax,-96(%rbp) 
  movq -96(%rbp), %rax 
  movq %rax, -24(%rbp) 
LAB1ENDIF: 
  movq	-24(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-24(%rbp), %rax 
  jmp endmetodo1
  endmetodo1:
  leave
  ret 
.LFE1:
  .size	resto, .-resto
.LC1:
  .string	"la funcion resto devuelve: %i "  
  .globl	inc
  .type	inc, @function
inc:
.LFB2:
  enter $32,$0
  movq  %rdi,-8(%rbp) 
  movq $1,-16(%rbp) 
  movq	-8(%rbp), %rax 
  add	-16(%rbp), %rax 
  movq	 %rax,-24(%rbp) 
  movq	-24(%rbp), %rsi 
  movq $.LC2,%rdi
  movq	$0, %rax 
  call printf
  movq	-24(%rbp), %rax 
  jmp endmetodo2
  endmetodo2:
  leave
  ret 
.LFE2:
  .size	inc, .-inc
.LC2:
  .string	"la funcion inc devuelve: %i "  
