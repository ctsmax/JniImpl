#include "pch.h"
#include "HookFunction.h"

static HookFunctionBase* g_hookFunctions;

void HookFunctionBase::Register()
{
	m_next = g_hookFunctions;
	g_hookFunctions = this;
}

void HookFunctionBase::RunAll()
{
	for (auto func = g_hookFunctions; func; func = func->m_next)
	{
		func->Run();
	}
}