  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $32,$0
  movq $7,-16(%rbp) 
  movq -16(%rbp), %rax 
  movq %rax, -8(%rbp) 
  movq	-8(%rbp),%rdi 
  call inc 
  movq	%rax, -24(%rbp)  
  movq -24(%rbp), %rax 
  movq %rax, -8(%rbp) 
  movq	-8(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  ret 
  leave
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	inc
  .type	inc, @function
inc:
.LFB1:
  enter $32,$0
  movq  %rdi,-8(%rbp) 
  movq $1,-16(%rbp) 
  movq	-8(%rbp), %rax 
  add	-16(%rbp), %rax 
  movq	 %rax,-24(%rbp) 
  movq -24(%rbp), %rax 
  movq %rax, -8(%rbp) 
  movq	-8(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  ret 
  leave
.LFE1:
  .size	inc, .-inc
.LC1:
  .string	"la funcion inc devuelve: %i "  
