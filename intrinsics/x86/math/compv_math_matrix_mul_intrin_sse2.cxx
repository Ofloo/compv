/* Copyright (C) 2016-2017 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: GPLv3. For commercial license please contact us.
* Source code: https://github.com/DoubangoTelecom/compv
* WebSite: http://compv.org
*/
#include "compv/intrinsics/x86/math/compv_math_matrix_mul_intrin_sse2.h"

#if COMPV_ARCH_X86 && COMPV_INTRINSIC
#include "compv/compv_simd_globals.h"
#include "compv/math/compv_math.h"
#include "compv/compv_mem.h"
#include "compv/compv_debug.h"

COMPV_NAMESPACE_BEGIN()

// We'll read beyond the end of the data which means ri and rj must be strided
void MatrixMulGA_float64_Intrin_SSE2(COMPV_ALIGNED(SSE) compv_float64_t* ri, COMPV_ALIGNED(SSE) compv_float64_t* rj, const compv_float64_t* c1, const compv_float64_t* s1, compv_uscalar_t count)
{
	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED(); // ASM

	__m128d xmmC, xmmS, xmmRI, xmmRJ;

	xmmC = _mm_load1_pd(c1);
	xmmS = _mm_load1_pd(s1);

	for (compv_uscalar_t i = 0; i < count; i += 2) { // more than count (up to stride)
		xmmRI = _mm_load_pd(&ri[i]);
		xmmRJ = _mm_load_pd(&rj[i]);
		_mm_store_pd(&ri[i], _mm_add_pd(_mm_mul_pd(xmmRI, xmmC), _mm_mul_pd(xmmRJ, xmmS)));
		_mm_store_pd(&rj[i], _mm_sub_pd(_mm_mul_pd(xmmRJ, xmmC), _mm_mul_pd(xmmRI, xmmS)));
	}
}

// We'll read beyond the end of the data which means ri and rj must be strided
void MatrixMulGA_float32_Intrin_SSE2(COMPV_ALIGNED(SSE) compv_float32_t* ri, COMPV_ALIGNED(SSE) compv_float32_t* rj, const compv_float32_t* c1, const compv_float32_t* s1, compv_uscalar_t count)
{
	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED(); // ASM

	__m128 xmmC, xmmS, xmmRI, xmmRJ;

	xmmC = _mm_load1_ps(c1);
	xmmS = _mm_load1_ps(s1);

	for (compv_uscalar_t i = 0; i < count; i += 4) { // more than count (up to stride)
		xmmRI = _mm_load_ps(&ri[i]);
		xmmRJ = _mm_load_ps(&rj[i]);
		_mm_store_ps(&ri[i], _mm_add_ps(_mm_mul_ps(xmmRI, xmmC), _mm_mul_ps(xmmRJ, xmmS)));
		_mm_store_ps(&rj[i], _mm_sub_ps(_mm_mul_ps(xmmRJ, xmmC), _mm_mul_ps(xmmRI, xmmS)));
	}
}

// We'll read beyond the end of the data which means S must be strided and washed
// S must be symmetric matrix
// rowStart should be >= 1 as it doesn't make sense
void MatrixMaxAbsOffDiagSymm_float64_Intrin_SSE2(const COMPV_ALIGNED(SSE) compv_float64_t* S, compv_uscalar_t *row, compv_uscalar_t *col, compv_float64_t* max, compv_uscalar_t rowStart, compv_uscalar_t rowEnd, compv_uscalar_t strideInBytes)
{
	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED(); // ASM
	compv_uscalar_t i, j;
	__m128d xmmAbs, xmmMax, xmm0, xmmAbsMask, xmmAllZerosMask;
	int cmp;

	xmmAbsMask = _mm_load_pd(reinterpret_cast<const double*>(kAVXFloat64MaskAbs));
	xmmAllZerosMask = _mm_cmpeq_pd(xmmAbsMask, xmmAbsMask); // 0xfff....
	xmmMax = _mm_setzero_pd();
	*max = 0;
	*row = 0;
	*col = 0;
	(xmm0);

	// "j" is undigned which means "j - 1" will overflow when rowStart is equal to zero
	// we don't need this check on asm (using registers)
	if (rowStart == 0) {
		rowStart = 1;
	}

	// Find max value without worrying about the indexes
	const uint8_t* S0_ = reinterpret_cast<const uint8_t*>(S) + (rowStart * strideInBytes); // j start at row index 1
	const compv_float64_t* S1_;
	for (j = rowStart; j < rowEnd; ++j) { // j = 0 is on diagonal
		S1_ = reinterpret_cast<const compv_float64_t*>(S0_);
		i = 0;
		for (; i < j - 1; i += 2) { // i stops at j because the matrix is symmetric
			xmmAbs = _mm_and_pd(_mm_load_pd(&S1_[i]), xmmAbsMask); // abs(S)
#if 0 // SSE41 and not faster
			COMPV_DEBUG_INFO_CODE_FOR_TESTING();
			cmp = _mm_test_all_zeros(_mm_castpd_si128(_mm_cmpgt_pd(xmmAbs, xmmMax)), xmmAllZerosMask);
			if (!cmp) {
				*row = j;
				xmm0 = _mm_shuffle_pd(xmmAbs, xmmAbs, 0x01); // invert: high | low
				if (_mm_comigt_sd(xmmAbs, xmmMax)) {
					xmmMax = xmmAbs;
					*col = i;
				}
				if (_mm_comigt_sd(xmm0, xmmMax)) {
					xmmMax = xmm0;
					*col = i + 1;
				}
				xmmMax = _mm_shuffle_pd(xmmMax, xmmMax, 0x0); // duplicate low double
			}
#else // SSE2
			cmp = _mm_movemask_pd(_mm_cmpgt_pd(xmmAbs, xmmMax));
			if (cmp) { // most of the time matrix will be full of zeros/epsilons (sparse)
				*row = j;
				if (cmp == 1) {
					xmmMax = xmmAbs;
					*col = i;
				}
				else if (cmp == 2) {
					xmmMax = _mm_shuffle_pd(xmmAbs, xmmAbs, 0x01);
					*col = i + 1;
				}
				else {
					xmm0 = _mm_shuffle_pd(xmmAbs, xmmAbs, 0x01);
					if (_mm_comigt_sd(xmmAbs, xmmMax)) {
						xmmMax = xmmAbs;
						*col = i;
					}
					if (_mm_comigt_sd(xmm0, xmmMax)) {
						xmmMax = xmm0;
						*col = i + 1;
					}
				}
				xmmMax = _mm_shuffle_pd(xmmMax, xmmMax, 0x0); // duplicate low double
			}
#endif
		}
		for (; i < j; i += 1) { // i stops at j because the matrix is symmetric
			xmmAbs = _mm_and_pd(_mm_load_sd(&S1_[i]), xmmAbsMask); // abs(S)
			if (_mm_comigt_sd(xmmAbs, xmmMax)) {
				xmmMax = _mm_shuffle_pd(xmmAbs, xmmAbs, 0); // duplicate low double
				*row = j;
				*col = i;
			}
		}
		S0_ += strideInBytes;
	}
	*max = _mm_cvtsd_f64(xmmMax);
}

COMPV_NAMESPACE_END()

#endif /* COMPV_ARCH_X86 && COMPV_INTRINSIC */