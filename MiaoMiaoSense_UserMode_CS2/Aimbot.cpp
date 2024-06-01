#include "Features.hpp"
#include <iostream>
#include <windows.h>

static Vector3 oldAngle;
static Vector3 newAngle;
float m_pitch = 0.022;
float m_yaw = 0.022;
void Features::RCS()
{
	//while (true) { // setting.RCSenable
		Sleep(5);
		if (GameRead::GetAimPunchCache().count <= 0 && GameRead::GetAimPunchCache().count > 0xFFFF)
			return;
		const auto shotsFired = GameRead::GetShotFire();
		if (shotsFired > 1)
		{
			Vector3 aimPunch = GameRead::GetAimPunchAngle();
			if (aimPunch.IsZero())
				return;
			auto sensPointer = GameRead::GetSensPointer();
			auto sensitivity = GameRead::GetSensitivity();
			newAngle.x = (aimPunch.y - oldAngle.y) * 2.f / (m_pitch * sensitivity) / 1;
			newAngle.y = -(aimPunch.x - oldAngle.x) * 2.f / (m_yaw * sensitivity) / 1;
			clampAngles(newAngle);

			if (GetAsyncKeyState(VK_LBUTTON))
				mouse_event(MOUSEEVENTF_MOVE, (int)newAngle.x, (int)newAngle.y, 0, 0);
			//std::cout << "test";

			oldAngle = aimPunch;
		}
		else
		{
			oldAngle.x = oldAngle.y = oldAngle.z = 0.f;
		}
	//}
}
/*
void Features::RCS() {
	//C_UTL_VECTOR AimPunchAngle = GameRead::GetAimPunchCache();
	Vector3 ViewAngle = GameRead::GetViewAngle();

	static Vector3 oldPunch;
	Vector3 aimPunchAngle = GameRead::GetAimPunchAngle();//<Vector3>(localPlayer.aimPunchCache.data + (localPlayer.aimPunchCache.count - 1) * sizeof(Vector3));
	uint64_t Fired =  GameRead::GetShotFire();
	if (Fired > 1) {

		Vector3 recoilVector = {
			ViewAngle.x + oldPunch.x - aimPunchAngle.x * 2.f,
			ViewAngle.y + oldPunch.y - aimPunchAngle.y * 2.f
		};
		recoilVector = clampAngles(recoilVector);

		GameWrite::SetViewAngle(recoilVector);
		std::cout << "rcs";
	}
	oldPunch.x = aimPunchAngle.x * 2.f;
	oldPunch.y = aimPunchAngle.y * 2.f;
}*/