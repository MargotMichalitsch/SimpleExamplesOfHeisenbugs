	.file	"CompilerReordering.c"
	.local	x
	.comm	x,4,4
	.local	y
	.comm	y,4,4
	.text
	.globl	threadFunc
	.type	threadFunc, @function
threadFunc:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$15, x(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	threadFunc, .-threadFunc
	.section	.rodata
.LC0:
	.string	"%i\n"
.LC1:
	.string	"CompilerReordering.c"
.LC2:
	.string	"y == 5"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	y(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$5, x(%rip)
	leaq	-8(%rbp), %rax
	movl	$0, %ecx
	movl	$threadFunc, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
.L4:
	movl	x(%rip), %eax
	movl	%eax, y(%rip)
	movl	y(%rip), %eax
	cmpl	$5, %eax
	je	.L4
	movl	$__PRETTY_FUNCTION__.3252, %ecx
	movl	$26, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.3252, @object
	.size	__PRETTY_FUNCTION__.3252, 5
__PRETTY_FUNCTION__.3252:
	.string	"main"
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
