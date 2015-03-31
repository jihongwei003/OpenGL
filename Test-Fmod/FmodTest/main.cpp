#include "fmod_errors.h"
#include "fmod.hpp"

#include <stdio.h>  
#include <windows.h> 
//#include <conio.h>

#pragma comment(lib, "fmodex_vc.lib") //把音频库加入到链接器

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

int main()
{
	FMOD_RESULT result;
	FMOD::System * system;

	/* 创建Fmod主系统 */
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/* 初始化Fmod系统init方法 */
	result = system->init(1, FMOD_INIT_NORMAL, 0); //使用了1个虚拟声音
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/* 检测版本号 */   
	unsigned int version;
	result = system->getVersion(&version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x/n", version, FMOD_VERSION);
		return 0;
	}

	/* 设置声音可听见的最小和最远距离 */

	

	/* 加载媒体文件并播放 */  
	FMOD::Sound *sound;

	//stream(用 System::createStream创建)是在运行时解码，仅使用很少的内存作为缓冲，这就是为什么大文件最好用stream的原因
	result = system->createStream("Idina Menzel-Let It Go.mp3", FMOD_3D, 0, &sound); //其他格式：FMOD_NONBLOCKING
	   
	ERRCHECK(result);

	//如果不需要更改这个sound实例，或者这个声音很短(不循环)，就可以省去channel；一个“channel”就是一个声音的实例
	FMOD::Channel *channel; //定义Channel对象   

	//计算媒体文件的长度   
	unsigned int lenms;

	result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);

	printf("Total CD length %02d:%02d/n", lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100);


	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);

	//暂停时设定音量
	result = channel->setVolume(0.5f);
	ERRCHECK(result);

	//声音从这里才开始播放
	result = channel->setPaused(false);
	ERRCHECK(result);

	Sleep(lenms * 60 * 1000);//一定要sleep一下，要不然程序马上返回了，听不到声音，呵呵   
	ERRCHECK(result);

	/* 设置声道的位置及速度 */

	/* 得到当前可得到的2D或3D声道的数目 */

	/* 更新3D的位置速度和方向 */

	/* 响应键盘操作 */

	/* 关闭并释放资源 */

	return 0;
}