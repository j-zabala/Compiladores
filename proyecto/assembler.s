  .comm c,8 
  .text
  .globl	main
  .type	main, @function
main:
  LFB0:
  enter 0,$0
  movq $7,-16(%rbp) 
  movq -16(%rbp), %rax 
  movq rax, -8(%rbp) 
  movq $80,-24(%rbp) 
  movq -24(%rbp), %rax 
  movq rax, c(%rip) 
movq	-8(%rbp), %s 
call alo 
  leave
  LFE0:
.size	main, .-main  .globl	alo2
  .type	alo2, @function
alo2:
  LFB1:
  enter 1,$0
  movq  %s,rdi 
movq	-8(%rbp), %s 
call alo 
  leave
  LFE1:
.size	alo2, .-alo2  .globl	alo
  .type	alo, @function
alo:
  LFB2:
  enter 2,$0
  movq  %s,rdi 
  movq $1,-16(%rbp) 
movq	-8(%rbp), %rax 
add	-16(%rbp), %rax 
movq	 %rax,-24(%rbp) 
  movq -24(%rbp), %rax 
  movq rax, -8(%rbp) 
ret 
  leave
  LFE2:
.size	alo, .-alo