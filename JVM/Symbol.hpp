#pragma once
#include "Types.hpp"

template<int Version>
class Symbol
{
public:
	std::string_view AsString() {
		return std::string_view(impl._body, impl._length);
	}
	
	u2 GetLength() {
		return impl._length;
	}
private:
	struct Impl8
	{
		u2 _length;
		PAD(0x6);
		char _body[2];
	};

	struct Impl16
	{
		volatile u4 _hash_and_refcount; // 0x0
		u2 _length;						// 0x4
		char _body[2];					// 0x6
	};

	std::conditional_t<(Version == 8), Impl8, Impl16> impl;
};
