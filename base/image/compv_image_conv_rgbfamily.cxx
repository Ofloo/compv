/* Copyright (C) 2016-2017 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: GPLv3. For commercial license please contact us.
* Source code: https://github.com/DoubangoTelecom/compv
* WebSite: http://compv.org
*/
#include "compv/base/image/compv_image_conv_rgbfamily.h"
#include "compv/base/image/compv_image_conv_common.h"
#include "compv/base/math/compv_math_utils.h"
#include "compv/base/compv_debug.h"

#include "compv/base/image/intrin/x86/compv_image_conv_rgbfamily_intrin_ssse3.h"
#include "compv/base/image/intrin/x86/compv_image_conv_rgbfamily_intrin_avx2.h"

#if COMPV_HAVE_INTEL_IPP
#	include <ipp.h>
#endif

COMPV_NAMESPACE_BEGIN()

#if COMPV_ASM
#	if COMPV_ARCH_X86
		COMPV_EXTERNC void CompVImageConvRgb24family_to_y_Asm_X86_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb24Ptr, COMPV_ALIGNED(SSE) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_y_Asm_X86_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb32Ptr, COMPV_ALIGNED(SSE) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb24family_to_uv_planar_11_Asm_X86_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb24Ptr, COMPV_ALIGNED(SSE) uint8_t* outUPtr, COMPV_ALIGNED(SSE) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_uv_planar_11_Asm_X86_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb32Ptr, COMPV_ALIGNED(SSE) uint8_t* outUPtr, COMPV_ALIGNED(SSE) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb24family_to_y_Asm_X86_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb24Ptr, COMPV_ALIGNED(AVX) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_y_Asm_X86_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb32Ptr, COMPV_ALIGNED(AVX) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb24family_to_uv_planar_11_Asm_X86_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb24Ptr, COMPV_ALIGNED(AVX) uint8_t* outUPtr, COMPV_ALIGNED(AVX) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_uv_planar_11_Asm_X86_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb32Ptr, COMPV_ALIGNED(AVX) uint8_t* outUPtr, COMPV_ALIGNED(AVX) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
#	endif /* COMPV_ARCH_X86 */
#	if COMPV_ARCH_X64
		COMPV_EXTERNC void CompVImageConvRgb24family_to_uv_planar_11_Asm_X64_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb24Ptr, COMPV_ALIGNED(SSE) uint8_t* outUPtr, COMPV_ALIGNED(SSE) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_uv_planar_11_Asm_X64_SSSE3(COMPV_ALIGNED(SSE) const uint8_t* rgb32Ptr, COMPV_ALIGNED(SSE) uint8_t* outUPtr, COMPV_ALIGNED(SSE) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(SSE) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb24family_to_y_Asm_X64_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb24Ptr, COMPV_ALIGNED(AVX) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_y_Asm_X64_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb32Ptr, COMPV_ALIGNED(AVX) uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8);		
		COMPV_EXTERNC void CompVImageConvRgb24family_to_uv_planar_11_Asm_X64_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb24Ptr, COMPV_ALIGNED(AVX) uint8_t* outUPtr, COMPV_ALIGNED(AVX) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8);
		COMPV_EXTERNC void CompVImageConvRgb32family_to_uv_planar_11_Asm_X64_AVX2(COMPV_ALIGNED(AVX) const uint8_t* rgb32Ptr, COMPV_ALIGNED(AVX) uint8_t* outUPtr, COMPV_ALIGNED(AVX) uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, COMPV_ALIGNED(AVX) compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_VCoeffs8);
#	endif /* COMPV_ARCH_X64 */
#endif /* COMPV_ASM */

#if COMPV_ARCH_X86 && COMPV_ASM
#endif /* COMPV_ARCH_X86 && COMPV_ASM */

/******************************************
*************** rgb24family ***************
******************************************/

static void rgb24family_to_y_C(const uint8_t* rgbPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride, 
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t padSample = (stride - width);
	compv_uscalar_t padRGB = padSample * 3;
	compv_uscalar_t padY = padSample;
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[0]);
	const int16_t c1 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[1]);
	const int16_t c2 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[2]);
	// Y = (((33 * R) + (65 * G) + (13 * B))) >> 7 + 16
	for (compv_uscalar_t j = 0; j < height; ++j) {
		for (compv_uscalar_t i = 0; i < width; ++i) {
			*outYPtr++ = CompVMathUtils::clampPixel8((((c0 * rgbPtr[0]) + (c1 * rgbPtr[1]) + (c2 * rgbPtr[2])) >> 7) + 16);
			rgbPtr += 3;
		}
		rgbPtr += padRGB;
		outYPtr += padY;
	}
}

