#pragma once

#include "VertexArray.h"

/*3D网格，用于表示物体的模型*/
class Mesh{
public:
	enum ColorMode{COLOR, TEXTURE};

	/*不推荐使用无参构造*/
	Mesh();

	/*参数：
	*1.顶点数目
	*2.绘图模式。从列表中选取：{GL_LINES, GL_TRIANGLES}*/
	Mesh(unsigned vertexAmount, GLenum paintMode = GL_TRIANGLES); //把每个顶点作为一个独立的三角形

	/*清空数据*/
	void clear();

	/*绘制在屏幕上*/
	void paint();

	/*复制并装载数据
	*参数：
	*1.指向源数据的指针（任意类型指针可以强转成void*类型再传参）。源数据将被复制
	*2.源数据长度（字节数）
	*3.数据类型，从以下列表选取{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE……}
	*4.多少个数据表示一个点（如对于RGB表示的颜色，该参数为3）
	*/
	/*装载顶点坐标*/
	void loadVertex(void *pSrc, int length, GLenum type, int size);
	/*装载颜色*/
	void loadColor(void *pSrc, int length, GLenum type, int size);
	/*装载法向量*/
	void loadNormal(void *pSrc, int length, GLenum type);
	/*装载索引*/
	void loadIndex(void *pSrc, int length, GLenum type);

	/*析构*/
	~Mesh();

	/*初始化渲染参数(在使用Mesh之前调用)
	*打开背面剔除
	*设定清除颜色为黑色
	*打开平滑渐变
	*打开混合；设定alpha混合方程
	*定义“正面”的环绕方向
	*
	*参数：
	*1.是否应用顶点索引来绘图
	*2.是否计算光照
	*3.指定颜色的方式，二选一{TEXTURE, COLOR}TEXTURE表示颜色来自纹理贴图，COLOR表示直接指定颜色
	*4.定义正面的环绕方向，二选一{GL_CCW, GL_CW}CCW表示逆时针为正面，CW表示顺时针为正面
	*/
	static void InitMesh(bool usingIndex = true, bool usingLighting = true, ColorMode colorMode = TEXTURE, GLenum mode = GL_CCW);

	/*定义“正面”的环绕方向，参数为GL_CCW（逆时针）或GL_CW（顺时针）*/
	static void SetFrontFace(GLenum mode);

	/*设定新的绘画模式
	*参数同初始化函数*/
	static void SetRenderMode(bool usingIndex = true, bool usingLighting = true, ColorMode colorMode = TEXTURE);

protected:
	//坐标数组，必须使用
	VertexArray m_vertexArray; 

	//法向量数组，计算光照时使用
	VertexArray m_normalArray;

	//颜色数组，二选一：1.直接指定颜色 或 2.来自纹理
	VertexArray m_colorArray;
	VertexArray m_textureArray;

	//索引数组，可选
	VertexArray m_indexArray;

	unsigned m_vertexAmount;
	GLenum m_paintMode;

	/*渲染状态*/
	static bool m_usingIndex;
	static bool m_usingLighting;
	static ColorMode m_colorMode;
};