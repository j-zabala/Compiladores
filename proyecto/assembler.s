  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $48,$0
  movq $0,-16(%rbp) 
  movq $0,-24(%rbp) 
  movq	-16(%rbp), %rax 
  testq	%rax, %rax 
  jne	LAB4lOR 
  movq	-24(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB5lOR 
  LAB4lOR: 
  movq	 $1,-32(%rbp) 
  jmp	LAB6lOR 
  LAB5lOR: 
  movq	 $0,-32(%rbp) 
  LAB6lOR: 
  movq	-32(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-32(%rbp), %rax 
  jmp endmetodo0
  endmetodo0:
  leave
  ret 
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	breaks
  .type	breaks, @function
breaks:
.LFB1:
  enter $112,$0
  movq  %rdi,-8(%rbp) 
  movq $1,-32(%rbp) 
  movq -32(%rbp), %rax 
  movq %rax, -24(%rbp) 
  movq $0,-40(%rbp) 
  movq -40(%rbp), %rax 
  movq %rax, -16(%rbp) 
LAB0WHILE: 
  movq $10,-48(%rbp) 
  movq	 $0,-56(%rbp) 
  movq	-16(%rbp), %rdx 
  movq	-48(%rbp), %rax 
  cmp	%rax, %rdx
  jge	 LAB7.L 
  movq	 $1,-56(%rbp) 
LAB7.L: 
  movq	-56(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB8lAND 
  movq	-24(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB8lAND 
  movq	 $1,-64(%rbp) 
  jmp	LAB9lAND 
  LAB8lAND: 
  movq	 $0,-64(%rbp) 
  LAB9lAND: 
  cmp $1,-64(%rbp)  
  jne LAB1ENDWHILE 
  movq $1,-72(%rbp) 
  movq	-16(%rbp), %rax 
  add	-72(%rbp), %rax 
  movq	 %rax,-80(%rbp) 
  movq -80(%rbp), %rax 
  movq %rax, -16(%rbp) 
  movq $0,-88(%rbp) 
  movq	 $0,-96(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-88(%rbp), %rax 
  cmp	%rax, %rdx
  jge	 LAB10.L 
  movq	 $1,-96(%rbp) 
LAB10.L: 
  cmp $1,-96(%rbp)  
  jne LAB2ELSE 
  movq $0,-104(%rbp) 
  movq -104(%rbp), %rax 
  movq %rax, -24(%rbp) 
  jmp LAB3ENDIF 
LAB2ELSE: 
LAB3ENDIF: 
  jmp LAB0WHILE 
LAB1ENDWHILE: 
  movq	-16(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-16(%rbp), %rax 
  jmp endmetodo1
  endmetodo1:
  leave
  ret 
.LFE1:
  .size	breaks, .-breaks
.LC1:
  .string	"la funcion breaks devuelve: %i "  
