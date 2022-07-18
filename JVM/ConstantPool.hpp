#pragma once
#include "pch.h"
#include "Array.hpp"
#include "Symbol.hpp"

template<int Version>
class ConstantPool{
public:
	intptr_t* base() const { return (intptr_t*)(((char*)this) + 0x48); }

	auto symbol_at_addr(int which) const {
		return (Symbol<Version>**)&base()[which];
	}

	auto symbol_at(int which) {
		return *symbol_at_addr(which);
	}
private:
	struct Impl8
	{

	};

	struct Impl16
	{
		PAD(0x18);							
		Array<void*>* _resolved_klasses;	
		PAD(0x1C);						
		int _length;							
	};

	std::conditional_t<(Version == 8), Impl8, Impl16> impl;
};