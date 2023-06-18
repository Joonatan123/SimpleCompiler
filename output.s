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
test:	
		pushq	%rbp
		movq	%rsp, %rbp
		pushq	%rsi
		pushq	%rdi
		pushq	%rbx # end of function prologue

		pushq	%r15
		movq	%rsp, %r15
		subq	$8, %rsp # allocate to stack
		pushq	%rbx
		movq	24(%rbp), %rax # load variable
		movq	%rax, %rbx # mov for operation
		movq	16(%rbp), %rax # load variable
		addq	%rbx, %rax
		popq	%rbx
		movq	%rax, -8(%rbp) # store to variable
			#start if
		pushq	%rbx
		movq	-8(%rbp), %rax # load variable
		movq	%rax, %rbx # mov for operation
		movq	$100000, %rax # load literal to rax
		cmpq	%rbx, %rax
		mov	$1,%r14
		cmovl	%r14,%rax
		mov	$0,%r14
		cmovge	%r14,%rax
		popq	%rbx
		cmpq	$0, %rax
		je	l0
			# Return statement
		movq	$0, %rax # load literal to rax

		popq	%rbx # start of function epilogue
		popq	%rdi
		popq	%rsi
		movq	%rbp, %rsp
		popq	%rbp
		ret # end of return

l0:
		movq	$0, %rax # load literal to rax
		movq	%rax, -8(%rbp) # store to variable
			#start if
		pushq	%rbx
		movq	16(%rbp), %rax # load variable
		movq	%rax, %rbx # mov for operation
		movq	24(%rbp), %rax # load variable
		cmpq	%rbx, %rax
		mov	$1,%r14
		cmovl	%r14,%rax
		mov	$0,%r14
		cmovge	%r14,%rax
		popq	%rbx
		cmpq	$0, %rax
		je	l1
		movq	16(%rbp), %rax # load variable
		movq	%rax, -8(%rbp) # store to variable
		movq	24(%rbp), %rax # load variable
		movq	%rax, 16(%rbp) # store to variable
		movq	-8(%rbp), %rax # load variable
		movq	%rax, 24(%rbp) # store to variable
l1:
		pushq	%rbx
		movq	24(%rbp), %rax # load variable
		movq	%rax, %rbx # mov for operation
		movq	16(%rbp), %rax # load variable
		addq	%rbx, %rax
		popq	%rbx
		movq	%rax, 16(%rbp) # store to variable
		pushq	%r15
		movq	%rsp, %r15 # push rsp for funtion call
		movq	16(%rbp), %rax # load variable
		pushq	%rax # call argument on stack
		movq	16(%rbp), %rax # load variable
		pushq	%rax # call argument on stack
		call	printf
		movq	%r15, %rsp # remove call arguments from stack
		popq	%r15
		pushq	%r15
		movq	%rsp, %r15 # push rsp for funtion call
		movq	24(%rbp), %rax # load variable
		pushq	%rax # call argument on stack
		movq	24(%rbp), %rax # load variable
		pushq	%rax # call argument on stack
		movq	16(%rbp), %rax # load variable
		pushq	%rax # call argument on stack
		call	test
		movq	%r15, %rsp # remove call arguments from stack
		popq	%r15

		movq	%r15,%rsp # start of function epilogue
		popq	%r15
		popq	%rbx
		popq	%rdi
		popq	%rsi
		movq	%rbp, %rsp
		popq	%rbp
		ret # end of function

_start:	
		pushq	%r15
		movq	%rsp, %r15 # push rsp for funtion call
		movq	$1, %rax # load literal to rax
		pushq	%rax # call argument on stack
		movq	$1, %rax # load literal to rax
		pushq	%rax # call argument on stack
		movq	$0, %rax # load literal to rax
		pushq	%rax # call argument on stack
		call	test
		movq	%r15, %rsp # remove call arguments from stack
		popq	%r15

		mov	$60, %rax  # system call 60 is exit
		xor	%rdi, %rdi
		syscall
