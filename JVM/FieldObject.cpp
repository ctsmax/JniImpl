#include "pch.h"
#include "FieldObject.hpp"
#include "Klass.hpp"

#include "../Utilities/HookFunction.h"
#include "../Utilities/HookPattern.hpp"

static HookFunction hookFunction([]()
	{
		auto address = HookPattern::GetPattern("jvm.dll", "48 8B 05 ? ? ? ? 48 85 DB 75 48", 0x3);
		if (!address)
			address = HookPattern::GetPattern("jvm.dll", "48 03 05 ? ? ? ? 49 3B 40 18", 0x3);

		FieldObject::_narrow_oop = HookPattern::GetAddress<NarrowPtrStruct>(address);
		
	});

FieldObject* FieldObject::Decode(u4 value)
{
	return (FieldObject*)((uintptr_t)_narrow_oop._base + ((uintptr_t)value << _narrow_oop._shift));
}
