#include "BulletData.h"

const float BulletData::LENGTH = 1;//×Óµ¯µÄÂß¼­°ë³¤

const unsigned BulletData::MAX_TIME = 60;	/////////////////////////////////////////////////////

const float BulletData::VELOCITY = 1.2;

float BulletData::vertex[6] = {-BulletData::LENGTH*5, 0.0f, 0.0f, BulletData::LENGTH, 0.0f, 0.0f};

float BulletData::color[8] = {
	1.0f, 0.5f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.5f, 1.0f
};