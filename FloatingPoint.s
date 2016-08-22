	.file	"FloatingPoint.c"
	.local	a
	.comm	a,8,8
	.local	b
	.comm	b,8,8
	.section	.rodata
.LC1:
	.string	"a: %f\n"
	.text
	.globl	func1
	.type	func1, @function
func1:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movsd	a(%rip), %xmm1
	movsd	.LC0(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm0
	movsd	.LC3(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm1
	movsd	.LC4(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm0
	movsd	.LC5(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm1
	movsd	.LC6(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movsd	a(%rip), %xmm0
	movsd	.LC7(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, a(%rip)
	movq	a(%rip), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	addl	$1, -4(%rbp)
.L2:
	cmpl	$9, -4(%rbp)
	jle	.L3
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	func1, .-func1
	.globl	func2
	.type	func2, @function
func2:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movsd	b(%rip), %xmm1
	movsd	.LC0(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm0
	movsd	.LC3(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm1
	movsd	.LC4(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm0
	movsd	.LC5(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm1
	movsd	.LC6(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	movsd	b(%rip), %xmm0
	movsd	.LC7(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, b(%rip)
	addl	$1, -4(%rbp)
.L5:
	cmpl	$9, -4(%rbp)
	jle	.L6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	func2, .-func2
	.section	.rodata
.LC8:
	.string	"FloatingPoint.c"
.LC9:
	.string	"a == b"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	call	func1
	movl	$0, %eax
	call	func2
	movsd	a(%rip), %xmm0
	movsd	b(%rip), %xmm1
	ucomisd	%xmm1, %xmm0
	jp	.L11
	ucomisd	%xmm1, %xmm0
	je	.L12
.L11:
	movl	$__PRETTY_FUNCTION__.3793, %ecx
	movl	$51, %edx
	movl	$.LC8, %esi
	movl	$.LC9, %edi
	call	__assert_fail
.L12:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.3793, @object
	.size	__PRETTY_FUNCTION__.3793, 5
__PRETTY_FUNCTION__.3793:
	.string	"main"
	.align 8
.LC0:
	.long	1719614413
	.long	1072079006
	.align 8
.LC2:
	.long	2333366121
	.long	1074118410
	.align 8
.LC3:
	.long	2405181686
	.long	1070134722
	.align 8
.LC4:
	.long	1697350398
	.long	1073157447
	.align 8
.LC5:
	.long	1413754136
	.long	1074340347
	.align 8
.LC6:
	.long	1719614413
	.long	1073127582
	.align 8
.LC7:
	.long	1841940611
	.long	1070882608
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
