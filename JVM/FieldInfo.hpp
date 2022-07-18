#pragma once
#include "Types.hpp"
#include "Symbol.hpp"
#include "ConstantPool.hpp"

template<int Version>
class FieldInfo
{
public:
	enum FieldOffset {
		access_flags_offset = 0,
		name_index_offset = 1,
		signature_index_offset = 2,
		initval_index_offset = 3,
		low_packed_offset = 4,
		high_packed_offset = 5,
		field_slots = 6
	};

	u4 GetOffset() { return ((int)((u4)FieldOffset::low_packed_offset << 16) | (u4)FieldOffset::high_packed_offset); };
	
	Symbol<Version>* GetName(ConstantPool<Version>* cp) {
		int index = _shorts[name_index_offset];
		return cp->symbol_at(index);
	};

	Symbol<Version>* GetSig(ConstantPool<Version>* cp) {
		int index = _shorts[signature_index_offset];
		return cp->symbol_at(index);
	}
private:
	u2 _shorts[6];
};