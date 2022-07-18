#pragma once
#include "Array.hpp"
#include "Types.hpp"

#include "FieldObject.hpp"
#include "ConstantPool.hpp"
#include "FieldInfo.hpp"
#include "Symbol.hpp"
#include "Oop.hpp"

class KlassBase {
public:
	static inline NarrowPtrStruct _narrow_klass;
};

template<int Version>
class Klass : public KlassBase {
public:
	static Klass<Version>* Decode(u4 value) {
		return (Klass<Version>*)((uintptr_t)_narrow_klass._base + ((uintptr_t)value << _narrow_klass._shift));
	}
private:
	JFieldID GetInterfaceField(const char* name, const char* sig) {
		auto interfaces = impl->_local_interfaces;
		if (!interfaces)
			return NULL;

		JFieldID fid = NULL;

		const int length = interfaces->length();
		for (int i = 0; i < length; i++) {
			Klass* k = interfaces->at(i);

			if (fid = GetField(name, sig))
				return fid;

			if (fid = GetInterfaceField(name, sig))
				return fid;
		}

		return NULL;
	}

	JFieldID GetField(const char* name, const char* sig) {
		if (!impl->_fields)
			return NULL;

		for (int i = 0; i < impl->_java_fields_count; i++)
		{
			FieldInfo* field = (FieldInfo*)impl->_fields->adr_at(i * 6);
			if (!field)
				continue;

			Symbol* name_sym = field->GetName(impl->_constants);
			Symbol* sig_sym = field->GetSig(impl->_constants);

			if (name_sym->AsString() != name)
				continue;

			if (sig_sym->AsString() != sig)
				continue;

			return field->GetOffset();
		}

		return NULL;
	}

public:
	Klass<Version>* GetNext() {
		return impl._next_link;
	}

	Klass<Version>* GetSuper() {
		return impl._super;
	}

	Symbol<Version>* GetSymbol() {
		return impl._name;
	}

	Array<Klass<Version>*>* GetSecondarySupers() {
		return impl._secondary_super;
	}

	u4 GetSuperCheckOffset() {
		return impl._super_check_offset;
	}


	JFieldID GetFieldId(const char* name, const char* sig) {
		JFieldID fid;

		if (!(fid = GetField(name, sig))) {
			if (!(fid = GetInterfaceField(name, sig))) {
				auto super = impl._super;
				if (super) {
					fid = super->GetField(name, sig);
				}
			}
		}

		return fid;
	}

	auto GetStaticObj(u4 fid) {
		oop* mirror = *(oop**)impl._java_mirror;
		u4 data = *(u4*)(mirror + fid);
		return (FieldObject*)(FieldObject::Decode(data));
	}

private:
	struct Impl8 {
		PAD(0x8);										// 0x00
		u4 _super_check_offset;							// 0x8
		PAD(0x4);										// 0xC
		Symbol<Version>* _name;							// 0x10
		Array<Klass<Version>*>* _secondary_super;		// 0x18
		PAD(0x48);										// 0x20
		oop* _java_mirror;								// 0x68
		Klass<Version>* _super;							// 0x70
		PAD(0x10);										// 0x78
		Klass<Version>* _next_link;						// 0x88
		PAD(0x48);										// 0x90
		ConstantPool<Version>* _constants;				// 0xD8
		PAD(0x26);										// 0xE0
		u2 _java_fields_count;							// 0x106
		PAD(0x88);										// 0x108
		Array<Klass<Version>*>* _local_interfaces;		// 0x190
		PAD(0x18);										// 0x198
		Array<u2>* _fields;								// 0x1B0
	};

	struct Impl16 
	{
		PAD(0x14);										// 0x00
		u4 _super_check_offset;							// 0x14
		Symbol<Version>* _name;							// 0x18
		PAD(0x8);										// 0x20
		Array<Klass<Version>*>* _secondary_super;		// 0x28
		PAD(0x40);										// 0x30
		oop** _java_mirror;								// 0x70
		Klass<Version>* _super;							// 0x78
		PAD(0x10);										// 0x80
		Klass<Version>* _next_link;						// 0x90
		PAD(0x48);										// 0x98
		ConstantPool<Version>* _constants;				// 0xE0
		PAD(0x30);										// 0xE8
		u2 _java_fields_count;							// 0x118
		PAD(0x80);										// 0x1A0
		Array<Klass<Version>*>* _local_interfaces;		// 0x220
		PAD(0x18);										// 0x228
		Array<u2>* _fields;								// 0x2B0
	};

	std::conditional_t<(Version == 8), Impl8, Impl16> impl;
};
