#include "../tests/tests_common.h"

#define TAG_TEST								"UnitTestMathDot"
#if COMPV_OS_WINDOWS
#	define COMPV_TEST_IMAGE_FOLDER				"C:/Projects/GitHub/data/test_images"
#elif COMPV_OS_OSX
#	define COMPV_TEST_IMAGE_FOLDER				"/Users/mamadou/Projects/GitHub/data/test_images"
#else
#	define COMPV_TEST_IMAGE_FOLDER				NULL
#endif
#define COMPV_TEST_PATH_TO_FILE(filename)		compv_tests_path_from_file(filename, COMPV_TEST_IMAGE_FOLDER)

#define FILE_NAME_EQUIRECTANGULAR		"equirectangular_1282x720_gray.yuv"
#define FILE_NAME_OPENGLBOOK			"opengl_programming_guide_8th_edition_200x258_gray.yuv"
#define FILE_NAME_GRIOTS				"mandekalou_480x640_gray.yuv"

static const struct compv_unittest_dot {
	const bool dotSub;
	const bool float64Typ;
	const double sum;
} COMPV_UNITTEST_DOT[] =
{
	{ false, false, 416746.96347632096 }, // dot_float32
	{ true, false, 711936.62500000000 }, // dotSub_float32
	{ false, true, 416746.92382917117 }, // dot_float64
	{ true, true, 711936.70357957715 }, // dotSub_float64
};
static const size_t COMPV_UNITTEST_DOT_COUNT = sizeof(COMPV_UNITTEST_DOT) / sizeof(COMPV_UNITTEST_DOT[0]);

static const std::string compv_unittest_dot_to_string(const compv_unittest_dot* test) {
	return 
		std::string("dotSub:") + CompVBase::to_string(test->dotSub)
		+ std::string(", float64Typ:") + CompVBase::to_string(test->float64Typ);
}

COMPV_ERROR_CODE unittest_math_dot()
{
	for (size_t i = 0; i < COMPV_UNITTEST_DOT_COUNT; ++i) {
		const compv_unittest_dot* test = &COMPV_UNITTEST_DOT[i];
		COMPV_DEBUG_INFO_EX(TAG_TEST, "== Trying new test: MATH(DotProduct) -> %s ==", compv_unittest_dot_to_string(test).c_str());
		CompVMatPtr aa, bb;
		COMPV_CHECK_CODE_RETURN(CompVImage::read(COMPV_SUBTYPE_PIXELS_Y, 1282, 720, 1282, COMPV_TEST_PATH_TO_FILE(FILE_NAME_EQUIRECTANGULAR).c_str(), &aa));
		COMPV_CHECK_CODE_RETURN(CompVImage::read(COMPV_SUBTYPE_PIXELS_Y, 480, 640, 480, COMPV_TEST_PATH_TO_FILE(FILE_NAME_GRIOTS).c_str(), &bb));
		// I want the width to be odd (e.g. 1281x721) in order to have orphans
		COMPV_CHECK_CODE_RETURN(CompVImage::scale(aa, &aa, 1283, 721, COMPV_INTERPOLATION_TYPE_BICUBIC_FLOAT32));
		COMPV_CHECK_CODE_RETURN(CompVImage::scale(bb, &bb, 1283, 721, COMPV_INTERPOLATION_TYPE_BICUBIC_FLOAT32));
		if (test->float64Typ) {
			COMPV_CHECK_CODE_RETURN((CompVMathCast::process_static<float, double>(aa, &aa)));
			COMPV_CHECK_CODE_RETURN((CompVMathCast::process_static<float, double>(bb, &bb)));
		}
		// reduction to avoid overflow
		COMPV_CHECK_CODE_RETURN(CompVMath::scale(aa, 8e-3, &aa));
		COMPV_CHECK_CODE_RETURN(CompVMath::scale(bb, 8e-3, &bb));
		double sum;
		const double maxErr = (compv_tests_is_fma_enabled() || CompVThreadDispatcher::guessNumThreadsDividingAcrossY(1, aa->rows(), 1)) // MT and FMA slightly change the sum
			? (test->float64Typ ? 1.71131e-08 : 1.71131e-01)
			: 0;
		COMPV_ERROR_CODE(*dot_func)(const CompVMatPtr &A, const CompVMatPtr &B, double* ret)
			= test->dotSub ? CompVMath::dotSub : CompVMath::dot;		
		COMPV_CHECK_CODE_RETURN(dot_func(aa, bb, &sum));
		COMPV_DEBUG_INFO_EX(TAG_TEST, "sum= %lf vs %lf, err = %lf", sum, test->sum, std::abs(sum - test->sum));
		COMPV_CHECK_EXP_RETURN(std::abs(sum - test->sum) > maxErr, COMPV_ERROR_CODE_E_UNITTEST_FAILED, "Dot sum mismatch");
		COMPV_DEBUG_INFO_EX(TAG_TEST, "** Test OK **");
	}

	return COMPV_ERROR_CODE_S_OK;
}
