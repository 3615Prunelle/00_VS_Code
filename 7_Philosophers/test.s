	.text
	.file	"test.c"
	.globl	thread_routine                  # -- Begin function thread_routine
	.p2align	4, 0x90
	.type	thread_routine,@function
thread_routine:                         # @thread_routine
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	callq	pthread_self
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movabsq	$.L.str, %rdi
	movabsq	$.L.str.1, %rsi
	movabsq	$.L.str.2, %rcx
	movb	$0, %al
	callq	printf
	movl	$0, -20(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$1000000, -20(%rbp)             # imm = 0xF4240
	jge	.LBB0_4
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movl	i, %eax
	addl	$1, %eax
	movl	%eax, i
# %bb.3:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	thread_routine, .Lfunc_end0-thread_routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	leaq	-16(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	movabsq	$thread_routine, %rdx
	movq	%rcx, %rsi
	callq	pthread_create
	movq	-16(%rbp), %rsi
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	movabsq	$thread_routine, %rdx
	movq	%rcx, %rsi
	callq	pthread_create
	movq	-24(%rbp), %rsi
	movabsq	$.L.str.4, %rdi
	movb	$0, %al
	callq	printf
	movl	i, %esi
	movabsq	$.L.str.5, %rdi
	movb	$0, %al
	callq	printf
	movq	-16(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	movq	-16(%rbp), %rsi
	movabsq	$.L.str.6, %rdi
	movb	$0, %al
	callq	printf
	movq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	movq	-24(%rbp), %rsi
	movabsq	$.L.str.7, %rdi
	movb	$0, %al
	callq	printf
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	i,@object                       # @i
	.bss
	.globl	i
	.p2align	2
i:
	.long	0                               # 0x0
	.size	i, 4

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n"
	.size	.L.str, 67

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"\033[1;33m"
	.size	.L.str.1, 8

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"\033[0m"
	.size	.L.str.2, 5

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"Main: Creation du premier thread [%ld]\n"
	.size	.L.str.3, 40

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"Main: Creation du second thread [%ld]\n"
	.size	.L.str.4, 39

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"\ni = %d\n"
	.size	.L.str.5, 9

	.type	.L.str.6,@object                # @.str.6
.L.str.6:
	.asciz	"Main: Union du premier thread [%ld]\n"
	.size	.L.str.6, 37

	.type	.L.str.7,@object                # @.str.7
.L.str.7:
	.asciz	"Main: Union du second thread [%ld]\n"
	.size	.L.str.7, 36

	.ident	"Ubuntu clang version 12.0.1-19ubuntu3"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym thread_routine
	.addrsig_sym pthread_self
	.addrsig_sym printf
	.addrsig_sym pthread_create
	.addrsig_sym pthread_join
	.addrsig_sym i
