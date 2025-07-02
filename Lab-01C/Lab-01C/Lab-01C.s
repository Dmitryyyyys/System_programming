	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 1
	.file	"Lab-01C.cpp"
	.def	"?calculate_powers@@YAXNPAN00@Z";
	.scl	2;
	.type	32;
	.endef
	.globl	"?calculate_powers@@YAXNPAN00@Z" # -- Begin function ?calculate_powers@@YAXNPAN00@Z
	.p2align	4, 0x90
"?calculate_powers@@YAXNPAN00@Z":       # @"?calculate_powers@@YAXNPAN00@Z"
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-8, %esp
	subl	$32, %esp
	movl	24(%ebp), %eax
	movl	20(%ebp), %eax
	movl	16(%ebp), %eax
	movsd	8(%ebp), %xmm0                  # xmm0 = mem[0],zero
	movsd	%xmm0, 24(%esp)
	movsd	24(%esp), %xmm0                 # xmm0 = mem[0],zero
	mulsd	24(%esp), %xmm0
	movsd	%xmm0, 16(%esp)
	movsd	16(%esp), %xmm0                 # xmm0 = mem[0],zero
	mulsd	16(%esp), %xmm0
	movl	16(%ebp), %eax
	movsd	%xmm0, (%eax)
	movl	16(%ebp), %eax
	movsd	(%eax), %xmm0                   # xmm0 = mem[0],zero
	movl	16(%ebp), %eax
	mulsd	(%eax), %xmm0
	movsd	%xmm0, 8(%esp)
	movsd	8(%esp), %xmm0                  # xmm0 = mem[0],zero
	movl	16(%ebp), %eax
	mulsd	(%eax), %xmm0
	movl	20(%ebp), %eax
	movsd	%xmm0, (%eax)
	movsd	8(%esp), %xmm0                  # xmm0 = mem[0],zero
	mulsd	8(%esp), %xmm0
	movsd	%xmm0, (%esp)
	movsd	(%esp), %xmm0                   # xmm0 = mem[0],zero
	movl	20(%ebp), %eax
	mulsd	(%eax), %xmm0
	movl	24(%ebp), %eax
	movsd	%xmm0, (%eax)
	movl	%ebp, %esp
	popl	%ebp
	retl
                                        # -- End function
	.def	_main;
	.scl	2;
	.type	32;
	.endef
	.globl	_main                           # -- Begin function main
	.p2align	4, 0x90
_main:                                  # @main
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-8, %esp
	subl	$64, %esp
	movl	$0, 60(%esp)
	leal	"??_C@_0BD@DILDAJDF@Vvedite?5chislo?5x?3?5?$AA@", %eax
	movl	%eax, (%esp)
	calll	_printf
	leal	"??_C@_03DLDNIBIK@?$CFlf?$AA@", %ecx
	leal	48(%esp), %eax
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	calll	_scanf
	movsd	48(%esp), %xmm0                 # xmm0 = mem[0],zero
	leal	40(%esp), %edx
	leal	32(%esp), %ecx
	leal	24(%esp), %eax
	movsd	%xmm0, (%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 12(%esp)
	movl	%eax, 16(%esp)
	calll	"?calculate_powers@@YAXNPAN00@Z"
	movsd	40(%esp), %xmm0                 # xmm0 = mem[0],zero
	leal	"??_C@_0N@HNNHMJOD@x?$FO4?5?$DN?5?$CF?46lf?6?$AA@", %eax
	movl	%eax, (%esp)
	movsd	%xmm0, 4(%esp)
	calll	_printf
	movsd	32(%esp), %xmm0                 # xmm0 = mem[0],zero
	leal	"??_C@_0O@NLMGPGMH@x?$FO12?5?$DN?5?$CF?46lf?6?$AA@", %eax
	movl	%eax, (%esp)
	movsd	%xmm0, 4(%esp)
	calll	_printf
	movsd	24(%esp), %xmm0                 # xmm0 = mem[0],zero
	leal	"??_C@_0O@EOPHHMLD@x?$FO28?5?$DN?5?$CF?46lf?6?$AA@", %eax
	movl	%eax, (%esp)
	movsd	%xmm0, 4(%esp)
	calll	_printf
	xorl	%eax, %eax
	movl	%ebp, %esp
	popl	%ebp
	retl
                                        # -- End function
	.def	_printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_printf
	.globl	_printf                         # -- Begin function printf
	.p2align	4, 0x90
_printf:                                # @printf
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$28, %esp
	movl	8(%ebp), %eax
	leal	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %esi
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)                 # 4-byte Spill
	movl	%esp, %eax
	movl	$1, (%eax)
	calll	___acrt_iob_func
	movl	-16(%ebp), %edx                 # 4-byte Reload
	movl	%eax, %ecx
	movl	%esp, %eax
	movl	%esi, 12(%eax)
	movl	%edx, 4(%eax)
	movl	%ecx, (%eax)
	movl	$0, 8(%eax)
	calll	__vfprintf_l
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	$28, %esp
	popl	%esi
	popl	%ebp
	retl
                                        # -- End function
	.def	_scanf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_scanf
	.globl	_scanf                          # -- Begin function scanf
	.p2align	4, 0x90
