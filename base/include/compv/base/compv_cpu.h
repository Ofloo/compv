/* Copyright (C) 2016-2017 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: GPLv3. For commercial license please contact us.
* Source code: https://github.com/DoubangoTelecom/compv
* WebSite: http://compv.org
*/
#if !defined(_COMPV_BASE_CPU_H_)
#define _COMPV_BASE_CPU_H_

#include "compv/base/compv_config.h"
#include "compv/base/compv_obj.h"
#include "compv/base/compv_common.h"

COMPV_NAMESPACE_BEGIN()

#define COMPV_CPU_FLAG_BIT(b_) (((uint64_t)1) << (b_))
#define COMPV_CPU_FLAG_IS_SET(flags_, b_) (((uint64_t)(flags_) & COMPV_CPU_FLAG_BIT(b_)) != 0)
// Vendor
static const uint64_t kCpuFlagIntel = COMPV_CPU_FLAG_BIT(0);
static const uint64_t kCpuFlagAMD = COMPV_CPU_FLAG_BIT(1);

// These flags are only valid on ARM processors.
static const uint64_t kCpuFlagARM = COMPV_CPU_FLAG_BIT(5);
static const uint64_t kCpuFlagARM64 = COMPV_CPU_FLAG_BIT(6);
static const uint64_t kCpuFlagARM_NEON = COMPV_CPU_FLAG_BIT(7);
static const uint64_t kCpuFlagARM_NEON_FMA = COMPV_CPU_FLAG_BIT(8);
// 0x9 reserved for future ARM flag.

// These flags are only valid on x86/x64 processors.
static const uint64_t kCpuFlagX86 = COMPV_CPU_FLAG_BIT(10);
static const uint64_t kCpuFlagX64 = COMPV_CPU_FLAG_BIT(11);
static const uint64_t kCpuFlagMMX = COMPV_CPU_FLAG_BIT(12);
static const uint64_t kCpuFlagSSE = COMPV_CPU_FLAG_BIT(13);
static const uint64_t kCpuFlagSSE2 = COMPV_CPU_FLAG_BIT(14);
static const uint64_t kCpuFlagSSE3 = COMPV_CPU_FLAG_BIT(15);
static const uint64_t kCpuFlagSSSE3 = COMPV_CPU_FLAG_BIT(16);
static const uint64_t kCpuFlagSSE41 = COMPV_CPU_FLAG_BIT(17);
static const uint64_t kCpuFlagSSE42 = COMPV_CPU_FLAG_BIT(18);
static const uint64_t kCpuFlagSSE4a = COMPV_CPU_FLAG_BIT(19);
static const uint64_t kCpuFlagAVX = COMPV_CPU_FLAG_BIT(20);
static const uint64_t kCpuFlagAVX2 = COMPV_CPU_FLAG_BIT(21);
static const uint64_t kCpuFlagAVX512 = COMPV_CPU_FLAG_BIT(22);
static const uint64_t kCpuFlagFMA3 = COMPV_CPU_FLAG_BIT(23);
static const uint64_t kCpuFlagFMA4 = COMPV_CPU_FLAG_BIT(24);
static const uint64_t kCpuFlagERMS = COMPV_CPU_FLAG_BIT(25);
static const uint64_t kCpuFlagXOP = COMPV_CPU_FLAG_BIT(26);
static const uint64_t kCpuFlagLZCNT = COMPV_CPU_FLAG_BIT(27);
static const uint64_t kCpuFlagPOPCNT = COMPV_CPU_FLAG_BIT(28);
static const uint64_t kCpuFlagCMOV = COMPV_CPU_FLAG_BIT(29); // Conditional move and FCMOV instructions
static const uint64_t kCpuFlagAES = COMPV_CPU_FLAG_BIT(30);
static const uint64_t kCpuFlagRDRAND = COMPV_CPU_FLAG_BIT(31);
static const uint64_t kCpuFlagAVX512_F = COMPV_CPU_FLAG_BIT(32);
static const uint64_t kCpuFlagAVX512_CD = COMPV_CPU_FLAG_BIT(33);
static const uint64_t kCpuFlagAVX512_PF = COMPV_CPU_FLAG_BIT(34);
static const uint64_t kCpuFlagAVX512_ER = COMPV_CPU_FLAG_BIT(35);
static const uint64_t kCpuFlagAVX512_VL = COMPV_CPU_FLAG_BIT(36);
static const uint64_t kCpuFlagAVX512_BW = COMPV_CPU_FLAG_BIT(37);
static const uint64_t kCpuFlagAVX512_DQ = COMPV_CPU_FLAG_BIT(38);
static const uint64_t kCpuFlagAVX512_IFMA = COMPV_CPU_FLAG_BIT(39);
static const uint64_t kCpuFlagAVX512_VBMI = COMPV_CPU_FLAG_BIT(49);