#if COMPV_HAVE_INTEL_IPP
// No BGR to Gray
static void rgb_to_y_IPP(const uint8_t* rgbPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
{
	IppiSize roi = { static_cast<int>(width), static_cast<int>(height) };
	ippiRGBToGray_8u_C3C1R(rgbPtr, static_cast<int>(stride * 3), outYPtr, static_cast<int>(stride * 1), roi);
}
#endif /* COMPV_HAVE_INTEL_IPP */

static void rgb24family_to_uv_planar_11_C(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// 11 -> uv subsampling(1x1)
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t i, j, padUV = (stride - width), padRGB = (padUV * 3);
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0u = kRGBfamilyToYUV_UCoeffs8[0], c0v = kRGBfamilyToYUV_VCoeffs8[0];
	const int16_t c1u = kRGBfamilyToYUV_UCoeffs8[1], c1v = kRGBfamilyToYUV_VCoeffs8[1];
	const int16_t c2u = kRGBfamilyToYUV_UCoeffs8[2], c2v = kRGBfamilyToYUV_VCoeffs8[2];
	// U = (((-38 * R) + (-74 * G) + (112 * B))) >> 8 + 128
	// V = (((112 * R) + (-94 * G) + (-18 * B))) >> 8 + 128
	for (j = 0; j < height; ++j) {
		for (i = 0; i < width; ++i) {
			*outUPtr++ = CompVMathUtils::clampPixel8((((c0u* rgbPtr[0]) + (c1u * rgbPtr[1]) + (c2u * rgbPtr[2])) >> 8) + 128);
			*outVPtr++ = CompVMathUtils::clampPixel8(((((c0v * rgbPtr[0]) + (c1v* rgbPtr[1]) + (c2v * rgbPtr[2]))) >> 8) + 128);
			rgbPtr += 3;
		}
		rgbPtr += padRGB;
		outUPtr += padUV;
		outVPtr += padUV;
	}
}

void __rgb24family_to_y(const uint8_t* rgbPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgb24Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
		= rgb24family_to_y_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbPtr) && COMPV_IS_ALIGNED_SSE(outYPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb24family_to_y_Intrin_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb24family_to_y_Asm_X86_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbPtr) && COMPV_IS_ALIGNED_AVX2(outYPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb24family_to_y_Intrin_AVX2);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb24family_to_y_Asm_X86_AVX2);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb24family_to_y_Asm_X64_AVX2);
	}
	if (kRGBfamilyToYUV_YCoeffs8 == kRGBAToYUV_YCoeffs8) { // For now BGR not supported by IPP
		COMPV_EXEC_IFDEF_INTEL_IPP(funcptr = rgb_to_y_IPP);
	}
#endif
	funcptr(rgbPtr, outYPtr, width, height, stride, kRGBfamilyToYUV_YCoeffs8);

}
void CompVImageConvRGBfamily::rgb24_to_y(const uint8_t* rgb24Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb24family_to_y(rgb24Ptr, outYPtr, width, height, stride, kRGBAToYUV_YCoeffs8);
}
void CompVImageConvRGBfamily::bgr24_to_y(const uint8_t* bgr24Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb24family_to_y(bgr24Ptr, outYPtr, width, height, stride, kBGRAToYUV_YCoeffs8);
}

static void __rgb24family_to_uv_planar_11(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
		COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
		= rgb24family_to_uv_planar_11_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbPtr) && COMPV_IS_ALIGNED_SSE(outUPtr) && COMPV_IS_ALIGNED_SSE(outVPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Intrin_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Asm_X86_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Asm_X64_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbPtr) && COMPV_IS_ALIGNED_AVX2(outUPtr) && COMPV_IS_ALIGNED_AVX2(outVPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Intrin_AVX2);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Asm_X86_AVX2);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb24family_to_uv_planar_11_Asm_X64_AVX2);
	}