_scanf:                                 # @scanf
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$28, %esp
	movl	8(%ebp), %eax
	leal	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %esi
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)                 # 4-byte Spill
	movl	%esp, %eax
	movl	$0, (%eax)
	calll	___acrt_iob_func
	movl	-16(%ebp), %edx                 # 4-byte Reload
	movl	%eax, %ecx
	movl	%esp, %eax
	movl	%esi, 12(%eax)
	movl	%edx, 4(%eax)
	movl	%ecx, (%eax)
	movl	$0, 8(%eax)
	calll	__vfscanf_l
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	$28, %esp
	popl	%esi
	popl	%ebp
	retl
                                        # -- End function
	.def	__vfprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__vfprintf_l
	.globl	__vfprintf_l                    # -- Begin function _vfprintf_l
	.p2align	4, 0x90
__vfprintf_l:                           # @_vfprintf_l
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	20(%ebp), %eax
	movl	16(%ebp), %eax
	movl	12(%ebp), %eax
	movl	8(%ebp), %eax
	movl	20(%ebp), %eax
	movl	%eax, -20(%ebp)                 # 4-byte Spill
	movl	16(%ebp), %ebx
	movl	12(%ebp), %edi
	movl	8(%ebp), %esi
	calll	___local_stdio_printf_options
	movl	-20(%ebp), %ecx                 # 4-byte Reload
	movl	(%eax), %edx
	movl	%edx, -16(%ebp)                 # 4-byte Spill
	movl	4(%eax), %edx
	movl	%esp, %eax
	movl	%ecx, 20(%eax)
	movl	-16(%ebp), %ecx                 # 4-byte Reload
	movl	%ebx, 16(%eax)
	movl	%edi, 12(%eax)
	movl	%esi, 8(%eax)
	movl	%edx, 4(%eax)
	movl	%ecx, (%eax)
	calll	___stdio_common_vfprintf
	addl	$32, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
                                        # -- End function
	.def	___local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,___local_stdio_printf_options
	.globl	___local_stdio_printf_options   # -- Begin function __local_stdio_printf_options
	.p2align	4, 0x90
___local_stdio_printf_options:          # @__local_stdio_printf_options
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	leal	"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA", %eax
	popl	%ebp
	retl
                                        # -- End function
	.def	__vfscanf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__vfscanf_l
	.globl	__vfscanf_l                     # -- Begin function _vfscanf_l
	.p2align	4, 0x90
__vfscanf_l:                            # @_vfscanf_l
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$32, %esp
	movl	20(%ebp), %eax
	movl	16(%ebp), %eax
	movl	12(%ebp), %eax
	movl	8(%ebp), %eax
	movl	20(%ebp), %eax
	movl	%eax, -20(%ebp)                 # 4-byte Spill
	movl	16(%ebp), %ebx
	movl	12(%ebp), %edi
	movl	8(%ebp), %esi
	calll	___local_stdio_scanf_options
	movl	-20(%ebp), %ecx                 # 4-byte Reload
	movl	(%eax), %edx
	movl	%edx, -16(%ebp)                 # 4-byte Spill
	movl	4(%eax), %edx
	movl	%esp, %eax
	movl	%ecx, 20(%eax)
	movl	-16(%ebp), %ecx                 # 4-byte Reload
	movl	%ebx, 16(%eax)
	movl	%edi, 12(%eax)
	movl	%esi, 8(%eax)
	movl	%edx, 4(%eax)
	movl	%ecx, (%eax)
	calll	___stdio_common_vfscanf
	addl	$32, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
                                        # -- End function
	.def	___local_stdio_scanf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,___local_stdio_scanf_options
	.globl	___local_stdio_scanf_options    # -- Begin function __local_stdio_scanf_options
	.p2align	4, 0x90
