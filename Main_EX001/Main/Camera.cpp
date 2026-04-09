#include "StdAfx.h"

float *Camera_Zoom = (float*)0x626681;
float *Camera_RotY = (float*)0x6A9798;
float *Camera_RotZ = (float*)0x7D171A0;
float *Camera_PosZ = (float*)0x6A7770;
float *Camera_ClipX = (float*)0x6A967C;
float *Camera_ClipY = (float*)0x5E9D4E;
float *Camera_GlClip = (float*)0x62696E;
float *Camera_ClipAUX1 = (float*)0x6A9684;
float *Camera_ClipAUX2 = (float*)0x6A9690;
float *Camera_ClipAUX3 = (float*)0x6A8FBC;
float *Camera_ClipXCS = (float*)0x6A968C;
float *Camera_ClipYCS = (float*)0x5E9CFE;

void Reset()
{
	*Camera_RotY = 48.5;
	*Camera_RotZ = -45;
	*Camera_PosZ = 150;
	*Camera_ClipX = 1190;
	*Camera_ClipY = 2400;
	*Camera_ClipXCS = 2000;
	*Camera_ClipYCS = 3300;
	*Camera_GlClip = 2000;
	*Camera_Zoom = 35;
	*Camera_ClipAUX1 = 456;
	*Camera_ClipAUX2 = 1500;
	*Camera_ClipAUX3 = 540;
}

LRESULT CALLBACK MouseProc(int Code, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCTEX* mhs = (MOUSEHOOKSTRUCTEX*)lParam;

	HWND MuWnd = FindWindow("MU", NULL);

	if (Active[1])
	{
		if (GetForegroundWindow() == MuWnd)
		{
			if (wParam == WM_MOUSEWHEEL)
			{
				int direction = mhs->mouseData;

				if (direction > 0)
				{
					if (*Camera_Zoom < 58)
					{
						*Camera_Zoom += 1;
					}

					if (*Camera_Zoom > 58)
					{
						*Camera_Zoom = 58;
					}
				}
				else if (direction < 0)
				{
					if (*Camera_Zoom > 12)
					{
						*Camera_Zoom -= 1;
					}

					if (*Camera_Zoom < 12)
					{
						*Camera_Zoom = 12;
					}
				}

				*Camera_ClipX = 1190 + (abs(*Camera_PosZ - 150) * 3) + 4000;
				*Camera_ClipY = 2400 + (abs(*Camera_PosZ - 150) * 3) + 4000;
				*Camera_ClipXCS = 3000 + (abs(*Camera_PosZ - 150) * 3) + 4000;
				*Camera_ClipYCS = 4300 + (abs(*Camera_PosZ - 150) * 3) + 4000;
				*Camera_GlClip = 4000 + (abs(*Camera_PosZ - 150) * 3) + 1500;
				*Camera_ClipAUX1 = -2000 + (abs(*Camera_PosZ - 150) * 3) - 3000;
				*Camera_ClipAUX2 = 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
				*Camera_ClipAUX3 = 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
			}
			else if (wParam == WM_MBUTTONDOWN)
			{
				MoveCamera = true;
			}
			else if (wParam == WM_MBUTTONUP)
			{
				MoveCamera = false;
			}
			else if (wParam == WM_MOUSEMOVE)
			{
				if (MoveCamera)
				{
					if (MouseX < mhs->pt.x)
					{
						*Camera_RotZ += 8;

						if (*Camera_RotZ > 315)
						{
							*Camera_RotZ = -45;
						}
					}
					else if (MouseX > mhs->pt.x)
					{
						*Camera_RotZ -= 8;

						if (*Camera_RotZ < -405)
						{
							*Camera_RotZ = -45;
						}
					}
					if (MouseY < mhs->pt.y)
					{
						if (*Camera_RotY > -90)
						{
							*Camera_PosZ += 20;
							*Camera_RotY += abs((*Camera_PosZ + 330) / 640);
						}
					}
					else if (MouseY > mhs->pt.y)
					{
						if (*Camera_RotY > 25)
						{
							*Camera_PosZ -= 20;
							*Camera_RotY -= abs((*Camera_PosZ + 330) / 600);
						}
					}

					MouseX = mhs->pt.x;
					MouseY = mhs->pt.y;

					*Camera_ClipX = 1190 + (abs(*Camera_PosZ - 150) * 3) + 4000;
					*Camera_ClipY = 2400 + (abs(*Camera_PosZ - 150) * 3) + 4000;
					*Camera_ClipXCS = 3000 + (abs(*Camera_PosZ - 150) * 3) + 4000;
					*Camera_ClipYCS = 4300 + (abs(*Camera_PosZ - 150) * 3) + 4000;
					*Camera_GlClip = 4000 + (abs(*Camera_PosZ - 150) * 3) + 1500;
					*Camera_ClipAUX1 = -2000 + (abs(*Camera_PosZ - 150) * 3) - 3000;
					*Camera_ClipAUX2 = 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
					*Camera_ClipAUX3 = 2000 + (abs(*Camera_PosZ - 150) * 3) + 3000;
				}
			}
		}
	}

	return CallNextHookEx(m_Mouse, Code, wParam, lParam);
}