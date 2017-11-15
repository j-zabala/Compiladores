  .comm c,8 
  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $32,$0
  movq $16,-8(%rbp) 
  movq -8(%rbp), %rax 
  movq %rax, c(%rip) 
  movq $55,-16(%rbp) 
  movq	-16(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-16(%rbp), %rax 
  jmp endmetodo0
  endmetodo0:
  leave
  ret 
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	id
  .type	id, @function
id:
.LFB1:
  enter $16,$0
  movq  %rdi,-8(%rbp) 
  movq	-8(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  jmp endmetodo1
  endmetodo1:
  leave
  ret 
.LFE1:
  .size	id, .-id
.LC1:
  .string	"la funcion id devuelve: %i "  
