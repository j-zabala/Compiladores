  .comm c,8 
  .text
  .globl	main
  .type	main, @function
main:
.LFB0:
  enter $160,$0
  movq $16,-8(%rbp) 
  movq -8(%rbp), %rax 
  movq %rax, c(%rip) 
  movq $1,-16(%rbp) 
  movq $2,-24(%rbp) 
  movq	-16(%rbp), %rax 
  add	-24(%rbp), %rax 
  movq	 %rax,-32(%rbp) 
  movq $3,-40(%rbp) 
  movq	-32(%rbp), %rax 
  add	-40(%rbp), %rax 
  movq	 %rax,-48(%rbp) 
  movq $4,-56(%rbp) 
  movq	-48(%rbp), %rax 
  add	-56(%rbp), %rax 
  movq	 %rax,-64(%rbp) 
  movq $5,-72(%rbp) 
  movq	-64(%rbp), %rax 
  add	-72(%rbp), %rax 
  movq	 %rax,-80(%rbp) 
  movq $6,-88(%rbp) 
  movq	-80(%rbp), %rax 
  add	-88(%rbp), %rax 
  movq	 %rax,-96(%rbp) 
  movq $7,-104(%rbp) 
  movq	-96(%rbp), %rax 
  add	-104(%rbp), %rax 
  movq	 %rax,-112(%rbp) 
  movq $8,-120(%rbp) 
  movq	-112(%rbp), %rax 
  add	-120(%rbp), %rax 
  movq	 %rax,-128(%rbp) 
  movq $9,-136(%rbp) 
  movq	-128(%rbp), %rax 
  add	-136(%rbp), %rax 
  movq	 %rax,-144(%rbp) 
  movq	-144(%rbp), %rsi 
  movq $.LC0,%rdi
  movq	$0, %rax 
  call printf
  movq	-144(%rbp), %rax 
  jmp endmetodo0
  endmetodo0:
  leave
  ret 
.LFE0:
  .size	main, .-main
.LC0:
  .string	"la funcion main devuelve: %i "  
  .globl	fibonacci
  .type	fibonacci, @function
fibonacci:
.LFB1:
  enter $192,$0
  movq  %rdi,-8(%rbp) 
  movq $1,-40(%rbp) 
  movq -40(%rbp), %rax 
  movq %rax, -16(%rbp) 
  movq $1,-48(%rbp) 
  movq -48(%rbp), %rax 
  movq %rax, -24(%rbp) 
  movq $2,-56(%rbp) 
  movq -56(%rbp), %rax 
  movq %rax, -32(%rbp) 
  movq $2,-64(%rbp) 
  movq	 $0,-72(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-64(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB10.L 
  movq	 $1,-72(%rbp) 
LAB10.L: 
  cmp $1,-72(%rbp)  
  jne LAB0ELSE 
LAB2WHILE: 
  movq $2,-80(%rbp) 
  movq	 $0,-88(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-80(%rbp), %rax 
  cmp	%rax, %rdx
  jle	 LAB11.L 
  movq	 $1,-88(%rbp) 
LAB11.L: 
  cmp $1,-88(%rbp)  
  jne LAB3ENDWHILE 
  movq -24(%rbp), %rax 
  movq %rax, -16(%rbp) 
  movq -32(%rbp), %rax 
  movq %rax, -24(%rbp) 
  movq	-16(%rbp), %rax 
  add	-24(%rbp), %rax 
  movq	 %rax,-104(%rbp) 
  movq	-104(%rbp),%rdi 
  call id 
  movq	%rax, -96(%rbp)  
  movq -96(%rbp), %rax 
  movq %rax, -32(%rbp) 
  movq $1,-112(%rbp) 
  movq	-8(%rbp), %rax 
  sub	-112(%rbp), %rax 
  movq	 %rax,-120(%rbp) 
  movq -120(%rbp), %rax 
  movq %rax, -8(%rbp) 
  jmp LAB2WHILE 
LAB3ENDWHILE: 
  movq	-32(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-32(%rbp), %rax 
  jmp endmetodo1
  jmp LAB1ENDIF 
LAB0ELSE: 
LAB1ENDIF: 
  movq $2,-128(%rbp) 
  movq	 $0,-136(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-128(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB12.L 
  movq	 $1,-136(%rbp) 
LAB12.L: 
  cmp $1,-136(%rbp)  
  jne LAB4ELSE 
  movq	-32(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-32(%rbp), %rax 
  jmp endmetodo1
  jmp LAB5ENDIF 
LAB4ELSE: 
LAB5ENDIF: 
  movq $1,-144(%rbp) 
  movq	 $0,-152(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-144(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB13.L 
  movq	 $1,-152(%rbp) 
LAB13.L: 
  cmp $1,-152(%rbp)  
  jne LAB6ELSE 
  movq	-24(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-24(%rbp), %rax 
  jmp endmetodo1
  jmp LAB7ENDIF 
LAB6ELSE: 
LAB7ENDIF: 
  movq $0,-160(%rbp) 
  movq	 $0,-168(%rbp) 
  movq	-8(%rbp), %rdx 
  movq	-160(%rbp), %rax 
  cmp	%rax, %rdx
  jne	 LAB14.L 
  movq	 $1,-168(%rbp) 
LAB14.L: 
  cmp $1,-168(%rbp)  
  jne LAB8ELSE 
  movq	-16(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-16(%rbp), %rax 
  jmp endmetodo1
  jmp LAB9ENDIF 
LAB8ELSE: 
  movq $0,-176(%rbp) 
  movq	-176(%rbp), %rsi 
  movq $.LC1,%rdi
  movq	$0, %rax 
  call printf
  movq	-176(%rbp), %rax 
  jmp endmetodo1
LAB9ENDIF: 
  endmetodo1:
  leave
  ret 
.LFE1:
  .size	fibonacci, .-fibonacci
.LC1:
  .string	"la funcion fibonacci devuelve: %i "  
  .globl	id
  .type	id, @function
id:
.LFB2:
  enter $16,$0
  movq  %rdi,-8(%rbp) 
  movq	-8(%rbp), %rsi 
  movq $.LC2,%rdi
  movq	$0, %rax 
  call printf
  movq	-8(%rbp), %rax 
  jmp endmetodo2
  endmetodo2:
  leave
  ret 
.LFE2:
  .size	id, .-id
.LC2:
  .string	"la funcion id devuelve: %i "  
