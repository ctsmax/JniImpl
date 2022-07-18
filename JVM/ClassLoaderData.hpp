#pragma once
#include "Klass.hpp"

class ClassLoaderDataBase
{
public:
	static inline ClassLoaderDataBase* _head;
};

template<int Version>
class ClassLoaderData : public ClassLoaderDataBase
{
private:
	static inline std::vector<Klass<Version>*> _cached_klasses;
public:
	Klass<Version>* FindClass(const char* name) {
		for (auto& k : _cached_klasses) {
			if (k->GetSymbol()->AsString() == name)
				return k;
		}

		return NULL;
	}
public:
	void LoadClasses() {
		ClassLoaderData<Version>* cld = (ClassLoaderData<Version>*)ClassLoaderDataBase::_head;
		while (cld != NULL) {
			for (Klass<Version>* k = cld->GetKlasses(); k != NULL; k = k->GetNext())
			{
				ClassLoaderData<Version>::_cached_klasses.push_back(k);
			}
			cld = cld->Next();
		}
	}

	ClassLoaderData<Version>* Next() {
		return impl._next;
	}

	Klass<Version>* GetKlasses() {
		return impl._klasses;
	}
private:
	struct Impl8
	{
		PAD(0x28);							
		Klass<Version>* _klasses;			
		PAD(0x18);							
		ClassLoaderData<Version>* _next;	
	};

	struct Impl16
	{
		PAD(0x38);							
		Klass<Version>* _klasses;			
		PAD(0x30);							
		ClassLoaderData<Version>* _next;	
	};

	std::conditional_t<(Version == 8), Impl8, Impl16> impl;
};