#include "FrameTest.h"
#include <glut.h>
#include <iostream>

#include "MouseLimit.h"
#include "LinearMap.h"


FrameTest::FrameTest()
{
}

FrameTest::FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height)
{
	//构造里只创建 光照 摄像机！
	m_camera0 = new Camera();

}

/*不可删除的物体在Init()里创建！
* 一次性物体（子弹）在Display()里用ObjectList类创建！ */
void FrameTest::Init()
{
	m_init = new GlobalInit();

	viewAngleZ = 0;
	viewAngleY = 0;

	//viewMode = 1; //主角视角
	viewMode = 0; //上帝视角

	//相机的位置设定必须在这里！
	m_camera0->SetEyePos(2, 1, 0);
	m_camera0->SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //鼠标指针移至中心

}

void FrameTest::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 摄像机 */
	float viewDistance = 2.0f; //镜头与物体之间的距离；上帝视角：拉远镜头

	if (viewMode) //第一人称
	{
		m_camera0->SetEyePos(0, 0, 0);
		m_camera0->SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //上帝视角
	{
		m_camera0->SetTargetPos(0, 0, 0);
		m_camera0->SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}

	m_camera0->UpdatePerspective(75, 1.3); //必须放在这才能启动摄像机！
	m_camera0->Apply();


	/* 物体渲染 */
	glTranslatef(0.5f, 0, 0); // 平移
	glutWireCube(0.5);

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