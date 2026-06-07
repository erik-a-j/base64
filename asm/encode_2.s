	.file	"encode_2.c"
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
	cmp	rcx, 2
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r9, rcx
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	r8, rdx
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rcx, rdi
	jbe	.L7
	mov	edx, 3
	lea	r11, .LC0[rip]
	.p2align 4
	.p2align 3
.L3:
	movzx	r12d, BYTE PTR -2[r8+rdx]
	movzx	eax, BYTE PTR -3[r8+rdx]
	movzx	r10d, BYTE PTR -1[r8+rdx]
	add	rcx, 4
	mov	ebp, r12d
	mov	ebx, eax
	shr	bpl, 4
	sal	eax, 4
	add	ebp, eax
	mov	eax, r10d
	and	r10d, 63
	shr	al, 6
	lea	r12d, [rax+r12*4]
	movzx	eax, BYTE PTR [r11+r10]
	and	ebp, 63
	and	r12d, 63
	movzx	r10d, BYTE PTR [r11+r12]
	shr	bl, 2
	sal	eax, 8
	or	eax, r10d
	movzx	r10d, BYTE PTR [r11+rbp]
	movzx	ebx, bl
	sal	eax, 8
	or	eax, r10d
	movzx	r10d, BYTE PTR [r11+rbx]
	sal	eax, 8
	or	eax, r10d
	mov	DWORD PTR -4[rcx], eax
	mov	rax, rdx
	lea	rdx, 3[rdx]
	cmp	r9, rdx
	jnb	.L3
	sub	r9, rax
.L2:
	cmp	r9, 1
	je	.L12
	cmp	r9, 2
	je	.L13
.L5:
	mov	rax, rcx
	sub	rax, rdi
	cmp	rax, rsi
	jnb	.L9
	mov	BYTE PTR [rcx], 0
.L9:
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L13:
	.cfi_restore_state
	movzx	edx, BYTE PTR [r8+rax]
	movzx	r10d, BYTE PTR 1[r8+rax]
	xor	eax, eax
	mov	BYTE PTR 3[rcx], 61
	add	rcx, 4
	mov	r8d, edx
	shr	r8b, 2
	movzx	r9d, r8b
	lea	r8, .LC0[rip]
	mov	al, BYTE PTR [r8+r9]
	mov	r9d, r10d
	sal	edx, 4
	shr	r9b, 4
	add	edx, r9d
	and	edx, 63
	movzx	ebx, BYTE PTR [r8+rdx]
	mov	ah, bl
	mov	WORD PTR -4[rcx], ax
	lea	eax, 0[0+r10*4]
	and	eax, 60
	movzx	eax, BYTE PTR [r8+rax]
	mov	BYTE PTR -2[rcx], al
	jmp	.L5
	.p2align 4
	.p2align 3
.L12:
	movzx	eax, BYTE PTR [r8+rax]
	lea	r9, .LC0[rip]
	xor	edx, edx
	mov	WORD PTR 2[rcx], 15677
	add	rcx, 4
	mov	r8d, eax
	shr	r8b, 2
	sal	eax, 4
	movzx	r8d, r8b
	and	eax, 48
	mov	dl, BYTE PTR [r9+r8]
	movzx	eax, BYTE PTR [r9+rax]
	mov	dh, al
	mov	WORD PTR -4[rcx], dx
	jmp	.L5
	.p2align 4
	.p2align 3
.L7:
	xor	eax, eax
	jmp	.L2
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
