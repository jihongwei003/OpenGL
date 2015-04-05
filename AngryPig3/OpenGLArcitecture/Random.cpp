#include "Random.h"
#include <stdlib.h>
#include <time.h>

float Random::GenFloat(float low, float high)
{
	float s_low = low;
	float s_high = high;
	float temp;
	temp=(float)((rand()%(int)(100*(s_high-s_low))+100*s_low))/100.0f;
	return temp;
}

void Random::Randomize()
{
	srand((unsigned)time(NULL));
}