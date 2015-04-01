#include "Particles.h"

Particles::Particles()
{
	m_active = true;
	m_life = 1.0f;
	m_fade = 0.0f;

	m_size = 1;

	m_r = 0.0f;
	m_g = 0.0f;
	m_b = 0.0f;

	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;

	m_speedX = 0.0f;
	m_speedY = 0.0f;
	m_speedZ = 0.0f;

	m_accelX = 0.0f;
	m_accelY = 0.0f;
	m_accelZ = 0.0f;
}

Particles::Particles(
	float size,
	float life,
	float r, float g, float b,
	float x, float y, float z,
	float speedX, float speedY, float speedZ,
	float accelX, float accelY, float accelZ)
{
	m_active = true;
	m_fade = 0.0f;

	m_size = size;

	m_life = life;

	m_r = r;
	m_g = g;
	m_b = b;

	m_posX = x;
	m_posY = y;
	m_posZ = z;

	m_speedX = speedX;
	m_speedY = speedY;
	m_speedZ = speedZ;

	m_accelX = accelX;
	m_accelY = accelY;
	m_accelZ = accelZ;
}
