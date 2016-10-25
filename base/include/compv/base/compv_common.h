/* Copyright (C) 2016-2017 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: GPLv3. For commercial license please contact us.
* Source code: https://github.com/DoubangoTelecom/compv
* WebSite: http://compv.org
*/
#if !defined(_COMPV_BASE_COMMON_H_)
#define _COMPV_BASE_COMMON_H_

#include "compv/base/compv_config.h"

COMPV_NAMESPACE_BEGIN()

#define COMPV_CAT_(A, B) A ## B
#define COMPV_CAT(A, B) COMPV_CAT_(A, B)
#define COMPV_STRING_(A) #A
#define COMPV_STRING(A) COMPV_STRING_(A)

#define COMPV_VERSION_MAJOR 1
#define COMPV_VERSION_MINOR 0
#define COMPV_VERSION_MICRO 0
#if !defined(COMPV_VERSION_STRING)
#	define COMPV_VERSION_STRING COMPV_STRING(COMPV_CAT(COMPV_VERSION_MAJOR, .)) COMPV_STRING(COMPV_CAT(COMPV_VERSION_MINOR, .)) COMPV_STRING(COMPV_VERSION_MICRO)
#endif

#if !defined(COMPV_SAFE_DELETE_CPP)
#	define COMPV_SAFE_DELETE_CPP(cpp_obj) if(cpp_obj) delete (cpp_obj), (cpp_obj) = NULL;
#endif /* COMPV_SAFE_DELETE_CPP */

#define COMPV_ASSERT(x) do { bool __b_ret = (x); assert(__b_ret); } while(0)

#if COMPV_INTRINSIC
#	define COMPV_EXEC_IFDEF_INTRIN(EXPR) do { if (compv::CompVCpu::isIntrinsicsEnabled()) { (EXPR); } } while(0)
#else
#	define COMPV_EXEC_IFDEF_INTRIN(EXPR)
#endif
#if COMPV_INTRINSIC && COMPV_ARCH_X86
#	define COMPV_EXEC_IFDEF_INTRIN_X86(EXPR) do { if (compv::CompVCpu::isIntrinsicsEnabled()) { (EXPR); } } while(0)
#else
#	define COMPV_EXEC_IFDEF_INTRIN_X86(EXPR)
#endif
#if COMPV_ASM
#	define COMPV_EXEC_IFDEF_ASM(EXPR) do { if (compv::CompVCpu::isAsmEnabled()) { (EXPR); } } while(0)
#else
#	define COMPV_EXEC_IFDEF_ASM(EXPR)
#endif
#if COMPV_ASM && COMPV_ARCH_X64
#	define COMPV_EXEC_IFDEF_ASM_X64(EXPR) do { if (compv::CompVCpu::isAsmEnabled()) { (EXPR); } } while(0)
#else
#	define COMPV_EXEC_IFDEF_ASM_X64(EXPR)
#endif
#if COMPV_ASM && COMPV_ARCH_X86
#	define COMPV_EXEC_IFDEF_ASM_X86(EXPR) do { if (compv::CompVCpu::isAsmEnabled()) { (EXPR); } } while(0)
#else
#	define COMPV_EXEC_IFDEF_ASM_X86(EXPR)
#endif

#define COMPV_NUM_THREADS_SINGLE	1
#define COMPV_NUM_THREADS_BEST		-1

// Fixed point Q value
#if COMPV_ARCH_ARM
#	define COMPV_FXPQ	15
#else
#	define COMPV_FXPQ	16
#endif

#define COMPV_IS_ALIGNED(p, a) (!((uintptr_t)(p) & ((a) - 1)))
#define COMPV_IS_ALIGNED_MMX(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_MMX)
#define COMPV_IS_ALIGNED_SSE(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_SSE)
#define COMPV_IS_ALIGNED_AVX(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_AVX)
#define COMPV_IS_ALIGNED_AVX2(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_AVX2)
#define COMPV_IS_ALIGNED_AVX512(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_AVX512)
#define COMPV_IS_ALIGNED_NEON(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_NEON)
#define COMPV_IS_ALIGNED_DEFAULT(p) COMPV_IS_ALIGNED(p, COMPV_SIMD_ALIGNV_DEFAULT)