___local_stdio_scanf_options:           # @__local_stdio_scanf_options
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	leal	"?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA", %eax
	popl	%ebp
	retl
                                        # -- End function
	.section	.rdata,"dr",discard,"??_C@_0BD@DILDAJDF@Vvedite?5chislo?5x?3?5?$AA@"
	.globl	"??_C@_0BD@DILDAJDF@Vvedite?5chislo?5x?3?5?$AA@" # @"??_C@_0BD@DILDAJDF@Vvedite?5chislo?5x?3?5?$AA@"
"??_C@_0BD@DILDAJDF@Vvedite?5chislo?5x?3?5?$AA@":
	.asciz	"Vvedite chislo x: "

	.section	.rdata,"dr",discard,"??_C@_03DLDNIBIK@?$CFlf?$AA@"
	.globl	"??_C@_03DLDNIBIK@?$CFlf?$AA@"  # @"??_C@_03DLDNIBIK@?$CFlf?$AA@"
"??_C@_03DLDNIBIK@?$CFlf?$AA@":
	.asciz	"%lf"

	.section	.rdata,"dr",discard,"??_C@_0N@HNNHMJOD@x?$FO4?5?$DN?5?$CF?46lf?6?$AA@"
	.globl	"??_C@_0N@HNNHMJOD@x?$FO4?5?$DN?5?$CF?46lf?6?$AA@" # @"??_C@_0N@HNNHMJOD@x?$FO4?5?$DN?5?$CF?46lf?6?$AA@"
"??_C@_0N@HNNHMJOD@x?$FO4?5?$DN?5?$CF?46lf?6?$AA@":
	.asciz	"x^4 = %.6lf\n"

	.section	.rdata,"dr",discard,"??_C@_0O@NLMGPGMH@x?$FO12?5?$DN?5?$CF?46lf?6?$AA@"
	.globl	"??_C@_0O@NLMGPGMH@x?$FO12?5?$DN?5?$CF?46lf?6?$AA@" # @"??_C@_0O@NLMGPGMH@x?$FO12?5?$DN?5?$CF?46lf?6?$AA@"
"??_C@_0O@NLMGPGMH@x?$FO12?5?$DN?5?$CF?46lf?6?$AA@":
	.asciz	"x^12 = %.6lf\n"

	.section	.rdata,"dr",discard,"??_C@_0O@EOPHHMLD@x?$FO28?5?$DN?5?$CF?46lf?6?$AA@"
	.globl	"??_C@_0O@EOPHHMLD@x?$FO28?5?$DN?5?$CF?46lf?6?$AA@" # @"??_C@_0O@EOPHHMLD@x?$FO28?5?$DN?5?$CF?46lf?6?$AA@"
"??_C@_0O@EOPHHMLD@x?$FO28?5?$DN?5?$CF?46lf?6?$AA@":
	.asciz	"x^28 = %.6lf\n"

	.section	.bss,"bw",discard,"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"
	.globl	"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA" # @"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"
	.p2align	3, 0x0
"?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA":
	.quad	0                               # 0x0

	.section	.bss,"bw",discard,"?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA"
	.globl	"?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA" # @"?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA"
	.p2align	3, 0x0
"?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA":
	.quad	0                               # 0x0

	.section	.drectve,"yni"
	.ascii	" /FAILIFMISMATCH:\"_CRT_STDIO_ISO_WIDE_SPECIFIERS=0\""
	.addrsig
	.addrsig_sym "?calculate_powers@@YAXNPAN00@Z"
	.addrsig_sym _printf
	.addrsig_sym _scanf
	.addrsig_sym __vfprintf_l
	.addrsig_sym ___acrt_iob_func
	.addrsig_sym ___stdio_common_vfprintf
	.addrsig_sym ___local_stdio_printf_options
	.addrsig_sym __vfscanf_l
	.addrsig_sym ___stdio_common_vfscanf
	.addrsig_sym ___local_stdio_scanf_options
	.addrsig_sym "?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA"
	.addrsig_sym "?_OptionsStorage@?1??__local_stdio_scanf_options@@9@4_KA"
	.globl	__fltused
