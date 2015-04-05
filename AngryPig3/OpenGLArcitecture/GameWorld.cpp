#include "GameWorld.h"
#include <vector>
#include <glut.h>
#include "model/BulletData.h"

#include "Random.h"
#include <iostream>///////////////////////////////////////////////////////

GameWorld::GameWorld(void)
{
}

GameWorld::GameWorld(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera)
	: World(argc, argv, title, width, height, frameTimeMs, pCamera),
	ground(-15, 21, 60, -21, -0.1f, 0.4f, 0.4f, 0.17f)
{
	timeSinceLastShot = FIRE_INTERVAL;
	shooting = false;

	glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

	p0.x = 1;
	p0.z = -2;
	p0.rotY = -30;
	p0.rotZ = 20;
	p1.x = 2;
	p1.z = 1;
	p1.rotY = 60;
	p1.rotZ = -10;

	for(int i = 0; i < (int)5; i ++)
	{
		aBows[i].x = 60;
		aBows[i].z = i*10-20;
	}



	/*for(int i = -20; i < 20; i+=2){
	for(int j = 35; j < 75; j+=2){
	createBird(60, 5, i, 180, j, 0.3f);
	}
	}*/
	//createBird(60, 5, 20, 180, 70, 0.3f);
}

void GameWorld::onDisplay()
{
	/*游戏逻辑*/
	static unsigned timeSinceLastBirdCreated = 0;

	/*创建小鸟*/
	if(20 == timeSinceLastBirdCreated)
	{
		float genBirdX,genBirdY,genBirdZ; //生成小鸟的随机位置
		float genHoriAng,genElevAng;//发射小鸟的初始角度

		genBirdX = 56;
		genBirdZ = Random::GenFloat(-20.0,20.0);
		genBirdY = 2;

		genHoriAng = 180 + Random::GenFloat(-10.0,10.0);
		genElevAng	= Random::GenFloat(40.0,50.0);

		createBird(genBirdX,genBirdY,genBirdZ,genHoriAng,genElevAng,0.3f);
		timeSinceLastBirdCreated = 0;
	}
	else
	{
		timeSinceLastBirdCreated++;
	}

	/*处理子弹发射*/
	if(timeSinceLastShot < FIRE_INTERVAL)
		timeSinceLastShot++;

	if(shooting)
	{
		if(FIRE_INTERVAL == timeSinceLastShot)
		{
			timeSinceLastShot = 0;
			shoot();
		}
	}

	std::list<Bird*>::iterator iterBird;  
	std::list<Bullet*>::iterator iterBullet;

	/*小鸟碰地*/
	for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
	{
		if(sphereHitsPlaneY(0, (*iterBird)->y, (*iterBird)->getRadius()))
		{
			(*iterBird)->killed();
		}
	}

	/*小鸟碰城堡*/
	for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
	{
		if(sphereHitsPlaneX(-7, (*iterBird)->x, (*iterBird)->getRadius()))
		{
			(*iterBird)->killed();

			if(-12 < (*iterBird)->z && (*iterBird)->z < 12 && (*iterBird)->y < 8)
			{
				castleHit();
			}
		}
	}

	/*对任意两个子弹和小鸟做碰撞检测*/
	for(iterBullet = m_listPBullet.begin(); iterBullet != m_listPBullet.end(); iterBullet++)
	{
		for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
		{
			if(bulletHitsBird(*iterBullet, *iterBird))
			{
				(*iterBullet)->hitTarget();
				(*iterBird)->killed();
			}
		}
	}


	/*渲染场景*/
	ClearScreen();
	/*绘制不透明物体*/
	Mesh::SetRenderMode(false, true, Mesh::COLOR);
	barrel.render();
	base.render();
	mountain.render();
	castle.render();
	p0.render();
	p1.render();
	for(unsigned i = 0; i < 5; i++)
	{
		aBows[i].render();
	}

	ground.render();

	//遍历m_listPBird并绘制所有小鸟
	iterBird = m_listPBird.begin();
	while(iterBird != m_listPBird.end()){
		bool removable = (*iterBird)->render();
		if(removable)
		{
			//delete (*iterBird);
			iterBird = m_listPBird.erase(iterBird);
		}
		if(iterBird != m_listPBird.end())
		{
			iterBird++;
		}
	}

	/*绘制透明物体*/
	Mesh::SetRenderMode(false, false, Mesh::COLOR);
	axis.render();

	Mesh::SetRenderMode(false, true, Mesh::COLOR);
	//遍历m_listPBullet并绘制所有子弹
	iterBullet = m_listPBullet.begin();
	while(iterBullet != m_listPBullet.end()){
		bool removable = (*iterBullet)->render();

		if(removable)
		{
			//delete (*iterBullet);
			iterBullet = m_listPBullet.erase(iterBullet);
		}
		if(iterBullet != m_listPBullet.end())
		{
			iterBullet++;
		}
	}

	m_pCurCam->apply();

	RenderFinish();
}

