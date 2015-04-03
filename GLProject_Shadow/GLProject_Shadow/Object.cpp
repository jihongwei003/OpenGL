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
#include <math.h>
#include "ProjectToAxis.h"
#include "GLPointf.h"

#include "ViewManager.h"

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

	shadowDepth = 100;
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


void Object::PaintShadow(float vertex[][3], float lightPos[3])
{
	glDisable(GL_LIGHTING); //关闭灯光

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //关闭颜色缓存的写入	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	//设置深度比较函数
	glDepthMask(GL_FALSE);	//关闭深度缓存的写入

	glEnable(GL_STENCIL_TEST); //使用蒙板缓存

	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	//如果是逆时针（即面向视点）的多边形，通过了蒙板和深度测试，则把蒙板的值增加1
	glFrontFace(GL_CCW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	DoShadowPass(vertex, lightPos);

	//如果是顺时针（即背向视点）的多边形，通过了蒙板和深度测试，则把蒙板的值减少1
	glFrontFace(GL_CW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	DoShadowPass(vertex, lightPos);



	//把阴影绘制上颜色

	glFrontFace(GL_CCW);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	ViewManager::ViewOrtho();

	glRectf(-1, -1, 1, 1);

	ViewManager::ViewPerspective();

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Object::DoShadowPass(float vertex[][3], float lightPos[3])
{
	unsigned int k, jj;
	unsigned int p1, p2;
	GLPointf v1, v2;

	//对模型中的每一个面
	for (unsigned int i = 0; i < m_meshModel.vecFace.size(); i++)
	{
		//如果面在灯光的前面
		if ( m_meshModel.vecFace[i].lighted )
		{
			//对于被灯光照射的面的每一个相邻的面
			for (unsigned int j = 0; j < 3; j++)
			{
				k = m_meshModel.vecFace[i].neighbourFace[j];

				//如果面不存在，或不被灯光照射，那么这个边是边界
				if ((!k) || (!m_meshModel.vecFace[k - 1].lighted))
				{
					// 获得面的两个顶点
					p1 = m_meshModel.vecFace[i].faceIndices[j];
					jj = (j + 1) % 3;
					p2 = m_meshModel.vecFace[i].faceIndices[jj];

					//计算边的顶点到灯光的方向，并放大shadowDepth倍//方向没有单位化
					v1.x = (vertex[p1][0] - lightPos[0]) * shadowDepth;
					v1.y = (vertex[p1][1] - lightPos[1]) * shadowDepth;
					v1.z = (vertex[p1][2] - lightPos[2]) * shadowDepth;

					v2.x = (vertex[p2][0] - lightPos[0]) * shadowDepth;
					v2.y = (vertex[p2][1] - lightPos[1]) * shadowDepth;
					v2.z = (vertex[p2][2] - lightPos[2]) * shadowDepth;

					//绘制构成阴影体边界的面
					//glBegin(GL_TRIANGLES); //这样的方式画出来是毛刺形状的！
					glPushMatrix();
					glTranslatef(m_x, m_y, m_z);

					glBegin(GL_TRIANGLE_STRIP);
						glVertex3f(vertex[p1][0], vertex[p1][1], vertex[p1][2]);
						glVertex3f(vertex[p1][0] + v1.x, vertex[p1][1] + v1.y, vertex[p1][2] + v1.z);
						glVertex3f(vertex[p2][0], vertex[p2][1], vertex[p2][2]);
						glVertex3f(vertex[p2][0] + v2.x, vertex[p2][1] + v2.y, vertex[p2][2] + v2.z);
					glEnd();

					glPopMatrix();
				}
			}
		}
	}
}

void Object::SetLightedFaces(float lightPos[3])
{
	// 设置哪些面在灯光的前面
	for (unsigned int i = 0; i < m_meshModel.vecFace.size(); i++)
	{
		GLfloat side = m_meshModel.vecFace[i].planeEq.a*lightPos[0] +
			m_meshModel.vecFace[i].planeEq.b*lightPos[1] +
			m_meshModel.vecFace[i].planeEq.c*lightPos[2] +
			m_meshModel.vecFace[i].planeEq.d;

		if (side > 0)
			m_meshModel.vecFace[i].lighted = true;
		else
			m_meshModel.vecFace[i].lighted = false;

	}
}