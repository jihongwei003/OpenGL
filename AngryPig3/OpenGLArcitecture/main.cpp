#include <glut.h>

#include "world\World.h"
#include "world\Camera.h"
#include "world\Light.h"

#include "MouseController.h"
#include "MapFunction.h"
#include "LinearMap.h"

#include <iostream>
using namespace std;

#include "GameWorld.h"

#include "Random.h"

GameWorld *pWorld;
Camera cam;

//void Timer(int value);
void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}

void RenderScene(void){
	pWorld->onDisplay();
}				

void ChangeSize(int w, int h){
	pWorld->onChangeSize(w, h);
}

/*处理鼠标事件*/
/*参数为:当前鼠标相对于窗口左上角的位置*/
void mouseOperation(int x, int y){
	MouseController mouse(pWorld->getRenderWindowHandle());

	const int EDGE = 30;
	const int limitLeft = EDGE;//鼠标移动范围的左界
	const int limitRight = pWorld->getWidth() - EDGE;//鼠标移动范围的右界

	mouse.limitMouseMovingDomainRL(limitLeft, limitRight);

	/*【鼠标位置从窗口底端（坐标： pWorld->getHeight()）到窗口顶端（坐标：0）】映射到
	*【相对于z轴的视角（即仰角）从-90度到90度】*/
	LinearMap<float> mapAngleZ(pWorld->getHeight(), 0, -90, 90);
	//LinearMap<float> mapAngleZ(pWorld->getHeight(), 0, -30, 75);

	/*【鼠标位置从左界到右界】映射到【相对于y轴的视角从180度到-180度】*/
	LinearMap<float> mapAngleY(limitLeft, limitRight, 180, -180);
	//LinearMap<float> mapAngleY(limitLeft, limitRight, 60, -60);

	LinearMap<float> m(0, 600, -90, 90);
	float f = m.map(400);

	float viewAngleZ = mapAngleZ.map(y);
	float viewAngleY = mapAngleY.map(x);

	//cam.setCenterPos(5, 5, 2);
	//cam.setViewAngleWithCenterFixed(2, viewAngleY, viewAngleZ);
	cam.setEyePos(-2, 2, 0);
	cam.setViewAngleWithEyeFixed(viewAngleY, viewAngleZ);

	pWorld->setCannonAngle(viewAngleY, viewAngleZ);
	//pWorld->setCannonAngle(0, 0);
}

void DealMouseMove(int x,int y){
	mouseOperation(x,y);
}

void DealMouseDrag(int x, int y){
	mouseOperation(x, y);
}

void DealMouseButtonAction(int button, int state, int x, int y)
{
	if(GLUT_LEFT_BUTTON == button)
	{	
		if(GLUT_DOWN == state)
		{
			/*按下鼠标左键*/
			pWorld->onClick();
		}
		else
		{
			/*松开鼠标左键*/
			pWorld->onRelease();
		}
	}
}

int main(int argc, char* argv[]){
	
	/*创建世界*/
	pWorld = new GameWorld(argc, argv, "AngryPig", 640, 480, 20, &cam);

	/*应用光照*/
	float  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	Light light0(0);
	light0.setAmbient(ambientLight);
	light0.setDiffuse(diffuseLight);
	light0.turnOn();

	/*创建摄像机*/
	cam.setCenterPos(0, 0, 0);
	cam.setViewAngleWithCenterFixed(10, 0, 0);

	SetCursorPos(pWorld->getWidth() / 2, pWorld->getHeight() / 2);//鼠标指针移至中心

	/*注册回调函数*/
	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);

	glutMotionFunc(DealMouseMove); //设置移动回调函数

	glutPassiveMotionFunc(DealMouseDrag); //设置当前窗口的被动移动回调函数

	glutMouseFunc(DealMouseButtonAction); //注册当前窗口的鼠标回调函数

	glutTimerFunc(20, Timer, 0); //注册按一定时间间隔触发的定时器回调函数

	//glutKeyboardFunc(unsigned char key[]);

	/*开启主循环*/
	glutMainLoop();

	return 0;
}