#endif
	funcptr(rgbPtr, outUPtr, outVPtr, width, height, stride, kRGBfamilyToYUV_UCoeffs8, kRGBfamilyToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::rgb24_to_uv_planar_11(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb24family_to_uv_planar_11(rgbPtr, outUPtr, outVPtr, width, height, stride, kRGBAToYUV_UCoeffs8, kRGBAToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::bgr24_to_uv_planar_11(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb24family_to_uv_planar_11(rgbPtr, outUPtr, outVPtr, width, height, stride, kBGRAToYUV_UCoeffs8, kBGRAToYUV_VCoeffs8);
}

/******************************************
*************** rgb32family ***************
******************************************/

static void rgb32family_to_y_C(const uint8_t* rgbaPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t padSample = (stride - width);
	compv_uscalar_t padRGB = padSample << 2;
	compv_uscalar_t padY = padSample;
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0 = static_cast<int16_t>(kRGBAfamilyToYUV_YCoeffs8[0]);
	const int16_t c1 = static_cast<int16_t>(kRGBAfamilyToYUV_YCoeffs8[1]);
	const int16_t c2 = static_cast<int16_t>(kRGBAfamilyToYUV_YCoeffs8[2]);
	const int16_t c3 = static_cast<int16_t>(kRGBAfamilyToYUV_YCoeffs8[3]); // should be zero (used as padding for SIMD to align data)
																		   // Y = (((33 * R) + (65 * G) + (13 * B))) >> 7 + 16
	for (compv_uscalar_t j = 0; j < height; ++j) {
		for (compv_uscalar_t i = 0; i < width; ++i) {
			*outYPtr++ = CompVMathUtils::clampPixel8((((c0 * rgbaPtr[0]) + (c1 * rgbaPtr[1]) + (c2 * rgbaPtr[2]) + (c3 * rgbaPtr[3])) >> 7) + 16);
			rgbaPtr += 4;
		}
		rgbaPtr += padRGB;
		outYPtr += padY;
	}
}

static void rgb32family_to_uv_planar_11_C(const uint8_t* rgbaPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// 11 -> uv subsampling(1x1)
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t i, j, padUV = (stride - width), padRGB = (padUV << 2);
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0u = kRGBAfamilyToYUV_UCoeffs8[0], c0v = kRGBAfamilyToYUV_VCoeffs8[0];
	const int16_t c1u = kRGBAfamilyToYUV_UCoeffs8[1], c1v = kRGBAfamilyToYUV_VCoeffs8[1];
	const int16_t c2u = kRGBAfamilyToYUV_UCoeffs8[2], c2v = kRGBAfamilyToYUV_VCoeffs8[2];
	const int16_t c3u = kRGBAfamilyToYUV_UCoeffs8[3], c3v = kRGBAfamilyToYUV_VCoeffs8[3]; // should be zero (used as padding for SIMD to align data)
																						  // U = (((-38 * R) + (-74 * G) + (112 * B))) >> 8 + 128
																						  // V = (((112 * R) + (-94 * G) + (-18 * B))) >> 8 + 128
	for (j = 0; j < height; ++j) {
		for (i = 0; i < width; ++i) {
			*outUPtr++ = CompVMathUtils::clampPixel8((((c0u* rgbaPtr[0]) + (c1u * rgbaPtr[1]) + (c2u * rgbaPtr[2]) + (c3u * rgbaPtr[3])) >> 8) + 128);
			*outVPtr++ = CompVMathUtils::clampPixel8(((((c0v * rgbaPtr[0]) + (c1v* rgbaPtr[1]) + (c2v * rgbaPtr[2]) + (c3v * rgbaPtr[3]))) >> 8) + 128);
			rgbaPtr += 4;
		}
		rgbaPtr += padRGB;
		outUPtr += padUV;
		outVPtr += padUV;
	}
}

void __rgb32family_to_y(const uint8_t* rgbaPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgbaPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBAfamilyToYUV_YCoeffs8)
		= rgb32family_to_y_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbaPtr) && COMPV_IS_ALIGNED_SSE(outYPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb32family_to_y_Intrin_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb32family_to_y_Asm_X86_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbaPtr) && COMPV_IS_ALIGNED_AVX2(outYPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb32family_to_y_Intrin_AVX2);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb32family_to_y_Asm_X86_AVX2);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb32family_to_y_Asm_X64_AVX2);
	}
#endif
	funcptr(rgbaPtr, outYPtr, width, height, stride, kRGBAfamilyToYUV_YCoeffs8);
}
void CompVImageConvRGBfamily::rgba32_to_y(const uint8_t* rgba32Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_y(rgba32Ptr, outYPtr, width, height, stride, kRGBAToYUV_YCoeffs8);
}
void CompVImageConvRGBfamily::argb32_to_y(const uint8_t* argb32Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_y(argb32Ptr, outYPtr, width, height, stride, kARGBToYUV_YCoeffs8);
}
void CompVImageConvRGBfamily::bgra32_to_y(const uint8_t* bgra32Ptr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_y(bgra32Ptr, outYPtr, width, height, stride, kBGRAToYUV_YCoeffs8);
}


