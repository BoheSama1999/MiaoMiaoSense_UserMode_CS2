#include <iostream>

#include "Features.hpp"

void Features::bunny_hop() {
	//while (true) {
		const auto local_player_pawn = GameRead::GetLocalPawnAddr();

		if (local_player_pawn == 0) return;

		const auto flags = GameRead::Getfflag();

		const bool in_air = flags & (1 << 0);
		const bool space_pressed = GetAsyncKeyState(VK_SPACE);
		const auto force_jump = GameRead::bottens::GetJumpState();

		if (space_pressed && in_air) {
			Sleep(50);
			GameWrite::bottens::SetJumpState(65537);
		}
		else if (space_pressed && !in_air) {
			GameWrite::bottens::SetJumpState(256);

			#ifdef _DEBUG
			//std::cout << "jump" << std::endl;
			#endif // _DEBUG

		}
		else if (!space_pressed && force_jump == 65537) {
			GameWrite::bottens::SetJumpState(256);
			#ifdef _DEBUG
			//std::cout << "jump" << std::endl;
			#endif // _DEBUG
		}
	//}
}