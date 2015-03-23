#pragma once

/*OpenGL坐标轴方向：
*	x轴：屏幕左下角->右下角
*	y轴：屏幕左下角->左上角
*	z轴：向外
* 物体摆放方向：面向x轴正方向，头顶朝向y轴正方向
*/
class Camera{
public:
	Camera();

	void SetEyePos(float eyeX, float eyeY, float eyeZ);
	void SetTargetPos(float targetX, float targetY, float targetZ);

	/*第三人称环视物体
	* 参数：
	*	1.距离	
	*	2.左右摆角
	*	3.上下仰角*/
	void SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ);

	/*第一人称环视周围
	* 参数：
	*	1.左右摆角
	*	2.上下仰角*/
	void SetViewAngleWithEyeFixed(float rotY, float rotZ);

	/* 应用摄像机 */
	void Apply();

	/* 更新视野参数 */
	void UpdatePerspective(float aspect, float ratioWH);

private:
	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;

	float m_targetX;
	float m_targetY;
	float m_targetZ;

	/*关于视野的属性*/
	float m_aspect;  //视野广度角度
	float m_ratioWH; //宽高比
	float m_near;
	float m_far;
};