#define COMPV_ALIGNED(x)
#define COMPV_ALIGNED_DEFAULT(x)
#define COMPV_ALIGN_DEFAULT() COMPV_ALIGN(COMPV_SIMD_ALIGNV_DEFAULT)
#define COMPV_ALIGN_AVX() COMPV_ALIGN(COMPV_SIMD_ALIGNV_AVX)
#define COMPV_ALIGN_AVX2() COMPV_ALIGN(COMPV_SIMD_ALIGNV_AVX2)
#define COMPV_ALIGN_SSE() COMPV_ALIGN(COMPV_SIMD_ALIGNV_SSE)
#define COMPV_ALIGN_MMX() COMPV_ALIGN(COMPV_SIMD_ALIGNV_MMX)

#define COMPV_DEFAULT_ARG(arg_, val_) arg_

#define COMPV_IS_POW2(x) (((x) != 0) && !((x) & ((x) - 1)))

#define CompVPtrDef(T)			CompVPtr<T* >
#define CompVPtrArray(T)		CompVPtrDef(CompVArray<T >)
#define CompVPtrBox(T)			CompVPtrDef(CompVBox<T >)
#define CompVPtrBoxPoint(T)		CompVPtrDef(CompVBox<CompVPoint<T > >)

#define CompVPtrArrayNew(T)		CompVArray<T >::newObj
#define CompVPtrBoxNew(T)		CompVBox<T >::newObj
#define CompVPtrBoxPointNew(T)	CompVBox<CompVPoint<T > >::newObj

#if defined(_MSC_VER)
#	define snprintf		_snprintf
#	define vsnprintf	_vsnprintf
#	define strdup		_strdup
#	define stricmp		_stricmp
#	define strnicmp		_strnicmp
#else
#	if !HAVE_STRNICMP && !HAVE_STRICMP
#	define stricmp		strcasecmp
#	define strnicmp		strncasecmp
#	endif
#endif

/*******************************************************/
/* MACRO for shuffle parameter for _mm_shuffle_ps().   */
/* Argument fp3 is a digit[0123] that represents the fp*/
/* from argument "b" of mm_shuffle_ps that will be     */
/* placed in fp3 of result. fp2 is the same for fp2 in */
/* result. fp1 is a digit[0123] that represents the fp */
/* from argument "a" of mm_shuffle_ps that will be     */
/* places in fp1 of result. fp0 is the same for fp0 of */
/* result                                              */
/*******************************************************/
#define COMPV_MM_SHUFFLE(fp3,fp2,fp1,fp0) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))

/*
Macro to build arg32 values for _mm(256/128)_shuffle_epi8().
a,b,c,d must be <= 16 for _mm128_shuffle_epi8() and <32 for _mm256_shuffle_epi8()
*/
#define COMPV_MM_SHUFFLE_EPI8(fp3,fp2,fp1,fp0) ((fp3 << 24) | (fp2 << 16) | (fp1 << 8) | (fp0 & 0xFF))

typedef int32_t compv_core_id_t;
typedef intptr_t compv_scalar_t;  /* This type *must* have the width of a general-purpose register on the target CPU. 64bits or 32bits. */
typedef uintptr_t compv_uscalar_t;  /* This type *must* have the width of a general-purpose register on the target CPU. 64bits or 32bits. */
typedef float compv_float32_t;
typedef double compv_float64_t;
typedef compv_float32_t compv_float32x2_t[2];

enum COMPV_DEBUG_LEVEL {
    COMPV_DEBUG_LEVEL_INFO = 4,
    COMPV_DEBUG_LEVEL_WARN = 3,
    COMPV_DEBUG_LEVEL_ERROR = 2,
    COMPV_DEBUG_LEVEL_FATAL = 1,
};

#define kErrorCodeSuccessStart		0
#define kErrorCodeWarnStart			10000
#define kErrorCodeErrorStart		(kErrorCodeWarnStart << 1)
#define kErrorCodeFatalStart		(kErrorCodeErrorStart << 1)

// TODO(dmi) complete COMPVGetErrorString(code) with all the newly added codes
enum COMPV_ERROR_CODE {
    COMPV_ERROR_CODE_S_OK = kErrorCodeSuccessStart,

    COMPV_ERROR_CODE_W = kErrorCodeWarnStart,
	COMPV_ERROR_CODE_W_WINDOW_CLOSED,

