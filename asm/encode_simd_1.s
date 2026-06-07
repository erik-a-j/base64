	.file	"encode_simd_1.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.string	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
	.text
	.p2align 4
	.globl	b64_encode
	.type	b64_encode, @function
b64_encode:
.LFB6447:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	r10, rdi
	mov	r9, rcx
	mov	rdi, rsi
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	rsi, rdx
	push	r13
	mov	r8, r10
	push	r12
	push	rbx
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	cmp	rcx, 63
	jbe	.L2
	vmovdqa64	zmm7, ZMMWORD PTR .LC0[rip]
	vmovdqa64	zmm6, ZMMWORD PTR .LC2[rip]
	mov	edx, 264305664
	xor	eax, eax
	vmovdqa64	zmm5, ZMMWORD PTR .LC3[rip]
	vmovdqa64	zmm4, ZMMWORD PTR .LC5[rip]
	vpbroadcastd	zmm3, edx
	mov	edx, 4129776
	vpbroadcastd	zmm2, edx
	.p2align 4
	.p2align 3
.L3:
	vpermb	zmm0, zmm7, ZMMWORD PTR [rsi+rax]
	mov	rdx, rax
	add	r8, 64
	add	rax, 48
	add	rdx, 112
	vpandd	zmm1, zmm3, zmm0
	vpandd	zmm0, zmm2, zmm0
	vpmulhuw	zmm1, zmm1, zmm6
	vpmullw	zmm0, zmm4, zmm0
	vpord	zmm0, zmm0, zmm1
	vpermb	zmm0, zmm0, zmm5
	vmovdqu64	ZMMWORD PTR -64[r8], zmm0
	cmp	r9, rdx
	jnb	.L3
	sub	r9, rax
	add	rsi, rax
	mov	rax, r8
	sub	rax, r10
	sub	rdi, rax
	vzeroupper
.L2:
	mov	rcx, r8
	cmp	r9, 2
	jbe	.L10
	mov	edx, 3
	lea	r11, .LC6[rip]
	.p2align 4
	.p2align 3
.L5:
	movzx	r12d, BYTE PTR -2[rsi+rdx]
	movzx	eax, BYTE PTR -3[rsi+rdx]
	movzx	r10d, BYTE PTR -1[rsi+rdx]
	add	rcx, 4
	mov	r13d, r12d
	mov	ebx, eax
	shr	r13b, 4
	sal	eax, 4
	add	r13d, eax
	mov	eax, r10d
	and	r10d, 63
	shr	al, 6
	lea	r12d, [rax+r12*4]
	movzx	eax, BYTE PTR [r11+r10]
	and	r13d, 63
	and	r12d, 63
	movzx	r10d, BYTE PTR [r11+r12]
	shr	bl, 2
	sal	eax, 8
	or	eax, r10d
	movzx	r10d, BYTE PTR [r11+r13]
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
	jnb	.L5
	sub	r9, rax
.L4:
	cmp	r9, 1
	je	.L16
	cmp	r9, 2
	je	.L17
.L7:
	mov	rax, rcx
	sub	rax, r8
	cmp	rax, rdi
	jnb	.L13
	mov	BYTE PTR [rcx], 0
.L13:
	pop	rbx
	pop	r12
	pop	r13
	pop	rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4
	.p2align 3
.L17:
	.cfi_restore_state
	movzx	edx, BYTE PTR [rsi+rax]
	movzx	r10d, BYTE PTR 1[rsi+rax]
	xor	eax, eax
	mov	BYTE PTR 3[rcx], 61
	add	rcx, 4
	mov	esi, edx
	shr	sil, 2
	movzx	r9d, sil
	lea	rsi, .LC6[rip]
	mov	al, BYTE PTR [rsi+r9]
	mov	r9d, r10d
	sal	edx, 4
	shr	r9b, 4
	add	edx, r9d
	and	edx, 63
	mov	ah, BYTE PTR [rsi+rdx]
	mov	WORD PTR -4[rcx], ax
	lea	eax, 0[0+r10*4]
	and	eax, 60
	movzx	eax, BYTE PTR [rsi+rax]
	mov	BYTE PTR -2[rcx], al
	jmp	.L7
	.p2align 4
	.p2align 3
.L16:
	movzx	eax, BYTE PTR [rsi+rax]
	lea	r9, .LC6[rip]
	xor	edx, edx
	mov	WORD PTR 2[rcx], 15677
	add	rcx, 4
	mov	esi, eax
	shr	sil, 2
	sal	eax, 4
	movzx	esi, sil
	and	eax, 48
	mov	dl, BYTE PTR [r9+rsi]
	movzx	eax, BYTE PTR [r9+rax]
	mov	dh, al
	mov	WORD PTR -4[rcx], dx
	jmp	.L7
	.p2align 4
	.p2align 3
.L10:
	xor	eax, eax
	jmp	.L4
	.cfi_endproc
.LFE6447:
	.size	b64_encode, .-b64_encode
	.section	.rodata
	.align 64
.LC0:
	.byte	1
	.byte	0
	.byte	2
	.byte	1
	.byte	4
	.byte	3
	.byte	5
	.byte	4
	.byte	7
	.byte	6
	.byte	8
	.byte	7
	.byte	10
	.byte	9
	.byte	11
	.byte	10
	.byte	13
	.byte	12
	.byte	14
	.byte	13
	.byte	16
	.byte	15
	.byte	17
	.byte	16
	.byte	19
	.byte	18
	.byte	20
	.byte	19
	.byte	22
	.byte	21
	.byte	23
	.byte	22
	.byte	25
	.byte	24
	.byte	26
	.byte	25
	.byte	28
	.byte	27
	.byte	29
	.byte	28
	.byte	31
	.byte	30
	.byte	32
	.byte	31
	.byte	34
	.byte	33
	.byte	35
	.byte	34
	.byte	37
	.byte	36
	.byte	38
	.byte	37
	.byte	40
	.byte	39
	.byte	41
	.byte	40
	.byte	43
	.byte	42
	.byte	44
	.byte	43
	.byte	46
	.byte	45
	.byte	47
	.byte	46
	.align 64
.LC2:
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.value	64
	.value	1024
	.align 64
.LC3:
	.byte	65
	.byte	66
	.byte	67
	.byte	68
	.byte	69
	.byte	70
	.byte	71
	.byte	72
	.byte	73
	.byte	74
	.byte	75
	.byte	76
	.byte	77
	.byte	78
	.byte	79
	.byte	80
	.byte	81
	.byte	82
	.byte	83
	.byte	84
	.byte	85
	.byte	86
	.byte	87
	.byte	88
	.byte	89
	.byte	90
	.byte	97
	.byte	98
	.byte	99
	.byte	100
	.byte	101
	.byte	102
	.byte	103
	.byte	104
	.byte	105
	.byte	106
	.byte	107
	.byte	108
	.byte	109
	.byte	110
	.byte	111
	.byte	112
	.byte	113
	.byte	114
	.byte	115
	.byte	116
	.byte	117
	.byte	118
	.byte	119
	.byte	120
	.byte	121
	.byte	122
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.byte	43
	.byte	47
	.align 64
.LC5:
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
	.value	16
	.value	256
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
