#pragma once

class Camera{
public:
	Camera();

	/*设定眼睛（观察点）位置*/
	void setEyePos(float eyeX, float eyeY, float eyeZ);

	/*设定观察中心（被观察点）位置*/
	void setCenterPos(float centerX, float centerY, float centerZ);

	/*固定中心位置，根据距离和观察角度（角度制）设定眼睛位置
	*参数：
	*1.距离
	*定义射线l为：以观察中心为起点，眼睛向观察中心的方向为方向
	*2.射线l 在xz平面内的投影相对于y轴的转角 （以x轴所指方向为0°）
	*3.射线l 与xz平面的夹角 （射线位于面内时角度为0°，向上看时角度为正）*/
	void setViewAngleWithCenterFixed(float distance, float rotY, float rotZ);

	/*固定眼睛位置，根据观察角度（角度制）设定观察点位置（相当于第一视角）
	*参数：
	*定义射线l为：以眼睛为起点，视线的方向为射线方向
	*1.射线l 在xz平面内的投影相对于y轴的转角 （以x轴所指方向为0°）
	*2.射线l 与xz平面的夹角 （射线位于面内时角度为0°，向上看时角度为正）*/
	void setViewAngleWithEyeFixed(float rotY, float rotZ);

	/*重设宽高比*/
	void setRatioWH(float ratioWH);

	/*从调用者的视角观察场景
	*举例：假设有摄像机cam已经设定好参数，调用cam.apply()就会以cam的视角显示场景*/
	void apply();

protected:
	/*使用属性域更新视野参数*/
	void updatePerspective();

	/*眼睛（观察点）的位置*/
	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;

	/*观察中心（被观察点）的位置*/
	float m_centerX;
	float m_centerY;
	float m_centerZ;

	/*关于视野的属性*/
	float m_aspect;//视野广度角度
	float m_ratioWH;
	float m_near;
	float m_far;
};