    COMPV_ERROR_CODE_E = kErrorCodeErrorStart,
    COMPV_ERROR_CODE_E_NOT_IMPLEMENTED,
    COMPV_ERROR_CODE_E_NOT_INITIALIZED,
    COMPV_ERROR_CODE_E_NOT_FOUND,
    COMPV_ERROR_CODE_E_INVALID_CALL,
    COMPV_ERROR_CODE_E_INVALID_STATE,
    COMPV_ERROR_CODE_E_INVALID_PARAMETER,
    COMPV_ERROR_CODE_E_INVALID_PIXEL_FORMAT,
    COMPV_ERROR_CODE_E_INVALID_IMAGE_FORMAT,
    COMPV_ERROR_CODE_E_FAILED_TO_OPEN_FILE,
    COMPV_ERROR_CODE_E_FAILED_TO_READ_FILE,
    COMPV_ERROR_CODE_E_OUT_OF_MEMORY,
    COMPV_ERROR_CODE_E_OUT_OF_BOUND,
    COMPV_ERROR_CODE_E_DECODER_NOT_FOUND,
    COMPV_ERROR_CODE_E_FILE_NOT_FOUND,
    COMPV_ERROR_CODE_E_TIMEDOUT,
    COMPV_ERROR_CODE_E_UNITTEST_FAILED,
    COMPV_ERROR_CODE_E_SYSTEM,
    COMPV_ERROR_CODE_E_THIRD_PARTY_LIB,
    COMPV_ERROR_CODE_E_GL,
    COMPV_ERROR_CODE_E_GLEW,
    COMPV_ERROR_CODE_E_GLFW,

    COMPV_ERROR_CODE_F = kErrorCodeFatalStart,
};

#define COMPV_ERROR_CODE_IS_SUCCESS(code_) ((code_) < kErrorCodeWarnStart)
#define COMPV_ERROR_CODE_IS_OK(code_) COMPV_ERROR_CODE_IS_SUCCESS((code_))
#define COMPV_ERROR_CODE_IS_FAILURE(code_) (!COMPV_ERROR_CODE_IS_SUCCESS((code_)))
#define COMPV_ERROR_CODE_IS_NOK(code_) COMPV_ERROR_CODE_IS_FAILURE((code_))
#define COMPV_ERROR_CODE_IS_WARN(code_) ((code_) >= kErrorCodeWarnStart && (code_) < kErrorCodeErrorStart)
#define COMPV_ERROR_CODE_IS_ERROR(code_) ((code_) >= kErrorCodeErrorStart && (code_) < kErrorCodeFatalStart)
#define COMPV_ERROR_CODE_IS_FATAL(code_) ((code_) >= kErrorCodeFatalStart)

// In COMPV_CHECK_HR(errcode) When (errcode) is a function it will be executed twice when used in "COMPV_DEBUG_ERROR(errcode)" and "If(errcode)"
extern COMPV_BASE_API const char* CompVGetErrorString(COMPV_NAMESPACE::COMPV_ERROR_CODE code);
#define COMPV_CHECK_CODE_BAIL(errcode) do { COMPV_NAMESPACE::COMPV_ERROR_CODE __code__ = (errcode); if (COMPV_ERROR_CODE_IS_NOK(__code__)) { COMPV_DEBUG_ERROR("Operation Failed (%s)", CompVGetErrorString(__code__)); goto bail; } } while(0)
#define COMPV_CHECK_CODE_RETURN(errcode) do { COMPV_NAMESPACE::COMPV_ERROR_CODE __code__ = (errcode); if (COMPV_ERROR_CODE_IS_NOK(__code__)) { COMPV_DEBUG_ERROR("Operation Failed (%s)", CompVGetErrorString(__code__)); return __code__; } } while(0)
#define COMPV_CHECK_CODE_ASSERT(errcode) do { COMPV_NAMESPACE::COMPV_ERROR_CODE __code__ = (errcode); COMPV_ASSERT(COMPV_ERROR_CODE_IS_OK(__code__)); } while(0)
#define COMPV_CHECK_EXP_RETURN(exp, errcode) do { if ((exp)) COMPV_CHECK_CODE_RETURN(errcode); } while(0)
#define COMPV_CHECK_EXP_BAIL(exp, errcode) do { if ((exp)) COMPV_CHECK_CODE_BAIL(errcode); } while(0)

enum COMPV_SORT_TYPE {
    COMPV_SORT_TYPE_BUBBLE, /**< https://en.wikipedia.org/wiki/Bubble_sort */
    COMPV_SORT_TYPE_QUICK, /**< https://en.wikipedia.org/wiki/Quicksort */
};

enum {
    // These are per function-scope
    COMPV_TOKENIDX0,
    COMPV_TOKENIDX1,
    COMPV_TOKENIDX2,
    COMPV_TOKENIDX3,