static void __rgb32family_to_uv_planar_11(const uint8_t* rgbaPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgbaPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
		COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
		= rgb32family_to_uv_planar_11_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbaPtr) && COMPV_IS_ALIGNED_SSE(outUPtr) && COMPV_IS_ALIGNED_SSE(outVPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Intrin_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Asm_X86_SSSE3);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Asm_X64_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbaPtr) && COMPV_IS_ALIGNED_AVX2(outUPtr) && COMPV_IS_ALIGNED_AVX2(outVPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Intrin_AVX2);
		COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Asm_X86_AVX2);
		COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb32family_to_uv_planar_11_Asm_X64_AVX2);
	}
#endif
	funcptr(rgbaPtr, outUPtr, outVPtr, width, height, stride, kRGBfamilyToYUV_UCoeffs8, kRGBfamilyToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::rgba32_to_uv_planar_11(const uint8_t* rgba32Ptr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_uv_planar_11(rgba32Ptr, outUPtr, outVPtr, width, height, stride, kRGBAToYUV_UCoeffs8, kRGBAToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::argb32_to_uv_planar_11(const uint8_t* argb32Ptr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_uv_planar_11(argb32Ptr, outUPtr, outVPtr, width, height, stride, kARGBToYUV_UCoeffs8, kARGBToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::bgra32_to_uv_planar_11(const uint8_t* bgra32Ptr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb32family_to_uv_planar_11(bgra32Ptr, outUPtr, outVPtr, width, height, stride, kBGRAToYUV_UCoeffs8, kBGRAToYUV_VCoeffs8);
}


/******************************************
*************** rgb565lefamily ***************
******************************************/

static void rgb565lefamily_to_y_C(const uint8_t* rgb565lePtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t i, j, padSample = (stride - width); // pad in samples
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[0]);
	const int16_t c1 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[1]);
	const int16_t c2 = static_cast<int16_t>(kRGBfamilyToYUV_YCoeffs8[2]);
	const uint16_t* rgb565lePtrSamples = reinterpret_cast<const uint16_t*>(rgb565lePtr);
	uint16_t r, g, b;
	// Y = (((33 * R) + (65 * G) + (13 * B))) >> 7 + 16
	for (j = 0; j < height; ++j) {
		for (i = 0; i < width; ++i) {
			// FIXME: do not use variables r, g, b
			//r = (*rgb565lePtrSamples) >> 11;
			//g = (*rgb565lePtrSamples >> 5) & 0x3f;
			//b = *rgb565lePtrSamples & 0x1f;
			//r = (r * 255 + 15) / 31;
			//g = (g * 255 + 31) / 63;
			//b = (b * 255 + 15) / 31;
			r = ((*rgb565lePtrSamples & 0xF800) >> 8);
			g = ((*rgb565lePtrSamples & 0x07E0) >> 3);
			b = ((*rgb565lePtrSamples & 0x001F) << 3);
			*outYPtr++ = CompVMathUtils::clampPixel8((((c0 * r) + (c1 * g) + (c2 * b)) >> 7) + 16);
			++rgb565lePtrSamples;
		}
		rgb565lePtrSamples += padSample;
		outYPtr += padSample;
	}
}

static void rgb565lefamily_to_uv_planar_11_C(const uint8_t* rgb565lePtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	// up to the caller to use multi-threading
	// 11 -> uv subsampling(1x1)
	// single-threaded code

	COMPV_DEBUG_INFO_CODE_NOT_OPTIMIZED("No SIMD implementation found");
	compv_uscalar_t i, j, padSample = (stride - width); // pad in samples
	// Convert coeffs from int8 to int16 to avoid math ops overflow
	const int16_t c0u = kRGBfamilyToYUV_UCoeffs8[0], c0v = kRGBfamilyToYUV_VCoeffs8[0];
	const int16_t c1u = kRGBfamilyToYUV_UCoeffs8[1], c1v = kRGBfamilyToYUV_VCoeffs8[1];
	const int16_t c2u = kRGBfamilyToYUV_UCoeffs8[2], c2v = kRGBfamilyToYUV_VCoeffs8[2];
	const int16_t* rgb565lePtrSamples = reinterpret_cast<const int16_t*>(rgb565lePtr);
	int16_t r, g, b;
	// U = (((-38 * R) + (-74 * G) + (112 * B))) >> 8 + 128
	// V = (((112 * R) + (-94 * G) + (-18 * B))) >> 8 + 128
	for (j = 0; j < height; ++j) {
		for (i = 0; i < width; ++i) {
			// FIXME: do not use variables r, g, b
			//r = *rgb565lePtrSamples >> 11;
			//g = (*rgb565lePtrSamples >> 5) & 0x3f;
			//b = *rgb565lePtrSamples & 0x1f;
			r = ((*rgb565lePtrSamples & 0xF800) >> 8);
			g = ((*rgb565lePtrSamples & 0x07E0) >> 3);
			b = ((*rgb565lePtrSamples & 0x001F) << 3);
			*outUPtr++ = CompVMathUtils::clampPixel8((((c0u* r) + (c1u * g) + (c2u * b)) >> 8) + 128);
			*outVPtr++ = CompVMathUtils::clampPixel8(((((c0v * r) + (c1v* g) + (c2v * b))) >> 8) + 128);
			++rgb565lePtrSamples;
		}
		rgb565lePtrSamples += padSample;
		outUPtr += padSample;
		outVPtr += padSample;
	}
}

void __rgb565lefamily_to_y(const uint8_t* rgbPtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgb565lePtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_YCoeffs8)
		= rgb565lefamily_to_y_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbPtr) && COMPV_IS_ALIGNED_SSE(outYPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		//COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb565lefamily_to_y_Intrin_SSSE3);
		//COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb565lefamily_to_y_Asm_X86_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbPtr) && COMPV_IS_ALIGNED_AVX2(outYPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		//COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb565lefamily_to_y_Intrin_AVX2);
		//COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb565lefamily_to_y_Asm_X86_AVX2);
		//COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb565lefamily_to_y_Asm_X64_AVX2);
	}
#endif
	funcptr(rgbPtr, outYPtr, width, height, stride, kRGBfamilyToYUV_YCoeffs8);
}
void CompVImageConvRGBfamily::rgb565le_to_y(const uint8_t* rgb565lePtr, uint8_t* outYPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb565lefamily_to_y(rgb565lePtr, outYPtr, width, height, stride, kRGBAToYUV_YCoeffs8);
}

static void __rgb565lefamily_to_uv_planar_11(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
	COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
{
	// internal function, no need to check result or input parameters
	void(*funcptr)(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride,
		COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_UCoeffs8, COMPV_ALIGNED(DEFAULT) const int8_t* kRGBfamilyToYUV_VCoeffs8)
		= rgb565lefamily_to_uv_planar_11_C;
#if COMPV_ARCH_X86
	if (CompVCpu::isEnabled(kCpuFlagSSSE3) && COMPV_IS_ALIGNED_SSE(rgbPtr) && COMPV_IS_ALIGNED_SSE(outUPtr) && COMPV_IS_ALIGNED_SSE(outVPtr) && COMPV_IS_ALIGNED_SSE(stride)) {
		//COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb565lefamily_to_uv_planar_11_Intrin_SSSE3);
		//COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb565lefamily_to_uv_planar_11_Asm_X86_SSSE3);
	}
	if (CompVCpu::isEnabled(kCpuFlagAVX2) && COMPV_IS_ALIGNED_AVX2(rgbPtr) && COMPV_IS_ALIGNED_AVX2(outUPtr) && COMPV_IS_ALIGNED_AVX2(outVPtr) && COMPV_IS_ALIGNED_AVX2(stride)) {
		//COMPV_EXEC_IFDEF_INTRIN_X86(funcptr = CompVImageConvRgb565lefamily_to_uv_planar_11_Intrin_AVX2);
		//COMPV_EXEC_IFDEF_ASM_X86(funcptr = CompVImageConvRgb565lefamily_to_uv_planar_11_Asm_X86_AVX2);
		//COMPV_EXEC_IFDEF_ASM_X64(funcptr = CompVImageConvRgb565lefamily_to_uv_planar_11_Asm_X64_AVX2);
	}
#endif
	funcptr(rgbPtr, outUPtr, outVPtr, width, height, stride, kRGBfamilyToYUV_UCoeffs8, kRGBfamilyToYUV_VCoeffs8);
}
void CompVImageConvRGBfamily::rgb565le_to_uv_planar_11(const uint8_t* rgbPtr, uint8_t* outUPtr, uint8_t* outVPtr, compv_uscalar_t width, compv_uscalar_t height, compv_uscalar_t stride) {
	__rgb565lefamily_to_uv_planar_11(rgbPtr, outUPtr, outVPtr, width, height, stride, kRGBAToYUV_UCoeffs8, kRGBAToYUV_VCoeffs8);
}

COMPV_NAMESPACE_END()
