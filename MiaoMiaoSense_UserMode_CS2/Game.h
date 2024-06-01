#include <cstdint>
// offsets
#include "buttons.hpp"
#include "client.dll.hpp"
#include "offsets.hpp"

#include "Vector.hpp"
#include "MemCat.hpp"
#include "MiaoMiaoSense.hpp"

// for AimPunchCache
struct C_UTL_VECTOR
{
	DWORD_PTR count = 0;
	DWORD_PTR data = 0;
};

namespace GameRead {
		inline uintptr_t GetLocalPawnAddr() {
			return driver::read_memory<std::uintptr_t>(driverhandle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		}

		inline uint32_t Getfflag() {
			return driver::read_memory<std::uint32_t>(driverhandle, GetLocalPawnAddr() + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);
		}

		inline int32_t GetShotFire() {
			return driver::read_memory<std::int32_t>(driverhandle, GetLocalPawnAddr() + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired);
		}

		inline Vector3 GetViewAngle() {
			return driver::read_memory<Vector3>(driverhandle, client + cs2_dumper::offsets::client_dll::dwViewAngles);
		}

		inline uintptr_t GetSensPointer() {
			return driver::read_memory<uintptr_t>(driverhandle, client + cs2_dumper::offsets::client_dll::dwSensitivity);
		}
		
		inline float GetSensitivity() {
			return driver::read_memory<float>(driverhandle, GetSensPointer() + cs2_dumper::offsets::client_dll::dwSensitivity_sensitivity);
		}

		inline C_UTL_VECTOR GetAimPunchCache() {
			return driver::read_memory<C_UTL_VECTOR>(driverhandle, GetLocalPawnAddr() + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchCache);
		}

		inline Vector3 GetAimPunchAngle() {
			//return driver::read_memory<Vector3>(driverhandle, GetLocalPawnAddr() + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchAngle);
			return driver::read_memory<Vector3>(driverhandle, GetAimPunchCache().data + (GetAimPunchCache().count - 1) * sizeof(Vector3));
		}

		class bottens {
		public:
			static DWORD GetJumpState() {
				return driver::read_memory<DWORD>(driverhandle, client + cs2_dumper::buttons::jump);
			}
		};
}

namespace GameWrite {
	inline void SetViewAngle(Vector3 View) {
		driver::write_memory<Vector3>(driverhandle, cs2_dumper::offsets::client_dll::dwViewAngles, View);
	}
	class bottens {
	public:
		static void SetJumpState(int state) {
			driver::write_memory<DWORD>(driverhandle, client + cs2_dumper::buttons::jump, state);
		}
	};
}