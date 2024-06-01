#pragma once

#include <cstdint>
#include <array>
#include <Windows.h>

class CHandle {
public:
	uint32_t GetEntryIndex() const noexcept {
		return index & 0x7FFF;
	}

	bool IsValid() const noexcept {
		return index < 0 && index != 0xFFFFFFFF;
	}

	bool operator==(const CHandle other) const noexcept {
		return index == other.index;
	}

	bool operator!=(const CHandle other) const noexcept {
		return index != other.index;
	}

private:
	uint32_t index;
};