/*设置炮筒的指向*/
void GameWorld::setCannonAngle(float angY, float angZ)
{
	barrel.rotY = angY;
	barrel.rotZ = angZ;
}

/*按下鼠标*/
void GameWorld::onClick()
{
	shooting = true;
}

/*松开鼠标*/
void GameWorld::onRelease()
{
	shooting = false;
}

void GameWorld::shoot()
{
	float x, y, z;
	barrel.countLeftFrontCoord(&x, &y, &z);
	createBullet(x, y, z, barrel.rotY, barrel.rotZ, BulletData::VELOCITY);

	barrel.countRightFrontCoord(&x, &y, &z);
	createBullet(x, y, z, barrel.rotY, barrel.rotZ, BulletData::VELOCITY);
}

void GameWorld::createBullet(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	Bullet *pBullet = new Bullet;
	pBullet->setInitStatus(x, y, z, rotY, rotZ, velocity);

	m_listPBullet.push_back(pBullet);
}

void GameWorld::createBird(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	Bird *pBird = new Bird;
	pBird->setInitStatus(x, y, z, rotY, rotZ, velocity);

	m_listPBird.push_back(pBird);
}

/*小鸟和子弹是否碰撞*/
//方法：子弹前中后三点只要有一点碰撞即认定碰撞
bool GameWorld::bulletHitsBird(Bullet *pBullet, Bird *pBird)
{
	float birdX = pBird->x;
	float birdY = pBird->y;
	float birdZ = pBird->z;
	float r = pBird->getRadius();

	float bulletX, bulletY, bulletZ;//被检测点（两端点及中点）的坐标

	pBullet->getFrontCoord(&bulletX, &bulletY, &bulletZ);
	if(countPointDis2(birdX, birdY, birdZ, bulletX, bulletY, bulletZ) < r * r)
		return true;

	if(countPointDis2(birdX, birdY, birdZ, pBullet->x, pBullet->y, pBullet->z) < r * r)
		return true;

	pBullet->getBackCoord(&bulletX, &bulletY, &bulletZ);
	if(countPointDis2(birdX, birdY, birdZ, bulletX, bulletY, bulletZ) < r)
		return true;


	return false;
}

/*计算两点间距离的平方*/
float GameWorld::countPointDis2(float x0, float y0, float z0, float x1, float y1, float z1)
{
	return 
		(x1-x0) * (x1-x0) +
		(y1-y0) * (y1-y0) +
		(z1-z0) * (z1-z0);
}

/*计算球体与指定平面是否相交
*planeX表示x型平面，即垂直于x轴的平面*/
bool GameWorld::sphereHitsPlaneX(float planeX , float sphereX, float r)
{
	bool isIntersect = false;
	if(abs(sphereX - planeX) <= abs(r)){
		isIntersect = true;
	}
	return isIntersect;
}
/*planeY表示y型平面，即垂直于y轴的平面*/
bool GameWorld::sphereHitsPlaneY(float planeY , float sphereY, float r)
{
	bool isIntersect = false;
	if(abs(sphereY - planeY) <= abs(r)){
		isIntersect = true;
	}
	return isIntersect;
}

/*城堡被小鸟击中*/
void GameWorld::castleHit()
{
}

	/*加分*/
void GameWorld::score()
{
}

GameWorld::~GameWorld(void)
{

}
