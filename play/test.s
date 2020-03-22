	.text
	.file	"test.cpp"
	.globl	_Z4testi
	.p2align	4, 0x90
	.type	_Z4testi,@function
_Z4testi:
	movl	%edi, -4(%rsp)
	movl	-4(%rsp), %eax
	shll	$1, %eax
	retq
.Lfunc_end0:
	.size	_Z4testi, .Lfunc_end0-_Z4testi

	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 4cf0dddcc6f5122a847e5e319435f558e02d38c9)"
	.section	".note.GNU-stack","",@progbits
