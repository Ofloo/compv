; Copyright (C) 2016 Doubango Telecom <https://www.doubango.org>
;
; This file is part of Open Source ComputerVision (a.k.a CompV) project.
; Source code hosted at https://github.com/DoubangoTelecom/compv
; Website hosted at http://compv.org
;
; CompV is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; CompV is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with CompV.
;
%include "compv_common_x86.s"

COMPV_YASM_DEFAULT_REL

global sym(Convlt1_hz_float32_minpack4_Asm_X86_SSE2)

section .data

section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; This function requires sizeof(float) = 4byte = 32bits
; arg(0) -> const uint8_t* in_ptr
; arg(1) -> uint8_t* out_ptr
; arg(2) -> compv_scalar_t width
; arg(3) -> compv_scalar_t height
; arg(4) -> compv_scalar_t pad
; arg(5) -> const float* hkern_ptr
; arg(6) -> compv_scalar_t kern_size
; void Convlt1_hz_float32_minpack4_Asm_X86_SSE2(const uint8_t* in_ptr, uint8_t* out_ptr, compv_scalar_t width, compv_scalar_t height, compv_scalar_t pad, const float* hkern_ptr, compv_scalar_t kern_size)
sym(Convlt1_hz_float32_minpack4_Asm_X86_SSE2):
	push rbp
	mov rbp, rsp
	COMPV_YASM_SHADOW_ARGS_TO_STACK 7
	COMPV_YASM_SAVE_XMM 7 ;XMM[6-7]
	push rsi
	push rdi
	push rbx
	;; end prolog ;;

	%define COMPV_SIZE_OF_FLOAT 4 ; up to the caller to make sure sizeof(float)=4
	%define i_xmmSF3	rsp + 0

	; align stack and alloc memory
	COMPV_YASM_ALIGN_STACK 16, rax
	sub rsp, 16*1
	; [rsp + 0] = xmmSF3

	; i = rdi
	; xor rdi, rdi

	; rcx = col

	; rbx = max

	; j = rsi
	xor rsi, rsi

	; xmm7 = xmmZero
	pxor xmm7, xmm7

	; arg(4) = pad += (width & 3)
	mov rdx, arg(2) ; width
	mov rax, arg(4) ; pad
	and rdx, 3
	add rax, rdx
	mov arg(4), rax
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; for (j = 0; j < height; ++j)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.LoopRows
		xor rdi, rdi ; i = 0
		mov rbx, arg(2) ; width
		sub rbx, 15 ; rbx = (width - 15)
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		; for (i = 0; i < width - 15; i += 16)
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.LoopColumns16
			xorps xmm5, xmm5 ; xmm5 = xmmSF0
			xorps xmm6, xmm6 ; xmm6 = xmmSF1
			xorps xmm4, xmm4 ; xmm4 = xmmSF2
			movaps [i_xmmSF3], xmm7

			xor rcx, rcx ; col = 0
			mov rax, arg(0) ; in_ptr
			mov rdx, arg(5) ; hkern_ptr
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; for (col = 0; col < kern_size; ++col)
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			.LoopColumns16Kern16
				movdqu xmm0, [rax + rcx] ; xmm0 = xmmI0
				movss xmm1, [rdx + rcx*COMPV_SIZE_OF_FLOAT]
				movdqa xmm2, xmm0
				movdqa xmm3, xmm0
				shufps xmm1, xmm1, 0x0 ; xmm1 = xmmCoeff
				
				punpcklbw xmm2, xmm7
				punpcklbw xmm3, xmm7
				punpcklwd xmm2, xmm7
				punpckhwd xmm3, xmm7
				cvtdq2ps xmm2, xmm2
				cvtdq2ps xmm3, xmm3
				mulps xmm2, xmm1
				mulps xmm3, xmm1
				addps xmm5, xmm2
				addps xmm6, xmm3

				movdqa xmm3, xmm0
				punpckhbw xmm3, xmm7
				punpckhbw xmm0, xmm7
				punpcklwd xmm3, xmm7
				punpckhwd xmm0, xmm7
				cvtdq2ps xmm3, xmm3
				cvtdq2ps xmm0, xmm0
				mulps xmm3, xmm1
				mulps xmm0, xmm1
				addps xmm4, xmm3
				addps xmm0, [i_xmmSF3]
				movaps [i_xmmSF3], xmm0

			inc rcx
			cmp rcx, arg(6)
			jl .LoopColumns16Kern16		

			mov rax, arg(1) ; out_ptr
			mov rdx, arg(0) ; in_ptr
			cvtps2dq xmm5, xmm5
			cvtps2dq xmm6, xmm6
			cvtps2dq xmm4, xmm4
			cvtps2dq xmm3, [i_xmmSF3]
			packssdw xmm5, xmm6
			packssdw xmm4, xmm3
			packuswb xmm5, xmm4
			movdqu [rax], xmm5
			lea rax, [rax + 16]
			lea rdx, [rdx + 16]
			mov arg(1), rax ; out_ptr += 16
			mov arg(0), rdx ; in_ptr += 16

		lea rdi, [rdi + 16] ; i += 16
		cmp rdi, rbx
		jl .LoopColumns16

		mov rbx, arg(2) ; width
		sub rbx, 3 ; rbx = (width - 3)
		cmp rdi, rbx
		jge .EndOfLoopColumns4
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		; for (; i < width - 3; i += 4)
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		.LoopColumns4
			xorps xmm4, xmm4 ; xmm4 = xmmSF0

			xor rcx, rcx ; col = 0
			mov rax, arg(0) ; in_ptr
			mov rdx, arg(5) ; hkern_ptr
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; for (col = 0; col < kern_size; ++col)
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			.LoopColumns4Kern16
				movd xmm0, [rax + rcx] ; xmm0 = xmmI0
				movss xmm1, [rdx + rcx*COMPV_SIZE_OF_FLOAT]
				punpcklbw xmm0, xmm7
				shufps xmm1, xmm1, 0x0 ; xmm1 = xmmCoeff
				punpcklwd xmm0, xmm7
				cvtdq2ps xmm0, xmm0
				mulps xmm0, xmm1
				addps xmm4, xmm0

			inc rcx
			cmp rcx, arg(6)
			jl .LoopColumns4Kern16

			mov rax, arg(1) ; out_ptr
			cvtps2dq xmm4, xmm4
			packssdw xmm4, xmm4
			packuswb xmm4, xmm4
			movd rdx, xmm4
			mov [rax], dword edx
			
			mov rdx, arg(0) ; in_ptr
			add rax, 4
			add rdx, 4
			mov arg(1), rax ; out_ptr += 4
			mov arg(0), rdx ; in_ptr += 4

		lea rdi, [rdi + 4] ; i+= 4
		cmp rdi, rbx
		jl .LoopColumns4
		.EndOfLoopColumns4

		mov rax, arg(1) ; out_ptr
		mov rdx, arg(0) ; in_ptr
		add rax, arg(4)
		add rdx, arg(4)
		mov arg(1), rax ; out_ptr += pad
		mov arg(0), rdx ; in_ptr += pad

	inc rsi ; ++j
	cmp rsi, arg(3)
	jl .LoopRows

	; unalign stack and free memory
	add rsp, 16*1
	COMPV_YASM_UNALIGN_STACK

	%undef COMPV_SIZE_OF_FLOAT
	%undef i_xmmSF3

	;; begin epilog ;;
	pop rbx
	pop rdi
	pop rsi
	COMPV_YASM_RESTORE_XMM
	COMPV_YASM_UNSHADOW_ARGS
	mov rsp, rbp
	pop rbp
	ret