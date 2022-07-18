#include "pch.h"
#include "HookPattern.hpp"

uintptr_t HookPattern::GetPattern(const char* modStr, const char* ptrn, size_t offset)
{
	auto PatternToBytes = [](const char* szpattern) {
		auto       m_iBytes = std::vector<int>{};
		const auto szStartAddr = const_cast<char*>(szpattern);
		const auto szEndAddr = const_cast<char*>(szpattern) + strlen(szpattern);

		for (auto szCurrentAddr = szStartAddr; szCurrentAddr < szEndAddr; ++szCurrentAddr) {
			if (*szCurrentAddr == '?') {
				++szCurrentAddr;
				if (*szCurrentAddr == '?') ++szCurrentAddr;
				m_iBytes.push_back(-1);
			}
			else m_iBytes.push_back(strtoul(szCurrentAddr, &szCurrentAddr, 16));
		}
		return m_iBytes;
	};

	uintptr_t mod = (uintptr_t)GetModuleHandleA(modStr);
	if (!mod)
		return 0x0;

	const auto pDosHeader = (PIMAGE_DOS_HEADER)mod;
	const auto pNTHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)mod + pDosHeader->e_lfanew);
	const auto dwSizeOfImage = pNTHeaders->OptionalHeader.SizeOfImage;
	auto       m_iPatternBytes = PatternToBytes(ptrn);
	const auto pScanBytes = reinterpret_cast<std::uint8_t*>(mod);
	const auto m_iPatternBytesSize = m_iPatternBytes.size();
	const auto m_iPatternBytesData = m_iPatternBytes.data();

	for (auto i = 0ul; i < dwSizeOfImage - m_iPatternBytesSize; ++i) {
		bool bFound = true;

		for (auto j = 0ul; j < m_iPatternBytesSize; ++j) {
			if (pScanBytes[i + j] != m_iPatternBytesData[j] && m_iPatternBytesData[j] != -1) {
				bFound = false;
				break;
			}
		}

		if (bFound) {
			auto ret = reinterpret_cast<uintptr_t>(&pScanBytes[i]);
			return ret ? ret + offset : 0x0;
		}
	}

	return NULL;
}
