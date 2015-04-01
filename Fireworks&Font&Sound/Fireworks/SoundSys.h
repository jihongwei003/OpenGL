#pragma once

#include "fmod_errors.h"
#include "fmod.hpp"

#include <windows.h> 

#pragma comment(lib, "fmodex_vc.lib") //把音频库加入到链接器

#include <map>

class SoundSys
{
public:
	SoundSys();

	bool CheckVersion(unsigned int version); //是否为当前支持的版本

	void CreatSys(unsigned int channelMax); //指定容纳的虚拟声音的个数

	void LoadSound(char *fileName); //所有的这类方法都应该返回bool型！

	bool PlayMusic(char *fileName); //播放背景音乐，对应的有暂停功能；播放3D音效，对应的有3D属性设置功能，更新功能
	bool PlaySoundEffect(char *fileName); //播放短暂的音效，没有暂停功能，没有3D音效

	bool SetPause(char *fileName, bool pause);
	bool Stop(char *fileName);

	void Use3DSound(bool used3D);

	bool SetSrcAttributes(char* fileName, FMOD_VECTOR srcPos, FMOD_VECTOR srcVel); //设定声源的位置和速度(channel)
	bool SetEarAttributes(FMOD_VECTOR earPos, FMOD_VECTOR earVel, FMOD_VECTOR earForward, FMOD_VECTOR earUp); //设定听者位置、速度、向前方向、向上方向(system)
	void Update3DEffect();

	void ExitSys();
	//~SoundSys();

private:
	//SoundSys(const SoundSys& other){}
	//SoundSys& operator=(const SoundSys& other){}

	void ErrCheck(FMOD_RESULT result);

	FMOD_RESULT result;
	FMOD::System * system;

	bool m_use3DSound;

	/* 一个sound可以播放多次，每次播放都会得到新的channel句柄；一个channel只能播放一次 *//////////每次播放？？？//////////////////////
	std::map<char*, FMOD::Sound*> m_soundsMap;
	std::map<char*, FMOD::Sound*>::iterator m_soundIter;

	std::map<FMOD::Sound*, FMOD::Channel*> m_channelMap;
	std::map<FMOD::Sound*, FMOD::Channel*>::iterator m_channelIter;
};

inline
void SoundSys::Use3DSound(bool used3D)
{
	m_use3DSound = used3D;
}