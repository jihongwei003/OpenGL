#pragma once
#include "world\World.h"

#include <list>

#include "Axis.h"
#include "GunBarrel.h"
#include "Mountain.h"
#include "Ground.h"
#include "Castle.h"
#include "Pig.h"
#include "Bow.h"
#include "Bird.h"
#include "GunBase.h"
#include "Bullet.h"

class GameWorld : public World
{
public:
	GameWorld(void);

	/*构造并初始化
	*设定视口大小
	*设定帧长度
	*绑定并初始化摄像机*/
	GameWorld(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera);

	virtual void onDisplay() override;

	/*设置炮筒的指向*/
	void setCannonAngle(float angY, float angZ);

	/*按下鼠标*/
	void onClick();
	/*松开鼠标*/
	void onRelease();

	~GameWorld(void);

protected:
	/*炮台开炮*/
	void shoot();

	/*创建1颗子弹*/
	void createBullet(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*创建1只小鸟*/
	void createBird(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*小鸟和子弹是否碰撞*/
	bool bulletHitsBird(Bullet *pBullet, Bird *pBird);

	/*计算两点间距离的平方*/
	float countPointDis2(float x0, float y0, float z0, float x1, float y1, float z1);

	/*计算球体与指定平面是否相交
	*planeX表示x型平面，即垂直于x轴的平面*/
	bool sphereHitsPlaneX(float planeX , float sphereX, float r);
	/*planeY表示y型平面，即垂直于y轴的平面*/
	bool sphereHitsPlaneY(float planeY , float sphereY, float r);

	/*城堡被小鸟击中*/
	void castleHit();

	/*加分*/
	void score();

	std::list<Bullet*> m_listPBullet;
	std::list<Bird*> m_listPBird;

	Axis axis;
	GunBarrel barrel;
	GunBase base;
	Mountain mountain;
	Ground ground;
	Castle castle;
	Pig p0, p1;
	Bow aBows[5];

	bool shooting;
	int timeSinceLastShot;
	static const int FIRE_INTERVAL = 4;
};

