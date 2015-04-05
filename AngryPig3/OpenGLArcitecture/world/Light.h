#pragma once

/*光照
*固定功能管线阶段最多可以使用8个*/
class Light
{
public:
	Light(void);

	/*光照序号，必须介于（含）0-7之间*/
	Light(unsigned short id);

	/*打开这个光源*/
	void turnOn();

	/*关闭这个光源*/
	void turnOff();

	/*设定环境光*/
	void setAmbient(float *src);

	/*设定散射光*/
	void setDiffuse(float *src);

	/*打开光照。使用光照前先调用
	*包括：光照、颜色追踪*/
	static void Enable();

	~Light(void);

protected:
	unsigned short m_id;

	float m_ambient[4];
	float m_diffuse[4];
};

