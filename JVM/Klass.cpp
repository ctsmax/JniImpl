#include "pch.h"
#include "Klass.hpp"

#include "../Utilities/HookFunction.h"
#include "../Utilities/HookPattern.hpp"

static HookFunction hookFunction([]()
	{
		auto address = HookPattern::GetPattern("jvm.dll", "48 03 05 ? ? ? ? 8B 40 08", 0x3);
		if (!address)
			address = HookPattern::GetPattern("jvm.dll", "48 03 15 ? ? ? ? EB 04 48 8B 56 08 48 8B 07 48 8B CF", 0x3);

		KlassBase::_narrow_klass = HookPattern::GetAddress<NarrowPtrStruct>(address);
	});