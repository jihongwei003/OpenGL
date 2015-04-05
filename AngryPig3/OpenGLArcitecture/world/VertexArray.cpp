#include "VertexArray.h"

#include <string.h>

#include <iostream>/////////////////////////////////////////////////////////////////////

VertexArray::VertexArray()
{
	m_pInfo = NULL;
}

void VertexArray::loadArray(void *pSrc, int length, GLenum type, int size)
{
	m_pInfo = (void*)(new char[length]);

	memcpy(m_pInfo, pSrc, length);
	m_type = type;
	m_size = size;
}

void* VertexArray::getInfoPointer()
{
	return m_pInfo;
}

GLenum VertexArray::getType()
{
	return m_type;
}

int VertexArray::getSize()
{
	return m_size;
}

void VertexArray::clear()
{
	if(m_pInfo != NULL)
	{
		delete[] m_pInfo;
		m_pInfo = NULL;//重新初始化！不能有野指针
	}
}

VertexArray::~VertexArray()
{
	clear();
}