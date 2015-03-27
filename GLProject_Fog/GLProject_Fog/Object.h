/*
* 绘制一个物体，首先要设置渲染模式（如果是下列默认值，则可以省略），然后再进行渲染
* 渲染模式：
*	bool usingIndex      是否使用索引，默认true
*	bool usingLighting   是否使用光照，默认true；可追加设置光照材质
*	ColorMode colorMode  颜色模式，默认TEXTURE //自动绑定纹理贴图
*	GLenum mode          “正面”的环绕方向，GL_CCW（逆时针），GL_CW（顺时针）默认逆时针
*	GLenum paintMode     同glBegin()参数
*/

/*
* OpenGL坐标轴方向：
*	x轴：屏幕左下角->右下角
*	y轴：屏幕左下角->左上角
*	z轴：向外
* 物体摆放方向：面向x轴正方向，头顶朝向y轴正方向
*/

#pragma once

#include "MeshModel.h"

enum ColorMode{ COLOR, TEXTURE };

class Object
{
public:
	Object();

	/* OpenGL是状态机，对于每一个要绘制的物体，都要先设定它的渲染模式 */
	void SetRenderMode(
		bool usingIndex = false, 
		bool usingLighting = true, 
		ColorMode colorMode = TEXTURE, 
		GLenum mode = GL_CCW,
		GLenum paintMode = GL_TRIANGLES);

	void SetPos(float x, float y, float z);
	void SetRot(float rotX, float rotY, float rotZ);

	void GetPos(float *x, float *y, float *z);

	/* 默认移动方式下的绘制：rotX,rotY,rotZ的旋转中心都在物体中心 */
	void Paint(unsigned vertexAmount); //根据设定好的渲染模式，绘制出来经过坐标变换和旋转的模型

	/* 自定义移动方式下的绘制 */
	void PaintModel(unsigned vertexAmount); //绘制出来没有经过坐标变换和旋转的模型

	/* 是否为一次性物体（如子弹） */
	void SetAvailable(bool available);
	bool IsAvailable();

protected:
	/* 物体是否还继续使用（渲染） */
	bool m_available;

	/* 物体中心位置 */
	float m_x;
	float m_y;
	float m_z;

	float m_rotX; //右手握住 X轴 的旋转角度，即侧翻角
	float m_rotY; //右手握住 Y轴 的旋转角度，即转角
	float m_rotZ; //右手握住 Z轴 的旋转角度，即仰角

	/* 渲染状态 */
	bool m_usingIndex;
	bool m_usingLighting;
	ColorMode m_colorMode;
	GLenum m_mode;
	GLenum m_paintMode;

	MeshModel m_meshModel;
};