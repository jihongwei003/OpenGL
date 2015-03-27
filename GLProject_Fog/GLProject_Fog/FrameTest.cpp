#include "FrameTest.h"
#include <glut.h>

#include "MouseLimit.h"
#include "LinearMap.h"

#include <iostream>///////////////////////////////////

FrameTest::FrameTest()
{
}

FrameTest::FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height)
{
	//构造里只创建 光照 摄像机！
	m_light0 = new Light();
	m_camera0 = new Camera();

	//pCube = new TestCube();//不能在这里创建，要么纹理ID分配失败！
}

/*不可删除的物体在Init()里创建！
* 一次性物体（子弹）在Display()里用ObjectList类创建！ */
void FrameTest::Init()
{
	m_init = new GlobalInit();

	/* 添加其他初始状态 */

	float positionL[] = { 0, 400, 0, 1 };
	m_light0->SetLightPos(positionL);
	m_light0->TurnOnColorTrack();
	//m_light0->TurnOn(); //光照在Display中开启

	//设定游戏按键
	keys = new Keys();

	viewAngleZ = 0;
	viewAngleY = 0;

	viewMode = 1; //主角视角

	//相机的位置设定必须在这里！
	m_camera0->SetEyePos(2, 1, 0);
	m_camera0->SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //鼠标指针移至中心

	//雾的创建和启用
	m_fog = new Fog();
	m_fog->Apply();

	//带纹理的东西必须在这里创建，不能在构造里面创建，要么纹理ID分配会失败！
	m_axis = new Axis();

	pSkyBox = new SkyBox();

	pTankChassis = new TankChassis();
	pTankChassis->SetPos(2, 1, 0); //底盘位置

	pTankTurret = new TankTurret();

	
	pTankBarrel = new TankBarrel();
	//pTankBarrel->SetPos(4.4, 2.5, 0);////////////////////////////////////////////////////////////

}

void FrameTest::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/* 灯光 */
	m_light0->TurnOn();


	/* 摄像机 */
	float tankChassisPosX = 0, tankChassisPosY = 0, tankChassisPosZ = 0;
	pTankChassis->GetPos(&tankChassisPosX, &tankChassisPosY, &tankChassisPosZ);

	float viewDistance = 10; //镜头与物体之间的距离；上帝视角：拉远镜头
	if (viewMode) //第一人称
	{
		//m_camera0->SetEyePos(0, 0.6, 0);
		m_camera0->SetEyePos(tankChassisPosX - 4, tankChassisPosY + 1.5, tankChassisPosZ);
		m_camera0->SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //上帝视角
	{
		//m_camera0->SetTargetPos(0, 0, 0);
		m_camera0->SetTargetPos(tankChassisPosX, tankChassisPosY, tankChassisPosZ);
		m_camera0->SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}
	m_camera0->UpdatePerspective(75, 1.3); //必须放在这才能启动摄像机！
	m_camera0->Apply();


	/* 物体渲染 */
	/* 先绘制【不透明物体】！ */
	//这五个属性如果不为(false, true, TEXTURE, GL_CCW, GL_TRIANGLES)才需要指定！
	m_axis->SetRenderMode(false, false, COLOR, GL_CCW, GL_LINES);
	m_axis->Render();


	//坦克底盘
	pTankChassis->SetRenderMode();
	pTankChassis->Render();
	
	//坦克炮塔
	pTankTurret->SetPos(tankChassisPosX, tankChassisPosY + 1.5, tankChassisPosZ); 
	//pTankTurret->SetRot(0, viewAngleY, viewAngleZ / 2);
	pTankTurret->SetRot(0, -30, 15);
	pTankTurret->SetRenderMode();
	pTankTurret->Render();
	
	//坦克炮筒
	pTankBarrel->SetPos(tankChassisPosX + 3, tankChassisPosY + 1.5, tankChassisPosZ); 
	//pTankBarrel->SetRot(0, viewAngleY, viewAngleZ);
	pTankBarrel->SetRot(0, -30, 30); //rotY就是向左转30度
	pTankBarrel->SetRenderMode();
	pTankBarrel->Render();

	//glEnable(GL_TEXTURE_2D);
	//天空盒
	pSkyBox->SetRenderMode(false, true, TEXTURE, GL_CCW);
	pSkyBox->Render();
	pSkyBox->SetPos(0, 250, 0);


	glFlush();
	glutSwapBuffers();
}

void FrameTest::MouseMotion(int x, int y)
{
	MouseLimit *pMouse = new MouseLimit();
	//MouseLimit mouse(m_WindowP->GetWindowHandle());//好像不是这个窗口了？

	//鼠标移动左右范围
	const int EDGE = 30;
	const int limitLeft = EDGE;
	const int limitRight = m_WindowP->GetWidth() - EDGE;

	pMouse->MouseMovLimitRL(limitLeft, limitRight);

	//从窗口中鼠标的位置映射到离窗口中心的角度rotY(左右)、rotZ(上下)
	pMouse->PosIntoAngleY(limitLeft, limitRight, 180, -180);
	pMouse->PosIntoAngleZ(m_WindowP->GetHeight(), 0, -90, 90);
	//pMouse->PosIntoAngleZ(m_WindowP->GetHeight(), 0, -20, 60);/////////////////////////

	viewAngleY = pMouse->GetMapAngleY(x);
	viewAngleZ = pMouse->GetMapAngleZ(y);
}

void FrameTest::MousePassiveMotion(int x, int y)
{
	MouseMotion(x, y);
}

void FrameTest::MouseButton(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
		{
			/*按下鼠标左键*/
			std::cout << "按下鼠标左键" << std::endl;	
		}
		else
		{
			/*松开鼠标左键*/
			std::cout << "松开鼠标左键" << std::endl;
		}
	}
	if (GLUT_RIGHT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
		{
			/*按下鼠标左键*/
			std::cout << "按下鼠标右键" << std::endl;
		}
		else
		{
			/*松开鼠标左键*/
			std::cout << "松开鼠标右键" << std::endl;
		}
	}
}

void FrameTest::KeyboardSet(unsigned char key, int x, int y)//设定函数
{
	keys->SetPressed(key);
	if (key == ' ') //放在这里切换视角才不会被一直检测！
		viewMode = !viewMode;
}

void FrameTest::KeyboardUpSet(unsigned char key, int x, int y)
{
	keys->SetReleased(key);
}

void FrameTest::KeyboardRespond()//在Timer里调用响应函数
{
	if (keys->IsPressed('w'))
	{
		std::cout << "W按下" << std::endl;
	}

	if (keys->IsPressed('s'))
	{
		std::cout << "S按下" << std::endl;
	}

	if (keys->IsPressed('a'))
	{
		std::cout << "A按下" << std::endl;
	}

	if (keys->IsPressed('d'))
	{
		std::cout << "D按下" << std::endl;
	}

}

void FrameTest::SpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		std::cout << "F1全屏模式。" << std::endl;
		//Reshape(1024, 768);
	}
	if (key == GLUT_KEY_F2)
	{
		exit(0);
	}
}
