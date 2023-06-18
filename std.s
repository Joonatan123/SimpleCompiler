        .global _start

        .text

printint:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rsi
        pushq   %rdi
        pushq   %rbx # end of function prologue

        movq    16(%rbp), %rax
        andq    $0xf, %rax
        addq    $48, %rax
        cmp     $58, %rax
        jl      r1
        addq    $39, %rax
r1:

        movq    %rax, 16(%rbp)

        movq    %rbp, %rax
        addq    $16, %rax
        movq     %rax, %rsi             #string address

        movq     $1, %rax                # system call 1 is write
        movq     $1, %rdi                # file handle 1 is stdout
                     # address of string to output
        movq     $1, %rdx               # number of bytes
        syscall                         # invoke operating system to do the write

        popq    %rbx # start of function epilogue
        popq    %rdi
        popq    %rsi
        movq    %rbp, %rsp
        popq    %rbp
        ret # end of function



printf:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rsi
        pushq   %rdi
        pushq   %rbx # end of function prologue

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $28, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $24, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $20, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $16, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $12, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $8, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $4, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   %rsp
        movq    16(%rbp), %rax
        sar     $0, %rax
        pushq   %rax
        call printint
        popq    %rax
        popq    %rsp

        pushq   $10
        movq     %rsp, %rsi             #string address
        movq     $1, %rax                # system call 1 is write
        movq     $1, %rdi                # file handle 1 is stdout
                     # address of string to output
        movq     $1, %rdx               # number of bytes
        syscall                         # invoke operating system to do the write
        addq    $8, %rsp #idk

        popq    %rbx # start of function epilogue
        popq    %rdi
        popq    %rsi
        movq    %rbp, %rsp
        popq    %rbp
        ret # end of function
