#include "Tail.h"

Tail::Tail()
{
	m_tailLength = 8;
}

void Tail::Render()
{
	if (m_queTail.size() > 0)
	{
		float shellSize = m_queTail[0].GetSize();
		float r = 0.0f, g = 0.0f, b = 0.0f;
		float x = 0.0f, y = 0.0f, z = 0.0f;

		for (int i = 0; i<m_queTail.size(); i++)
		{
			shellSize -= 0.1;
			if (i > m_tailLength)//烟雾能够显示在屏幕上（不透明度大于0）的帧数
			{
				m_queTail.pop_back();
				break;
			}
			else
			{
				m_queTail[i].GetColor(r, g, b);
				m_queTail[i].GetPos(x, y, z);

				glColor4f(r, g, b, m_queTail[i].GetLife());

				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidSphere(shellSize, 3, 2);
				glPopMatrix();
			}
		}
	}
}