// These flags are only valid on MIPS processors.
static const uint64_t kCpuFlagMIPS = COMPV_CPU_FLAG_BIT(50);
static const uint64_t kCpuFlagMIPS_DSP = COMPV_CPU_FLAG_BIT(51);
static const uint64_t kCpuFlagMIPS_DSPR2 = COMPV_CPU_FLAG_BIT(52);

static const uint64_t kCpuFlagNone = ((uint64_t)0);
static const uint64_t kCpuFlagAll = ~kCpuFlagNone;

class COMPV_BASE_API CompVCpu : public CompVObj
{
protected:
    CompVCpu();
public:
    virtual ~CompVCpu();
    static COMPV_ERROR_CODE init();
    static int32_t coresCount() {
        return s_iCores;
    }
    static compv_core_id_t validCoreId(compv_core_id_t coreId);
    static uint64_t cyclesCountGlobal();
    static int32_t cache1LineSize() {
        return s_iCache1LineSize;
    }
    static int32_t cache1Size() {
        return s_iCache1Size;
    }
    static uint64_t timeProcess();
    static uint64_t getFlags() {
        return s_uFlags;
    }
    static uint64_t flagsDisabled() {
        return s_uFlagsDisabled;
    }
    static uint64_t flagsEnabled() {
        return s_uFlagsEnabled;
    }
    static const char* flagsAsString(uint64_t uFlags);
    static bool isEnabled(uint64_t flag) {
        return (s_uFlagsEnabled & flag) == flag;
    }
    static bool isSupported(uint64_t flag) {
        return (s_uFlags & flag) == flag;
    }
    static COMPV_ERROR_CODE flagsDisable(uint64_t flags);
    static COMPV_ERROR_CODE flagsEnable(uint64_t flags);
    static COMPV_ERROR_CODE setAsmEnabled(bool bEnabled);
    static COMPV_ERROR_CODE setIntrinsicsEnabled(bool bEnabled);
	static COMPV_ERROR_CODE setMathTrigFastEnabled(bool bMathTrigFast);
	static COMPV_ERROR_CODE setMathFixedPointEnabled(bool bMathFixedPoint);
	static COMPV_ERROR_CODE setIntelIppEnabled(bool bIntelIpp);
	static bool isBigEndian() {
		COMPV_CHECK_EXP_NOP(!s_bInitialized, COMPV_ERROR_CODE_E_NOT_INITIALIZED);
		return s_bBigEndian;
	}
	static bool isLittleEndian() { return !isBigEndian(); }
    static bool isAsmEnabled() { return CompVCpu::s_bAsmEnabled; }
    static bool isIntrinsicsEnabled() { return CompVCpu::s_bIntrinsicsEnabled; }
	static bool isMathTrigFast() { return s_bMathTrigFast; }
	static bool isMathFixedPoint() { return s_bMathFixedPoint; }
	static bool isIntelIppEnabled() { return s_bIntelIpp; }

private:
	static bool s_bInitialized;
    static uint64_t s_uFlags;
    static uint64_t s_uFlagsDisabled;
    static uint64_t s_uFlagsEnabled;
	static bool s_bBigEndian;
    static bool s_bAsmEnabled;
    static bool s_bIntrinsicsEnabled;
	static bool s_bMathTrigFast;
	static bool s_bMathFixedPoint;
	static bool s_bIntelIpp;
    static int32_t s_iCores;
    static int32_t s_iCache1LineSize;
    static int32_t s_iCache1Size;
};

COMPV_NAMESPACE_END()

#endif /* _COMPV_BASE_CPU_H_ */