    COMPV_TOKENIDX_MAX
    // no limitation but alloc memory -> do not abuse
};

enum COMPV_MAT_TYPE {
	COMPV_MAT_TYPE_RAW,
	COMPV_MAT_TYPE_PIXELS
};

enum COMPV_MAT_SUBTYPE { // 'COMPV_MAT_SUBTYPE_PIXELS_XXX' are same as 'COMPV_PIXEL_FORMAT'
	COMPV_MAT_SUBTYPE_RAW,

	COMPV_MAT_SUBTYPE_PIXELS_R8G8B8, // RGB24
	COMPV_MAT_SUBTYPE_PIXELS_B8G8R8, // BGR8
	COMPV_MAT_SUBTYPE_PIXELS_R8G8B8A8, // RGB32
	COMPV_MAT_SUBTYPE_PIXELS_B8G8R8A8, // BGRA32
	COMPV_MAT_SUBTYPE_PIXELS_A8B8G8R8, // ABGR32
	COMPV_MAT_SUBTYPE_PIXELS_A8R8G8B8, // ARGB32
	COMPV_MAT_SUBTYPE_PIXELS_GRAYSCALE, // Y-only
	COMPV_MAT_SUBTYPE_PIXELS_I420, // http://www.fourcc.org/yuv.php#IYUV
	COMPV_MAT_SUBTYPE_PIXELS_IYUV = COMPV_MAT_SUBTYPE_PIXELS_I420
	//!\\ Update 'COMPV_PIXEL_FORMAT' if you add new values to COMPV_MAT_SUBTYPE_PIXELS_XXX
};

enum COMPV_PIXEL_FORMAT { // Same as 'COMPV_MAT_SUBTYPE'
	COMPV_PIXEL_FORMAT_NONE = COMPV_MAT_SUBTYPE_RAW,
	COMPV_PIXEL_FORMAT_R8G8B8 = COMPV_MAT_SUBTYPE_PIXELS_R8G8B8, // RGB24
	COMPV_PIXEL_FORMAT_B8G8R8 = COMPV_MAT_SUBTYPE_PIXELS_B8G8R8, // BGR8
	COMPV_PIXEL_FORMAT_R8G8B8A8 = COMPV_MAT_SUBTYPE_PIXELS_R8G8B8A8, // RGB32
	COMPV_PIXEL_FORMAT_B8G8R8A8 = COMPV_MAT_SUBTYPE_PIXELS_B8G8R8A8, // BGRA32
	COMPV_PIXEL_FORMAT_A8B8G8R8 = COMPV_MAT_SUBTYPE_PIXELS_A8B8G8R8, // ABGR32
	COMPV_PIXEL_FORMAT_A8R8G8B8 = COMPV_MAT_SUBTYPE_PIXELS_A8R8G8B8, // ARGB32
	COMPV_PIXEL_FORMAT_GRAYSCALE = COMPV_MAT_SUBTYPE_PIXELS_GRAYSCALE, // Y-only
	COMPV_PIXEL_FORMAT_I420 = COMPV_MAT_SUBTYPE_PIXELS_I420, // http://www.fourcc.org/yuv.php#IYUV
	COMPV_PIXEL_FORMAT_IYUV = COMPV_MAT_SUBTYPE_PIXELS_IYUV
	//!\\ Update 'COMPV_MAT_SUBTYPE_PIXELS_XXX' if you add new values here
};

enum COMPV_IMAGE_FORMAT {
	COMPV_IMAGE_FORMAT_NONE,
	COMPV_IMAGE_FORMAT_RAW,
	COMPV_IMAGE_FORMAT_JPEG,
	COMPV_IMAGE_FORMAT_JPG = COMPV_IMAGE_FORMAT_JPEG,
	COMPV_IMAGE_FORMAT_BMP,
	COMPV_IMAGE_FORMAT_BITMAP = COMPV_IMAGE_FORMAT_BMP,
	COMPV_IMAGE_FORMAT_PNG
};

struct CompVImageInfo {
	COMPV_IMAGE_FORMAT format;
	COMPV_PIXEL_FORMAT pixelFormat;
	int32_t width;
	int32_t stride;
	int32_t height;
public:
	CompVImageInfo() : format(COMPV_IMAGE_FORMAT_RAW), pixelFormat(COMPV_PIXEL_FORMAT_NONE), width(0), stride(0), height(0) { }
};

COMPV_NAMESPACE_END()

#endif /* _COMPV_BASE_COMMON_H_ */