#include "pch.h"
#include "ClassLoaderData.hpp"

#include "../Utilities/HookFunction.h"
#include "../Utilities/HookPattern.hpp"

static HookFunction hookFunction([]()
	{
		ClassLoaderDataBase::_head = HookPattern::GetAddress<ClassLoaderDataBase*>(HookPattern::GetPattern("jvm.dll", "48 C7 01 ? ? ? ? 48 8B 05 ? ? ? ?", 0xA));
	});