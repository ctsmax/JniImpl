#pragma once

class HookPattern
{
public:
	static uintptr_t GetPattern(const char* modStr, const char* ptrn, size_t offset = 0);

	template <typename T>
	static T GetAddress(uintptr_t addr) {
		if (!addr)
			return (T)0x0;

		auto adr = *(int32_t*)(addr)+addr + 4;
		return *(T*)(adr);
	}
};