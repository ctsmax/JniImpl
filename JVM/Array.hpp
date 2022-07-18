#pragma once

template <typename T>
class Array {
protected:
	int _length;                                 // the number of array elements
	T   _data[1];                                // the array memory

	void initialize(int length) {
		_length = length;
	}
public:
	int  length() const { return _length; }
	T* data() { return _data; }
	bool is_empty() const { return length() == 0; }

	int index_of(const T& x) const {
		int i = length();
		while (i-- > 0 && _data[i] != x);

		return i;
	}

	bool contains(const T& x) const { return index_of(x) >= 0; }

	T    at(int i) const { return _data[i]; }
	void at_put(const int i, const T& x) { _data[i] = x; }
	T* adr_at(const int i) { return &_data[i]; }
	int  find(const T& x) { return index_of(x); }
};