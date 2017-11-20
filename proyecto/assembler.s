  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $48,$0
  movq $200,-16(%rbp) 
  movq $330,-24(%rbp) 
  movq $400,-32(%rbp) 
  movq	-32(%rbp),%rdx 
  movq	-24(%rbp),%rsi 
  movq	-16(%rbp),%rdi 
  call promedio 
  movq	%rax, -8(%rbp)  
  movq	-8(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  jmp endmetodo0
  endmetodo0:
  leave
  ret 
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	promedio
  .type	promedio, @function
promedio:
.LFB1:
  enter $224,$0
  movq  %rdi,-8(%rbp) 
  movq  %rsi,-16(%rbp) 
  movq  %rdx,-24(%rbp) 
  movq	 $0,-32(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-24(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB8.L 
  movq	 $1,-32(%rbp) 
LAB8.L: 
  movq	 $0,-40(%rbp) 
  movq	-16(%rbp), %rdx 
  movq	-24(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB9.L 
  movq	 $1,-40(%rbp) 
LAB9.L: 
  movq	-32(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB10lAND 
  movq	-40(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB10lAND 
  movq	 $1,-48(%rbp) 
  jmp	LAB11lAND 
  LAB10lAND: 
  movq	 $0,-48(%rbp) 
  LAB11lAND: 
  cmp $1,-48(%rbp)  
  jne LAB0ELSE 
  movq	-8(%rbp), %rax 
  add	-16(%rbp), %rax 
  movq	 %rax,-56(%rbp) 
  movq $20,-64(%rbp) 
  movq	$0, %rdx 
  movq	-56(%rbp), %rax 
  movq -64(%rbp),%rbx 
  cqo
  idiv %rbx 
  movq	 %rax,-72(%rbp) 
  movq	-72(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-72(%rbp), %rax 
  jmp endmetodo1
  jmp LAB1ENDIF 
LAB0ELSE: 
LAB1ENDIF: 
  movq	 $0,-80(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-16(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB12.L 
  movq	 $1,-80(%rbp) 
LAB12.L: 
  movq	 $0,-88(%rbp) 
  movq	-24(%rbp), %rdx 
  movq	-16(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB13.L 
  movq	 $1,-88(%rbp) 
LAB13.L: 
  movq	-80(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB14lAND 
  movq	-88(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB14lAND 
  movq	 $1,-96(%rbp) 
  jmp	LAB15lAND 
  LAB14lAND: 
  movq	 $0,-96(%rbp) 
  LAB15lAND: 
  cmp $1,-96(%rbp)  
  jne LAB2ELSE 
  movq	-8(%rbp), %rax 
  add	-24(%rbp), %rax 
  movq	 %rax,-104(%rbp) 
  movq $20,-112(%rbp) 
  movq	$0, %rdx 
  movq	-104(%rbp), %rax 
  movq -112(%rbp),%rbx 
  cqo
  idiv %rbx 
  movq	 %rax,-120(%rbp) 
  movq	-120(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-120(%rbp), %rax 
  jmp endmetodo1
  jmp LAB3ENDIF 
LAB2ELSE: 
LAB3ENDIF: 
  movq	 $0,-128(%rbp) 
  movq	-16(%rbp), %rdx 
  movq	-8(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB16.L 
  movq	 $1,-128(%rbp) 
LAB16.L: 
  movq	 $0,-136(%rbp) 
  movq	-24(%rbp), %rdx 
  movq	-8(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB17.L 
  movq	 $1,-136(%rbp) 
LAB17.L: 
  movq	-128(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB18lAND 
  movq	-136(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB18lAND 
  movq	 $1,-144(%rbp) 
  jmp	LAB19lAND 
  LAB18lAND: 
  movq	 $0,-144(%rbp) 
  LAB19lAND: 
  cmp $1,-144(%rbp)  
  jne LAB4ELSE 
  movq	-24(%rbp), %rax 
  add	-16(%rbp), %rax 
  movq	 %rax,-152(%rbp) 
  movq $20,-160(%rbp) 
  movq	$0, %rdx 
  movq	-152(%rbp), %rax 
  movq -160(%rbp),%rbx 
  cqo
  idiv %rbx 
  movq	 %rax,-168(%rbp) 
  movq	-168(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-168(%rbp), %rax 
  jmp endmetodo1
  jmp LAB5ENDIF 
LAB4ELSE: 
LAB5ENDIF: 
  movq	 $0,-176(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-16(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB20.L 
  movq	 $1,-176(%rbp) 
LAB20.L: 
  movq	 $0,-184(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-24(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB21.L 
  movq	 $1,-184(%rbp) 
LAB21.L: 
  movq	-176(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB22lAND 
  movq	-184(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB22lAND 
  movq	 $1,-192(%rbp) 
  jmp	LAB23lAND 
  LAB22lAND: 
  movq	 $0,-192(%rbp) 
  LAB23lAND: 
  movq	 $0,-200(%rbp) 
  movq	-16(%rbp), %rdx 
  movq	-24(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB24.L 
  movq	 $1,-200(%rbp) 
LAB24.L: 
  movq	-192(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB25lAND 
  movq	-200(%rbp), %rax 
  testq	%rax, %rax 
  je	LAB25lAND 
  movq	 $1,-208(%rbp) 
  jmp	LAB26lAND 
  LAB25lAND: 
  movq	 $0,-208(%rbp) 
  LAB26lAND: 
  cmp $1,-208(%rbp)  
  jne LAB6ELSE 
  movq	-8(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  jmp endmetodo1
  jmp LAB7ENDIF 
LAB6ELSE: 
LAB7ENDIF: 
  movq $10,-216(%rbp) 
  movq	-216(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-216(%rbp), %rax 
  jmp endmetodo1
  endmetodo1:
  leave
  ret 
.LFE1:
  .size	promedio, .-promedio
.LC1:
  .string	"la funcion promedio devuelve: %i "  
