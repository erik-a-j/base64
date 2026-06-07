	.file	"encode_3.c"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"=/"
	.text
	.p2align 4
	.globl	b64_encode
	.type	b64_encode, @function
b64_encode:
.LFB1:
	.cfi_startproc
	endbr64
	mov	r9, rdx
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	r8, rsi
	mov	r10, rcx
	mov	rdx, rdi
	cmp	rcx, 2
	jbe	.L40
	mov	esi, 3
	lea	rbx, .LC0[rip]
	jmp	.L19
	.p2align 4
	.p2align 3
.L15:
	cmp	al, 51
	jbe	.L45
	cmp	al, 61
	jbe	.L46
	and	r11d, 1
	movzx	eax, BYTE PTR [rbx+r11]
.L16:
	mov	BYTE PTR -1[rdx], al
	lea	rax, 3[rsi]
	cmp	r10, rax
	jb	.L47
.L41:
	mov	rsi, rax
.L19:
	movzx	eax, BYTE PTR -3[r9+rsi]
	mov	ecx, eax
	shr	cl, 2
	cmp	al, 103
	jbe	.L48
	cmp	cl, 51
	jbe	.L49
	cmp	cl, 61
	jbe	.L50
	and	ecx, 1
	movzx	ecx, BYTE PTR [rbx+rcx]
.L4:
	mov	BYTE PTR [rdx], cl
	movzx	ecx, BYTE PTR -2[r9+rsi]
	sal	eax, 4
	mov	r11d, ecx
	shr	r11b, 4
	add	eax, r11d
	mov	r11d, eax
	and	r11d, 63
	cmp	r11b, 25
	jbe	.L51
	cmp	r11b, 51
	jbe	.L52
	cmp	r11b, 61
	jbe	.L53
	and	eax, 1
	movzx	r11d, BYTE PTR [rbx+rax]
.L8:
	mov	BYTE PTR 1[rdx], r11b
	movzx	r11d, BYTE PTR -1[r9+rsi]
	mov	eax, r11d
	shr	al, 6
	lea	ecx, [rax+rcx*4]
	mov	eax, ecx
	and	eax, 63
	cmp	al, 25
	jbe	.L54
	cmp	al, 51
	jbe	.L55
	cmp	al, 61
	jbe	.L56
	and	ecx, 1
	movzx	eax, BYTE PTR [rbx+rcx]
.L12:
	mov	BYTE PTR 2[rdx], al
	mov	eax, r11d
	add	rdx, 4
	and	eax, 63
	cmp	al, 25
	ja	.L15
	add	eax, 65
	mov	BYTE PTR -1[rdx], al
	lea	rax, 3[rsi]
	cmp	r10, rax
	jnb	.L41
.L47:
	sub	r10, rsi
.L2:
	cmp	r10, 1
	je	.L57
	cmp	r10, 2
	je	.L58
.L27:
	mov	rax, rdx
	sub	rax, rdi
	cmp	rax, r8
	jnb	.L42
	mov	BYTE PTR [rdx], 0
.L42:
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4
	.p2align 3
.L54:
	.cfi_restore_state
	add	eax, 65
	jmp	.L12
	.p2align 4
	.p2align 3
.L51:
	add	r11d, 65
	jmp	.L8
	.p2align 4
	.p2align 3
.L48:
	add	ecx, 65
	jmp	.L4
	.p2align 4
	.p2align 3
.L55:
	add	eax, 71
	jmp	.L12
	.p2align 4
	.p2align 3
.L45:
	add	eax, 71
	jmp	.L16
	.p2align 4
	.p2align 3
.L52:
	add	r11d, 71
	jmp	.L8
	.p2align 4
	.p2align 3
.L49:
	add	ecx, 71
	jmp	.L4
	.p2align 4
	.p2align 3
.L50:
	sub	ecx, 4
	jmp	.L4
	.p2align 4
	.p2align 3
.L56:
	sub	eax, 4
	jmp	.L12
	.p2align 4
	.p2align 3
.L46:
	sub	eax, 4
	jmp	.L16
	.p2align 4
	.p2align 3
.L53:
	sub	r11d, 4
	jmp	.L8
	.p2align 4
	.p2align 3
.L58:
	movzx	ecx, BYTE PTR [r9+rsi]
	mov	eax, ecx
	shr	al, 2
	cmp	cl, 103
	jbe	.L59
	cmp	al, 51
	jbe	.L60
	cmp	al, 61
	jbe	.L61
	and	eax, 1
	lea	r10, .LC0[rip]
	movzx	eax, BYTE PTR [r10+rax]
.L29:
	mov	BYTE PTR [rdx], al
	movzx	eax, BYTE PTR 1[r9+rsi]
	sal	ecx, 4
	mov	esi, eax
	shr	sil, 4
	add	ecx, esi
	mov	esi, ecx
	and	esi, 63
	cmp	sil, 25
	jbe	.L62
	cmp	sil, 51
	jbe	.L63
	cmp	sil, 61
	jbe	.L64
	and	ecx, 1
	lea	rsi, .LC0[rip]
	movzx	esi, BYTE PTR [rsi+rcx]
.L33:
	mov	BYTE PTR 1[rdx], sil
	sal	eax, 2
	and	eax, 63
	cmp	al, 25
	jbe	.L65
	lea	esi, 71[rax]
	lea	ecx, -4[rax]
	cmp	al, 51
	mov	eax, esi
	cmova	eax, ecx
.L37:
	mov	BYTE PTR 2[rdx], al
	mov	BYTE PTR 3[rdx], 61
	add	rdx, 4
	jmp	.L27
	.p2align 4
	.p2align 3
.L57:
	movzx	eax, BYTE PTR [r9+rsi]
	mov	ecx, eax
	shr	cl, 2
	cmp	al, 103
	jbe	.L66
	cmp	cl, 51
	jbe	.L67
	cmp	cl, 61
	jbe	.L68
	and	ecx, 1
	lea	rsi, .LC0[rip]
	movzx	ecx, BYTE PTR [rsi+rcx]
.L22:
	mov	BYTE PTR [rdx], cl
	mov	WORD PTR 2[rdx], 15677
	sal	eax, 4
	and	eax, 63
	lea	esi, 65[rax]
	cmp	al, 25
	lea	ecx, 71[rax]
	mov	eax, esi
	cmova	eax, ecx
	add	rdx, 4
	mov	BYTE PTR -3[rdx], al
	jmp	.L27
.L67:
	add	ecx, 71
	jmp	.L22
.L59:
	add	eax, 65
	jmp	.L29
	.p2align 4
	.p2align 3
.L66:
	add	ecx, 65
	jmp	.L22
	.p2align 4
	.p2align 3
.L40:
	xor	esi, esi
	jmp	.L2
.L65:
	add	eax, 65
	jmp	.L37
.L62:
	add	esi, 65
	jmp	.L33
.L60:
	add	eax, 71
	jmp	.L29
.L68:
	sub	ecx, 4
	jmp	.L22
.L63:
	add	esi, 71
	jmp	.L33
.L61:
	sub	eax, 4
	jmp	.L29
.L64:
	sub	esi, 4
	jmp	.L33
	.cfi_endproc
.LFE1:
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
