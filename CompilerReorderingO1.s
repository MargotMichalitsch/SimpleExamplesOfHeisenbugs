	.file	"CompilerReordering.c"
	.text
	.globl	threadFunc
	.type	threadFunc, @function
threadFunc:
.LFB22:
	.cfi_startproc
	movl	$15, x(%rip)
	ret
	.cfi_endproc
.LFE22:
	.size	threadFunc, .-threadFunc
	.section	.rodata.str1.1,"aMS",@progbits,1
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
.LFB23:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	y(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$5, x(%rip)
	movl	$0, %ecx
	movl	$threadFunc, %edx
	movl	$0, %esi
	leaq	8(%rsp), %rdi
	call	pthread_create
	movl	x(%rip), %eax
.L3:
	cmpl	$5, %eax
	je	.L3
	movl	%eax, y(%rip)
	movl	$__PRETTY_FUNCTION__.3329, %ecx
	movl	$26, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.3329, @object
	.size	__PRETTY_FUNCTION__.3329, 5
__PRETTY_FUNCTION__.3329:
	.string	"main"
	.local	y
	.comm	y,4,4
	.local	x
	.comm	x,4,4
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
