#pragma once

#include "ADVobfuscator/MetaRandom.h"

__forceinline void Morph(int a) {

	volatile int _morph_var = static_cast<int>(1 + andrivet::ADVobfuscator::MetaRandom<0, 0x7FFFFF - 1>::value);

	if (_morph_var % 7) {
		_morph_var += (int)a + 4;
		while (!(_morph_var % 3)) 
			++_morph_var;
	}
	else if (_morph_var % 3) {
		_morph_var -= (int)a - 3;
		while (!(_morph_var % 5)) 
			++_morph_var;
	}
	else if (_morph_var % 2) {
		_morph_var = (_morph_var + 4) * ((int)a + 2);
		while (!(_morph_var % 3))
			if (_morph_var % 7)
				--_morph_var;
			else ++_morph_var;
	}
	else if (_morph_var % 9) {
		_morph_var = (_morph_var + 4) / ((int)a + 15);
		while (!(_morph_var % 3))
			if (_morph_var % 5)
				++_morph_var;
			else 
				--_morph_var;
	}
}

__forceinline void Morph(void* a) {
	Morph((int)a);
}

__forceinline void Morph(void) {
	volatile int _morph_var = static_cast<int>(1 + andrivet::ADVobfuscator::MetaRandom<0, 0x7FFFFF - 1>::value);
}