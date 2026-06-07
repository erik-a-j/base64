.LC0:
        .string "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
"b64_encode":
        test    rdi, rdi
        je      .L1
        test    rdx, rdx
        je      .L1
        test    sil, 3
        je      .L59
        test    rcx, rcx
        je      .L7
.L6:
        lea     r10, [rdx-3+rcx]
        lea     r9, [rdx-2+rcx]
        lea     r8, [rdx-1+rcx]
.L9:
        movzx   eax, BYTE PTR [rdx]
        mov     ecx, eax
        shr     cl, 2
        movzx   ecx, cl
        movzx   ecx, BYTE PTR .LC0[rcx]
        mov     BYTE PTR [rdi], cl
        cmp     rsi, 1
        je      .L1
        sal     eax, 4
        and     eax, 48
        cmp     rdx, r8
        jne     .L11
        movzx   eax, BYTE PTR .LC0[rax]
        mov     BYTE PTR [rdi+1], al
        cmp     rsi, 2
        je      .L1
        mov     BYTE PTR [rdi+2], 61
        cmp     rsi, 3
        je      .L60
.L12:
        mov     BYTE PTR [rdi+3], 61
        cmp     rsi, 4
        je      .L1
        add     rdi, 4
.L7:
        mov     BYTE PTR [rdi], 0
        ret
.L13:
        movzx   eax, BYTE PTR .LC0[rax]
        mov     BYTE PTR [rdi+2], al
        cmp     rsi, 3
        jne     .L12
.L1:
        ret
.L59:
        mov     rax, rsi
        shr     rax, 2
        lea     rax, [rax+rax*2]
        cmp     rcx, rax
        je      .L61
        test    rsi, rsi
        je      .L1
        test    rcx, rcx
        jne     .L6
        test    rsi, rsi
        jne     .L7
        ret
.L11:
        movzx   ecx, BYTE PTR [rdx+1]
        mov     r11d, ecx
        shr     r11b, 4
        add     rax, r11
        and     eax, 127
        movzx   eax, BYTE PTR .LC0[rax]
        mov     BYTE PTR [rdi+1], al
        cmp     rsi, 2
        je      .L1
        lea     eax, [0+rcx*4]
        and     eax, 60
        cmp     rdx, r9
        je      .L13
        movzx   ecx, BYTE PTR [rdx+2]
        mov     r11d, ecx
        shr     r11b, 6
        add     rax, r11
        and     eax, 127
        movzx   eax, BYTE PTR .LC0[rax]
        mov     BYTE PTR [rdi+2], al
        cmp     rsi, 3
        je      .L62
        and     ecx, 63
        add     rdi, 4
        movzx   eax, BYTE PTR .LC0[rcx]
        mov     BYTE PTR [rdi-1], al
        sub     rsi, 4
        je      .L1
        cmp     rdx, r10
        je      .L7
        add     rdx, 3
        jmp     .L9
.L61:
        lea     rsi, [rdx+rcx]
        test    rcx, rcx
        je      .L63
.L10:
        movzx   eax, BYTE PTR [rdx]
        add     rdi, 4
        add     rdx, 3
        mov     ecx, eax
        sal     eax, 4
        shr     cl, 2
        movzx   ecx, cl
        movzx   ecx, BYTE PTR .LC0[rcx]
        mov     BYTE PTR [rdi-4], cl
        movzx   ecx, BYTE PTR [rdx-2]
        mov     r8d, ecx
        shr     r8b, 4
        add     eax, r8d
        and     eax, 63
        movzx   eax, BYTE PTR .LC0[rax]
        mov     BYTE PTR [rdi-3], al
        movzx   eax, BYTE PTR [rdx-1]
        mov     r8d, eax
        and     eax, 63
        shr     r8b, 6
        movzx   eax, BYTE PTR .LC0[rax]
        lea     ecx, [r8+rcx*4]
        and     ecx, 63
        movzx   ecx, BYTE PTR .LC0[rcx]
        mov     BYTE PTR [rdi-2], cl
        mov     BYTE PTR [rdi-1], al
        cmp     rdx, rsi
        jne     .L10
        ret
.L63:
        ret
.L60:
        ret
.L62:
        ret