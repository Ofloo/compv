#include "../tests_common.h"
#include <compv/base/jsoncpp-1.8.4/json.h>

#define TAG_TEST			"TestPCA"
#if COMPV_OS_WINDOWS
#	define COMPV_TEST_MATH_FOLDER				"C:/Projects/GitHub/data/math"
#elif COMPV_OS_OSX
#	define COMPV_TEST_MATH_FOLDER				"/Users/mamadou/Projects/GitHub/data/math"
#else
#	define COMPV_TEST_MATH_FOLDER				NULL
#endif
#define COMPV_TEST_PATH_TO_FILE(filename)		compv_tests_path_from_file(filename, COMPV_TEST_MATH_FOLDER)

#define LOOP_COUNT			1

#define NUM_OBSERVATIONS		100
#define OBSERVATION_DIM			441
#define OBSERVATION_ROW_BASED	true // each row is an observation
#define PCA_DIM					92
#define FILE_INIT				"pca_init.json"
#define FILE_FEATURES_PARTIAL	"pca_features_partial.json"
#define FILE_FEATURES_FULL		"pca_features_full.json" // Do not include in unittest (large, too slow)

static COMPV_ERROR_CODE pca_compue();

COMPV_ERROR_CODE pca()
{
#if 1
	COMPV_CHECK_CODE_RETURN(pca_compue());
#elif 0
#endif

	return COMPV_ERROR_CODE_S_OK;
}

static COMPV_ERROR_CODE pca_compue()
{
#define PCA_COMPUTE_MEAN_MD5				"1eaf666bfd2097acbd4ca9c552a62fb7"
#define PCA_COMPUTE_EIGEN_VECTORS_MD5		"4af8ef623793f5480f673c2b0a1df6be"
#define PCA_COMPUTE_EIGEN_VALUES_MD5		"3344f4803ac45673db434d3151f6bc85"

#define PCA_COMPUTE_MEAN_FMA_MD5			"1eaf666bfd2097acbd4ca9c552a62fb7"
#define PCA_COMPUTE_EIGEN_VECTORS_FMA_MD5	"d5b38cb1a046f1403290654c436ea0f9"
#define PCA_COMPUTE_EIGEN_VALUES_FMA_MD5	"3344f4803ac45673db434d3151f6bc85"
	CompVBufferPtr content;
	Json::Reader reader;
	Json::Value root;
	COMPV_CHECK_CODE_RETURN(CompVFileUtils::read(COMPV_TEST_PATH_TO_FILE(FILE_FEATURES_PARTIAL).c_str(), &content));
	COMPV_CHECK_EXP_RETURN(!reader.parse(reinterpret_cast<const char*>(content->ptr()), reinterpret_cast<const char*>(content->ptr()) + content->size(), root, false)
		, COMPV_ERROR_CODE_E_JSON_CPP, "JSON parsing failed");

	CompVMatPtr features;
	COMPV_CHECK_CODE_RETURN(CompVJSON::read(&root, "features", &features));

	CompVMathPCAPtr pca;
	COMPV_CHECK_CODE_RETURN(CompVMathPCA::newObj(&pca));

	const uint64_t timeStart = CompVTime::nowMillis();
	for (size_t i = 0; i < LOOP_COUNT; ++i) {
		COMPV_CHECK_CODE_RETURN(pca->compute(features, PCA_DIM, OBSERVATION_ROW_BASED));
	}
	const uint64_t timeEnd = CompVTime::nowMillis();

	COMPV_DEBUG_INFO_EX(TAG_TEST, "Elapsed time(PCA, compute) = [[[ %" PRIu64 " millis ]]]", (timeEnd - timeStart));
#if 0
	COMPV_DEBUG_INFO_EX(TAG_TEST, "Mean=%s", compv_tests_md5(pca->mean()).c_str());
	COMPV_DEBUG_INFO_EX(TAG_TEST, "Vectors=%s", compv_tests_md5(pca->eingenVectors()).c_str());
	COMPV_DEBUG_INFO_EX(TAG_TEST, "values=%s", compv_tests_md5(pca->eingenValues()).c_str());
#endif

	COMPV_CHECK_EXP_RETURN(compv_tests_md5(pca->mean()).compare(compv_tests_is_fma_enabled() ? PCA_COMPUTE_MEAN_FMA_MD5 : PCA_COMPUTE_MEAN_MD5) != 0, COMPV_ERROR_CODE_E_UNITTEST_FAILED, "PCA Mean mismatch");
	COMPV_CHECK_EXP_RETURN(compv_tests_md5(pca->eingenVectors()).compare(compv_tests_is_fma_enabled() ? PCA_COMPUTE_EIGEN_VECTORS_FMA_MD5 : PCA_COMPUTE_EIGEN_VECTORS_MD5) != 0, COMPV_ERROR_CODE_E_UNITTEST_FAILED, "PCA EigenVectors mismatch");
	COMPV_CHECK_EXP_RETURN(compv_tests_md5(pca->eingenValues()).compare(compv_tests_is_fma_enabled() ? PCA_COMPUTE_EIGEN_VALUES_FMA_MD5 : PCA_COMPUTE_EIGEN_VALUES_MD5) != 0, COMPV_ERROR_CODE_E_UNITTEST_FAILED, "PCA EigenValues mismatch");

#undef PCA_COMPUTE_MEAN_MD5
#undef PCA_COMPUTE_EIGEN_VECTORS_MD5
#undef PCA_COMPUTE_EIGEN_VALUES_MD5
#undef PCA_COMPUTE_MEAN_FMA_MD5
#undef PCA_COMPUTE_EIGEN_VECTORS_FMA_MD5
#undef PCA_COMPUTE_EIGEN_VALUES_FMA_MD5
	return COMPV_ERROR_CODE_S_OK;
}
