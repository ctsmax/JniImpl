#pragma once
#include "Types.hpp"

template<int Version>
class Klass;

class FieldObject
{
public:
	static inline NarrowPtrStruct _narrow_oop;
public:
	static FieldObject* Decode(u4 value);
public:
	FieldObject* GetObj(u4 fid) {
		if (!fid || (uintptr_t)!this)
			return 0x0;

		auto val = *(u4*)((uintptr_t)this + fid);
		return Decode(val);
	}

	FieldObject* GetObjectArray(int index) {
		auto offset = 0x10;
		return this->GetObj(offset + 4 * index);  // return base_offset_in_bytes() + sizeof(T) * index;
	}

	template<int Version>
	Klass<Version>* GetClass() {
		if ((uintptr_t)!this)
			return 0x0;

		u4 val = *(u4*)((uintptr_t)this + 0x8);
		return Klass<Version>::Decode(val);
	}

	template <typename T>
	T Get(u4 fid) {
		if (!fid || (uintptr_t)!this)
			return 0x0;

		return *(T*)((uintptr_t)this + fid);
	}

	template <typename T>
	void Set(u4 fid, T v) {
		if (!fid || (uintptr_t)!this)
			return;

		*(T*)((uintptr_t)this + fid) = v;
	}
};