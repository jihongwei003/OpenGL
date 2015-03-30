#pragma once

#include "Particles.h"
#include <deque>
#include <glut.h>

class Tail
{
public:
	Tail();

	void SetTailLength(int length);
	int GetTailLength();

	void Render();

	std::deque<Particles> m_queTail;

private:
	int m_tailLength ;
};

inline void Tail::SetTailLength(int length)
{
	m_tailLength = length;
}
inline int Tail::GetTailLength()
{
	return m_tailLength;
}