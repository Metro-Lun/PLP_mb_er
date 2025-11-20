	.file	"aire.c"
	.text
	.p2align 4
	.globl	calculer_aire
	.type	calculer_aire, @function
calculer_aire:
.LFB0:
	.cfi_startproc
	endbr64
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	.LC0(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	mulsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	calculer_aire, .-calculer_aire
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC3:
	.string	"L'aire du cercle de rayon %.2f est %.2f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC3(%rip), %rdi
	movl	$2, %eax
	movsd	.LC1(%rip), %xmm1
	movsd	.LC2(%rip), %xmm0
	call	printf@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1413754136
	.long	1074340347
	.align 8
.LC1:
	.long	1610612736
	.long	1079222924
	.align 8
.LC2:
	.long	0
	.long	1075052544
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
