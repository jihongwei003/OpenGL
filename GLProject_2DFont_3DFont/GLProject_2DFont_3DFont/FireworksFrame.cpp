#include "FireworksFrame.h"
#include <glut.h>

#include "MouseLimit.h"
#include "LinearMap.h"

#include <iostream>///////////////////////////////////
//#include <list>

#include "Texture.h"

FireworksFrame::FireworksFrame()
{
}

FireworksFrame::FireworksFrame(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height)
{
	//构造里只创建 光照 摄像机！
	//m_light0 = new Light();
	m_camera0 = new Camera();

	//pCube = new TestCube();//不能在这里创建，要么纹理ID分配失败！
}

/*不可删除的物体在Init()里创建！
* 一次性物体（子弹）在Display()里用ObjectList类创建！ */
void FireworksFrame::Init()
{
	m_init = new GlobalInit();

	/* 添加其他初始状态 */

	//设定游戏按键
	keys = new Keys();

	//显示字体
	font.BuildFont();
	
	//font3D.UseTex(true);////////////////////////////////////////////////
	font3D.BuildFont();

	viewAngleZ = 0;
	viewAngleY = 0;

	viewMode = 0; //主角视角

	//相机的位置设定必须在这里！
	m_camera0->SetEyePos(2, 1, 1);
	m_camera0->SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //鼠标指针移至中心

	//带纹理的东西必须在这里创建，不能在构造里面创建，要么纹理ID分配会失败！
	m_axis = new Axis();


	isShoot = false;
	shootTimer = 0;

	t.LoadTexture("stars.bmp");
}

void FireworksFrame::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 摄像机 */

	float viewDistance = 10; //镜头与物体之间的距离；上帝视角：拉远镜头
	if (viewMode) //第一人称
	{
		//m_camera0->SetEyePos(-200, 100, 0); //看烟花
		m_camera0->SetEyePos(-5, 5, 5);
		m_camera0->SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //上帝视角
	{
		m_camera0->SetTargetPos(0, 0, 0);
		m_camera0->SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}
	m_camera0->UpdatePerspective(75, 1.3); //必须放在这才能启动摄像机！
	m_camera0->Apply();

	//显示文字
	char *string = "HAPPY NEW YEAR";
	font.glPrint(4, 5, string);

	string = "FGHIJ";
	font3D.glPrint(3, 0, string);

	/* 物体渲染 */
	/* 先绘制【不透明物体】！ */
	//这五个属性如果不为(false, true, TEXTURE, GL_CCW, GL_TRIANGLES)才需要指定！
	m_axis->SetRenderMode(false, false, COLOR, GL_CCW, GL_LINES);
	m_axis->Render();

	glEnable(GL_TEXTURE_2D);
	t.Apply();

	glBegin(GL_TRIANGLE_STRIP);

	glTexCoord2d(1, 1); glVertex3f(1500, 1500, -1500);
	glTexCoord2d(0, 1); glVertex3f(1500, 1500, 1500);
	glTexCoord2d(1, 0); glVertex3f(-1500, 1500, -1500);
	glTexCoord2d(0, 0); glVertex3f(-1500, 1500, 1500);

	glEnd();


	/* 其他逻辑计算 */
	if (isShoot)
		Shoot();

	m_fireworksListIter = m_fireworksList.begin();
	while (true)
	{
		if (m_fireworksListIter == m_fireworksList.end())
		{
			//如果列表为空，迭代器直接等于list.end();
			//上一次循环中，调用erase()方法，删除迭代器当前指向的元素，有可能导致迭代器增加至list.end()
			//上一次循环中，迭代器++也可能导致迭代器增加至list.end();
			break;
		}

		if (!(*m_fireworksListIter)->m_arrParticles[69].GetActive()) //迭代器解引用
		{
			delete(*m_fireworksListIter);
			m_fireworksListIter = m_fireworksList.erase(m_fireworksListIter);//erase:使作为参数的迭代器失效，返回指向该迭代器下一参数的迭代器
		}

		if (m_fireworksListIter != m_fireworksList.end()) //确保迭代器没有越界！
			m_fireworksListIter++;
	}

	/* 【透明物体】必须在绘制完不透明物体之后才能正确绘制！！ */
	//粒子系统
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D); //测试粒子系统没有使用纹理！

	for (m_fireworksListIter = m_fireworksList.begin(); m_fireworksListIter != m_fireworksList.end(); m_fireworksListIter++)
	{
		if ((*m_fireworksListIter)->m_arrParticles[50].GetActive())
		{
			(*m_fireworksListIter)->Render();
			(*m_fireworksListIter)->Run();
		}
	}
	glEnable(GL_DEPTH_TEST);
	glColor3f(1, 1, 1); //恢复纹理底层颜色！！

	glFlush();
	glutSwapBuffers();
}

void FireworksFrame::MouseMotion(int x, int y)
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

void FireworksFrame::MousePassiveMotion(int x, int y)
{
	MouseMotion(x, y);
}

void FireworksFrame::MouseButton(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
		{
			/*按下鼠标左键*/
			std::cout << "按下鼠标左键" << std::endl;
			isShoot = true;
		}
		else
		{
			/*松开鼠标左键*/
			std::cout << "松开鼠标左键" << std::endl;
			isShoot = false;
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

void FireworksFrame::KeyboardSet(unsigned char key, int x, int y)//设定函数
{
	keys->SetPressed(key);
	if (key == ' ') //放在这里切换视角才不会被一直检测！
		viewMode = !viewMode;
}

void FireworksFrame::KeyboardUpSet(unsigned char key, int x, int y)
{
	keys->SetReleased(key);
}

void FireworksFrame::KeyboardRespond()//在Timer里调用响应函数
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

void FireworksFrame::SpecialKey(int key, int x, int y)
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


/* 内部使用的函数 */
void FireworksFrame::Shoot()
{
	std::cout << "shootTimer:" << shootTimer << std::endl;

	if (0 == shootTimer)
	{
		/*用指针重复创建东西的时候，
		* 每回都要新声明一个指针，
		* 防止指针修改了对象的内容（每创建一个gunBarrel就多加一次速度）
		* 而没办法正常析构（触发了一个断点）！
		*/
		pParticle = new Fireworks();
		pParticle->Init();

		m_fireworksList.push_back(pParticle);

		shootTimer = 3; //想办法让一按下按键立刻发射？
	}
	else
		shootTimer--;
}