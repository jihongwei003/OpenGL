/*
* 绘制一个物体，首先要设置渲染模式（如果是下列默认值，则可以省略），然后再进行渲染
* 渲染模式：
*	bool usingIndex      是否使用索引，默认true
*	bool usingLighting   是否使用光照，默认true；可追加设置光照材质
*	ColorMode colorMode  颜色模式，默认TEXTURE //自动绑定纹理贴图
*	GLenum mode          “正面”的环绕方向，GL_CCW（逆时针），GL_CW（顺时针）默认逆时针
*	GLenum paintMode     同glBegin()参数
*/
#include "Object.h"
#include "MathConst.h"
#include <math.h>
#include "ProjectToAxis.h"

Object::Object() 
{
	m_available = true;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	m_rotX = 0; //侧翻角
	m_rotY = 0; //转角
	m_rotZ = 0; //仰角

	m_usingIndex = false;
	m_usingLighting = true;
	m_colorMode = TEXTURE;
	m_mode = GL_CCW;
	m_paintMode = GL_TRIANGLES;
	//SetRenderMode应该放在绘制的时候，因为初始化模型的时候设置没用！
}

void Object::SetRenderMode(
	bool usingIndex,
	bool usingLighting,
	ColorMode colorMode,
	GLenum mode,
	GLenum paintMode)
{
	m_usingIndex = usingIndex;
	m_usingLighting = usingLighting;
	m_colorMode = colorMode;
	m_mode = mode;
	m_paintMode = paintMode;

	if (usingLighting)
		glEnableClientState(GL_NORMAL_ARRAY);
	else
		glDisableClientState(GL_NORMAL_ARRAY);

	if (TEXTURE == colorMode)
	{
		glEnable(GL_TEXTURE_2D);
		m_meshModel.m_texture.Apply(); //必须在绘制之前绑定纹理贴图
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY); 
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glEnableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Object::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}
void Object::SetRot(float rotX, float rotY, float rotZ)
{
		m_rotX = rotX;
		m_rotY = rotY;
		m_rotZ = rotZ;
}

void Object::GetPos(float *x, float *y, float *z)
{
	*x = m_x;
	*y = m_y;
	*z = m_z;
}

/* 是否为一次性物体（如子弹） */
void Object::SetAvailable(bool available)
{
	m_available = available;
}
bool Object::IsAvailable()
{
	return m_available;
}

/* 绘制出来经过坐标变换和旋转的模型 */
void Object::Paint(unsigned vertexAmount)
{
	glPushMatrix();
	
	glTranslatef(m_x, m_y, m_z);
	
	glRotatef(m_rotX, 1.0f, 0.0f, 0.0f); //摆放时的角度，和“Move”无关！
	glRotatef(m_rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotZ, 0.0f, 0.0f, 1.0f);
	
	PaintModel(vertexAmount);
	
	glPopMatrix();
}

/*绘制出来没有经过坐标变换和旋转的模型 */
void Object::PaintModel(unsigned vertexAmount)
{
	//指定使用顶点数据(size,type,stride,pointer)
	glVertexPointer(m_meshModel.m_vertexArray.GetSize(), m_meshModel.m_vertexArray.GetType(), 0, m_meshModel.m_vertexArray.GetInfoPointer());

	//如果需要则装入法向量
	if (m_usingLighting)
	{
		glNormalPointer(m_meshModel.m_normalArray.GetType(), 0, m_meshModel.m_normalArray.GetInfoPointer());
	}

	//根据渲染模式装入颜色或者纹理
	if (TEXTURE == m_colorMode)
	{
		glTexCoordPointer(m_meshModel.m_textureArray.GetSize(), m_meshModel.m_textureArray.GetType(), 0, m_meshModel.m_textureArray.GetInfoPointer());
	}
	else
	{
		glColorPointer(m_meshModel.m_colorArray.GetSize(), m_meshModel.m_colorArray.GetType(), 0, m_meshModel.m_colorArray.GetInfoPointer());
	}

	/* 解引用数组元素的单个列表 */
	if (m_usingIndex) //默认不使用索引,只有Axis里指定过
	{
		//(mode,count,type,indices)；type同glBegin()中参数；获取当前所有已经启用的数组的顶点数据
		glDrawElements(m_paintMode, vertexAmount, m_meshModel.m_indexArray.GetType(), m_meshModel. m_indexArray.GetInfoPointer());
	}
	else
	{
		//(mode,first,count)；只能按顺序访问数据数组
		glDrawArrays(m_paintMode, 0, vertexAmount);
	}
}