/*************************************************************************
** utility.hpp                                                          **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2025 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdint>
#include <iomanip>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace math {

constexpr const double PI      = 3.141592653589793238462643383279502884;
constexpr const double HALF_PI = 1.570796326794896619231321691639751442;
constexpr const double TWO_PI  = 6.283185307179586476925286766559005768;
constexpr const double SQRT2   = 1.414213562373095048801688724209698079;

inline double deg2rad (double deg) {return PI*deg/180.0;}
inline double rad2deg (double rad) {return 180.0*rad/PI;}
double normalize_angle (double angle, double mod);
double normalize_0_2pi (double rad);
std::vector<double> svd (const double (&m)[2][2]);
double integral (double t0, double t1, int n, const std::function<double(double)> &f);

/** Signum function (returns x/abs(x) if x != 0, and 0 otherwise). */
template <typename T>
int sgn (T x) {return (x > T(0)) - (x < T(0));}

inline double clip (double x, double min, double max) {
	return x < min ? min : (x > max ? max : x);
}

} // namespace math

namespace util {

struct IsEmptyString : std::function<bool(std::string)> {
	bool operator () (const std::string &str) const {return str.empty();}
};

template <typename T>
std::string tohex (T val) {
	std::ostringstream oss;
	oss << std::hex << val;
	return oss.str();
}

std::string trim (const std::string &str, const char *ws=" \t\n\r\f");
std::string normalize_space (std::string str, const char *ws=" \t\n\r\f");
std::string tolower (const std::string &str);
std::string replace (std::string str, const std::string &find, const std::string &repl);
std::string to_string (double val);
std::string mimetype (const std::string &fname);

std::vector<std::string> split (const std::string &str, const std::string &sep, bool allowEmptyResult=false);
int ilog10 (int n);

bool read_double (std::istream &is, double &value);
std::string read_file_contents (const std::string &fname);
void write_file_contents (const std::string &fname, std::string::iterator start, std::string::iterator end);


/** Returns a sequence of bytes of a given integral value.
 *  @param[in] val get bytes of this value
 *  @param[in] n number of bytes to extract (from LSB to MSB), all if n == 0
 *  @return vector of bytes in big-endian order */
template <typename T>
std::vector<uint8_t> bytes (T val, int n=0) {
	if (n <= 0)
		n = sizeof(T);
	std::vector<uint8_t> ret(n);
	for (int i=0; i < n; i++) {
		ret[n-i-1] = val & 0xff;
		val >>= 8;
	}
	return ret;
}


/** Encodes the bytes in the half-open range [first,last) to Base64 and writes
 *  the result to the range starting at 'dest'.
 *  @param[in] first initial position of the range to be encoded
 *  @param[in] last final position of the range to be encoded
 *  @param[in] dest first position of the destination range
 *  @param[in] wrap if > 0, add a newline after the given number of characters written */
template <typename InputIterator, typename OutputIterator>
void base64_encode (InputIterator first, InputIterator last, OutputIterator dest, int wrap= 0) {
	static const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int count=0;
	while (first != last) {
		int padding = 0;
		unsigned char c0 = *first++, c1=0, c2=0;
		if (first == last)
			padding = 2;
		else {
			c1 = *first++;
			if (first == last)
				padding = 1;
			else
				c2 = *first++;
		}
		uint32_t n = (c0 << 16) | (c1 << 8) | c2;
		for (int i=0; i <= 3-padding; i++) {
			if (wrap > 0 && ++count > wrap) {
				count = 1;
				*dest++ = '\n';
			}
			*dest++ = base64_chars[(n >> 18) & 0x3f];
			n <<= 6;
		}
		while (padding--) {
			if (wrap > 0 && ++count > wrap) {
				count = 1;
				*dest++ = '\n';
			}
			*dest++ = '=';
		}
	}
}


inline void base64_encode (std::istream &is, std::ostream &os, int wrap= 0) {
	base64_encode(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>(),
					  std::ostreambuf_iterator<char>(os), wrap);
}


/** Simple implementation mimicking std::make_unique introduced in C++14.
 *  Constructs an object of class T on the heap and returns a unique_ptr<T> to it.
 *  @param[in] args arguments forwarded to an constructor of T */
template<typename T, typename... Args>
std::unique_ptr<T> make_unique (Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


/** Simple implementation mimicking array variant of std::make_unique introduced in C++14.
 *  Constructs an array of class T on the heap and returns a unique_ptr<T>(size) to it.
 *  @param[in] size size of array */
template<typename T>
std::unique_ptr<T> make_unique (std::size_t size) {
	return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}


template<typename T, typename U>
std::unique_ptr<T> static_unique_ptr_cast (std::unique_ptr<U> &&old){
	return std::unique_ptr<T>{static_cast<T*>(old.release())};
}

#ifdef HAVE___BUILTIN_CLZ

template <typename T>
typename std::enable_if<sizeof(T) <= sizeof(unsigned int), int>::type
count_leading_zeros (T val) {
	return val == 0 ? 8*sizeof(T) : __builtin_clz(val) - 8*(sizeof(unsigned int)-sizeof(T));
}

template <typename T>
typename std::enable_if<sizeof(T) == sizeof(unsigned long) && sizeof(unsigned long) != sizeof(unsigned int), int>::type
count_leading_zeros (T val) {
	return val == 0 ? 8*sizeof(T) : __builtin_clzl(val);
}

template <typename T>
typename std::enable_if<sizeof(T) == sizeof(unsigned long long) && sizeof(unsigned long long) != sizeof(unsigned long), int>::type
count_leading_zeros (T val) {
	return val == 0 ? 8*sizeof(T) : __builtin_clzll(val);
}

#elif defined(_MSC_VER)

#include <intrin.h>

template <typename T>
typename std::enable_if<sizeof(T) <= 4, int>::type
count_leading_zeros (T val) {
	unsigned long index;
	return _BitScanReverse(&index, val) ? static_cast<int>(8*sizeof(T)-1-index) : 8*sizeof(T);
}

#else

// fallback implementation if no built-in clz function is available
template <typename T>
typename std::enable_if<sizeof(T) <= 4, int>::type
count_leading_zeros (T val) {
	uint32_t val32 = val;
	static const uint8_t clz_table[16] = {4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	int n=0;
	if ((val32 & 0xFFFF0000) == 0) {n = 16; val32 <<= 16;}
	if ((val32 & 0xFF000000) == 0) {n += 8; val32 <<=  8;}
	if ((val32 & 0xF0000000) == 0) {n += 4; val32 <<=  4;}
	return n + clz_table[val32 >> (32-4)] - (32-8*sizeof(T));
}

#endif

/** Returns floor(log2(n)) where n is a positive integer.
 *  If n < 1, it returns -1. */
template <typename T>
int ilog2 (T n) {
	return n > 0 ? 8*sizeof(T)-1-count_leading_zeros(n) : -1;
}

template <typename T>
struct set_const_of {
	template <typename U>
	struct by {
		using type = typename std::conditional<
			std::is_const<U>::value,
			typename std::add_const<T>::type,
			typename std::remove_const<T>::type
		>::type;
	};
};

} // namespace util

#endif
