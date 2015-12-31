/* Copyright (C) 2016 Doubango Telecom <https://www.doubango.org>
*
* This file is part of Open Source ComputerVision (a.k.a CompV) project.
* Source code hosted at https://github.com/DoubangoTelecom/compv
* Website hosted at http://compv.org
*
* CompV is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CompV is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CompV.
*/
#include "compv/compv_buffer.h"
#include "compv/compv_mem.h"
#include "compv/compv_debug.h"

COMPV_NAMESPACE_BEGIN()

CompVBuffer::CompVBuffer(const void* pcPtr /*= NULL*/, size_t size /*= 0*/)
: CompVObj()
, m_pPtr(NULL)
, m_nSize(0)
{
	if (pcPtr && size) {
		COMPV_ASSERT(COMPV_ERROR_CODE_IS_OK(copyData(pcPtr, size)));
	}
}

COMPV_ERROR_CODE CompVBuffer::copyData(const void* pcPtr, size_t size)
{
	if (!pcPtr || !size) {
		COMPV_DEBUG_ERROR("Invalid parameter");
		return COMPV_ERROR_CODE_E_INVALID_PARAMETER;
	}
	COMPV_ASSERT((m_pPtr = CompVMem::realloc(m_pPtr, size)) != NULL);
	if (m_pPtr) {
		m_nSize = size;
		memcpy(m_pPtr, pcPtr, size);
	}
	else {
		COMPV_DEBUG_FATAL("Failed to allocate buffer with size = %lu", size);
		return COMPV_ERROR_CODE_E_OUT_OF_MEMORY;
	}
	return COMPV_ERROR_CODE_S_OK;
}

COMPV_ERROR_CODE CompVBuffer::takeData(void** ppPtr, size_t size)
{
	if (!ppPtr || !*ppPtr || !size) {
		COMPV_DEBUG_ERROR("Invalid parameter");
		return COMPV_ERROR_CODE_E_INVALID_PARAMETER;
	}
	CompVMem::free(&m_pPtr);
	m_pPtr = *ppPtr, *ppPtr = NULL;
	m_nSize = size;
	return COMPV_ERROR_CODE_S_OK;
}

CompVBuffer::~CompVBuffer()
{
	CompVMem::free(&m_pPtr);
}

COMPV_ERROR_CODE CompVBuffer::newObj(const void* pcPtr, size_t size, CompVObjWrapper<CompVBuffer*>* buffer)
{
	if (!buffer) {
		COMPV_DEBUG_ERROR("Invalid parameter");
		return COMPV_ERROR_CODE_E_INVALID_PARAMETER;
	}
	*buffer = new CompVBuffer(pcPtr, size);
	if (!*buffer) {
		COMPV_DEBUG_ERROR("Failed to alloc new 'CompVBuffer' object");
		return COMPV_ERROR_CODE_E_OUT_OF_MEMORY;
	}
	return COMPV_ERROR_CODE_S_OK;
}

COMPV_ERROR_CODE CompVBuffer::newObjAndNullData(CompVObjWrapper<CompVBuffer*>* buffer)
{
	return CompVBuffer::newObj(NULL, 0, buffer);
}

COMPV_ERROR_CODE CompVBuffer::newObjAndTakeData(void** ppPtr, size_t size, CompVObjWrapper<CompVBuffer*>* buffer)
{
	CompVObjWrapper<CompVBuffer*> buffer_;
	COMPV_ERROR_CODE err = COMPV_ERROR_CODE_S_OK;

	if (!buffer) {
		COMPV_DEBUG_ERROR("Invalid parameter");
		return COMPV_ERROR_CODE_E_INVALID_PARAMETER;
	}

	COMPV_CHECK_CODE_BAIL(err = CompVBuffer::newObjAndNullData(&buffer_));
	COMPV_CHECK_CODE_BAIL(err = buffer_->takeData(ppPtr, size));
	*buffer = buffer_;

bail:
	return err;
}

COMPV_ERROR_CODE CompVBuffer::newObjAndCopyData(const void* pcPtr, size_t size, CompVObjWrapper<CompVBuffer*>* buffer)
{
	CompVObjWrapper<CompVBuffer*> buffer_;
	COMPV_ERROR_CODE err = COMPV_ERROR_CODE_S_OK;

	if (!buffer) {
		COMPV_DEBUG_ERROR("Invalid parameter");
		return COMPV_ERROR_CODE_E_INVALID_PARAMETER;
	}

	COMPV_CHECK_CODE_BAIL(err = CompVBuffer::newObjAndNullData(&buffer_));
	COMPV_CHECK_CODE_BAIL(err = buffer_->copyData(pcPtr, size));
	*buffer = buffer_;

bail:
	return err;
}

COMPV_NAMESPACE_END()
