#pragma once

#include <glut.h>

class VertexArray{
public:
	VertexArray();

	/*参数：
	* 1.指向源数据的指针（任意类型指针可以强转成void*类型再传参）,源数据将被复制
	* 2.源数据长度（字节数）
	* 3.数据类型，从以下列表选取{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE……}
	* 4.多少个数据表示一个点（如对于RGB表示的颜色，该参数为3）
	*/
	void LoadArray(void *pSrc, int length, GLenum type, int size);

	void* GetInfoPointer(); 
	GLenum GetType();
	int GetSize();

	void Clear(); //释放内存

	~VertexArray();

protected:
	void *m_pInfo;
	GLenum m_type;
	int m_size;
};