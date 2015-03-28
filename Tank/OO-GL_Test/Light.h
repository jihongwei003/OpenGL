/* 
* 缺少聚光灯等效果！！！ 
* 缺少设置光源的光照材质！！！
*/
#pragma once

class Light
{
public:
	Light(void);
	/* （几号光源，位置，多次反射后强度，漫反射强度，镜面反射强度） */
	Light(unsigned short id, float positionL[], float ambientL[], float diffuseL[], float specularL[]);

	void SetLightPos(float positionL[]);

	void TurnOn();
	void TurnOff();

	static void TurnOnColorTrack(); //开启光照会忽略颜色，开启颜色追踪可以显示颜色

	~Light(void);

protected:
	unsigned short m_id;

	float m_positionL[4];
	float m_ambientL[4];
	float m_diffuseL[4];
	float m_specularL[4];
};

