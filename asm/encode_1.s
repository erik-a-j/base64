	.file	"encode_1.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
	.text
	.p2align 4
	.globl	b64_encode
	.type	b64_encode, @function
b64_encode:
.LFB0:
	.cfi_startproc
	endbr64
	test	rcx, rcx
	je	.L2
	test	rsi, rsi
	je	.L66
	movzx	eax, BYTE PTR [rdx]
	mov	r8d, eax
	shr	r8b, 2
	movzx	r9d, r8b
	lea	r8, .LC0[rip]
	movzx	r9d, BYTE PTR [r8+r9]
	mov	BYTE PTR [rdi], r9b
	cmp	rsi, 1
	je	.L66
	sal	eax, 4
	lea	r10, -1[rdx+rcx]
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	lea	r9, -2[rdx+rcx]
	lea	rbx, -3[rdx+rcx]
	and	eax, 48
	cmp	rdx, r10
	je	.L4
	.p2align 4
	.p2align 3
.L76:
	movzx	ecx, BYTE PTR 1[rdx]
	mov	r11d, ecx
	shr	r11b, 4
	add	rax, r11
	and	eax, 127
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR 1[rdi], al
	cmp	rsi, 2
	je	.L64
	lea	eax, 0[0+rcx*4]
	and	eax, 60
	cmp	r9, rdx
	je	.L9
	movzx	ecx, BYTE PTR 2[rdx]
	mov	r11d, ecx
	shr	r11b, 6
	add	rax, r11
	and	eax, 127
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR 2[rdi], al
	cmp	rsi, 3
	je	.L64
	and	ecx, 63
	add	rdi, 4
	sub	rsi, 4
	movzx	eax, BYTE PTR [r8+rcx]
	mov	BYTE PTR -1[rdi], al
	je	.L64
	cmp	rdx, rbx
	jne	.L75
	mov	rax, rdi
.L14:
	mov	BYTE PTR [rax], 0
.L64:
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L75:
	.cfi_restore_state
	movzx	eax, BYTE PTR 3[rdx]
	add	rdx, 3
	mov	ecx, eax
	shr	cl, 2
	movzx	ecx, cl
	movzx	ecx, BYTE PTR [r8+rcx]
	mov	BYTE PTR [rdi], cl
	cmp	rsi, 1
	je	.L64
	sal	eax, 4
	and	eax, 48
	cmp	rdx, r10
	jne	.L76
.L4:
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR 1[rdi], al
	cmp	rsi, 2
	je	.L64
	mov	BYTE PTR 2[rdi], 61
	cmp	rsi, 3
	je	.L64
.L59:
	lea	rax, 4[rdi]
	mov	BYTE PTR 3[rdi], 61
	cmp	rsi, 4
	jne	.L14
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L9:
	.cfi_restore_state
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR 2[rdi], al
	cmp	rsi, 3
	jne	.L59
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
.L2:
	.cfi_restore 3
	test	rsi, rsi
	je	.L66
	mov	BYTE PTR [rdi], 0
.L66:
	ret
	.cfi_endproc
.LFE0:
	.size	b64_encode, .-b64_encode
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
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
