#include "SoundSys.h"

#include <stdio.h>  

const int DISTANCEFACTOR = 1; //声音可见范围
const int INTERFACE_UPDATETIME = 50; //更新时的睡眠时间

SoundSys::SoundSys()
{
	m_use3DSound = false;
}

void SoundSys::ErrCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

bool SoundSys::CheckVersion(unsigned int version)
{
	result = system->getVersion(&version);
	ErrCheck(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x/n", version, FMOD_VERSION);
		return false;
	}
	else
	{
		return true;
	}
}

void SoundSys::CreatSys(unsigned int channelMax)
{
	/* 创建Fmod主系统 */
	result = FMOD::System_Create(&system);
	ErrCheck(result);

	/* 如果不适用默认的初始化，则必须在这里调用一系列初始化系统的函数 */

	/* 初始化Fmod系统init方法 */
	result = system->init(channelMax, FMOD_INIT_NORMAL, 0); //使用了1个虚拟声音
	ErrCheck(result);
}

void SoundSys::LoadSound(char *fileName)
{
	FMOD::Sound *sound;

	//stream(用 System::createStream创建)是在运行时解码，仅使用很少的内存作为缓冲，这就是为什么大文件最好用stream的原因
	result = system->createStream(fileName, FMOD_3D, 0, &sound); //暂时默认为3D音效
	ErrCheck(result);

	//计算媒体文件的长度   
	//unsigned int lenms;
	//result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
	//ErrCheck(result);
	//printf("Total CD length %02d:%02d/n", lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100);

	if (true == m_use3DSound)
	{
		sound->set3DMinMaxDistance(2.0f * DISTANCEFACTOR, 10000.0f * DISTANCEFACTOR); //可见声音范围
	}

	m_soundsMap.insert(std::pair<char*, FMOD::Sound*>(fileName, sound));
}

bool SoundSys::PlayMusic(char *fileName)
{
	//根据名字找到sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//如果不需要更改这个sound实例，或者这个声音很短(不循环)，就可以省去channel；一个“channel”就是一个声音的实例
	FMOD::Channel *channel;

	//使用FMOD_CHANNEL_FREE的话系统每回都会自动分配一个未使用的channel播放
	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel); //如果paused设为false的话，刚开始会以全音量播放

	m_channelMap.insert(std::pair<FMOD::Sound*, FMOD::Channel*>(sound, channel));

	//暂停时设定音量
	result = channel->setVolume(0.5f);
	ErrCheck(result);

	//声音从这里才开始播放
	result = channel->setPaused(false);
	ErrCheck(result);

	return true;
}

bool SoundSys::PlaySoundEffect(char *fileName)
{
	//根据名字找到sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//使用FMOD_CHANNEL_FREE的话系统每回都会自动分配一个未使用的channel播放
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, 0); 
}

bool SoundSys::SetPause(char *fileName, bool pause)
{
	//找到sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//找到channel
	FMOD::Channel *channel;
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		channel = m_channelIter->second;
	}
	else
	{
		return false;
	}

	result = channel->setPaused(pause);
	ErrCheck(result);
}

bool SoundSys::Stop(char *fileName)
{
	//根据名字找到sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	SetPause(fileName, true);
	sound->release();

	m_soundsMap.erase(m_soundIter); //删除sound

	//根据sound找到channel
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		m_channelMap.erase(m_channelIter); //删除channel
	}
	else
	{
		return false;
	}

	return true;
}

//前方为正Ｚ轴，左方为正Ｘ，上方为正Ｙ
bool SoundSys::SetSrcAttributes(char *fileName, FMOD_VECTOR srcPos, FMOD_VECTOR srcVel) //channel
{
	//找到sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//找到channel
	FMOD::Channel *channel;
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		channel = m_channelIter->second;
	}
	else
	{
		return false;
	}

	//result = channel->set3DAttributes(&srcPos, &srcVel); 
	result = channel->set3DAttributes(&srcPos, NULL);//如果不需要仿真都卜勒效应，srcVel给NULL即可
	ErrCheck(result);

	return true;
}

bool SoundSys::SetEarAttributes(FMOD_VECTOR earPos, FMOD_VECTOR earVel, FMOD_VECTOR earForward, FMOD_VECTOR earUp) //system
{
	result = system->set3DListenerAttributes(0, &earPos, &earVel, &earForward, &earUp);
	ErrCheck(result);

	return true;
}

void SoundSys::Update3DEffect()
{
	system->update();
	Sleep(INTERFACE_UPDATETIME - 1);
}

void SoundSys::ExitSys()
{
	//自动完成channel和sound的释放，且包含了对System::close的调用
	result = system->release(); 
}