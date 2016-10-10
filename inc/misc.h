/*
	misc.h
	* Miscellaneous utilities
*/

#ifndef MISC_H
#define MISC_H

#include <algorithm>

namespace tetris {

template <class T>
inline const T& clamp(const T& min, const T& val, const T& max) {
	return std::min(std::max(min, val), max);
}

template <class T>
inline bool inRange(const T& lower, const T& val, const T& upper) {
	return lower <= val && val <= upper;
}

}	// namespace tetris

#endif // MISC_H