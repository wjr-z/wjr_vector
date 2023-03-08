#pragma once
#ifndef __WJR_VECTOR_H
#define __WJR_VECTOR_H

#pragma push_macro("new")
#undef new

#include <stdexcept>
#include <string>

#pragma once
#ifndef __WJR_PAIR_H
#define __WJR_PAIR_H

#pragma once
#ifndef __WJR_TYPE_TRAITS_H
#define __WJR_TYPE_TRAITS_H

#include <functional>
#include <limits>
#pragma once
#ifndef __WJR_CPUINFO_H
#define __WJR_CPUINFO_H

#pragma once
#ifndef __WJR_MMACRO_H
#define __WJR_MMACRO_H

#include <cstdint>

#if defined(_MSC_VER)
/* Microsoft C/C++-compatible compiler */
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
/* GCC-compatible compiler, targeting x86/x86-64 */
#include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON__)
/* GCC-compatible compiler, targeting ARM with NEON */
#include <arm_neon.h>
#elif defined(__GNUC__) && defined(__IWMMXT__)
/* GCC-compatible compiler, targeting ARM with WMMX */
#include <mmintrin.h>
#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#include <altivec.h>
#elif defined(__GNUC__) && defined(__SPE__)
/* GCC-compatible compiler, targeting PowerPC with SPE */
#include <spe.h>
#endif

#if defined(__AVX512VL__)
#define WJR_AVX512VL 1
#else
#define WJR_AVX512VL 0
#endif

#if defined(__AVX512BW__)
#define WJR_AVX512BW 1
#else
#define WJR_AVX512BW 0
#endif

#if defined(__AVX512DQ__)
#define WJR_AVX512DQ 1
#else
#define WJR_AVX512DQ 0
#endif

#if defined(__AVX512F__) || (WJR_AVX512F && WJR_AVX512BW && WJR_AVX512DQ)
#define WJR_AVX512F 1
#else
#define WJR_AVX512F 0
#endif

#if defined(__AVX512__) || (WJR_AVX512F && WJR_AVX512BW && WJR_AVX512DQ)
#define WJR_AVX512 1
#else
#define WJR_AVX512 0
#endif

#if defined(__AVX2__) || (WJR_AVX512 || WJR_AVX512F)
#define WJR_AVX2 1
#else
#define WJR_AVX2 0
#endif

#if defined(__AVX__) || WJR_AVX2
#define WJR_AVX 1
#else
#define WJR_AVX 0
#endif

#if defined(__SSE4_2__) || WJR_AVX
#define WJR_SSE4_2 1
#else
#define WJR_SSE4_2 0
#endif

#if defined(__SSE4_1__) || WJR_SSE4_2
#define WJR_SSE4_1 1
#else
#define WJR_SSE4_1 0
#endif

#if defined(__SSSE3__) || WJR_SSE4_1
#define WJR_SSSE3 1
#else 
#define WJR_SSSE3 0
#endif

#if defined(__SSE3__) || WJR_SSSE3
#define WJR_SSE3 1
#else
#define WJR_SSE3 0
#endif

#if defined(__SSE2__) || WJR_SSE3 || _M_IX86_FP >= 2 || \
	(defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_X64)))
#define WJR_SSE2 1
#else
#define WJR_SSE2 0
#endif

#if defined(__SSE__) || WJR_SSE2 ||_M_IX86_FP >= 1
#define WJR_SSE 1
#else
#define WJR_SSE 0
#endif

#if defined(__MMX__) || WJR_SSE
#define WJR_MMX 1
#else
#define WJR_MMX 0
#endif

#if defined(__XOP__)
#define WJR_XOP 1
#else
#define WJR_XOP 0
#endif

#if defined(__pnacl__) || defined(__CLR_VER)
#define WJR_VM
#endif

#if (defined(_M_IX86) || defined(__i386__)) && !defined(WJR_VM)
#define WJR_X86_32
#endif

#if (defined(_M_X64) || defined(__x86_64__)) && !defined(WJR_VM)
#define WJR_X86_64
#endif

#if defined(WJR_X86_32) || defined(WJR_X86_64)
#define WJR_X86
#endif

#if (defined(__arm__) || defined(_M_ARM))
#define WJR_ARM
#endif

#if !defined(WJR_X86)
#error "ARM is not supported"
#endif

#if defined(__clang__)
#define WJR_COMPILER_CLANG
#elif defined(__GNUC__)
#define WJR_COMPILER_GCC
#elif defined(_MSC_VER)
#define WJR_COMPILER_MSVC
#endif

// judge if i can use inline asm
#if defined(WJR_X86) && (defined(WJR_COMPILER_GCC) || defined(WJR_COMPILER_CLANG))
#define WJR_INLINE_ASM
#if defined(WJR_COMPILER_GCC)
#define WJR_BETTER_INLINE_ASM
#endif // WJR_COMPILER_GCC
#endif

#if defined(__GNUC__)
#define WJR_HAS_GCC(major, minor, patchlevel)	            \
((__GNUC__ > (major)) ||					                \
	(__GNUC__ == (major) && __GNUC_MINOR__ > (minor)) ||	\
	(__GNUC__ == (major) && __GNUC_MINOR__ == (minor) && __GNUC_PATCHLEVEL__ >= (patchlevel)))
#else
#define WJR_HAS_GCC(major, minor, patchlevel) 0
#endif // __GNUC__

#if defined(__clang__)
#define WJR_HAS_CLANG(major, minor, patchlevel)	                    \
((__clang_major__ > (major)) ||					                    \
	(__clang_major__ == (major) && __clang_minor__ > (minor)) ||	\
	(__clang_major__ == (major) && __clang_minor__ == (minor) && __clang_patchlevel__ >= (patchlevel)))
#else
#define WJR_HAS_CLANG(major, minor, patchlevel) 0
#endif

#if defined(_MSC_VER)
#define WJR_HAS_MSVC(minor, level)	\
(_MSC_VER >= (minor) * 100 + (level))
#else
#define WJR_HAS_MSVC(minor, level) 0
#endif

#if (defined(WJR_COMPILER_GCC) && !WJR_HAS_GCC(7, 1, 0)) ||	\
	(defined(WJR_COMPILER_CLANG) && !WJR_HAS_CLANG(5, 0, 0))	
#error "GCC 7.1.0 or Clang 5.0.0 or later is required"
#endif 

#if defined(WJR_COMPILER_CLANG) || defined(WJR_COMPILER_GCC)
#define WJR_CPP_STANDARD __cplusplus
#elif defined(WJR_COMPILER_MSVC)
#define WJR_CPP_STANDARD _MSVC_LANG
#endif

#if WJR_CPP_STANDARD >= 199711L
#define WJR_CPP_03
#endif
#if WJR_CPP_STANDARD >= 201103L
#define WJR_CPP_11
#endif
#if WJR_CPP_STANDARD >= 201402L
#define WJR_CPP_14
#endif
#if WJR_CPP_STANDARD >= 201703L
#define WJR_CPP_17
#endif
#if WJR_CPP_STANDARD >= 202002L
#define WJR_CPP_20
#endif

#if WJR_SSE2
#define _WJR_FAST_MEMCHR
#define _WJR_FAST_MEMCMP
#define _WJR_FAST_MEMMIS
//#define _WJR_FAST_MEMCNT
#define _WJR_FAST_MEMSET
//#define _WJR_FAST_MEMCPY
#endif // WJR_SSE2

#if defined(NWJR_FAST_MEMCHR)
#undef _WJR_FAST_MEMCHR
#endif
#if defined(NWJR_FAST_MEMCMP)
#undef _WJR_FAST_MEMCMP
#endif
#if defined(NWJR_FAST_MEMMIS)
#undef _WJR_FAST_MEMMIS
#endif
#if defined(NWJR_FAST_MEMCNT)
#undef _WJR_FAST_MEMCNT
#endif
#if defined(NWJR_FAST_MEMSET)
#udnef _WJR_FAST_MEMSET
#endif
#if defined(NWJR_FAST_MEMCPY)
#endif

#if defined(WJR_INLINE_ASM) || defined(WJR_COMPILER_MSVC)
#define _WJR_FAST_REP
#endif

#if defined(NWJR_FAST_REP) 
#undef _WJR_FAST_REP
#endif

#if defined(NWJR_INTEL)
#undef _WJR_INTEL
#endif

#if defined(NWJR_AMD)
#undef _WJR_AMD
#endif

#if defined(_WJR_INTEL)
#define _WJR_ENHANCED_REP
#endif

#if defined(NWJR_ENHANCED_REP)
#undef _WJR_ENHANCED_REP
#endif

#define _WJR_CPUINFO

#if defined(NWJR_CPUINFO)
#undef _WJR_CPUINFO
#endif

#if defined(WJR_MAX_CACHE_SIZE) || defined(_WJR_CPUINFO)
#define _WJR_NON_TEMPORARY
#endif

#if defined(NWJR_NON_TEMPORARY)
#undef _WJR_NON_TEMPORARY
#endif

#if (defined(WJR_COMPILER_GCC) && WJR_HAS_GCC(10, 1, 0)) ||	\
	(defined(WJR_COMPILER_CLANG) && WJR_HAS_CLANG(10, 0, 0))	|| \
	(!defined(WJR_COMPILER_GCC) && !defined(WJR_COMPILER_CLANG) && defined(__has_builtin))
#define WJR_HAS_BUILTIN(x) __has_builtin(x)
#else
#define WJR_HAS_BUILTIN(x) 0
#endif 

#if defined(__has_attribute)
#define WJR_HAS_ATTRIBUTE(x) __has_attribute(x)
#elif defined(__has_cpp_attribute)
#define WJR_HAS_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define WJR_HAS_ATTRIBUTE(x) 0
#endif

#if defined(__has_include)
#define WJR_HAS_INCLUDE(x) __has_include(x)
#else
#define WJR_HAS_INCLUDE(x) 0
#endif // __has_include

#if WJR_HAS_INCLUDE(<execution>)
//#define WJR_HAS_EXECUTION
#endif // WJR_HAS_INCLUDE(<execution>)

#ifndef WJR_NODISCARD
#ifndef __has_cpp_attribute
#define WJR_NODISCARD
#elif __has_cpp_attribute(nodiscard) >= 201603L // TRANSITION, VSO#939899 (need toolset update)
#define WJR_NODISCARD [[nodiscard]]
#else
#define WJR_NODISCARD
#endif
#endif

#ifdef WJR_CPP_20
#define WJR_EXPLICIT(expression) explicit(expression)
#define WJR_EXPLICIT20(expreesion) explicit(expression)
#else
#define WJR_EXPLICIT(expression) explicit
#define WJR_EXPLICIT20(expression)
#endif

#if WJR_HAS_ATTRIBUTE(always_inline)
#define WJR_FORCEINLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define WJR_FORCEINLINE __forceinline
#else
#define WJR_FORCEINLINE
#endif

#if defined(WJR_FORCEINLINE)
#define WJR_INTRINSIC_INLINE inline WJR_FORCEINLINE
#else
#define WJR_INTRINSIC_INLINE inline
#endif

#if defined(WJR_CPP_20)
#define WJR_CONSTEXPR20 constexpr
#else
#define WJR_CONSTEXPR20
#endif

#define WJR_FORCEINLINE_CONSTEXPR20 WJR_FORCEINLINE WJR_CONSTEXPR20
#define WJR_INTRINSIC_CONSTEXPR20 WJR_INTRINSIC_INLINE WJR_CONSTEXPR20
#define WJR_INLINE_CONSTEXPR20 inline WJR_CONSTEXPR20
#define WJR_INTRINSIC_CONSTEXPR WJR_INTRINSIC_INLINE constexpr

#define _WJR_BEGIN namespace wjr{
#define _WJR_END }
#define _WJR_SIMD_BEGIN _WJR_BEGIN namespace simd{
#define _WJR_SIMD_END } _WJR_END
#define _WJR_ASM_BEGIN _WJR_BEGIN namespace masm{
#define _WJR_ASM_END } _WJR_END
#define _WJR_ALGO_BEGIN _WJR_BEGIN namespace algo{
#define _WJR_ALGO_END } _WJR_END
#define _WJR_MP_BEGIN _WJR_BEGIN namespace mp{
#define _WJR_MP_END } _WJR_END
#define _WJR_LITERALS_BEGIN _WJR_BEGIN namespace literals{
#define _WJR_LITERALS_END } _WJR_END

#ifndef _WJR_NOEXCEPTION
#define _WJR_TRY try{
#define _WJR_CATCH(x) }catch(x){
#define _WJR_CATCH_ALL }catch(...){
#define _WJR_END_CATCH }
#define _WJR_THROW(x) throw x
#define _WJR_RELEASE throw
#else
#define _WJR_TRY { if constexpr(true){
#define _WJR_CATCH(x) } if constexpr(false){
#define _WJR_CATCH_ALL } if constexpr(false){
#define _WJR_END_CATCH }}
#define _WJR_THROW(x) 
#define _WJR_RELEASE
#endif

#define WJR_MACRO_NULL(...)

#define WJR_MACRO_LABEL(NAME) __wjr_label_##NAME

#if defined(WJR_X86_64)
#define WJR_BYTE_WIDTH 8
#else
#define WJR_BYTE_WIDTH 4
#endif 

#define WJR_CONCAT(x, y) x##y
#define WJR_MACRO_CONCAT(x, y) WJR_CONCAT(x, y)

#define WJR_EXPAND(x) x

#define __WJR_DEFINE_0(x)
#define __WJR_DEFINE_1(x) x
#define WJR_DEFINE(x, y) __WJR_DEFINE_##y (x)

#define WJR_STR(x) #x
#define WJR_MACRO_STR(x) WJR_STR(x)

#define WJR_OVERLAP_P(p1, s1, p2, s2) \
	((p1) + (s1) > (p2) && (p2) + (s2) > (p1))

#define WJR_OVERLAP_P_N(p1, p2, n)	\
	WJR_OVERLAP_P(p1, n, p2, n)

#define WJR_SAME_OR_SEPARATE_P(p1, s1, p2, s2)	\
	((p1) == (p2) || !WJR_OVERLAP_P(p1, s1, p2, s2))

#define WJR_SAME_OR_SEPARATE_P_N(p1, p2, n)	\
	WJR_SAME_OR_SEPARATE_P(p1, n, p2, n)

#define WJR_PRE_OR_SEPARATE_P(p1, s1, p2, s2) \
	((p1) <= (p2) || !WJR_OVERLAP_P(p1, s1, p2, s2))

#define WJR_PRE_OR_SEPARATE_P_N(p1, p2, n)	\
	WJR_PRE_OR_SEPARATE_P(p1, n, p2, n)

#define WJR_POST_OR_SEPARATE_P(p1, s1, p2, s2) \
	((p1) >= (p2) || !WJR_OVERLAP_P(p1, s1, p2, s2))

#define WJR_POST_OR_SEPARATE_P_N(p1, p2, n)	\
	WJR_POST_OR_SEPARATE_P(p1, n, p2, n)

#define WJR_REGISTER_HAS_MEMBER_FUNCTION(FUNC, NAME)							\
template<typename Enable, typename T, typename...Args>							\
struct __has_member_function_##NAME : std::false_type {};						\
template<typename T, typename...Args>											\
struct __has_member_function_##NAME <std::void_t<decltype(						\
	std::declval<T>(). FUNC (std::declval<Args>()...))>, T, Args...>			\
	: std::true_type {};														\
template<typename T, typename...Args>											\
struct has_member_function_##NAME :												\
	__has_member_function_##NAME<void, T, Args...> {};							\
template<typename T, typename...Args>											\
constexpr bool has_member_function_##NAME##_v =									\
	has_member_function_##NAME<T, Args...>::value;

#define WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(FUNC, NAME)						\
template<typename Enable, typename T, typename...Args>							\
struct __has_static_member_function_##NAME : std::false_type {};				\
template<typename T, typename...Args>											\
struct __has_static_member_function_##NAME <std::void_t<decltype(				\
	T:: FUNC (std::declval<Args>()...))>, T, Args...>							\
	: std::true_type {};														\
template<typename T, typename...Args>											\
struct has_static_member_function_##NAME :										\
	__has_static_member_function_##NAME<void, T, Args...> {};					\
template<typename T, typename...Args>											\
constexpr bool has_static_member_function_##NAME##_v =							\
	has_static_member_function_##NAME<T, Args...>::value;

#define WJR_REGISTER_HAS_GLOBAL_FUNCTION(FUNC, NAME)							\
template<typename Enable, typename...Args>										\
struct __has_global_function_##NAME : std::false_type {};						\
template<typename...Args>														\
struct __has_global_function_##NAME <std::void_t<decltype(						\
	FUNC (std::declval<Args>()...))>, Args...>									\
	: std::true_type {};														\
template<typename...Args>														\
struct has_global_function_##NAME :												\
	__has_global_function_##NAME<void, Args...> {};								\
template<typename...Args>														\
constexpr bool has_global_function_##NAME##_v =									\
	has_global_function_##NAME<Args...>::value;

#define WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(OP, NAME)						\
template<typename Enable, typename T, typename U>								\
struct __has_global_binary_operator_##NAME : std::false_type {};				\
template<typename T, typename U>												\
struct __has_global_binary_operator_##NAME <std::void_t<decltype(				\
	std::declval<T>() OP std::declval<U>())>, T, U>								\
	: std::true_type {};														\
template<typename T, typename U>												\
struct has_global_binary_operator_##NAME :										\
	__has_global_binary_operator_##NAME<void, T, U> {};							\
template<typename T, typename U>												\
constexpr bool has_global_binary_operator_##NAME##_v =							\
	has_global_binary_operator_##NAME<T, U>::value;								\
template<typename T, typename U>												\
struct has_global_binary_operator<T, U, std:: NAME<>> :							\
	has_global_binary_operator_##NAME<T, U> {};

#define WJR_REGISTER_HAS_GLOBAL_UNARY_OPERATOR(OP, NAME)							\
template<typename Enable, typename T>											\
struct __has_global_unary_operator_##NAME : std::false_type {};					\
template<typename T>															\
struct __has_global_unary_operator_##NAME <std::void_t<decltype(				\
	OP std::declval<T>())>, T>													\
	: std::true_type {};														\
template<typename T>															\
struct has_global_unary_operator_##NAME :										\
	__has_global_unary_operator_##NAME<void, T> {};								\
template<typename T>															\
constexpr bool has_global_unary_operator_##NAME##_v =							\
	has_global_unary_operator_##NAME<T>::value;

#define WJR_REGISTER_HAS_TYPE(TYPE, NAME)										\
template<typename Enable, typename T>							                \
struct __has_type_##NAME : std::false_type {};				                    \
template<typename T>											                \
struct __has_type_##NAME <std::void_t<decltype(				                    \
	std::declval<typename T::TYPE>())>, T>							            \
	: std::true_type {};														\
template<typename T>											                \
struct has_type_##NAME :										                \
	__has_static_member_function_##NAME<void, T> {};					        \
template<typename T>											                \
constexpr bool has_type_##NAME##_v =							                \
	has_type_##NAME<T>::value;

#define WJR_REGISTER_HAS_TYPE_ARGS(TYPE, NAME)									\
template<typename Enable, typename T, typename...Args>							\
struct __has_type_##NAME : std::false_type {};				                    \
template<typename T, typename...Args>											\
struct __has_type_##NAME <std::void_t<decltype(				                    \
	std::declval<typename T::template TYPE<Args...>>())>, T, Args...>			\
	: std::true_type {};														\
template<typename T, typename...Args>											\
struct has_type_##NAME :										                \
	__has_type_##NAME<void, T, Args...> {};					                    \
template<typename T, typename...Args>											\
constexpr bool has_type_##NAME##_v =							                \
	has_type_##NAME<T, Args...>::value;

#endif
#if defined(_WJR_CPUINFO)
#include <cpuinfo_x86.h>
#endif // _WJR_CPUINFO

_WJR_BEGIN

#if defined(_WJR_CPUINFO)
extern const cpu_features::X86Info cpuinfo;
extern const cpu_features::CacheInfo cacheinfo;
extern const cpu_features::X86Microarchitecture microarchitecture;

extern const size_t __max_cache_size;
extern const bool __is_intel;
extern const bool __is_amd;

inline bool is_sse() {
	return WJR_SSE || cpuinfo.features.sse;
}
inline bool is_sse2() {
	return WJR_SSE2 || cpuinfo.features.sse2;
}
inline bool is_sse3() {
	return WJR_SSE3 || cpuinfo.features.sse3;
}
inline bool is_ssse3() {
	return WJR_SSSE3 || cpuinfo.features.ssse3;
}
inline bool is_sse4_1() {
	return WJR_SSE4_1 || cpuinfo.features.sse4_1;
}
inline bool is_sse4_2() {
	return WJR_SSE4_2 || cpuinfo.features.sse4_2;
}
inline bool is_avx() {
	return WJR_AVX || cpuinfo.features.avx;
}
inline bool is_avx2() {
	return WJR_AVX2 || cpuinfo.features.avx2;
}

inline bool is_popcnt() {
	return cpuinfo.features.popcnt;
}

#endif // _WJR_CPUINFO

#if defined(_WJR_NON_TEMPORARY)
inline size_t max_cache_size() {
#if defined(WJR_MAX_CACHE_SIZE)
	return WJR_MAX_CACHE_SIZE;
#else
	return __max_cache_size;
#endif
}
#endif // _WJR_NON_TEMPORARY

inline bool is_intel() {
#if defined(_WJR_INTEL)
	return true;
#elif defined(NWJR_INTEL)
	return false;
#elif defined(_WJR_CPUINFO)
	return __is_intel;
#else
	return false;
#endif
}

inline bool is_amd() {
#if defined(_WJR_AMD)
	return true;
#elif defined(NWJR_AMD)
	return false;
#elif defined(_WJR_CPUINFO)
	return __is_amd;
#else
	return false;
#endif
}

inline bool is_enhanced_rep() {
#if defined(_WJR_ENHNACED_REP)
	return true;
#else
	return is_intel();
#endif
}

_WJR_END

#endif // __WJR_CPUINFO_H

_WJR_BEGIN

WJR_INTRINSIC_CONSTEXPR bool is_likely(bool f) noexcept {
#if WJR_HAS_BUILTIN(__builtin_expect) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
	return __builtin_expect(f, true);
#else
	return f;
#endif
}

WJR_INTRINSIC_CONSTEXPR bool is_unlikely(bool f) noexcept {
#if WJR_HAS_BUILTIN(__builtin_expect) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
	return __builtin_expect(f, false);
#else
	return f;
#endif
}

WJR_INTRINSIC_CONSTEXPR bool is_constant_evaluated() noexcept {
#if defined(__cpp_lib_is_constant_evaluated) 
	return std::is_constant_evaluated();
#elif WJR_HAS_BUILTIN(__builtin_is_constant_evaluated) || WJR_HAS_GCC(9,1,0) || WJR_HAS_CLANG(9,0,0)
	return __builtin_is_constant_evaluated();
#else
	return false;
#endif
}

WJR_INTRINSIC_INLINE void unreachable() noexcept {
#if defined(_cpp_lib_unreachable)
	return std::unreachable();
#elif WJR_HAS_BUILTIN(__builtin_unreachable) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
	__builtin_unreachable();
#elif defined(WJR_COMPILER_MSVC)
	__assume(0);
#endif
}

WJR_INTRINSIC_CONSTEXPR void assume(bool cond) noexcept {
#if WJR_HAS_BUILTIN(__builtin_assume)
	__builtin_assume(cond);
#else
	if (is_unlikely(!cond)) {
		unreachable();
	}
#endif 
}

template<typename T>
WJR_INTRINSIC_CONSTEXPR bool is_constant_p(T x) noexcept {
#if WJR_HAS_BUILTIN(__builtin_constant_p) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
	return __builtin_constant_p(x);
#else
	return is_constant_evaluated();
#endif
}

#if defined(__cpp_lib_is_constant_evaluated) || WJR_HAS_BUILTIN(__builtin_is_constant_evaluated) ||		\
	WJR_HAS_GCC(9,1,0) || WJR_HAS_CLANG(9,0,0)
#define WJR_HAS_CONSTANT_EVALUATED
#endif 

#if WJR_HAS_BUILTIN(__builtin_constant_p) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
#define WJR_HAS_CONSTANT_P
#define WJR_HAS_STRONG_CONSTANT_P
#define WJR_HAS_WEAK_CONSTANT_P
#elif defined(WJR_HAS_CONSTANT_EVALUATED)
#define WJR_HAS_WEAK_CONSTANT_P
#endif

struct disable_tag {};

struct default_construct_tag {};
struct value_construct_tag {};

struct extend_tag {};
struct reserve_tag {};

constexpr size_t byte_width = WJR_BYTE_WIDTH;

template<typename T, typename U, typename _Pred>
struct has_global_binary_operator : std::false_type {};

template<typename T, typename U, typename _Pred>
constexpr bool has_global_binary_operator_v = has_global_binary_operator<T, U, _Pred>::value;

WJR_REGISTER_HAS_MEMBER_FUNCTION(operator(), call_operator);
WJR_REGISTER_HAS_MEMBER_FUNCTION(operator[], subscript_operator);
WJR_REGISTER_HAS_MEMBER_FUNCTION(operator->, point_to_operator);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(+, plus);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(-, minus);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(&, bit_and);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(| , bit_or);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(^, bit_xor);
WJR_REGISTER_HAS_GLOBAL_UNARY_OPERATOR(~, bit_not);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(== , equal_to);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(!= , not_equal_to);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(> , greater);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(>= , greater_equal);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(< , less);
WJR_REGISTER_HAS_GLOBAL_BINARY_OPERATOR(<= , less_equal);
WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(min, min);
WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(max, max);

template<typename T, typename...Args>
struct is_any_of : std::disjunction<std::is_same<T, Args>...> {};

template<typename T, typename...Args>
constexpr bool is_any_of_v = is_any_of<T, Args...>::value;

template<typename T>
using remove_ref_t = std::remove_reference_t<T>;

template<typename T>
using remove_cvref_t = std::remove_cv_t<remove_ref_t<T>>;

template<typename T>
using remove_cref_t = std::remove_const_t<remove_ref_t<T>>;

template<typename T>
using add_lref_t = std::add_lvalue_reference_t<T>;

template<typename T>
using add_rref_t = std::add_rvalue_reference_t<T>;

template<typename T>
using add_cvref_t = add_lref_t<std::add_cv_t<T>>;

template<typename T>
using add_cref_t = add_lref_t<std::add_const_t<T>>;

template<typename T>
struct is_standard_comparator :
	is_any_of<remove_cvref_t<T>,
	std::less<>,
	std::less_equal<>,
	std::equal_to<>,
	std::not_equal_to<>,
	std::greater<>,
	std::greater_equal<>
	> {};

template<typename T>
constexpr bool is_standard_comparator_v = is_standard_comparator<T>::value;

template<typename T>
struct is_left_standard_comparator :
	is_any_of<std::remove_cv_t<T>,
	std::less<>,
	std::less_equal<>
	> {};

template<typename T>
constexpr bool is_left_standard_comparator_v = is_left_standard_comparator<T>::value;

template<typename T>
struct is_right_standard_comparator :
	is_any_of<remove_cvref_t<T>,
	std::greater<>,
	std::greater_equal<>
	> {};

template<typename T>
constexpr bool is_right_standard_comparator_v = is_right_standard_comparator<T>::value;

template<typename T>
struct unrefwrap {
	using type = T;
};

template<typename T>
struct unrefwrap<std::reference_wrapper<T>> {
	using type = T&;
};

template<typename T>
using unrefwrap_t = typename unrefwrap<T>::type;

template<typename T>
using iter_cat_t = typename std::iterator_traits<T>::iterator_category;

template<typename T>
using iter_diff_t = typename std::iterator_traits<T>::difference_type;

template<typename T>
using iter_val_t = typename std::iterator_traits<T>::value_type;

template<typename T>
using iter_ref_t = typename std::iterator_traits<T>::reference;

//template<typename T>
//using iter_ptr_t = typename std::iterator_traits<T>::pointer;

template<typename T, typename = void>
struct is_iterator : std::false_type {};

template<typename T>
struct is_iterator<T, std::void_t<iter_cat_t<T>>> : std::true_type {};

template<typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;

template<typename _Iter, typename = void>
struct _Is_contiguous_iterator_helper : std::false_type {};

template<typename _Iter>
struct _Is_contiguous_iterator_helper<_Iter, typename _Iter::is_contiguous_iterator> : std::true_type {};

template<typename T>
struct _Is_contiguous_iterator_helper<T*, void> : std::true_type {};

#if defined(WJR_CPP_20)
template<typename T>
struct is_contiguous_iterator : std::bool_constant<std::contiguous_iterator<T> || _Is_contiguous_iterator_helper<T>::value> {};
#else
template<typename T>
struct is_contiguous_iterator : _Is_contiguous_iterator_helper<T> {};
#endif

template<typename _Iter>
struct is_contiguous_iterator<std::reverse_iterator<_Iter>> : is_contiguous_iterator<_Iter> {};

template<typename T>
constexpr bool is_contiguous_iterator_v = is_contiguous_iterator<T>::value;

template<typename T>
struct is_input_iter : std::is_convertible<iter_cat_t<T>, std::input_iterator_tag> {};

template<typename T>
constexpr bool is_input_iter_v = is_input_iter<T>::value;

template<typename T>
struct is_output_iter : std::is_convertible<iter_cat_t<T>, std::output_iterator_tag> {};

template<typename T>
constexpr bool is_output_iter_v = is_output_iter<T>::value;

template<typename T>
struct is_forward_iter : std::is_convertible<iter_cat_t<T>, std::forward_iterator_tag> {};

template<typename T>
constexpr bool is_forward_iter_v = is_forward_iter<T>::value;

template<typename T>
struct is_bidir_iter : std::is_convertible<iter_cat_t<T>, std::bidirectional_iterator_tag> {};

template<typename T>
constexpr bool is_bidir_iter_v = is_bidir_iter<T>::value;

template<typename T>
struct is_random_iter : std::is_convertible<iter_cat_t<T>, std::random_access_iterator_tag> {};

template<typename T>
constexpr bool is_random_iter_v = is_random_iter<T>::value;

template<size_t n>
struct __uint_helper {};

template<>
struct __uint_helper<8> {
	using type = unsigned char;
};
template<>
struct __uint_helper<16> {
	using type = unsigned short;
};
template<>
struct __uint_helper<32> {
	using type = std::conditional_t<sizeof(unsigned int) == 4, unsigned int, unsigned long>;
};
template<>
struct __uint_helper<64> {
	using type = unsigned long long;
};

template<size_t n>
using uint_t = typename __uint_helper<n>::type;

template<size_t n>
struct __int_helper {};

template<>
struct __int_helper<8> {
	using type = signed char;
};
template<>
struct __int_helper<16> {
	using type = signed short;
};
template<>
struct __int_helper<32> {
	using type = std::conditional_t<sizeof(int) == 4, int, long>;
};
template<>
struct __int_helper<64> {
	using type = long long;
};

template<size_t n>
using int_t = typename __int_helper<n>::type;

using int8_t = int_t<8>;
using int16_t = int_t<16>;
using int32_t = int_t<32>;
using int64_t = int_t<64>;

using uint8_t = uint_t<8>;
using uint16_t = uint_t<16>;
using uint32_t = uint_t<32>;
using uint64_t = uint_t<64>;

using intptr_t = int_t<sizeof(void*) * 8>;
using uintptr_t = uint_t<sizeof(void*) * 8>;

template<size_t n, bool __s>
using int_or_uint_t = std::conditional_t<__s, int_t<n>, uint_t<n>>;

template<typename T>
struct make_integral {
	static_assert(std::is_integral_v<T>, "T must be an integral type");
	using type = int_or_uint_t<sizeof(T) * 8, std::is_signed_v<T>>;
};

template<typename T>
using make_integral_t = typename make_integral<T>::type;

template<typename T>
constexpr std::make_unsigned_t<T> make_unsigned(T t) {
	return static_cast<std::make_unsigned_t<T>>(t);
}

template<typename T, typename U, typename _Pred>
struct is_comparable : std::conjunction<
	has_global_binary_operator<T, U, _Pred>,
	has_global_binary_operator<U, T, _Pred>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool is_comparable_v = is_comparable<T, U, _Pred>::value;

// note that (int8_t)(-1) != (uint8_t)(-1)
// but in memory they are the same
template<typename T, typename U, bool = sizeof(T) == sizeof(U) && std::is_integral_v<T>&& std::is_integral_v<U>>
constexpr bool __is_memory_comparable_helper_v =
std::is_same_v<T, bool> || std::is_same_v<U, bool> || static_cast<T>(-1) == static_cast<U>(-1);

template<typename T, typename U>
constexpr bool __is_memory_comparable_helper_v<T, U, false> = false;

template<typename T, typename U, typename _Pred>
struct is_memory_comparable : std::conjunction<
	is_standard_comparator<_Pred>,
	is_comparable<T, U, _Pred>,
	std::bool_constant<__is_memory_comparable_helper_v<T, U>>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool is_memory_comparable_v = is_memory_comparable<T, U, _Pred>::value;

enum class ipmc_result {
	none,
	all,
	exit
};

template<typename T, typename U, typename _Pred,
	std::enable_if_t<is_any_of_v<_Pred, std::equal_to<>, std::not_equal_to<>>, int> = 0>
constexpr ipmc_result is_possible_memory_comparable(const U& v, _Pred pred) {
	static_assert(std::is_integral_v<T> && std::is_integral_v<U>, "T and U must be integral types");
	using nt = T;
	using nu = U;
	using cat = std::common_type_t<nt, nu>;
	auto _Val = static_cast<cat>(v);
	if constexpr (std::is_signed_v<nt> && std::is_unsigned_v<cat>) {
		static_assert(static_cast<nt>(-1) == std::numeric_limits<cat>::max(), "error");
		if constexpr (std::is_same_v<_Pred, std::equal_to<>>) {
			return ((std::numeric_limits<nt>::min() <= _Val && _Val <= static_cast<nt>(-1))
				|| _Val <= std::numeric_limits<nt>::max()) ? ipmc_result::exit : ipmc_result::none;
		}
		else {
			return (std::numeric_limits<nt>::max() < _Val && _Val < std::numeric_limits<nt>::min()) ?
				ipmc_result::all : ipmc_result::exit;
		}
	}
	else {
		if constexpr (std::is_same_v<_Pred, std::equal_to<>>) {
			return (std::numeric_limits<nt>::min() <= _Val && _Val <= std::numeric_limits<nt>::max()) ?
				ipmc_result::exit : ipmc_result::none;
		}
		else {
			return (std::numeric_limits<nt>::max() < _Val || _Val < std::numeric_limits<nt>::min()) ?
				ipmc_result::all : ipmc_result::exit;
		}
	}
}

template<typename T>
struct _Auto_variable_helper {
	using type = std::conditional_t<sizeof(T) <= 256 / 8, T, const T&>;
};

template<typename T>
using auto_var_t = typename _Auto_variable_helper<T>::type;

template<size_t i, size_t..._Index>
struct is_any_index_of : std::disjunction<std::bool_constant<i == _Index>...> {};

template<size_t i, size_t..._Index>
constexpr bool is_any_index_of_v = is_any_index_of<i, _Index...>::value;

template<typename T>
struct ref_wrapper {
	using type = T;
};

template<typename T>
struct ref_wrapper<T&> {
	using type = std::reference_wrapper<T>;
};

template<typename T>
struct ref_wrapper<T&&> {
	using type = T;
};

template<typename T>
using ref_wrapper_t = typename ref_wrapper<T>::type;

template<typename...Args>
struct is_integrals : std::conjunction<std::is_integral<Args>...> {};

template<typename...Args>
constexpr bool is_integrals_v = is_integrals<Args...>::value;

template<typename...Args>
struct is_floating_points : std::conjunction<std::is_floating_point<Args>...> {};

template<typename...Args>
constexpr bool is_floating_points_v = is_floating_points<Args...>::value;

template<typename...Args>
struct is_arithmetics : std::conjunction<std::is_arithmetic<Args>...> {};

template<typename...Args>
constexpr bool is_arithmetics_v = is_arithmetics<Args...>::value;

template<typename T>
struct is_unsigned_integral : std::conjunction<std::is_integral<T>, std::is_unsigned<T>> {};

template<typename T>
constexpr bool is_unsigned_integral_v = is_unsigned_integral<T>::value;

template<typename T>
struct is_signed_integral : std::conjunction<std::is_integral<T>, std::is_signed<T>> {};

template<typename T>
constexpr bool is_signed_integral_v = is_signed_integral<T>::value;

template<typename T>
struct is_reverse_iterator : std::false_type {};

template<typename _Iter>
struct is_reverse_iterator<std::reverse_iterator<_Iter>> : std::negation<is_reverse_iterator<_Iter>> {};

template<typename T>
constexpr bool is_reverse_iterator_v = is_reverse_iterator<T>::value;

template<typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr auto enum_cast(T t) noexcept {
	return static_cast<std::underlying_type_t<T>>(t);
}

namespace enum_ops {
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T> operator|(T lhs, T rhs) noexcept {
		return static_cast<T>(enum_cast(lhs) | enum_cast(rhs));
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T> operator&(T lhs, T rhs) noexcept {
		return static_cast<T>(enum_cast(lhs) & enum_cast(rhs));
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T> operator^(T lhs, T rhs) noexcept {
		return static_cast<T>(enum_cast(lhs) ^ enum_cast(rhs));
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T> operator~(T t) noexcept {
		return static_cast<T>(~enum_cast(t));
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T&> operator|=(T& lhs, T rhs) noexcept {
		return lhs = lhs | rhs;
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T&> operator&=(T& lhs, T rhs) noexcept {
		return lhs = lhs & rhs;
	}
	template<typename T>
	constexpr std::enable_if_t<std::is_enum_v<T>, T&> operator^=(T& lhs, T rhs) noexcept {
		return lhs = lhs ^ rhs;
	}
}

namespace _To_address_helper {
	WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(to_address, to_address);
}

template<typename T>
constexpr auto to_address(T* p) noexcept {
	static_assert(!std::is_function_v<T>, "");
	return p;
}

template<typename T>
constexpr auto to_address(const T& p) noexcept {
	if constexpr (_To_address_helper::has_static_member_function_to_address_v<std::pointer_traits<T>, T>) {
		return std::pointer_traits<T>::to_address(p);
	}
	else {
		return wjr::to_address(p.operator->());
	}
}

template<typename T>
constexpr void* voidify(const T* ptr) {
	return const_cast<void*>(static_cast<const volatile void*>(ptr));
}

template<typename T>
constexpr auto get_address(T* p) noexcept {
	return p;
}

template<typename T>
constexpr auto get_address(const T& p) noexcept {
	if constexpr (_To_address_helper::has_static_member_function_to_address_v<std::pointer_traits<T>, T>) {
		return std::pointer_traits<T>::to_address(p);
	}
	else if constexpr (wjr::has_member_function_point_to_operator_v<add_cref_t<T>>) {
		return wjr::get_address(p.operator->());
	}
	else {
		return std::addressof(*std::forward<T>(p));
	}
}

template<typename iter>
using iter_address_t = std::add_pointer_t<remove_ref_t<iter_ref_t<iter>>>;

template<typename T>
struct type_identity {
	using type = T;
};

template<typename T>
using type_identity_t = typename type_identity<T>::type;

template<typename T, typename = void>
struct _Is_default_convertible : std::false_type {};

template<typename T>
void _Test_default_convertible(const T&);

template<typename T>
struct _Is_default_convertible < T, std::void_t<decltype(_Test_default_convertible<T>({})) >> : std::true_type{};

template<typename T>
using is_default_convertible = _Is_default_convertible<T>;

template<typename T>
constexpr bool is_default_convertible_v = is_default_convertible<T>::value;

template<typename T, typename U, typename = void>
struct _Is_swappable_with : std::false_type {};

template<typename T, typename U>
struct _Is_swappable_with<T, U, std::void_t<decltype(std::swap(std::declval<T>(), std::declval<U>()))>>
	: std::true_type {};

template<typename T, typename U>
struct is_swappable_with :
	std::conjunction<_Is_swappable_with<T, U>, _Is_swappable_with<U, T>> {};

template<typename T, typename U>
constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;

template<typename T>
struct is_swappable : is_swappable_with<std::add_lvalue_reference_t<T>, std::add_lvalue_reference_t<T>> {};

template<typename T>
constexpr bool is_swappable_v = is_swappable<T>::value;

template<typename T, typename U>
struct _Is_nothrow_swappable_with : std::bool_constant<noexcept(std::swap(std::declval<T>(), std::declval<U>()))
	&& noexcept(std::swap(std::declval<U>(), std::declval<T>()))> {};

template<typename T, typename U>
struct is_nothrow_swappable_with :
	std::conjunction<is_swappable_with<T, U>, _Is_nothrow_swappable_with<T, U>> {};

template<typename T, typename U>
constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;

template<typename T>
struct is_nothrow_swappable :
	is_nothrow_swappable_with<std::add_lvalue_reference_t<T>, std::add_lvalue_reference_t<T>> {};

template<typename T>
constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

template<typename iter, std::enable_if_t<is_iterator_v<iter>, int> = 0>
struct __make_iter_wrapper : public std::tuple<iter, iter> {
	using _Mybase = std::tuple<iter, iter>;
	using _Mybase::_Mybase;
	using _Mybase::operator=;

	constexpr iter begin() const noexcept { return std::get<0>(*this); }
	constexpr iter end() const noexcept { return std::get<1>(*this); }

	constexpr decltype(auto) size() const noexcept {
		return std::distance(begin(), end());
	}

};

template<typename iter>
constexpr __make_iter_wrapper<iter> make_iter_wrapper(iter first, iter last) {
	return { first, last };
}

template<typename T>
using alloc_ptr_t = typename std::allocator_traits<T>::pointer;

template<typename T>
using alloc_value_t = typename std::allocator_traits<T>::value_type;

template<typename T>
using alloc_size_t = typename std::allocator_traits<T>::size_type;

template<typename T>
using alloc_diff_t = typename std::allocator_traits<T>::difference_type;

// The default allocator uses the default constructor and destructor, which is beneficial to optimization.
// But if the constructor and destructor of the allocator are not default, then the allocator cannot be used.
template<typename T>
struct is_default_allocator : std::false_type {};

template<typename T>
struct is_default_allocator<std::allocator<T>> : std::true_type {};

template<typename T>
constexpr bool is_default_allocator_v = is_default_allocator<T>::value;

WJR_REGISTER_HAS_MEMBER_FUNCTION(destroy, destroy);
WJR_REGISTER_HAS_MEMBER_FUNCTION(construct, construct);

// Use the default destructor, which is beneficial for optimization.
// But if the destructor of the allocator has side effects, then do not use this allocator.

template<typename Alloc, typename Iter, typename...Args>
struct is_default_allocator_construct : std::disjunction<is_default_allocator<Alloc>,
	std::negation<has_member_function_construct<Alloc, iter_address_t<Iter>, Args...>>> {};

template<typename Alloc, typename Iter, typename...Args>
constexpr bool is_default_allocator_construct_v = is_default_allocator_construct<Alloc, Iter, Args...>::value;

template<typename Alloc, typename Iter>
struct is_default_allocator_destroy : std::disjunction<is_default_allocator<Alloc>,
	std::negation<has_member_function_destroy<Alloc, iter_address_t<Iter>>>> {};

template<typename Alloc, typename Iter>
constexpr bool is_default_allocator_destroy_v = is_default_allocator_destroy<Alloc, Iter>::value;

_WJR_END

namespace std {
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(begin, begin);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(cbegin, cbegin);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(end, end);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(cend, cend);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(rbegin, rbegin);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(crbegin, crbegin);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(rend, rend);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(crend, crend);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(data, data);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(size, size);
	WJR_REGISTER_HAS_MEMBER_FUNCTION(size, size);
	WJR_REGISTER_HAS_GLOBAL_FUNCTION(swap, swap);
}

_WJR_BEGIN

template<typename _Container>
constexpr auto size(const _Container& c) {
	if constexpr (std::has_member_function_size_v<_Container>) {
		return c.size();
	}
	else {
		return std::distance(std::begin(c), std::end(c));
	}
}

template<typename _Ty, size_t _Size>
constexpr size_t size(const _Ty(&)[_Size]) noexcept {
	return _Size;
}

_WJR_END

#endif

_WJR_BEGIN

// using empty base optimization

template<size_t index, typename T>
struct _Pair_wrapper1 {
	template<typename _Ty = T, std::enable_if_t<std::is_default_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper1() noexcept(std::is_nothrow_default_constructible_v<_Ty>)
		: val() {}
	template<typename _Ty = T, std::enable_if_t<std::is_copy_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper1(const _Ty& other) noexcept(std::is_nothrow_copy_constructible_v<_Ty>)
		: val(other) {}
	template<typename _Ty = T, std::enable_if_t<std::is_move_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper1(_Ty&& other) noexcept(std::is_nothrow_move_constructible_v<_Ty>)
		: val(std::forward<_Ty>(other)) {}
	template<typename...Args, std::enable_if_t<std::is_constructible_v<T, Args...>, int> = 0>
	constexpr _Pair_wrapper1(Args&&...args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
		: val(std::forward<Args>(args)...) {}
	_Pair_wrapper1(const _Pair_wrapper1&) = default;
	_Pair_wrapper1(_Pair_wrapper1&&) noexcept = default;
	_Pair_wrapper1& operator=(const _Pair_wrapper1&) = default;
	_Pair_wrapper1& operator=(_Pair_wrapper1&&) noexcept = default;
	constexpr T& value() noexcept { return val; }
	constexpr const T& value() const noexcept { return val; }
private:
	T val;
};

template<size_t index, typename T>
struct _Pair_wrapper2 : private T {
	using _Mybase = T;
	template<typename _Ty = T, std::enable_if_t<std::is_default_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper2() noexcept(std::is_nothrow_default_constructible_v<_Ty>)
		: _Mybase() {}
	template<typename _Ty = T, std::enable_if_t<std::is_copy_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper2(const _Ty& other) noexcept(std::is_nothrow_copy_constructible_v<_Ty>)
		: _Mybase(other) {}
	template<typename _Ty = T, std::enable_if_t<std::is_move_constructible_v<_Ty>, int> = 0>
	constexpr _Pair_wrapper2(_Ty&& other) noexcept(std::is_nothrow_move_constructible_v<_Ty>)
		: _Mybase(std::forward<_Ty>(other)) {}
	template<typename...Args, std::enable_if_t<std::is_constructible_v<T, Args...>, int> = 0>
	constexpr _Pair_wrapper2(Args&&...args) noexcept(std::is_nothrow_constructible_v<T, Args...>)
		: _Mybase(std::forward<Args>(args)...) {}
	_Pair_wrapper2(const _Pair_wrapper2&) = default;
	_Pair_wrapper2(_Pair_wrapper2&&) noexcept = default;
	_Pair_wrapper2& operator=(const _Pair_wrapper2&) = default;
	_Pair_wrapper2& operator=(_Pair_wrapper2&&) noexcept = default;
	constexpr T& value() noexcept { return *this; }
	constexpr const T& value() const noexcept { return *this; }
};

template<size_t index, typename T>
using _Pair_wrapper = std::conditional_t<
	std::conjunction_v<std::is_class<T>, std::is_empty<T>, std::negation<std::is_final<T>>>,
	_Pair_wrapper2<index, T>,
	_Pair_wrapper1<index, T>
>;

template<typename T, typename U>
class pair : private _Pair_wrapper<0, T>, private _Pair_wrapper<1, U> {

	template<typename _Ty, typename _Uy>
	using _Is_default_constructible = std::conjunction <
		std::is_default_constructible<_Ty>,
		std::is_default_constructible<_Uy>>;
	template<typename _Ty, typename _Uy>
	using _Is_default_convertible = std::conjunction <
		is_default_convertible<_Ty>,
		is_default_convertible<_Uy>>;

	template<typename _Ty, typename _Uy>
	using _Is_copy_constructible = std::conjunction <
		std::is_copy_constructible<_Ty>,
		std::is_copy_constructible<_Uy>>;

	template<typename _Ty, typename _Uy, typename _Vty, typename _Wuy>
	using _Is_convertible = std::conjunction <
		std::is_convertible<_Vty, _Ty>,
		std::is_convertible<_Wuy, _Uy>>;

	template<typename _Ty, typename _Uy, typename _Vty, typename _Wuy>
	using _Is_constructible = std::conjunction<
		std::is_constructible<_Ty, _Vty>,
		std::is_constructible<_Uy, _Wuy>>;

public:
	using _Mybase1 = _Pair_wrapper<0, T>;
	using _Mybase2 = _Pair_wrapper<1, U>;

	using first_type = T;
	using second_type = U;

	template<typename _Ty = T, typename _Uy = U, std::enable_if_t<
		std::conjunction_v<_Is_default_constructible<_Ty, _Uy>,
		_Is_default_convertible<_Ty, _Uy>>, bool> = true>
		constexpr pair() noexcept(std::conjunction_v<std::is_nothrow_default_constructible<_Ty>,
			std::is_nothrow_default_constructible<_Uy>>)
		: _Mybase1(), _Mybase2() {}

	template<typename _Ty = T, typename _Uy = U, std::enable_if_t<
		std::conjunction_v<_Is_default_constructible<_Ty, _Uy>,
		std::negation<_Is_default_convertible<_Ty, _Uy>>>, bool> = false>
	constexpr explicit pair() noexcept(std::conjunction_v<std::is_nothrow_default_constructible<_Ty>,
		std::is_nothrow_default_constructible<_Uy>>)
		: _Mybase1(), _Mybase2() {}

	template<typename _Ty = T, typename _Uy = U, std::enable_if_t<
		std::conjunction_v<_Is_copy_constructible<_Ty, _Uy>,
		_Is_convertible<_Ty, _Uy, const _Ty&, const _Uy&>>, bool> = true>
		constexpr pair(const T& _First, const U& _Second)
		noexcept(std::conjunction_v<std::is_nothrow_copy_constructible<_Ty>, std::is_nothrow_copy_constructible<_Uy>>)
		: _Mybase1(_First), _Mybase2(_Second) {}

	template<typename _Ty = T, typename _Uy = U, std::enable_if_t<
		std::conjunction_v<_Is_copy_constructible<_Ty, _Uy>,
		std::negation<_Is_convertible<_Ty, _Uy, const _Ty&, const _Uy&>>>, bool> = false>
	constexpr explicit pair(const T& _First, const U& _Second)
		noexcept(std::conjunction_v<std::is_nothrow_copy_constructible<_Ty>, std::is_nothrow_copy_constructible<_Uy>>)
		: _Mybase1(_First), _Mybase2(_Second) {}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, _Other1, _Other2>,
		_Is_convertible<T, U, _Other1, _Other2>>, bool> = true>
		constexpr pair(_Other1&& _First, _Other2&& _Second)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, _Other1>, std::is_nothrow_constructible<U, _Other2>>)
		: _Mybase1(std::forward<_Other1>(_First)), _Mybase2(std::forward<_Other2>(_Second)) {}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, _Other1, _Other2>,
		std::negation<_Is_convertible<T, U, _Other1, _Other2>>>, bool> = false>
	constexpr explicit pair(_Other1&& _First, _Other2&& _Second)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, _Other1>, std::is_nothrow_constructible<U, _Other2>>)
		: _Mybase1(std::forward<_Other1>(_First)), _Mybase2(std::forward<_Other2>(_Second)) {}

	pair(const pair&) = default;
	pair(pair&&) noexcept = default;

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, const _Other1&, const _Other2&>,
		_Is_convertible<T, U, const _Other1&, const _Other2&>>, bool> = true>
		constexpr pair(const pair<_Other1, _Other2>& other)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, const _Other1&>, std::is_nothrow_constructible<U, const _Other2&>>)
		: _Mybase1(other.first()), _Mybase2(other.second()) {}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, const _Other1&, const _Other2&>,
		std::negation<_Is_convertible<T, U, const _Other1&, const _Other2&>>>, bool> = false>
	constexpr explicit pair(const pair<_Other1, _Other2>& other)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, const _Other1&>, std::is_nothrow_constructible<U, const _Other2&>>)
		: _Mybase1(other.first()), _Mybase2(other.second()) {}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, _Other1, _Other2>,
		_Is_convertible<T, U, _Other1, _Other2>>, bool> = true>
		constexpr pair(pair<_Other1, _Other2>&& other)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, _Other1>, std::is_nothrow_constructible<U, _Other2>>)
		: _Mybase1(std::forward<_Other1>(other.first())), _Mybase2(std::forward<_Other2>(other.second())) {}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<_Is_constructible<T, U, _Other1, _Other2>,
		std::negation<_Is_convertible<T, U, _Other1, _Other2>>>, bool> = false>
	constexpr explicit pair(pair<_Other1, _Other2>&& other)
		noexcept(std::conjunction_v<std::is_nothrow_constructible<T, _Other1>, std::is_nothrow_constructible<U, _Other2>>)
		: _Mybase1(std::forward<_Other1>(other.first())), _Mybase2(std::forward<_Other2>(other.second())) {}

	template<typename _Tuple1, typename _Tuple2, size_t...N1, size_t...N2>
	constexpr pair(_Tuple1& tp1, _Tuple2& tp2, std::index_sequence<N1...>, std::index_sequence<N2...>)
		: _Mybase1(std::get<N1>(std::move(tp1))...), _Mybase2(std::get<N2>(std::move(tp2))...) {}

	template<typename...Args1, typename...Args2>
	constexpr pair(std::piecewise_construct_t, std::tuple<Args1...> tp1, std::tuple<Args2...> tp2)
		: pair(tp1, tp2, std::index_sequence_for<Args1...>{}, std::index_sequence_for<Args2...>{}) {}

	constexpr pair&
		operator=(std::conditional_t<std::conjunction_v<std::is_copy_assignable<T>,
			std::is_copy_assignable<U>>, const pair&, const wjr::disable_tag&> other)
		noexcept(std::conjunction_v<std::is_nothrow_copy_assignable<T>, std::is_nothrow_copy_assignable<U>>) {
		first() = other.first();
		second() = other.second();
		return *this;
	}

	constexpr pair&
		operator=(std::conditional_t<std::conjunction_v<std::is_move_assignable<T>,
			std::is_move_assignable<U>>, pair&&, wjr::disable_tag&&> other)
		noexcept(std::conjunction_v<std::is_nothrow_move_assignable<T>, std::is_nothrow_move_assignable<U>>) {
		first() = std::forward<T>(other.first());
		second() = std::forward<U>(other.second());
		return *this;
	}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<std::negation<std::is_same<pair, pair<_Other1, _Other2>>>,
		std::is_assignable<T&, const _Other1&>,
		std::is_assignable<U&, const _Other2&>>, int> = 0>
		constexpr pair& operator=(const pair<_Other1, _Other2>& other)
		noexcept(std::conjunction_v<std::is_nothrow_assignable<T&, const _Other1&>,
			std::is_nothrow_assignable<U&, const _Other2&>>) {
		first() = other.first();
		second() = other.second();
		return *this;
	}

	template<typename _Other1, typename _Other2, std::enable_if_t<
		std::conjunction_v<std::negation<std::is_same<pair, pair<_Other1, _Other2>>>,
		std::is_assignable<T&, _Other1>,
		std::is_assignable<U&, _Other2>>, int> = 0>
		constexpr pair& operator=(pair<_Other1, _Other2>&& other)
		noexcept(std::conjunction_v<std::is_nothrow_assignable<T&, _Other1>,
			std::is_nothrow_assignable<U&, _Other2>>) {
		first() = std::forward<_Other1>(other.first());
		second() = std::forward<_Other2>(other.second());
		return *this;
	}

	constexpr void swap(pair& other)
		noexcept(std::conjunction_v<is_nothrow_swappable<T>, is_nothrow_swappable<U>>) {
		using std::swap;
		swap(first(), other.first());
		swap(second(), other.second());
	}

	constexpr T& first() noexcept { return _Mybase1::value(); }
	constexpr const T& first() const noexcept { return _Mybase1::value(); }
	constexpr U& second() noexcept { return _Mybase2::value(); }
	constexpr const U& second() const noexcept { return _Mybase2::value(); }
};

#ifdef WJR_CPP17
template<typename T, typename U>
pair(T, U) -> pair<T, U>;
#endif

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return lhs.first() == rhs.first() && lhs.second() == rhs.second();
}

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return !(lhs == rhs);
}

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return lhs.first() < rhs.first() || (!(rhs.first() < lhs.first()) && lhs.second() < rhs.second());
}

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return rhs < lhs;
}

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return !(rhs < lhs);
}

template<typename T, typename U>
WJR_NODISCARD constexpr bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
	return !(lhs < rhs);
}

template<typename T, typename U>
WJR_NODISCARD constexpr pair<unrefwrap_t<T>, unrefwrap_t<U>> make_pair(T&& t, U&& u)
noexcept(std::conjunction_v<std::is_nothrow_constructible<unrefwrap_t<T>, T>,
	std::is_nothrow_constructible<unrefwrap_t<U>, U>>) {
	return pair<unrefwrap_t<T>, unrefwrap_t<U>>(std::forward<T>(t), std::forward<U>(u));
}

_WJR_END

namespace std {

	template<typename T, typename U>
	using _Wjr_pair = wjr::pair<T, U>;

	template<typename T, typename U, enable_if_t<conjunction_v<wjr::is_swappable<T>, wjr::is_swappable<U>>, int> = 0>
	void swap(_Wjr_pair<T, U>& lhs, _Wjr_pair<T, U>& rhs)
		noexcept(noexcept(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}
	template<typename T, typename U>
	struct tuple_size<_Wjr_pair<T, U>> : integral_constant<size_t, 2> {};

	template<size_t I, typename T, typename U>
	struct tuple_element<I, _Wjr_pair<T, U>> {
		static_assert(I < 2, "tuple_element index out of bounds");
		using type = conditional_t<I == 0, T, U>;
	};

	template<typename _Ret, typename _Pair>
	WJR_NODISCARD constexpr _Ret& _Wjr_pair_get(_Pair& p, integral_constant<size_t, 0>) noexcept {
		return p.first();
	}

	template<typename _Ret, typename _Pair>
	WJR_NODISCARD constexpr _Ret& _Wjr_pair_get(_Pair& p, integral_constant<size_t, 1>) noexcept {
		return p.second();
	}

	template<size_t I, typename T, typename U>
	WJR_NODISCARD constexpr tuple_element_t<I, _Wjr_pair<T, U>>& get(_Wjr_pair<T, U>& p) noexcept {
		using _Ret = tuple_element_t<I, _Wjr_pair<T, U>>&;
		return _Wjr_pair_get<_Ret>(p, integral_constant<size_t, I>{});
	}

	template<typename T, typename U>
	WJR_NODISCARD constexpr T& get(_Wjr_pair<T, U>& p) noexcept {
		return get<0>(p);
	}

	template<typename U, typename T>
	WJR_NODISCARD constexpr U& get(_Wjr_pair<T, U>& p) noexcept {
		return get<1>(p);
	}

	template<size_t I, typename T, typename U>
	WJR_NODISCARD constexpr const tuple_element_t<I, _Wjr_pair<T, U>>& get(const _Wjr_pair<T, U>& p) noexcept {
		using _Ret = const tuple_element_t<I, _Wjr_pair<T, U>>&;
		return _Wjr_pair_get<_Ret>(p, integral_constant<size_t, I>{});
	}

	template<typename T, typename U>
	WJR_NODISCARD constexpr const T& get(const _Wjr_pair<T, U>& p) noexcept {
		return get<0>(p);
	}

	template<typename U, typename T>
	WJR_NODISCARD constexpr const U& get(const _Wjr_pair<T, U>& p) noexcept {
		return get<1>(p);
	}


	template <size_t I, typename T, typename U>
	WJR_NODISCARD constexpr tuple_element_t<I, _Wjr_pair<T, U>>&& get(
		_Wjr_pair<T, U>&& p) noexcept {
		using _RRtype = tuple_element_t<I, _Wjr_pair<T, U>>&&;
		return forward<_RRtype>(get<I>(p));
	}

	template <typename T, typename U>
	WJR_NODISCARD constexpr T&& get(_Wjr_pair<T, U>&& p) noexcept {
		return get<0>(move(p));
	}

	template <typename U, typename T>
	WJR_NODISCARD constexpr U&& get(_Wjr_pair<T, U>&& p) noexcept {
		return get<1>(move(p));
	}

	template <size_t I, typename T, typename U>
	WJR_NODISCARD constexpr const tuple_element_t<I, _Wjr_pair<T, U>>&& get(
		const _Wjr_pair<T, U>&& p) noexcept {
		using _RRtype = const tuple_element_t<I, _Wjr_pair<T, U>>&&;
		return forward<_RRtype>(get<I>(p));
	}

	template <typename T, typename U>
	WJR_NODISCARD constexpr const T&& get(
		const _Wjr_pair<T, U>&& p) noexcept {
		return get<0>(move(p));
	}

	template <typename U, typename T>
	WJR_NODISCARD constexpr const U&& get(
		const _Wjr_pair<T, U>&& p) noexcept {
		return get<1>(move(p));
	}

}

#endif // __WJR_COMPRESSED_PAIR_H
#pragma once
#ifndef __WJR_ALGORITHM_H__
#define __WJR_ALGORITHM_H__

#include <algorithm>
#include <memory>
#include <limits>
#include <cstring>

#pragma once
#ifndef __WJR_ALGO_ALOG_H
#define __WJR_ALGO_ALOG_H

#pragma once
#ifndef __WJR_OPTIMIZER_H
#define __WJR_OPTIMIZER_H

// 1. fill dst with val (memset)
// The minimum cycle section length must be 1, 2, 4, 8 when _WJR_FAST_MEMSET defined
// and must be 1 when NWJR_FAST_MEMSET defined
// Get the bytes to be filled through the get function
// 2. copy src to dst (memcpy)

// TODO 
// 1. fill a constant value when default-construct (memset)
// 2. fill a constant value when value-cosntruct (memset)
// 3. relocate , copy src to dst, and then fill dst with a constant value (memcpy and memset)
// 4. reloacte , copy src to dst, and then run a function on dst (memcpy and run func(User defined))



_WJR_BEGIN

template<size_t N>
constexpr size_t _Get_max_bytes_num() {
#if defined(WJR_X86_64)
	if constexpr (N % 8 == 0)return 8;
	else
#endif
		if constexpr (N % 4 == 0)return 4;
		else if constexpr (N % 2 == 0)return 2;
		else return 1;
}

template<size_t C, typename _Ty>
size_t _Get_bytes_num(const _Ty& val) {
	constexpr size_t N = sizeof(_Ty);
	constexpr size_t M = _Get_max_bytes_num<C>();
	const auto ptr = reinterpret_cast<const uint8_t*>(&val);
	if constexpr (N == C) {
		if constexpr (N == 1) {
			return 1;
		}
		else if constexpr (N == 2) {
			return (ptr[0] == ptr[1]) ? 1 : 2;
		}
		else if constexpr (N == 3) {
			return (*reinterpret_cast<const uint16_t*>(ptr) == *reinterpret_cast<const uint16_t*>(ptr + 1)) ? 1 : 0;
		}
		else if constexpr (N == 4) {
			auto x = *reinterpret_cast<const uint32_t*>(ptr);
			return ((x >> 8) == (x & 0x00FFFFFF)) ? 1 : 4;
		}
		else if constexpr (N == 5) {
			return (*reinterpret_cast<const uint32_t*>(ptr) == *reinterpret_cast<const uint32_t*>(ptr + 1)) ? 1 : 0;
		}
		else if constexpr (N == 6) {
			return (*reinterpret_cast<const uint32_t*>(ptr) == *reinterpret_cast<const uint32_t*>(ptr + 2)) ? 2 : 6;
		}
		else if constexpr (N == 7) {
			auto x = *reinterpret_cast<const uint32_t*>(ptr);
			auto y = *reinterpret_cast<const uint32_t*>(ptr + 4);
			return ((x >> 8) == (x & 0x00FFFFFF)) && ((y >> 8) == (y & 0x00FFFFFF)) ? 1 : 0;
		}
		else if constexpr (N == 8) {
			auto x = *reinterpret_cast<const uint64_t*>(ptr);
			return ((x >> 8) == (x & 0x00FFFFFFFFFFFFFF)) ? 1 : 8;
		}
		else {
			if (!is_constant_p(val)) {
				return 0;
			}
			else {
				for (size_t i = 0; i < N - M; ++i) {
					if (ptr[i] != ptr[i + M]) {
						return 0;
					}
				}
				for (size_t i = 0; i < M - 1; ++i) {
					if (ptr[i] != ptr[i + 1]) {
						return M;
					}
				}
				return 1;
			}
		}
	}
	else {
		// all zeros
		if constexpr (N <= 8) {
			constexpr uint8_t zero[8] = { 0,0,0,0,0,0,0,0 };
			return ::memcmp(ptr, zero, N) == 0 ? 1 : 0;
		}
		else {
			if (!is_constant_p(val)) {
				return 0;
			}
			else {
				for (size_t i = 0; i < N; ++i) {
					if (ptr[i] != 0) {
						return 0;
					}
				}
				return 1;
			}
		}
	}
}

template<typename T, typename U,
	bool =
	std::is_same_v<bool, std::remove_reference_t<U>> >= std::is_same_v<bool, T> &&
	((std::is_integral_v<T>&& std::is_integral_v<std::remove_reference_t<U>>) ||
		(std::is_floating_point_v<T> && std::is_floating_point_v<std::remove_reference_t<U>>)) &&
	!std::is_volatile_v<T> &&
	!std::is_volatile_v<std::remove_reference_t<U>>
>
struct __is_byte_constructible {
	constexpr static bool is_copy = sizeof(T) == sizeof(U);
	constexpr static bool is_fill = true;
	constexpr static T get(const U& val) {
		return static_cast<T>(val);
	}
};

template<typename T, bool =
	std::is_trivially_copyable_v<T> &&
	!std::is_volatile_v<T>>
	struct __is_byte_copy_constructible_helper {
	constexpr static bool is_copy = true;
	constexpr static bool is_fill = !std::is_empty_v<T>;
	constexpr static const T& get(const T& val) {
		return val;
	}
};

template<typename T>
struct __is_byte_copy_constructible_helper<T, false> {
	constexpr static bool is_copy = false;
	constexpr static bool is_fill = false;
};

template<typename T, bool =
	std::is_trivially_copyable_v<T> &&
	!std::is_volatile_v<T>>
	struct __is_byte_move_constructible_helper {
	constexpr static bool is_copy = true;
	constexpr static bool is_fill = !std::is_empty_v<T>;
	constexpr static const T& get(const T& val) {
		return val;
	}
};

template<typename T>
struct __is_byte_move_constructible_helper<T, false> {
	constexpr static bool is_copy = false;
	constexpr static bool is_fill = false;
};

template<typename T, typename U>
struct __is_byte_constructible<T, U, false> {
	constexpr static bool is_copy = false;
	constexpr static bool is_fill = false;
};

template<typename T>
struct __is_byte_constructible<T, T, false> : __is_byte_copy_constructible_helper<T> {};

template<typename T>
struct __is_byte_constructible<T, const T, false> : __is_byte_copy_constructible_helper<T> {};

template<typename T>
struct __is_byte_constructible<T, T&, false> : __is_byte_copy_constructible_helper<T> {};

template<typename T>
struct __is_byte_constructible<T, const T&, false> : __is_byte_copy_constructible_helper<T> {};

template<typename T>
struct __is_byte_constructible<T, T&&, false> : __is_byte_move_constructible_helper<T> {};

template<typename T, typename U>
struct is_byte_constructible : __is_byte_constructible<std::remove_reference_t<T>, U> {};

template<typename T, typename U>
struct is_byte_assignable : __is_byte_constructible<std::remove_reference_t<T>, U> {};

_WJR_END

#endif // __WJR_OPTIMIZER_H

#pragma once



_WJR_LITERALS_BEGIN

constexpr unsigned long long operator"" _KiB(unsigned long long n) {
	return n * 1024;
}

constexpr unsigned long long operator"" _MiB(unsigned long long n) {
	return n * 1024 * 1024;
}

constexpr unsigned long long operator"" _GiB(unsigned long long n) {
	return n * 1024 * 1024 * 1024;
}

constexpr unsigned long long operator""_KB(unsigned long long n) {
	return n * 1000;
}

constexpr unsigned long long operator""_MB(unsigned long long n) {
	return n * 1000 * 1000;
}

constexpr unsigned long long operator""_GB(unsigned long long n) {
	return n * 1000 * 1000 * 1000;
}

_WJR_LITERALS_END
#pragma once
#ifndef __WJR_SIMD_SIMD_INTRIN_H
#define __WJR_SIMD_SIMD_INTRIN_H

#pragma once
#ifndef __WJR_SIMD_SIMD_CAST_H__
#define __WJR_SIMD_SIMD_CAST_H__



_WJR_SIMD_BEGIN

struct lo {};
struct hi {};

template<typename T, typename U>
WJR_INTRINSIC_INLINE T simd_cast(U);

/* TODO */
template<typename T1, typename T2, typename U>
WJR_INTRINSIC_INLINE U simd_cast(U, T2);

#if WJR_SSE
#endif // WJR_SSE

#if WJR_SSE2

template<>
WJR_INTRINSIC_INLINE __m128 simd_cast<__m128>(__m128i v) {
	return _mm_castsi128_ps(v);
}
template<>
WJR_INTRINSIC_INLINE __m128i simd_cast<__m128i>(__m128 v) {
	return _mm_castps_si128(v);
}
template<>
WJR_INTRINSIC_INLINE __m128d simd_cast<__m128d>(__m128 v) {
	return _mm_castps_pd(v);
}
template<>
WJR_INTRINSIC_INLINE __m128 simd_cast<__m128>(__m128d v) {
	return _mm_castpd_ps(v);
}
template<>
WJR_INTRINSIC_INLINE __m128i simd_cast<__m128i>(__m128d v) {
	return _mm_castpd_si128(v);
}
template<>
WJR_INTRINSIC_INLINE __m128d simd_cast<__m128d>(__m128i v) {
	return _mm_castsi128_pd(v);
}

#define __WJR_REGISTER_SIMD_CAST_WITH_INTEGER(IT, SUF)	            \
template<>	                                                        \
WJR_INTRINSIC_INLINE IT simd_cast<IT>(__m128i v){	                \
	return static_cast<IT>(_mm_cvtsi128_si##SUF(v));	            \
}	                                                                \
template<>	                                                        \
WJR_INTRINSIC_INLINE __m128i simd_cast<__m128i>(IT v){	            \
	return _mm_cvtsi##SUF##_si128(v);	                            \
}

__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int8_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int16_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int32_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int64_t, 64);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint8_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint16_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint32_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint64_t, 64);

#undef __WJR_REGISTER_SIMD_CAST_WITH_INTEGER

#endif // WJR_SSE2

#if WJR_AVX2

template<>
WJR_INTRINSIC_INLINE __m256 simd_cast<__m256>(__m256i v) {
	return _mm256_castsi256_ps(v);
}
template<>
WJR_INTRINSIC_INLINE __m256i simd_cast<__m256i>(__m256 v) {
	return _mm256_castps_si256(v);
}
template<>
WJR_INTRINSIC_INLINE __m256d simd_cast<__m256d>(__m256 v) {
	return _mm256_castps_pd(v);
}
template<>
WJR_INTRINSIC_INLINE __m256 simd_cast<__m256>(__m256d v) {
	return _mm256_castpd_ps(v);
}
template<>
WJR_INTRINSIC_INLINE __m256i simd_cast<__m256i>(__m256d v) {
	return _mm256_castpd_si256(v);
}
template<>
WJR_INTRINSIC_INLINE __m256d simd_cast<__m256d>(__m256i v) {
	return _mm256_castsi256_pd(v);
}

template<>
WJR_INTRINSIC_INLINE __m256i simd_cast<__m256i>(__m128i v) {
	return _mm256_castsi128_si256(v);
}

template<>
WJR_INTRINSIC_INLINE __m128i simd_cast<__m128i>(__m256i v) {
	return _mm256_castsi256_si128(v);
}

#define __WJR_REGISTER_SIMD_CAST_WITH_INTEGER(IT, SUF)	            \
template<>	                                                        \
WJR_INTRINSIC_INLINE IT simd_cast<IT>(__m256i v){	                \
	return simd_cast<IT>(simd_cast<__m128i>(v));					\
}	                                                                \
template<>	                                                        \
WJR_INTRINSIC_INLINE __m256i simd_cast<__m256i>(IT v){	            \
	return simd_cast<__m256i>(simd_cast<__m128i>(v));				\
}

__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int8_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int16_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int32_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(int64_t, 64);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint8_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint16_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint32_t, 32);
__WJR_REGISTER_SIMD_CAST_WITH_INTEGER(uint64_t, 64);

#undef __WJR_REGISTER_SIMD_CAST_WITH_INTEGER

#endif // WJR_AVX

_WJR_SIMD_END

#endif // __WJR_SIMD_SIMD_CAST_H__

_WJR_SIMD_BEGIN

#if WJR_SSE2

WJR_INTRINSIC_INLINE static __m128i mm_loadu_si16(void const* p);

WJR_INTRINSIC_INLINE static __m128i mm_loadu_si32(void const* p);

WJR_INTRINSIC_INLINE static __m128i mm_loadu_si64(void const* p);

#endif // WJR_SSE2

struct sse {
	using mask_type = uint16_t;
#if WJR_SSE
	using float_type = __m128;
#endif // WJR_SSE
#if WJR_SSE2
	using int_type = __m128i;
	using double_type = __m128d;
#endif // WJR_SSE2

	constexpr static size_t width();

	constexpr static mask_type mask();

#if WJR_SSE
	WJR_INTRINSIC_INLINE static mask_type movemask_ps(__m128 v);

	WJR_INTRINSIC_INLINE static void sfence();

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128 shuffle_ps(__m128 a, __m128 b);
#endif // WJR_SSE

#if WJR_SSE2

	WJR_INTRINSIC_INLINE static __m128i add_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i add_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i add_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i add_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i add(__m128i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static int8_t add_epi8(__m128i a);
	WJR_INTRINSIC_INLINE static int16_t add_epi16(__m128i a);
	WJR_INTRINSIC_INLINE static int32_t add_epi32(__m128i a);
	WJR_INTRINSIC_INLINE static int64_t add_epi64(__m128i a);

	WJR_INTRINSIC_INLINE static uint8_t add_epu8(__m128i a);
	WJR_INTRINSIC_INLINE static uint16_t add_epu16(__m128i a);
	WJR_INTRINSIC_INLINE static uint32_t add_epu32(__m128i a);
	WJR_INTRINSIC_INLINE static uint64_t add_epu64(__m128i a);

	WJR_INTRINSIC_INLINE static int8_t add(__m128i a, int8_t);
	WJR_INTRINSIC_INLINE static int16_t add(__m128i a, int16_t);
	WJR_INTRINSIC_INLINE static int32_t add(__m128i a, int32_t);
	WJR_INTRINSIC_INLINE static int64_t add(__m128i a, int64_t);
	WJR_INTRINSIC_INLINE static uint8_t add(__m128i a, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t add(__m128i a, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t add(__m128i a, uint32_t);
	WJR_INTRINSIC_INLINE static uint64_t add(__m128i a, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i adds_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i adds_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i adds_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i adds_epu16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i adds(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i adds(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i adds(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i adds(__m128i a, __m128i b, uint16_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i alignr_epi16(__m128i a, __m128i b, int c);
	WJR_INTRINSIC_INLINE static __m128i alignr_epi32(__m128i a, __m128i b, int c);
	WJR_INTRINSIC_INLINE static __m128i alignr_epi64(__m128i a, __m128i b, int c);

	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, int16_t);
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, int32_t);
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, int64_t);
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i alignr(__m128i a, __m128i b, int c, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i And(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i AndNot(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i avg_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i avg_epu16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i avg(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i avg(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i avg(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i avg(__m128i a, __m128i b, uint16_t);

	// notice that mask must be 0 or 255(every byte)
	WJR_INTRINSIC_INLINE static __m128i blendv_epi8(__m128i a, __m128i b, __m128i mask);
	WJR_INTRINSIC_INLINE static __m128i blendv_epi16(__m128i a, __m128i b, __m128i mask);
	WJR_INTRINSIC_INLINE static __m128i blendv_epi32(__m128i a, __m128i b, __m128i mask);

	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, int8_t);
	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, int16_t);
	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, int32_t);
	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i blendv(__m128i a, __m128i b, __m128i mask, uint32_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i bslli(__m128i val);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i bsrli(__m128i val);

	WJR_INTRINSIC_INLINE static __m128i cmpeq_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpeq_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpeq_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i cmpge_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpge_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpge_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpge_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpge_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpge_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpge(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i cmpgt_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpgt_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpgt_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpgt_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpgt_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpgt_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i cmple_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmple_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmple_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmple_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmple_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmple_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmple(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i cmplt_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmplt_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmplt_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmplt_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmplt_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmplt_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmplt(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i cmpne_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpne_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i cmpne_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i cmpne(__m128i a, __m128i b, uint32_t);

	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::equal_to<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::not_equal_to<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::greater<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::greater_equal<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::less<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m128i cmp(__m128i a, __m128i b, std::less_equal<>, T);

	WJR_INTRINSIC_INLINE static __m128i concat(uint64_t lo, uint64_t hi);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi8(__m128i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi16(__m128i a);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi32(__m128i a);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int64_t extract_epi64(__m128i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, int8_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, int16_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, int32_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int64_t extract(__m128i a, int64_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, uint8_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, uint16_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m128i a, uint32_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int64_t extract(__m128i a, uint64_t);

	WJR_INTRINSIC_INLINE static uint64_t getlow(__m128i v);
	WJR_INTRINSIC_INLINE static uint64_t gethigh(__m128i v);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert_epi16(__m128i a, int i);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, int16_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, uint16_t);

	WJR_INTRINSIC_INLINE static void lfence();

	WJR_INTRINSIC_INLINE static __m128i load(const __m128i* ptr);
	WJR_INTRINSIC_INLINE static __m128i loadu(const __m128i* ptr);
	WJR_INTRINSIC_INLINE static __m128i loadu_si16(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i loadu_si32(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i loadu_si64(const void* ptr);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m128i logical_and(__m128i a, __m128i b, T);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m128i logical_not(__m128i v, T);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m128i logical_or(__m128i a, __m128i b, T);

	WJR_INTRINSIC_INLINE static __m128i madd_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static void maskmoveu(__m128i a, __m128i mask, char* mem_addr);

	WJR_INTRINSIC_INLINE static __m128i max_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i max_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i max_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i max_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i max_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i max_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i max(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static int8_t max_epi8(__m128i a);
	WJR_INTRINSIC_INLINE static int16_t max_epi16(__m128i a);
	WJR_INTRINSIC_INLINE static int32_t max_epi32(__m128i a);

	WJR_INTRINSIC_INLINE static uint8_t max_epu8(__m128i a);
	WJR_INTRINSIC_INLINE static uint16_t max_epu16(__m128i a);
	WJR_INTRINSIC_INLINE static uint32_t max_epu32(__m128i a);

	WJR_INTRINSIC_INLINE static int8_t max(__m128i a, int8_t);
	WJR_INTRINSIC_INLINE static int16_t max(__m128i a, int16_t);
	WJR_INTRINSIC_INLINE static int32_t max(__m128i a, int32_t);
	WJR_INTRINSIC_INLINE static uint8_t max(__m128i a, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t max(__m128i a, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t max(__m128i a, uint32_t);

	WJR_INTRINSIC_INLINE static void mfence();

	WJR_INTRINSIC_INLINE static __m128i min_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i min_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i min_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i min_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i min_epu16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i min_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i min(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static int8_t min_epi8(__m128i a);
	WJR_INTRINSIC_INLINE static int16_t min_epi16(__m128i a);
	WJR_INTRINSIC_INLINE static int32_t min_epi32(__m128i a);

	WJR_INTRINSIC_INLINE static uint8_t min_epu8(__m128i a);
	WJR_INTRINSIC_INLINE static uint16_t min_epu16(__m128i a);
	WJR_INTRINSIC_INLINE static uint32_t min_epu32(__m128i a);

	WJR_INTRINSIC_INLINE static int8_t min(__m128i a, int8_t);
	WJR_INTRINSIC_INLINE static int16_t min(__m128i a, int16_t);
	WJR_INTRINSIC_INLINE static int32_t min(__m128i a, int32_t);

	WJR_INTRINSIC_INLINE static uint8_t min(__m128i a, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t min(__m128i a, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t min(__m128i a, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i move_epi64(__m128i a);

	WJR_INTRINSIC_INLINE static mask_type movemask_epi8(__m128i a);
	WJR_INTRINSIC_INLINE static mask_type movemask_pd(__m128d v);

	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, int8_t);
	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, int32_t);
	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, int64_t);

	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, uint8_t);
	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, uint32_t);
	WJR_INTRINSIC_INLINE static mask_type movemask(__m128i v, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i mul_epu32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i mulhi_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i mulhi_epu16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i mullo_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i negate_epi8(__m128i a);
	WJR_INTRINSIC_INLINE static __m128i negate_epi16(__m128i a);
	WJR_INTRINSIC_INLINE static __m128i negate_epi32(__m128i a);
	WJR_INTRINSIC_INLINE static __m128i negate_epi64(__m128i a);

	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, int8_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, int16_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, int32_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, int64_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i negate(__m128i a, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i Not(__m128i v);

	WJR_INTRINSIC_INLINE static __m128i Or(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i packs_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i packs_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i packus_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i preloadu_si16(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si32(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si48(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si64(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si80(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si96(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si112(const void* ptr);
	WJR_INTRINSIC_INLINE static __m128i preloadu_si128(const void* ptr);

	WJR_INTRINSIC_INLINE static __m128i preloadu_si16x(const void* ptr, int n);

	WJR_INTRINSIC_INLINE static __m128i sad_epu8(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i zeros();
	WJR_INTRINSIC_INLINE static __m128i ones();

	WJR_INTRINSIC_INLINE static __m128i set_epi8(
		char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
		char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0);

	WJR_INTRINSIC_INLINE static __m128i set_epi16(
		short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);
	WJR_INTRINSIC_INLINE static __m128i set_epi32(int e3, int e2, int e1, int e0);
	WJR_INTRINSIC_INLINE static __m128i set_epi64x(long long e1, long long e0);

	WJR_INTRINSIC_INLINE static __m128i setr_epi8(
		char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
		char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0);

	WJR_INTRINSIC_INLINE static __m128i setr_epi16(
		short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);
	WJR_INTRINSIC_INLINE static __m128i setr_epi32(int e3, int e2, int e1, int e0);

	WJR_INTRINSIC_INLINE static __m128i set1_epi8(int8_t val);
	WJR_INTRINSIC_INLINE static __m128i set1_epi16(int16_t val);
	WJR_INTRINSIC_INLINE static __m128i set1_epi32(int32_t val);
	WJR_INTRINSIC_INLINE static __m128i set1_epi64(int64_t val);

	WJR_INTRINSIC_INLINE static __m128i set1(int8_t val, int8_t);
	WJR_INTRINSIC_INLINE static __m128i set1(int16_t val, int16_t);
	WJR_INTRINSIC_INLINE static __m128i set1(int32_t val, int32_t);
	WJR_INTRINSIC_INLINE static __m128i set1(int64_t val, int64_t);
	WJR_INTRINSIC_INLINE static __m128i set1(uint8_t val, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i set1(uint16_t val, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i set1(uint32_t val, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i set1(uint64_t val, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i setmin_epi8();
	WJR_INTRINSIC_INLINE static __m128i setmin_epi16();
	WJR_INTRINSIC_INLINE static __m128i setmin_epi32();

	WJR_INTRINSIC_INLINE static __m128i setmin(int8_t);
	WJR_INTRINSIC_INLINE static __m128i setmin(int16_t);
	WJR_INTRINSIC_INLINE static __m128i setmin(int32_t);
	WJR_INTRINSIC_INLINE static __m128i setmin(uint8_t);
	WJR_INTRINSIC_INLINE static __m128i setmin(uint16_t);
	WJR_INTRINSIC_INLINE static __m128i setmin(uint32_t);

	WJR_INTRINSIC_INLINE static __m128i setmax_epi8();
	WJR_INTRINSIC_INLINE static __m128i setmax_epi16();
	WJR_INTRINSIC_INLINE static __m128i setmax_epi32();

	WJR_INTRINSIC_INLINE static __m128i setmax(int8_t);
	WJR_INTRINSIC_INLINE static __m128i setmax(int16_t);
	WJR_INTRINSIC_INLINE static __m128i setmax(int32_t);
	WJR_INTRINSIC_INLINE static __m128i setmax(uint8_t);
	WJR_INTRINSIC_INLINE static __m128i setmax(uint16_t);
	WJR_INTRINSIC_INLINE static __m128i setmax(uint32_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i shuffle_epi32(__m128i v);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i shufflehi_epi16(__m128i v);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i shufflelo_epi16(__m128i v);

	WJR_INTRINSIC_INLINE static __m128i sll_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sll_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sll_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i sll(__m128i a, __m128i b, uint64_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i v);
	WJR_INTRINSIC_INLINE static __m128i slli_epi16(__m128i a, int imm8);
	WJR_INTRINSIC_INLINE static __m128i slli_epi32(__m128i a, int imm8);
	WJR_INTRINSIC_INLINE static __m128i slli_epi64(__m128i a, int imm8);

	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, int32_t);
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, int64_t);
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i slli(__m128i a, int imm8, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i sra_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sra_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i sra(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i sra(__m128i a, __m128i b, int32_t);

	WJR_INTRINSIC_INLINE static __m128i srai_epi16(__m128i a, int imm8);
	WJR_INTRINSIC_INLINE static __m128i srai_epi32(__m128i a, int imm8);

	WJR_INTRINSIC_INLINE static __m128i srai(__m128i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m128i srai(__m128i a, int imm8, int32_t);

	WJR_INTRINSIC_INLINE static __m128i srl_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i srl_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i srl_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i srl(__m128i a, __m128i b, uint64_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i v);
	WJR_INTRINSIC_INLINE static __m128i srli_epi16(__m128i a, int imm8);
	WJR_INTRINSIC_INLINE static __m128i srli_epi32(__m128i a, int imm8);
	WJR_INTRINSIC_INLINE static __m128i srli_epi64(__m128i a, int imm8);

	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, int32_t);
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, int64_t);
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i srli(__m128i a, int imm8, uint64_t);

	WJR_INTRINSIC_INLINE static void stream(__m128i* ptr, __m128i v);

	WJR_INTRINSIC_INLINE static void store(__m128i* ptr, __m128i val);
	WJR_INTRINSIC_INLINE static void storeu(__m128i* ptr, __m128i val);

	WJR_INTRINSIC_INLINE static __m128i sub_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sub_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sub_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sub_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i sub(__m128i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i subs_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i subs_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i subs_epu8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i subs_epu16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i subs(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i subs(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i subs(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i subs(__m128i a, __m128i b, uint16_t);

	WJR_INTRINSIC_INLINE static __m128i unpackhi_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpackhi_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpackhi_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpackhi_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m128i unpackhi(__m128i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i unpacklo_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpacklo_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpacklo_epi32(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i unpacklo_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i unpacklo(__m128i a, __m128i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i Xor(__m128i a, __m128i b);

#endif // WJR_SSE2

#if WJR_SSE3
	WJR_INTRINSIC_INLINE static __m128i lddqu(const __m128i* ptr);
#endif // WJR_SSE3

#if WJR_SSSE3

	WJR_INTRINSIC_INLINE static __m128i abs_epi8(__m128i val);
	WJR_INTRINSIC_INLINE static __m128i abs_epi16(__m128i val);
	WJR_INTRINSIC_INLINE static __m128i abs_epi32(__m128i val);

	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, int8_t);
	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, int16_t);
	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, int32_t);
	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i abs(__m128i val, uint32_t);

	WJR_INTRINSIC_INLINE static __m128i shuffle_epi8(__m128i v, __m128i imm8);

	WJR_INTRINSIC_INLINE static __m128i sign_epi8(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sign_epi16(__m128i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m128i sign_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, int8_t);
	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m128i sign(__m128i a, __m128i b, uint32_t);

#endif // WJR_SSSE3

#if WJR_SSE4_1
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i blend_epi16(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpeq_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m128i cmpeq(__m128i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i cmpgt_epi64(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i cmpgt(__m128i a, __m128i b, int64_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert_epi8(__m128i a, int i);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert_epi32(__m128i a, int i);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert_epi64(__m128i a, int64_t i);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, int8_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, int32_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int64_t i, int64_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, uint8_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int i, uint32_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i insert(__m128i a, int64_t i, uint64_t);

	WJR_INTRINSIC_INLINE static __m128i minpos_epu16(__m128i a);

	WJR_INTRINSIC_INLINE static __m128i mul_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i mullo_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i packus_epi32(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m128i stream_load(__m128i* p);

	WJR_INTRINSIC_INLINE static int test_all_ones(__m128i a);

	WJR_INTRINSIC_INLINE static int test_all_zeros(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static int test_all_zeros(__m128i a);

	WJR_INTRINSIC_INLINE static int test_mix_ones_zeros(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static int testc(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static int testnzc(__m128i a, __m128i b);

	WJR_INTRINSIC_INLINE static int testz(__m128i a, __m128i b);
#endif // WJR_SSE4_1

};

struct avx {
	using mask_type = uint32_t;
#if WJR_AVX
	using float_type = __m256;
	using int_type = __m256i;
	using double_type = __m256d;
#endif // WJR_AVX

	constexpr static size_t width();

	constexpr static mask_type mask();

#if WJR_AVX

	WJR_INTRINSIC_INLINE static __m256i concat(__m128i a, __m128i b);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi32(__m256i v);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int64_t extract_epi64(__m256i v);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m256i v, int32_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int64_t extract(__m256i v, int64_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m128i extract_si128(__m256i v);

	WJR_INTRINSIC_INLINE static __m128i getlow(__m256i a);

	WJR_INTRINSIC_INLINE static __m128i gethigh(__m256i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i insert_epi8(__m256i v, int8_t i);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i insert_epi16(__m256i v, int16_t i);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i insert_epi32(__m256i v, int32_t i);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i insert_epi64(__m256i v, int64_t i);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i insert_si128(__m256i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m256i load(const __m256i* p);
	WJR_INTRINSIC_INLINE static __m256i loadu(const __m256i* p);

	WJR_INTRINSIC_INLINE static __m256i ones();

	WJR_INTRINSIC_INLINE static __m256i preloadu_si16(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si32(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si48(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si64(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si80(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si96(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si112(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si128(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si144(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si160(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si176(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si192(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si208(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si224(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si240(const void* ptr);
	WJR_INTRINSIC_INLINE static __m256i preloadu_si256(const void* ptr);

	WJR_INTRINSIC_INLINE static __m256i preloadu_si16x(const void* ptr, int n);

	WJR_INTRINSIC_INLINE static __m256i set_epi8(
		char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24,
		char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16,
		char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
		char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0);

	WJR_INTRINSIC_INLINE static __m256i set_epi16(
		short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8,
		short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);

	WJR_INTRINSIC_INLINE static __m256i set_epi32(
		int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0);

	WJR_INTRINSIC_INLINE static __m256i set_epi64x(
		long long e3, long long e2, long long e1, long long e0);

	WJR_INTRINSIC_INLINE static __m256i setr_epi8(
		char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24,
		char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16,
		char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
		char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0);

	WJR_INTRINSIC_INLINE static __m256i setr_epi16(
		short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8,
		short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0);

	WJR_INTRINSIC_INLINE static __m256i setr_epi32(
		int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0);

	WJR_INTRINSIC_INLINE static __m256i setr_epi64x(
		long long e3, long long e2, long long e1, long long e0);

	WJR_INTRINSIC_INLINE static __m256i set1_epi8(int8_t a);
	WJR_INTRINSIC_INLINE static __m256i set1_epi16(int16_t a);
	WJR_INTRINSIC_INLINE static __m256i set1_epi32(int32_t a);
	WJR_INTRINSIC_INLINE static __m256i set1_epi64(int64_t a);

	WJR_INTRINSIC_INLINE static __m256i set1(int8_t a, int8_t);
	WJR_INTRINSIC_INLINE static __m256i set1(int16_t a, int16_t);
	WJR_INTRINSIC_INLINE static __m256i set1(int32_t a, int32_t);
	WJR_INTRINSIC_INLINE static __m256i set1(int64_t a, int64_t);
	WJR_INTRINSIC_INLINE static __m256i set1(uint8_t a, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i set1(uint16_t a, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i set1(uint32_t a, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i set1(uint64_t a, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i setmin_epi8();
	WJR_INTRINSIC_INLINE static __m256i setmin_epi16();
	WJR_INTRINSIC_INLINE static __m256i setmin_epi32();
	WJR_INTRINSIC_INLINE static __m256i setmin_epi64();

	WJR_INTRINSIC_INLINE static __m256i setmin(int8_t);
	WJR_INTRINSIC_INLINE static __m256i setmin(int16_t);
	WJR_INTRINSIC_INLINE static __m256i setmin(int32_t);
	WJR_INTRINSIC_INLINE static __m256i setmin(int64_t);

	WJR_INTRINSIC_INLINE static __m256i setmax_epi8();
	WJR_INTRINSIC_INLINE static __m256i setmax_epi16();
	WJR_INTRINSIC_INLINE static __m256i setmax_epi32();
	WJR_INTRINSIC_INLINE static __m256i setmax_epi64();

	WJR_INTRINSIC_INLINE static __m256i setmax(int8_t);
	WJR_INTRINSIC_INLINE static __m256i setmax(int16_t);
	WJR_INTRINSIC_INLINE static __m256i setmax(int32_t);
	WJR_INTRINSIC_INLINE static __m256i setmax(int64_t);

	WJR_INTRINSIC_INLINE static void stream(__m256i* p, __m256i a);

	WJR_INTRINSIC_INLINE static void store(__m256i* p, const __m256i& a);
	WJR_INTRINSIC_INLINE static void storeu(__m256i* p, const __m256i& a);

	WJR_INTRINSIC_INLINE static int test_all_zeros(__m256i a);

	WJR_INTRINSIC_INLINE static int testc(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static int testnzc(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static int testz(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i zeros();
#endif // WJR_AVX

#if WJR_AVX2
	WJR_INTRINSIC_INLINE static __m256i And(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i AndNot(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i Or(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i Xor(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i Not(__m256i v);

	WJR_INTRINSIC_INLINE static __m256i abs_epi8(__m256i v);
	WJR_INTRINSIC_INLINE static __m256i abs_epi16(__m256i v);
	WJR_INTRINSIC_INLINE static __m256i abs_epi32(__m256i v);

	WJR_INTRINSIC_INLINE static __m256i abs(__m256i v, int8_t);
	WJR_INTRINSIC_INLINE static __m256i abs(__m256i v, int16_t);
	WJR_INTRINSIC_INLINE static __m256i abs(__m256i v, int32_t);
	WJR_INTRINSIC_INLINE static __m256i abs(__m256i v, int64_t);

	WJR_INTRINSIC_INLINE static __m256i add_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i add_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i add_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i add_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i add(__m256i a, __m256i b, uint64_t);

	WJR_INTRINSIC_INLINE static uint8_t add_epu8(__m256i v);
	WJR_INTRINSIC_INLINE static uint16_t add_epu16(__m256i v);
	WJR_INTRINSIC_INLINE static uint32_t add_epu32(__m256i v);
	WJR_INTRINSIC_INLINE static uint64_t add_epu64(__m256i v);

	WJR_INTRINSIC_INLINE static int8_t add_epi8(__m256i v);
	WJR_INTRINSIC_INLINE static int16_t add_epi16(__m256i v);
	WJR_INTRINSIC_INLINE static int32_t add_epi32(__m256i v);
	WJR_INTRINSIC_INLINE static int64_t add_epi64(__m256i v);

	WJR_INTRINSIC_INLINE static int8_t add(__m256i v, int8_t);
	WJR_INTRINSIC_INLINE static int16_t add(__m256i v, int16_t);
	WJR_INTRINSIC_INLINE static int32_t add(__m256i v, int32_t);
	WJR_INTRINSIC_INLINE static int64_t add(__m256i v, int64_t);
	WJR_INTRINSIC_INLINE static uint8_t add(__m256i v, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t add(__m256i v, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t add(__m256i v, uint32_t);
	WJR_INTRINSIC_INLINE static uint64_t add(__m256i v, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i adds_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i adds_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i adds_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i adds_epu16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i adds(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i adds(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i adds(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i adds(__m256i a, __m256i b, uint16_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i alignr_epi16(__m256i a, __m256i b, int c);
	WJR_INTRINSIC_INLINE static __m256i alignr_epi32(__m256i a, __m256i b, int c);
	WJR_INTRINSIC_INLINE static __m256i alignr_epi64(__m256i a, __m256i b, int c);

	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, int16_t);
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, int32_t);
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, int64_t);
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i alignr(__m256i a, __m256i b, int c, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i avg_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i avg_epu16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i avg(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i avg(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i avg(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i avg(__m256i a, __m256i b, uint16_t);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i blend_epi16(__m256i a, __m256i b);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i blend_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i blendv_epi8(__m256i a, __m256i b, __m256i mask);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i bslli_epi128(__m256i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i bsrli_epi128(__m256i a);

	WJR_INTRINSIC_INLINE static __m256i cmpeq_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpeq_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpeq_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpeq_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpeq(__m256i a, __m256i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i cmpge_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpge_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpge_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpge_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpge_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpge_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpge(__m256i a, __m256i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m256i cmpgt_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpgt_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epu32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpgt_epu64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpgt(__m256i a, __m256i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i cmple_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmple_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmple_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmple_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmple_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmple_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmple(__m256i a, __m256i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m256i cmplt_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmplt_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmplt_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmplt_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmplt_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmplt_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmplt(__m256i a, __m256i b, uint32_t);

	WJR_INTRINSIC_INLINE static __m256i cmpne_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpne_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i cmpne_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i cmpne(__m256i a, __m256i b, uint32_t);

	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::equal_to<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::not_equal_to<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::greater<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::greater_equal<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::less<>, T);
	template<typename T>
	WJR_INTRINSIC_INLINE static __m256i cmp(__m256i a, __m256i b, std::less_equal<>, T);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi8(__m256i v);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract_epi16(__m256i v);

	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m256i v, int8_t);
	template<int imm8>
	WJR_INTRINSIC_INLINE static int extract(__m256i v, int16_t);

	WJR_INTRINSIC_INLINE static __m256i hadd_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i hadd_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i hadd(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i hadd(__m256i a, __m256i b, int32_t);

	WJR_INTRINSIC_INLINE static __m256i hadds_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i hsub_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i hsub_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i hsub(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i hsub(__m256i a, __m256i b, int32_t);

	WJR_INTRINSIC_INLINE static __m256i hsubs_epi16(__m256i a, __m256i b);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m256i logical_and(__m256i a, __m256i b, T);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m256i logical_not(__m256i v, T);

	template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
		uint8_t, uint16_t, uint32_t, uint64_t>, int> = 0>
	WJR_INTRINSIC_INLINE static __m256i logical_or(__m256i a, __m256i b, T);

	WJR_INTRINSIC_INLINE static __m256i madd_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i max_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i max_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i max_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i max_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i max_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i max_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i max(__m256i a, __m256i b, uint32_t);

	WJR_INTRINSIC_INLINE static int8_t max_epi8(__m256i a);
	WJR_INTRINSIC_INLINE static int16_t max_epi16(__m256i a);
	WJR_INTRINSIC_INLINE static int32_t max_epi32(__m256i a);
	WJR_INTRINSIC_INLINE static uint8_t max_epu8(__m256i a);
	WJR_INTRINSIC_INLINE static uint16_t max_epu16(__m256i a);
	WJR_INTRINSIC_INLINE static uint32_t max_epu32(__m256i a);

	WJR_INTRINSIC_INLINE static int8_t max(__m256i a, int8_t);
	WJR_INTRINSIC_INLINE static int16_t max(__m256i a, int16_t);
	WJR_INTRINSIC_INLINE static int32_t max(__m256i a, int32_t);

	WJR_INTRINSIC_INLINE static uint8_t max(__m256i a, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t max(__m256i a, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t max(__m256i a, uint32_t);

	WJR_INTRINSIC_INLINE static __m256i min_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i min_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i min_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i min_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i min_epu16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i min_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i min(__m256i a, __m256i b, uint32_t);

	WJR_INTRINSIC_INLINE static int8_t min_epi8(__m256i a);
	WJR_INTRINSIC_INLINE static int16_t min_epi16(__m256i a);
	WJR_INTRINSIC_INLINE static int32_t min_epi32(__m256i a);

	WJR_INTRINSIC_INLINE static uint8_t min_epu8(__m256i a);
	WJR_INTRINSIC_INLINE static uint16_t min_epu16(__m256i a);
	WJR_INTRINSIC_INLINE static uint32_t min_epu32(__m256i a);

	WJR_INTRINSIC_INLINE static int8_t min(__m256i a, int8_t);
	WJR_INTRINSIC_INLINE static int16_t min(__m256i a, int16_t);
	WJR_INTRINSIC_INLINE static int32_t min(__m256i a, int32_t);
	WJR_INTRINSIC_INLINE static uint8_t min(__m256i a, uint8_t);
	WJR_INTRINSIC_INLINE static uint16_t min(__m256i a, uint16_t);
	WJR_INTRINSIC_INLINE static uint32_t min(__m256i a, uint32_t);

	WJR_INTRINSIC_INLINE static mask_type movemask_epi8(__m256i a);

	WJR_INTRINSIC_INLINE static __m256i mul_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i mul_epu32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i mulhi_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i mulhi_epu16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i mullo_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i packs_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i packs_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i packus_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i packus_epi32(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i shuffle_epi8(__m256i a, __m256i b);
	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i shuffle_epi32(__m256i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i shufflehi_epi16(__m256i a);

	template<int imm8>
	WJR_INTRINSIC_INLINE static __m256i shufflelo_epi16(__m256i a);

	WJR_INTRINSIC_INLINE static __m256i sll_epi16(__m256i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m256i sll_epi32(__m256i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m256i sll_epi64(__m256i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i sll(__m256i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i slli_epi16(__m256i a, int imm8);
	WJR_INTRINSIC_INLINE static __m256i slli_epi32(__m256i a, int imm8);
	WJR_INTRINSIC_INLINE static __m256i slli_epi64(__m256i a, int imm8);

	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, int32_t);
	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, int64_t);
	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i slli(__m256i a, int imm8, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i sra_epi16(__m256i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m256i sra_epi32(__m256i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m256i sra(__m256i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i sra(__m256i a, __m128i b, int32_t);

	WJR_INTRINSIC_INLINE static __m256i srai_epi16(__m256i a, int imm8);
	WJR_INTRINSIC_INLINE static __m256i srai_epi32(__m256i a, int imm8);

	WJR_INTRINSIC_INLINE static __m256i srai(__m256i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m256i srai(__m256i a, int imm8, int32_t);

	WJR_INTRINSIC_INLINE static __m256i stream_load(__m256i const* p);

	WJR_INTRINSIC_INLINE static __m256i srl_epi16(__m256i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m256i srl_epi32(__m256i a, __m128i b);
	WJR_INTRINSIC_INLINE static __m256i srl_epi64(__m256i a, __m128i b);

	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i srl(__m256i a, __m128i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i srli_epi16(__m256i a, int imm8);
	WJR_INTRINSIC_INLINE static __m256i srli_epi32(__m256i a, int imm8);
	WJR_INTRINSIC_INLINE static __m256i srli_epi64(__m256i a, int imm8);

	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, int16_t);
	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, int32_t);
	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, int64_t);
	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i srli(__m256i a, int imm8, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i sub_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i sub_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i sub_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i sub_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i sub(__m256i a, __m256i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i subs_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i subs_epi16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i subs_epu8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i subs_epu16(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i subs(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i subs(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i subs(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i subs(__m256i a, __m256i b, uint16_t);

	WJR_INTRINSIC_INLINE static int test_all_ones(__m256i a);

	WJR_INTRINSIC_INLINE static __m256i unpackhi_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpackhi_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpackhi_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpackhi_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, uint32_t);
	WJR_INTRINSIC_INLINE static __m256i unpackhi(__m256i a, __m256i b, uint64_t);

	WJR_INTRINSIC_INLINE static __m256i unpacklo_epi8(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpacklo_epi16(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpacklo_epi32(__m256i a, __m256i b);
	WJR_INTRINSIC_INLINE static __m256i unpacklo_epi64(__m256i a, __m256i b);

	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, int8_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, int16_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, int32_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, int64_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, uint8_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, uint16_t);
	WJR_INTRINSIC_INLINE static __m256i unpacklo(__m256i a, __m256i b, uint32_t);
#endif // WJR_AVX2

};

_WJR_SIMD_END

#ifndef __WJR_SIMD_SIMD_INTRIN_H
#error "This file should not be included directly. Include <wjr/simd/simd_intrin.h> instead."
#endif 

#pragma once
#ifndef __WJR_MATH_H__
#define __WJR_MATH_H__

#pragma once
#ifndef __WJR_ASM_ASM_H
#define __WJR_ASM_ASM_H



#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

#if WJR_HAS_BUILTIN(__builtin_addc) || WJR_HAS_CLANG(5, 0, 0)
template<typename T>
WJR_INTRINSIC_INLINE static T __wjr_builtin_adc(T a, T b, T carry_in, T* carry_out) {
	constexpr auto _Nd = std::numeric_limits<T>::digits;

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;
	constexpr auto _Nd_us = std::numeric_limits<unsigned short>::digits;
	constexpr auto _Nd_ub = std::numeric_limits<unsigned char>::digits;

	if constexpr (_Nd <= _Nd_ub) {
		unsigned char CF = 0;
		T ret = __builtin_addcb(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_us) {
		unsigned short CF = 0;
		T ret = __builtin_addcs(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ui) {
		unsigned int CF = 0;
		T ret = __builtin_addc(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ul) {
		unsigned long CF = 0;
		T ret = __builtin_addcl(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
#if defined(WJR_X86_64)
	else if constexpr (_Nd <= _Nd_ull) {
		unsigned long long CF = 0;
		T ret = __builtin_addcll(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
#endif // WJR_X86_64
	else {
		static_assert(_Nd <= _Nd_ull, "unsupported integer type");
	}
}
#elif defined(WJR_COMPILER_MSVC)
template<typename T>
WJR_INTRINSIC_INLINE static T __wjr_msvc_adc(T a, T b, T carry_in, T* carry_out) {
	constexpr auto _Nd = std::numeric_limits<T>::digits;

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	//constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;
	constexpr auto _Nd_us = std::numeric_limits<unsigned short>::digits;
	constexpr auto _Nd_ub = std::numeric_limits<unsigned char>::digits;

	if constexpr (_Nd <= _Nd_ub) {
		unsigned char ret = 0;
		*carry_out = _addcarry_u8(carry_in, a, b, &ret);
		return ret;
	}
	else if constexpr (_Nd <= _Nd_us) {
		unsigned short ret = 0;
		*carry_out = _addcarry_u16(carry_in, a, b, &ret);
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ui) {
		unsigned int ret = 0;
		*carry_out = _addcarry_u32(carry_in, a, b, &ret);
		return ret;
	}
#if defined(WJR_X86_64)
	else if constexpr (_Nd <= _Nd_ull) {
		unsigned long long ret = 0;
		*carry_out = _addcarry_u64(carry_in, a, b, &ret);
		return ret;
	}
#endif // WJR_X86_64
	else {
		static_assert(_Nd <= _Nd_ull, "unsupported integer type");
	}
}
#endif

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 T adc(T a, T b, T carry_in, T* carry_out) {
	if (!wjr::is_constant_evaluated()) {
		if (!((is_constant_p(a) && is_constant_p(b)) || (is_constant_p(carry_in) && carry_in == 0))) {
#if WJR_HAS_BUILTIN(__builtin_addc) || WJR_HAS_CLANG(5, 0, 0)
			return __wjr_builtin_adc(a, b, carry_in, carry_out);
#elif defined(WJR_COMPILER_MSVC)
			return __wjr_msvc_adc(a, b, carry_in, carry_out);
#elif defined(WJR_INLINE_ASM)
#if defined(WJR_BETTER_INLINE_ASM)
			asm("add $255, %b0\n\t"
				"adc %3, %2\n\t"
				"setb %b1"
				: "+r"(carry_in), "=rm"(*carry_out), "+%r"(a)
				: "rm"(b)
				: "cc");
#else
			asm("add $255, %b0\n\t"
				"adc %3, %2\n\t"
				"setb %b1"
				: "+r"(carry_in), "=r"(*carry_out), "+%r"(a)
				: "r"(b)
				: "cc");
			return a;
#endif // WJR_BETTER_INLINE_ASM
#endif
		}
	}
	T c = 0;
	a += b;
	c = a < b;
	a += carry_in;
	c |= a < carry_in;
	*carry_out = c;
	return a;
}

_WJR_ASM_END
#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

#if WJR_HAS_BUILTIN(__builtin_subc) || WJR_HAS_CLANG(5, 0, 0)
template<typename T>
WJR_INTRINSIC_INLINE static T __wjr_builtin_sbb(T a, T b, T carry_in, T* carry_out) {
	constexpr auto _Nd = std::numeric_limits<T>::digits;

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;
	constexpr auto _Nd_us = std::numeric_limits<unsigned short>::digits;
	constexpr auto _Nd_ub = std::numeric_limits<unsigned char>::digits;

	if constexpr (_Nd <= _Nd_ub) {
		unsigned char CF = 0;
		T ret = __builtin_subcb(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_us) {
		unsigned short CF = 0;
		T ret = __builtin_subcs(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ui) {
		unsigned int CF = 0;
		T ret = __builtin_subc(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ul) {
		unsigned long CF = 0;
		T ret = __builtin_subcl(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
#if defined(WJR_X86_64)
	else if constexpr (_Nd <= _Nd_ull) {
		unsigned long long CF = 0;
		T ret = __builtin_subcll(a, b, carry_in, &CF);
		*carry_out = CF;
		return ret;
	}
#endif // WJR_X86_64
	else {
		static_assert(_Nd <= _Nd_ull, "unsupported integer type");
	}
}
#elif defined(WJR_COMPILER_MSVC)
template<typename T>
WJR_INTRINSIC_INLINE static T __wjr_msvc_sbb(T a, T b, T carry_in, T* carry_out) {
	constexpr auto _Nd = std::numeric_limits<T>::digits;

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	//constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;
	constexpr auto _Nd_us = std::numeric_limits<unsigned short>::digits;
	constexpr auto _Nd_ub = std::numeric_limits<unsigned char>::digits;

	if constexpr (_Nd <= _Nd_ub) {
		unsigned char ret = 0;
		*carry_out = _subborrow_u8(carry_in, a, b, &ret);
		return ret;
	}
	else if constexpr (_Nd <= _Nd_us) {
		unsigned short ret = 0;
		*carry_out = _subborrow_u16(carry_in, a, b, &ret);
		return ret;
	}
	else if constexpr (_Nd <= _Nd_ui) {
		unsigned int ret = 0;
		*carry_out = _subborrow_u32(carry_in, a, b, &ret);
		return ret;
	}
#if defined(WJR_X86_64)
	else if constexpr (_Nd <= _Nd_ull) {
		unsigned long long ret = 0;
		*carry_out = _subborrow_u64(carry_in, a, b, &ret);
		return ret;
	}
#endif // WJR_X86_64
	else {
		static_assert(_Nd <= _Nd_ull, "unsupported integer type");
	}
}
#endif

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 T sbb(T a, T b, T carry_in, T* carry_out) {
	if (!wjr::is_constant_evaluated()) {
		if (!((is_constant_p(a) && is_constant_p(b)) || (is_constant_p(carry_in) && carry_in == 0))) {
#if WJR_HAS_BUILTIN(__builtin_subc) || WJR_HAS_CLANG(5, 0, 0)
			return __wjr_builtin_sbb(a, b, carry_in, carry_out);
#elif defined(WJR_COMPILER_MSVC)
			return __wjr_msvc_sbb(a, b, carry_in, carry_out);
#elif defined(WJR_INLINE_ASM) // Clang does not need inline assembly
#if defined(WJR_BETTER_INLINE_ASM)
			asm("add $255, %b0\n\t"
				"sbb %3, %2\n\t"
				"setb %b1"
				: "+r"(carry_in), "=rm"(*carry_out), "+r"(a)
				: "rm"(b)
				: "cc");
#else
			asm("add $255, %b0\n\t"
				"sbb %3, %2\n\t"
				"setb %b1"
				: "+r"(carry_in), "=r"(*carry_out), "+r"(a)
				: "r"(b)
				: "cc");
			return a;
#endif // WJR_BETTER_INLINE_ASM
#endif
		}
	}
	T c = 0;
	c = a < b;
	a -= b;
	c |= a < carry_in;
	a -= carry_in;
	*carry_out = c;
	return a;
}

_WJR_ASM_END

#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

const static int _WJR_LOG_TABLE[256] = {
		0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
		8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR static int __wjr_fallback_clz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if (x == 0) {
		return _Nd;
	}

	int n = 0;
	// use _Table

	if constexpr (_Nd > 32) {
		if (x >> 32) {
			n += 32;
			x >>= 32;
		}
	}
	if constexpr (_Nd > 16) {
		if (x >> 16) {
			n += 16;
			x >>= 16;
		}
	}
	if constexpr (_Nd > 8) {
		if (x >> 8) {
			n += 8;
			x >>= 8;
		}
	}
	return  _Nd - (n + _WJR_LOG_TABLE[x]);
}

#if WJR_HAS_BUILTIN(__builtin_clz) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_builtin_clz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if (x == 0) {
		return _Nd;
	}

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;

	if constexpr (_Nd <= _Nd_ui) {
		constexpr auto __diff = _Nd_ui - _Nd;
		return __builtin_clz(x) - __diff;
	}
	else if constexpr (_Nd <= _Nd_ul) {
		constexpr auto __diff = _Nd_ul - _Nd;
		return __builtin_clzl(x) - __diff;
	}
#if defined(WJR_X86_64)
	else if constexpr (_Nd <= _Nd_ull) {
		constexpr auto __diff = _Nd_ull - _Nd;
		return __builtin_clzll(x) - __diff;
	}
#endif // WJR_X86_64
	else {
		static_assert(_Nd <= _Nd_ull, "countl_zero is not implemented for this type");
	}
}
#elif defined(WJR_COMPILER_MSVC)
#if defined(WJR_X86)

template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_avx2_clz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if constexpr (_Nd <= 16) {
		return static_cast<int>(__lzcnt16(x) - (16 - _Nd));
	}
	else if constexpr (_Nd <= 32) {
		return static_cast<int>(__lzcnt(x));
	}
	else {
#if defined(WJR_X86_32)
		const auto xh = static_cast<unsigned int>(x >> 32);
		const auto xl = static_cast<unsigned int>(x);
		if (xh == 0) {
			return 32 + static_cast<int>(__lzcnt(xl));
		}
		else {
			return static_cast<int>(__lzcnt(xh));
		}
#else
		return static_cast<int>(__lzcnt64(x));
#endif
	}
}

template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_normal_clz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	unsigned long _Result;
	if constexpr (_Nd <= 32) {
		if (!_BitScanReverse(&_Result, x)) {
			return _Nd;
		}
	}
	else {
#if defined(WJR_X86_32)
		const auto xh = static_cast<unsigned int>(x >> 32);
		if (_BitScanReverse(&_Result, xh)) {
			return static_cast<int>(31 - _Result);
		}
		const auto xl = static_cast<unsigned int>(x);
		if (!_BitScanReverse(&_Result, xl)) {
			return _Nd;
		}
#else
		if (!_BitScanReverse64(&_Result, x)) {
			return _Nd;
		}
#endif
	}
	return static_cast<int>(_Nd - 1 - _Result);
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_clz(T x) noexcept {
#if WJR_AVX2
	return __wjr_msvc_x86_64_avx2_clz(x);
#elif defined(_WJR_CPUINFO)
	if (is_avx2()) {
		return __wjr_msvc_x86_64_avx2_clz(x);
	}
	else {
		return __wjr_msvc_x86_64_normal_clz(x);
	}
#else
	return __wjr_msvc_x86_64_normal_clz(x);
#endif // WJR_AVX2
}
#elif defined(WJR_ARM)
template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_INLINE static int __wjr_msvc_arm_clz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if (x == 0) {
		return _Nd;
	}
	if constexpr (_Nd <= 32) {
		return static_cast<int>(_CountLeadingZeros(x));
	}
	else {
		return static_cast<int>(_CountLeadingZeros64(x));
	}
}
#endif
#endif

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int clz(T x) noexcept {
	if (!wjr::is_constant_evaluated()) {
#if WJR_HAS_BUILTIN(__builtin_clz) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
		return __wjr_builtin_clz(x);
#elif defined(WJR_COMPILER_MSVC)
#if defined(WJR_X86)
		return __wjr_msvc_x86_64_clz(x);
#elif defined(WJR_ARM)
		return __wjr_msvc_arm_clz(x);
#endif
#endif
	}
	return __wjr_fallback_clz(x);
}

_WJR_ASM_END

#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

#if WJR_HAS_BUILTIN(__builtin_ctz) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_builtin_ctz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if (x == 0) {
		return _Nd;
	}

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;

	if constexpr (_Nd <= _Nd_ui) {
		return __builtin_ctz(x);
	}
	else if constexpr (_Nd <= _Nd_ul) {
		return __builtin_ctzl(x);
	}
	else if constexpr (_Nd <= _Nd_ull) {
		return __builtin_ctzll(x);
	}
	else {
		static_assert(_Nd <= _Nd_ull, "countr_zero is not implemented for this type");
	}
}
#elif defined(WJR_COMPILER_MSVC) && defined(WJR_X86) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) \
    && !defined(__INTEL_COMPILER)
template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_avx2_ctz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	constexpr T _Max = std::numeric_limits<T>::max();
	if constexpr (_Nd <= 32) {
		return static_cast<int>(_tzcnt_u32(static_cast<unsigned int>(~_Max | x)));
	}
	else {
#if defined(WJR_X86_32)
		const auto xh = static_cast<unsigned int>(x >> 32);
		const auto xl = static_cast<unsigned int>(x);
		if (xh == 0) {
			return 32 + static_cast<int>(_tzcnt_u32(xl));
		}
		else {
			return static_cast<int>(_tzcnt_u32(xh));
		}
#else
		return static_cast<int>(_tzcnt_u64(x));
#endif // WJR_X86_32
	}
}

template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_normal_ctz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	constexpr T _Max = std::numeric_limits<T>::max();
	unsigned long _Result;
	if constexpr (_Nd <= 32) {
		if (!_BitScanForward(&_Result, x)) {
			return _Nd;
		}
	}
	else {
#if defined(WJR_X86_32)
		const auto xl = static_cast<unsigned int>(x);
		if (_BitScanForward(&_Result, xl)) {
			return static_cast<int>(_Result);
		}
		const auto xh = static_cast<unsigned int>(x >> 32);
		if (!_BitScanForward(&_Result, xh)) {
			return _Nd;
		}
		else {
			return static_cast<int>(32 + _Result);
		}

#else
		if (!_BitScanForward64(&_Result, x)) {
			return _Nd;
		}
#endif
	}
	return static_cast<int>(_Result);
}

template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_ctz(T x) noexcept {
#if WJR_AVX2
	return __wjr_msvc_x86_64_avx2_ctz(x);
#elif defined(_WJR_CPUINFO)
	if (is_avx2()) {
		return __wjr_msvc_x86_64_avx2_ctz(x);
	}
	else {
		return __wjr_msvc_x86_64_normal_ctz(x);
	}
#else
	return __wjr_msvc_x86_64_normal_ctz(x);
#endif // WJR_AVX2
}
#endif

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int ctz(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;
	if (!wjr::is_constant_evaluated()) {
#if WJR_HAS_BUILTIN(__builtin_ctz) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
		return __wjr_builtin_ctz(x);
#elif defined(WJR_COMPILER_MSVC) && defined(WJR_X86) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) \
	&& !defined(__INTEL_COMPILER)
		return __wjr_msvc_x86_64_ctz(x);
#endif
	}
	return _Nd - clz(static_cast<T>(static_cast<T>(~x) & static_cast<T>(x - 1)));
}

_WJR_ASM_END
#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

template<typename _Ty>
WJR_INTRINSIC_CONSTEXPR static int __wjr_fallback_popcount(_Ty _Val) noexcept {
	constexpr int _Digits = std::numeric_limits<_Ty>::digits;
#if defined(WJR_X86_32) || defined(WJR_ARM)
	if constexpr (_Digits == 64) {
		// 64-bit bit operations on architectures without 64-bit registers are less efficient,
		// hence we split the value so that it fits in 32-bit registers
		return _Popcount_fallback(static_cast<unsigned long>(_Val))
			+ _Popcount_fallback(static_cast<unsigned long>(_Val >> 32));
	}
#endif // defined(WJR_X86_32) || defined(WJR_ARM)
	// we static_cast these bit patterns in order to truncate them to the correct size
	_Val = static_cast<_Ty>(_Val - ((_Val >> 1) & static_cast<_Ty>(0x5555'5555'5555'5555ull)));
	_Val = static_cast<_Ty>((_Val & static_cast<_Ty>(0x3333'3333'3333'3333ull))
		+ ((_Val >> 2) & static_cast<_Ty>(0x3333'3333'3333'3333ull)));
	_Val = static_cast<_Ty>((_Val + (_Val >> 4)) & static_cast<_Ty>(0x0F0F'0F0F'0F0F'0F0Full));
	// Multiply by one in each byte, so that it will have the sum of all source bytes in the highest byte
	_Val = static_cast<_Ty>(_Val * static_cast<_Ty>(0x0101'0101'0101'0101ull));
	// Extract highest byte
	return static_cast<int>(_Val >> (_Digits - 8));
}

#if WJR_HAS_BUILTIN(__builtin_popcount) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
template<typename T>
WJR_INTRINSIC_INLINE static int __wjr_builtin_popcount(T x) noexcept {
	constexpr auto _Nd = std::numeric_limits<T>::digits;

	constexpr auto _Nd_ull = std::numeric_limits<unsigned long long>::digits;
	constexpr auto _Nd_ul = std::numeric_limits<unsigned long>::digits;
	constexpr auto _Nd_ui = std::numeric_limits<unsigned int>::digits;

	if constexpr (_Nd <= _Nd_ui) {
		return __builtin_popcount(static_cast<unsigned>(x));
	}
	else if constexpr (_Nd <= _Nd_ul) {
		return __builtin_popcountl(static_cast<unsigned long>(x));
	}
	else if constexpr (_Nd <= _Nd_ull) {
		return __builtin_popcountll(static_cast<unsigned long long>(x));
	}
	else {
		static_assert(_Nd <= _Nd_ull, "unsupported integer type");
	}

}
#elif defined(WJR_COMPILER_MSVC) && defined(WJR_X86) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) \
	&& !defined(__INTEL_COMPILER)
template <typename T>
WJR_INTRINSIC_INLINE static int __wjr_msvc_x86_64_popcount(T x) noexcept {
	constexpr int _Digits = std::numeric_limits<T>::digits;
	if constexpr (_Digits <= 16) {
		return static_cast<int>(__popcnt16(x));
	}
	else if constexpr (_Digits == 32) {
		return static_cast<int>(__popcnt(x));
	}
	else {
#ifdef WJR_X86_32
		return static_cast<int>(__popcnt(x >> 32) + __popcnt(static_cast<unsigned int>(x)));
#else
		return static_cast<int>(__popcnt64(x));
#endif // WJR_X86_32
	}
}
#endif

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int popcnt(T x) noexcept {
	if (!wjr::is_constant_evaluated()) {
#if WJR_HAS_BUILTIN(__builtin_popcount) || WJR_HAS_GCC(7,1,0) || WJR_HAS_CLANG(5,0,0)
		return __wjr_builtin_popcount(x);
#elif defined(_MSC_VER) && defined(WJR_X86) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) \
	&& !defined(__INTEL_COMPILER)
		return __wjr_msvc_x86_64_popcount(x);
#endif 
	}
	return __wjr_fallback_popcount(x);
}

_WJR_ASM_END
#ifndef __WJR_ASM_ASM_H
#error "This file should not be included directly. Include <wjr/asm.h> instead."
#endif

_WJR_ASM_BEGIN

#if defined(_WJR_FAST_REP)

WJR_INTRINSIC_INLINE void rep_stosb(unsigned char* s, unsigned char val, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__stosb(s, val, n);
#else
	asm volatile("rep stosb" : "+D"(s), "+c"(n) : "a"(val) : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_stosw(unsigned short* s, unsigned short val, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__stosw(s, val, n);
#else
	asm volatile("rep stosw" : "+D"(s), "+c"(n) : "a"(val) : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_stosd(unsigned int* s, unsigned int val, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__stosd(s, val, n);
#else
	asm volatile("rep stosd" : "+D"(s), "+c"(n) : "a"(val) : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_stosq(unsigned long long* s, unsigned long long val, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__stosq(s, val, n);
#else
	asm volatile("rep stosq" : "+D"(s), "+c"(n) : "a"(val) : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_movsb(unsigned char* d, const unsigned char* s, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__movsb(d, s, n);
#else
	asm volatile("rep movsb" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_movsw(unsigned short* d, const unsigned short* s, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__movsw(d, s, n);
#else
	asm volatile("rep movsw" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_movsd(unsigned int* d, const unsigned int* s, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__movsd(d, s, n);
#else
	asm volatile("rep movsd" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
#endif
}

WJR_INTRINSIC_INLINE void rep_movsq(unsigned long long* d, const unsigned long long* s, size_t n) {
#if defined(WJR_COMPILER_MSVC)
	__movsq(d, s, n);
#else
	asm volatile("rep movsq" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
#endif
}

#endif  // _WJR_FAST_REP

_WJR_ASM_END

#endif // __WJR_ASM_ASM_H

_WJR_BEGIN

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
constexpr bool has_single_bit(T x) noexcept {
	return x != 0 && (x & (x - 1)) == 0;
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int countl_zero(T x) noexcept {
	return wjr::masm::clz(x);
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int countl_one(T x) noexcept {
	return wjr::countl_zero(static_cast<T>(~x));
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int countr_zero(T x) noexcept {
	return wjr::masm::ctz(x);
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int countr_one(T x) noexcept {
	return wjr::countr_zero(static_cast<T>(~x));
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int bit_width(T x) noexcept {
	return std::numeric_limits<T>::digits - wjr::countl_zero(x);
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 T bit_floor(T x) noexcept {
	if (x != 0) {
		return static_cast<T>(T{ 1 } << (wjr::bit_width(x) - 1));
	}
	return T{ 0 };
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 T bit_ceil(T x) noexcept {
	if (x <= 1) {
		return T{ 1 };
	}
	return static_cast<T>(T{ 1 } << wjr::bit_width(x - 1));
}

template<typename T, std::enable_if_t<wjr::is_unsigned_integral_v<T>, int> = 0>
WJR_INTRINSIC_CONSTEXPR20 int popcount(T x) noexcept {
	return wjr::masm::popcnt(x);
}

template< typename T, typename U >
constexpr bool cmp_equal(T t, U u) noexcept
{
	using UT = std::make_unsigned_t<T>;
	using UU = std::make_unsigned_t<U>;
	if constexpr (std::is_signed_v<T> == std::is_signed_v<U>)
		return t == u;
	else if constexpr (std::is_signed_v<T>)
		return t < 0 ? false : UT(t) == u;
	else
		return u < 0 ? false : t == UU(u);
}

template< typename T, typename U >
constexpr bool cmp_not_equal(T t, U u) noexcept {
	return !cmp_equal(t, u);
}

template< typename T, typename U >
constexpr bool cmp_less(T t, U u) noexcept {
	using UT = std::make_unsigned_t<T>;
	using UU = std::make_unsigned_t<U>;
	if constexpr (std::is_signed_v<T> == std::is_signed_v<U>)
		return t < u;
	else if constexpr (std::is_signed_v<T>)
		return t < 0 ? true : UT(t) < u;
	else
		return u < 0 ? false : t < UU(u);
}

template< typename T, typename U >
constexpr bool cmp_greater(T t, U u) noexcept {
	return wjr::cmp_less(u, t);
}

template< typename T, typename U >
constexpr bool cmp_less_equal(T t, U u) noexcept {
	return !wjr::cmp_greater(t, u);
}

template< typename T, typename U >
constexpr bool cmp_greater_equal(T t, U u) noexcept {
	return !wjr::cmp_less(t, u);
}

template< typename R, typename T>
constexpr bool in_range(T t) noexcept {
	return wjr::cmp_greater_equal(t, std::numeric_limits<R>::min()) &&
		wjr::cmp_less_equal(t, std::numeric_limits<R>::max());
}

template<typename R, typename T>
struct _Broadcast;

template<typename R, typename T>
inline _Broadcast<R, T> broadcast{};

template<>
struct _Broadcast<uint8_t, uint8_t> {
	constexpr uint8_t operator()(uint8_t x)const {
		return x;
	}
};
template<>
struct _Broadcast<uint16_t, uint16_t> {
	constexpr uint16_t operator()(uint16_t x)const {
		return x;
	}
};
template<>
struct _Broadcast<uint32_t, uint32_t> {
	constexpr uint32_t operator()(uint32_t x)const {
		return x;
	}
};
template<>
struct _Broadcast<uint64_t, uint64_t> {
	constexpr uint64_t operator()(uint64_t x)const {
		return x;
	}
};

template<>
struct _Broadcast<uint16_t, uint8_t> {
	constexpr uint16_t operator()(uint8_t x)const {
		return x | ((uint16_t)x << 8);
	}
};

template<>
struct _Broadcast<uint32_t, uint16_t> {
	constexpr uint32_t operator()(uint16_t x)const {
		return x | ((uint32_t)x << 16);
	}
};
template<>
struct _Broadcast<uint64_t, uint32_t> {
	constexpr uint64_t operator()(uint32_t x)const {
		return x | ((uint64_t)x << 32);
	}
};

template<>
struct _Broadcast<uint32_t, uint8_t> {
	constexpr uint32_t operator()(uint8_t x)const {
		return x * (uint32_t)0x01010101;
	}
};
template<>
struct _Broadcast<uint64_t, uint16_t> {
	constexpr uint64_t operator()(uint16_t x)const {
		return x * (uint64_t)0x0001000100010001;
	}
};

template<>
struct _Broadcast<uint64_t, uint8_t> {
	constexpr uint64_t operator()(uint8_t x)const {
		return x * (uint64_t)0x0101010101010101;
	}
};

_WJR_END

#endif // __WJR_MATH_H__

_WJR_BEGIN

#if WJR_SSE2
template<>
struct _Broadcast<__m128i, uint8_t> {
	__m128i operator()(uint8_t v) const {
		return _mm_set1_epi8(v);
	}
};
template<>
struct _Broadcast<__m128i, uint16_t> {
	__m128i operator()(uint16_t v) const {
		return _mm_set1_epi16(v);
	}
};
template<>
struct _Broadcast<__m128i, uint32_t> {
	__m128i operator()(uint32_t v) const {
		return _mm_set1_epi32(v);
	}
};
template<>
struct _Broadcast<__m128i, uint64_t> {
	__m128i operator()(uint64_t v) const {
		return _mm_set1_epi64x(v);
	}
};
template<>
struct _Broadcast<__m128i, __m128i> {
	__m128i operator()(__m128i v) const {
		return v;
	}
};
#endif // WJR_SSE2

#if WJR_AVX
template<>
struct _Broadcast<__m256i, uint8_t> {
	__m256i operator()(uint8_t v) const {
		return _mm256_set1_epi8(v);
	}
};
template<>
struct _Broadcast<__m256i, uint16_t> {
	__m256i operator()(uint16_t v) const {
		return _mm256_set1_epi16(v);
	}
};
template<>
struct _Broadcast<__m256i, uint32_t> {
	__m256i operator()(uint32_t v) const {
		return _mm256_set1_epi32(v);
	}
};
template<>
struct _Broadcast<__m256i, uint64_t> {
	__m256i operator()(uint64_t v) const {
		return _mm256_set1_epi64x(v);
	}
};
template<>
struct _Broadcast<__m256i, __m256i> {
	__m256i operator()(__m256i v) const {
		return v;
	}
};
template<>
struct _Broadcast<__m256i, __m128i> {
	__m256i operator()(__m128i v) const {
#if WJR_AVX2
		return _mm256_broadcastsi128_si256(v);
#else
		return _mm256_insertf128_si256(_mm256_castsi128_si256(v), v, 1);
#endif // WJR_AVX2
	}
};

#endif // WJR_AVX

_WJR_END

_WJR_SIMD_BEGIN

#if WJR_SSE2

__m128i mm_loadu_si16(void const* p) {
	return simd_cast<__m128i>(*reinterpret_cast<uint16_t const*>(p));
}

__m128i mm_loadu_si32(void const* p) {
	return simd_cast<__m128i>(*reinterpret_cast<int32_t const*>(p));
}

__m128i mm_loadu_si64(void const* p) {
	return simd_cast<__m128i>(*reinterpret_cast<int64_t const*>(p));
}

#endif // WJR_SSE2

/*------SSE------*/

constexpr size_t sse::width() { return 128; }

constexpr sse::mask_type sse::mask() { return 0xFFFF; }

#if WJR_SSE
sse::mask_type sse::movemask_ps(__m128 v) {
	return _mm_movemask_ps(v);
}

void sse::sfence() { return _mm_sfence(); }

template<int imm8>
__m128 sse::shuffle_ps(__m128 a, __m128 b) {
	static_assert(imm8 >= 0 && imm8 <= 255, "imm8 must be in range [0, 255]");
	return _mm_shuffle_ps(a, b, imm8);
}
#endif // WJR_SSE

#if WJR_SSE2

__m128i sse::add_epi8(__m128i a, __m128i b) { return _mm_add_epi8(a, b); }
__m128i sse::add_epi16(__m128i a, __m128i b) { return _mm_add_epi16(a, b); }
__m128i sse::add_epi32(__m128i a, __m128i b) { return _mm_add_epi32(a, b); }
__m128i sse::add_epi64(__m128i a, __m128i b) { return _mm_add_epi64(a, b); }

__m128i sse::add(__m128i a, __m128i b, int8_t) { return add_epi8(a, b); }
__m128i sse::add(__m128i a, __m128i b, int16_t) { return add_epi16(a, b); }
__m128i sse::add(__m128i a, __m128i b, int32_t) { return add_epi32(a, b); }
__m128i sse::add(__m128i a, __m128i b, int64_t) { return add_epi64(a, b); }
__m128i sse::add(__m128i a, __m128i b, uint8_t) { return add_epi8(a, b); }
__m128i sse::add(__m128i a, __m128i b, uint16_t) { return add_epi16(a, b); }
__m128i sse::add(__m128i a, __m128i b, uint32_t) { return add_epi32(a, b); }
__m128i sse::add(__m128i a, __m128i b, uint64_t) { return add_epi64(a, b); }

int8_t sse::add_epi8(__m128i a) { return add_epu8(a); }
int16_t sse::add_epi16(__m128i a) { return add_epu16(a); }
int32_t sse::add_epi32(__m128i a) { return add_epu32(a); }
int64_t sse::add_epi64(__m128i a) { return add_epu64(a); }

uint8_t sse::add_epu8(__m128i a) {
	auto b = shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a);
	a = add(a, b, uint8_t());
	b = zeros();
	a = sad_epu8(a, b);
	return simd_cast<uint8_t>(a);
}

uint16_t sse::add_epu16(__m128i a) {
	a = add(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a), uint16_t());
	a = add(a, shuffle_epi32<_MM_SHUFFLE(1, 1, 1, 1)>(a), uint16_t());
	a = add(a, srli<2>(a), uint16_t());
	return simd_cast<uint16_t>(a);
}

uint32_t sse::add_epu32(__m128i a) {
	a = add(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a), uint32_t());
	a = add(a, shuffle_epi32<_MM_SHUFFLE(1, 1, 1, 1)>(a), uint32_t());
	return simd_cast<uint32_t>(a);
}

uint64_t sse::add_epu64(__m128i a) {
	a = add(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a), uint64_t());
	return simd_cast<uint64_t>(a);
}

int8_t sse::add(__m128i a, int8_t) { return add_epi8(a); }
int16_t sse::add(__m128i a, int16_t) { return add_epi16(a); }
int32_t sse::add(__m128i a, int32_t) { return add_epi32(a); }
int64_t sse::add(__m128i a, int64_t) { return add_epi64(a); }
uint8_t sse::add(__m128i a, uint8_t) { return add_epu8(a); }
uint16_t sse::add(__m128i a, uint16_t) { return add_epu16(a); }
uint32_t sse::add(__m128i a, uint32_t) { return add_epu32(a); }
uint64_t sse::add(__m128i a, uint64_t) { return add_epu64(a); }

__m128i sse::adds_epi8(__m128i a, __m128i b) { return _mm_adds_epi8(a, b); }
__m128i sse::adds_epi16(__m128i a, __m128i b) { return _mm_adds_epi16(a, b); }

__m128i sse::adds_epu8(__m128i a, __m128i b) { return _mm_adds_epu8(a, b); }
__m128i sse::adds_epu16(__m128i a, __m128i b) { return _mm_adds_epu16(a, b); }

__m128i sse::adds(__m128i a, __m128i b, int8_t) { return adds_epi8(a, b); }
__m128i sse::adds(__m128i a, __m128i b, int16_t) { return adds_epi16(a, b); }
__m128i sse::adds(__m128i a, __m128i b, uint8_t) { return adds_epu8(a, b); }
__m128i sse::adds(__m128i a, __m128i b, uint16_t) { return adds_epu16(a, b); }

template<int imm8>
__m128i sse::alignr(__m128i a, __m128i b) {
	constexpr int s = imm8 & 0x1F;
#if WJR_SSSE3
	return _mm_alignr_epi8(a, b, s);
#else
	if constexpr (s == 0) {
		return b;
	}
	if constexpr (s == 16) {
		return a;
	}
	if constexpr (s < 16) {
		return Or(slli<16 - s>(a), srli<s>(b));
	}
	return srli<s - 16>(a);
#endif // WJR_SSSE3
}

__m128i sse::alignr_epi16(__m128i a, __m128i b, int c) {
	return Or(slli(a, 16 - c, uint16_t()), srli(b, c, uint16_t()));
}

__m128i sse::alignr_epi32(__m128i a, __m128i b, int c) {
	return Or(slli(a, 32 - c, uint32_t()), srli(b, c, uint32_t()));
}

__m128i sse::alignr_epi64(__m128i a, __m128i b, int c) {
	return Or(slli(a, 64 - c, uint64_t()), srli(b, c, uint64_t()));
}

__m128i sse::alignr(__m128i a, __m128i b, int c, int16_t) { return alignr_epi16(a, b, c); }
__m128i sse::alignr(__m128i a, __m128i b, int c, int32_t) { return alignr_epi32(a, b, c); }
__m128i sse::alignr(__m128i a, __m128i b, int c, int64_t) { return alignr_epi64(a, b, c); }
__m128i sse::alignr(__m128i a, __m128i b, int c, uint16_t) { return alignr_epi16(a, b, c); }
__m128i sse::alignr(__m128i a, __m128i b, int c, uint32_t) { return alignr_epi32(a, b, c); }
__m128i sse::alignr(__m128i a, __m128i b, int c, uint64_t) { return alignr_epi64(a, b, c); }

__m128i sse::And(__m128i a, __m128i b) { return _mm_and_si128(a, b); }

__m128i sse::AndNot(__m128i a, __m128i b) { return _mm_andnot_si128(a, b); }

__m128i sse::avg_epu8(__m128i a, __m128i b) { return _mm_avg_epu8(a, b); }
__m128i sse::avg_epu16(__m128i a, __m128i b) { return _mm_avg_epu16(a, b); }

__m128i sse::avg(__m128i a, __m128i b, int8_t) { return avg_epu8(a, b); }
__m128i sse::avg(__m128i a, __m128i b, int16_t) { return avg_epu16(a, b); }
__m128i sse::avg(__m128i a, __m128i b, uint8_t) { return avg_epu8(a, b); }
__m128i sse::avg(__m128i a, __m128i b, uint16_t) { return avg_epu16(a, b); }

// notice that mask must be 0 or 255(every byte)
__m128i sse::blendv_epi8(__m128i a, __m128i b, __m128i mask) {
#if WJR_SSE4_1
	return _mm_blendv_epi8(a, b, mask);
#elif defined(WJR_COMPILER_GCC)
	return ((~mask) & a) | (mask & b);
#else
	return Or(AndNot(mask, a), And(mask, b));
#endif // WJR_SSE4_1
}

__m128i sse::blendv_epi16(__m128i a, __m128i b, __m128i mask) {
	return blendv_epi8(b, a, logical_not(mask, uint16_t()));
}

__m128i sse::blendv_epi32(__m128i a, __m128i b, __m128i mask) {
	return blendv_epi8(b, a, logical_not(mask, uint32_t()));
}

__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, int8_t) { return blendv_epi8(a, b, mask); }
__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, int16_t) { return blendv_epi16(a, b, mask); }
__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, int32_t) { return blendv_epi32(a, b, mask); }
__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, uint8_t) { return blendv_epi8(a, b, mask); }
__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, uint16_t) { return blendv_epi16(a, b, mask); }
__m128i sse::blendv(__m128i a, __m128i b, __m128i mask, uint32_t) { return blendv_epi32(a, b, mask); }

template<int imm8>
__m128i sse::bslli(__m128i val) { return _mm_bslli_si128(val, imm8); }

template<int imm8>
__m128i sse::bsrli(__m128i val) { return _mm_bsrli_si128(val, imm8); }

__m128i sse::cmpeq_epi8(__m128i a, __m128i b) { return _mm_cmpeq_epi8(a, b); }
__m128i sse::cmpeq_epi16(__m128i a, __m128i b) { return _mm_cmpeq_epi16(a, b); }
__m128i sse::cmpeq_epi32(__m128i a, __m128i b) { return _mm_cmpeq_epi32(a, b); }

__m128i sse::cmpeq(__m128i a, __m128i b, int8_t) { return cmpeq_epi8(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, int16_t) { return cmpeq_epi16(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, int32_t) { return cmpeq_epi32(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, uint8_t) { return cmpeq_epi8(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, uint16_t) { return cmpeq_epi16(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, uint32_t) { return cmpeq_epi32(a, b); }

__m128i sse::cmpge_epi8(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epi8(a, b);
#elif WJR_SSE4_1
	return cmpeq(min(a, b, int8_t()), b, uint8_t());
#else
	return Not(cmpgt(b, a, int8_t()));
#endif // WJR_XOP
}

__m128i sse::cmpge_epi16(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epi16(a, b);
#else
	return cmpeq(min(a, b, int16_t()), b, uint16_t());
#endif // WJR_XOP
}

__m128i sse::cmpge_epi32(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epi32(a, b);
#elif WJR_SSE4_1
	return cmpeq(min(a, b, int32_t()), b, uint32_t());
#else
	return Not(cmpgt(b, a, int32_t()));
#endif // WJR_XOP
}

__m128i sse::cmpge_epu8(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epu8(a, b);
#else
	return cmpeq(min(a, b, uint8_t()), b, uint8_t());
#endif // WJR_XOP
}

__m128i sse::cmpge_epu16(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epu16(a, b);
#elif WJR_SSE4_1
	return cmpeq(min(a, b, uint16_t()), b, uint16_t());
#else
	return logical_not(subs(b, a, uint16_t()), uint16_t());
#endif // WJR_XOP
}

__m128i sse::cmpge_epu32(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comge_epu32(a, b);
#elif WJR_SSE4_1
	return cmpeq(min(a, b, uint32_t()), b, uint32_t());
#else
	return Not(cmpgt(b, a, uint32_t()));
#endif // WJR_XOP
}

__m128i sse::cmpge(__m128i a, __m128i b, int8_t) { return cmpge_epi8(a, b); }
__m128i sse::cmpge(__m128i a, __m128i b, int16_t) { return cmpge_epi16(a, b); }
__m128i sse::cmpge(__m128i a, __m128i b, int32_t) { return cmpge_epi32(a, b); }
__m128i sse::cmpge(__m128i a, __m128i b, uint8_t) { return cmpge_epu8(a, b); }
__m128i sse::cmpge(__m128i a, __m128i b, uint16_t) { return cmpge_epu16(a, b); }
__m128i sse::cmpge(__m128i a, __m128i b, uint32_t) { return cmpge_epu32(a, b); }

__m128i sse::cmpgt_epi8(__m128i a, __m128i b) { return _mm_cmpgt_epi8(a, b); }
__m128i sse::cmpgt_epi16(__m128i a, __m128i b) { return _mm_cmpgt_epi16(a, b); }
__m128i sse::cmpgt_epi32(__m128i a, __m128i b) { return _mm_cmpgt_epi32(a, b); }

__m128i sse::cmpgt_epu8(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comgt_epu8(a, b);
#else
	return cmpgt_epi8(Xor(a, setmin_epi8()), Xor(b, setmin_epi8()));
#endif // WJR_XOP
}

__m128i sse::cmpgt_epu16(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comgt_epu16(a, b);
#else
	return cmpgt_epi16(Xor(a, setmin_epi16()), Xor(b, setmin_epi16()));
#endif // WJR_XOP
}

__m128i sse::cmpgt_epu32(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comgt_epu32(a, b);
#else
	return cmpgt_epi32(Xor(a, setmin_epi32()), Xor(b, setmin_epi32()));
#endif // WJR_XOP
}

__m128i sse::cmpgt(__m128i a, __m128i b, int8_t) { return cmpgt_epi8(a, b); }
__m128i sse::cmpgt(__m128i a, __m128i b, int16_t) { return cmpgt_epi16(a, b); }
__m128i sse::cmpgt(__m128i a, __m128i b, int32_t) { return cmpgt_epi32(a, b); }
__m128i sse::cmpgt(__m128i a, __m128i b, uint8_t) { return cmpgt_epu8(a, b); }
__m128i sse::cmpgt(__m128i a, __m128i b, uint16_t) { return cmpgt_epu16(a, b); }
__m128i sse::cmpgt(__m128i a, __m128i b, uint32_t) { return cmpgt_epu32(a, b); }

__m128i sse::cmple_epi8(__m128i a, __m128i b) { return cmpge_epi8(b, a); }
__m128i sse::cmple_epi16(__m128i a, __m128i b) { return cmpge_epi16(b, a); }
__m128i sse::cmple_epi32(__m128i a, __m128i b) { return cmpge_epi32(b, a); }

__m128i sse::cmple_epu8(__m128i a, __m128i b) { return cmpge_epu8(b, a); }
__m128i sse::cmple_epu16(__m128i a, __m128i b) { return cmpge_epu16(b, a); }
__m128i sse::cmple_epu32(__m128i a, __m128i b) { return cmpge_epu32(b, a); }

__m128i sse::cmple(__m128i a, __m128i b, int8_t) { return cmple_epi8(a, b); }
__m128i sse::cmple(__m128i a, __m128i b, int16_t) { return cmple_epi16(a, b); }
__m128i sse::cmple(__m128i a, __m128i b, int32_t) { return cmple_epi32(a, b); }
__m128i sse::cmple(__m128i a, __m128i b, uint8_t) { return cmple_epu8(a, b); }
__m128i sse::cmple(__m128i a, __m128i b, uint16_t) { return cmple_epu16(a, b); }
__m128i sse::cmple(__m128i a, __m128i b, uint32_t) { return cmple_epu32(a, b); }

__m128i sse::cmplt_epi8(__m128i a, __m128i b) { return _mm_cmplt_epi8(a, b); }
__m128i sse::cmplt_epi16(__m128i a, __m128i b) { return _mm_cmplt_epi16(a, b); }
__m128i sse::cmplt_epi32(__m128i a, __m128i b) { return _mm_cmplt_epi32(a, b); }

__m128i sse::cmplt_epu8(__m128i a, __m128i b) { return cmpgt_epu8(b, a); }
__m128i sse::cmplt_epu16(__m128i a, __m128i b) { return cmpgt_epu16(b, a); }
__m128i sse::cmplt_epu32(__m128i a, __m128i b) { return cmpgt_epu32(b, a); }

__m128i sse::cmplt(__m128i a, __m128i b, int8_t) { return cmplt_epi8(a, b); }
__m128i sse::cmplt(__m128i a, __m128i b, int16_t) { return cmplt_epi16(a, b); }
__m128i sse::cmplt(__m128i a, __m128i b, int32_t) { return cmplt_epi32(a, b); }
__m128i sse::cmplt(__m128i a, __m128i b, uint8_t) { return cmplt_epu8(a, b); }
__m128i sse::cmplt(__m128i a, __m128i b, uint16_t) { return cmplt_epu16(a, b); }
__m128i sse::cmplt(__m128i a, __m128i b, uint32_t) { return cmplt_epu32(a, b); }

__m128i sse::cmpne_epi8(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comneq_epi8(a, b);
#else
	return Not(cmpeq_epi8(a, b));
#endif
}

__m128i sse::cmpne_epi16(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comneq_epi16(a, b);
#else
	return Not(cmpeq_epi16(a, b));
#endif
}

__m128i sse::cmpne_epi32(__m128i a, __m128i b) {
#if WJR_XOP
	return _mm_comneq_epi32(a, b);
#else
	return Not(cmpeq_epi32(a, b));
#endif
}

__m128i sse::cmpne(__m128i a, __m128i b, int8_t) { return cmpne_epi8(a, b); }
__m128i sse::cmpne(__m128i a, __m128i b, int16_t) { return cmpne_epi16(a, b); }
__m128i sse::cmpne(__m128i a, __m128i b, int32_t) { return cmpne_epi32(a, b); }
__m128i sse::cmpne(__m128i a, __m128i b, uint8_t) { return cmpne_epi8(a, b); }
__m128i sse::cmpne(__m128i a, __m128i b, uint16_t) { return cmpne_epi16(a, b); }
__m128i sse::cmpne(__m128i a, __m128i b, uint32_t) { return cmpne_epi32(a, b); }

template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::equal_to<>, T) { return cmpeq(a, b, T()); }
template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::not_equal_to<>, T) { return cmpne(a, b, T()); }
template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::greater<>, T) { return cmpgt(a, b, T()); }
template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::greater_equal<>, T) { return cmpge(a, b, T()); }
template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::less<>, T) { return cmplt(a, b, T()); }
template<typename T>
__m128i sse::cmp(__m128i a, __m128i b, std::less_equal<>, T) { return cmple(a, b, T()); }

__m128i sse::concat(uint64_t lo, uint64_t hi) { return set_epi64x(hi, lo); }

template<int imm8>
int sse::extract_epi8(__m128i a) {
	static_assert(imm8 >= 0 && imm8 < 16, "imm8 must be in range [0, 15]");
#if WJR_SSE4_1
	return _mm_extract_epi8(a, imm8);
#else
	if constexpr (imm8 & 1) {
		return extract_epi16<(imm8 >> 1)>(a) >> 8;
	}
	else {
		return extract_epi16 <(imm8 >> 1)>(a) & 0xff;
	}
#endif // WJR_SSE4_1
}

template<int imm8>
int sse::extract_epi16(__m128i a) {
	static_assert(imm8 >= 0 && imm8 < 8, "imm8 must be in range [0, 7]");
	return _mm_extract_epi16(a, imm8);
}

template<int imm8>
int sse::extract_epi32(__m128i a) {
	static_assert(imm8 >= 0 && imm8 < 4, "imm8 must be in range [0, 3]");
#if WJR_SSE4_1
	return _mm_extract_epi32(a, imm8);
#else
	if constexpr (imm8 == 0) {
		return simd_cast<uint32_t>(a);
	}
	else if constexpr (imm8 == 1) {
		return static_cast<uint32_t>(simd_cast<uint64_t>(a) >> 32);
	}
	else if constexpr (imm8 == 2) {
		return simd_cast<uint32_t>(shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	}
	else {
		return simd_cast<uint32_t>(shuffle_epi32<_MM_SHUFFLE(3, 3, 3, 3)>(a));
	}
#endif // WJR_SSE4_1
}

template<int imm8>
int64_t sse::extract_epi64(__m128i a) {
	static_assert(imm8 >= 0 && imm8 < 2, "imm8 must be in range [0, 1]");
#if WJR_SSE4_1
	return _mm_extract_epi64(a, imm8);
#else
	if constexpr (imm8 == 0) {
		return simd_cast<uint64_t>(a);
	}
	else {
		return simd_cast<uint64_t>(shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	}
#endif // WJR_SSE4_1
}

template<int imm8>
int sse::extract(__m128i a, int8_t) { return extract_epi8<imm8>(a); }
template<int imm8>
int sse::extract(__m128i a, int16_t) { return extract_epi16<imm8>(a); }
template<int imm8>
int sse::extract(__m128i a, int32_t) { return extract_epi32<imm8>(a); }
template<int imm8>
int64_t sse::extract(__m128i a, int64_t) { return extract_epi64<imm8>(a); }
template<int imm8>
int sse::extract(__m128i a, uint8_t) { return extract_epi8<imm8>(a); }
template<int imm8>
int sse::extract(__m128i a, uint16_t) { return extract_epi16<imm8>(a); }
template<int imm8>
int sse::extract(__m128i a, uint32_t) { return extract_epi32<imm8>(a); }
template<int imm8>
int64_t sse::extract(__m128i a, uint64_t) { return extract_epi64<imm8>(a); }

uint64_t sse::getlow(__m128i v) { return simd_cast<uint64_t>(v); }
uint64_t sse::gethigh(__m128i v) { return extract_epi64<1>(v); }

template<int imm8>
__m128i sse::insert_epi16(__m128i a, int i) {
	return _mm_insert_epi16(a, i, imm8);
}

template<int imm8>
__m128i sse::insert(__m128i a, int i, int16_t) { return insert_epi16<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int i, uint16_t) { return insert_epi16<imm8>(a, i); }

void sse::lfence() { _mm_lfence(); }

__m128i sse::load(const __m128i* ptr) { return _mm_load_si128(ptr); }
__m128i sse::loadu(const __m128i* ptr) { return _mm_loadu_si128(ptr); }
__m128i sse::loadu_si16(const void* ptr) { return simd::mm_loadu_si16(ptr); }
__m128i sse::loadu_si32(const void* ptr) { return simd::mm_loadu_si32(ptr); }
__m128i sse::loadu_si64(const void* ptr) { return simd::mm_loadu_si64(ptr); }

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m128i sse::logical_and(__m128i a, __m128i b, T) {
	return Not(Or(logical_not(a, T()), logical_not(b, T())));
}

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m128i sse::logical_not(__m128i v, T) {
	auto Zero = zeros();
	return cmpeq(v, Zero, T());
}

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m128i sse::logical_or(__m128i a, __m128i b, T) {
	return Not(logical_not(Or(a, b), T()));
}

__m128i sse::madd_epi16(__m128i a, __m128i b) {
	return _mm_madd_epi16(a, b);
}

void sse::maskmoveu(__m128i a, __m128i mask, char* mem_addr) {
	return _mm_maskmoveu_si128(a, mask, mem_addr);
}

__m128i sse::max_epi8(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_max_epi8(a, b);
#else
	return blendv_epi8(b, a, cmpgt_epi8(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::max_epi16(__m128i a, __m128i b) { return _mm_max_epi16(a, b); }

__m128i sse::max_epi32(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_max_epi32(a, b);
#else
	return blendv_epi8(b, a, cmpgt_epi32(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::max_epu8(__m128i a, __m128i b) { return _mm_max_epu8(a, b); }

__m128i sse::max_epu16(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_max_epu16(a, b);
#else
	return add(subs_epu16(b, a), a, uint16_t());
#endif // WJR_SSE4_1
}

__m128i sse::max_epu32(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_max_epu32(a, b);
#else
	return blendv_epi8(b, a, cmpgt_epu32(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::max(__m128i a, __m128i b, int8_t) { return max_epi8(a, b); }
__m128i sse::max(__m128i a, __m128i b, int16_t) { return max_epi16(a, b); }
__m128i sse::max(__m128i a, __m128i b, int32_t) { return max_epi32(a, b); }
__m128i sse::max(__m128i a, __m128i b, uint8_t) { return max_epu8(a, b); }
__m128i sse::max(__m128i a, __m128i b, uint16_t) { return max_epu16(a, b); }
__m128i sse::max(__m128i a, __m128i b, uint32_t) { return max_epu32(a, b); }

int8_t sse::max_epi8(__m128i a) {
	return 0x7fu ^ min_epu8(Xor(a, set1_epi8(0x7fu)));
}

int16_t sse::max_epi16(__m128i a) {
#if WJR_SSE4_1
	return 0x7fffu ^ min_epu16(Xor(a, set1_epi16(0x7fffu)));
#else
	a = max_epi16(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = max_epi16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = max_epi16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	return simd_cast<int16_t>(a);
#endif // WJR_SSE4_1
}

int32_t sse::max_epi32(__m128i a) {
	a = max_epi32(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = max_epi32(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	return simd_cast<int32_t>(a);
}

uint8_t sse::max_epu8(__m128i a) {
#if WJR_SSE4_1
	return 0xffu ^ min_epu8(Xor(a, ones()));
#else
	a = max_epu8(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = max_epu8(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = max_epu8(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	auto X = simd_cast<uint32_t>(a);
	return std::max((uint8_t)X, (uint8_t)(X >> 8));
#endif // WJR_SSE4_1
}

uint16_t sse::max_epu16(__m128i a) {
#if WJR_SSE4_1
	return 0xffffu ^ min_epu16(Xor(a, ones()));
#else
	a = max_epu16(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = max_epu16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = max_epu16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	return simd_cast<uint16_t>(a);
#endif // WJR_SSE4_1
}

uint32_t sse::max_epu32(__m128i a) {
	a = max_epu32(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = max_epu32(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	return simd_cast<uint32_t>(a);
}

int8_t sse::max(__m128i a, int8_t) { return max_epi8(a); }
int16_t sse::max(__m128i a, int16_t) { return max_epi16(a); }
int32_t sse::max(__m128i a, int32_t) { return max_epi32(a); }
uint8_t sse::max(__m128i a, uint8_t) { return max_epu8(a); }
uint16_t sse::max(__m128i a, uint16_t) { return max_epu16(a); }
uint32_t sse::max(__m128i a, uint32_t) { return max_epu32(a); }

void sse::mfence() { _mm_mfence(); }

__m128i sse::min_epi8(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_min_epi8(a, b);
#else
	return blendv_epi8(a, b, cmpgt_epi8(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::min_epi16(__m128i a, __m128i b) { return _mm_min_epi16(a, b); }

__m128i sse::min_epi32(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_min_epi32(a, b);
#else
	return blendv_epi8(a, b, cmpgt_epi32(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::min_epu8(__m128i a, __m128i b) { return _mm_min_epu8(a, b); }

__m128i sse::min_epu16(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_min_epu16(a, b);
#else
	return blendv_epi8(a, b, cmpgt_epu16(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::min_epu32(__m128i a, __m128i b) {
#if WJR_SSE4_1
	return _mm_min_epu32(a, b);
#else
	return blendv_epi8(a, b, cmpgt_epu32(a, b));
#endif // WJR_SSE4_1
}

__m128i sse::min(__m128i a, __m128i b, int8_t) { return min_epi8(a, b); }
__m128i sse::min(__m128i a, __m128i b, int16_t) { return min_epi16(a, b); }
__m128i sse::min(__m128i a, __m128i b, int32_t) { return min_epi32(a, b); }
__m128i sse::min(__m128i a, __m128i b, uint8_t) { return min_epu8(a, b); }
__m128i sse::min(__m128i a, __m128i b, uint16_t) { return min_epu16(a, b); }
__m128i sse::min(__m128i a, __m128i b, uint32_t) { return min_epu32(a, b); }

int8_t sse::min_epi8(__m128i a) {
	return 0x80u ^ min_epu8(Xor(a, setmin_epi8()));
}

int16_t sse::min_epi16(__m128i a) {
#if WJR_SSE4_1
	return 0x8000u ^ min_epu16(Xor(a, setmin_epi16()));
#else
	a = min_epi16(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = min_epi16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = min_epi16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	return simd_cast<int16_t>(a);
#endif // WJR_SSE4_1
}

int32_t sse::min_epi32(__m128i a) {
	a = min_epi32(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = min_epi32(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	return simd_cast<int32_t>(a);
}

uint8_t sse::min_epu8(__m128i a) {
#if WJR_SSE4_1
	a = min_epu8(a, srli_epi16(a, 8));
	a = _mm_minpos_epu16(a);
	return simd_cast<uint8_t>(a);
#else
	a = min_epu8(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = min_epu8(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = min_epu8(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	auto X = simd_cast<uint32_t>(a);
	return std::min((uint8_t)X, (uint8_t)(X >> 8));
#endif // WJR_SSE4_1
}

uint16_t sse::min_epu16(__m128i a) {
#if WJR_SSE4_1
	return simd_cast<uint16_t>(_mm_minpos_epu16(a));
#else
	a = min_epu16(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = min_epu16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	a = min_epu16(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 1, 0)>(a));
	return simd_cast<uint16_t>(a);
#endif // WJR_SSE4_1
}

uint32_t sse::min_epu32(__m128i a) {
	a = min_epu32(a, shuffle_epi32<_MM_SHUFFLE(3, 2, 3, 2)>(a));
	a = min_epu32(a, shufflelo_epi16<_MM_SHUFFLE(1, 0, 3, 2)>(a));
	return simd_cast<uint32_t>(a);
}

int8_t sse::min(__m128i a, int8_t) { return min_epi8(a); }
int16_t sse::min(__m128i a, int16_t) { return min_epi16(a); }
int32_t sse::min(__m128i a, int32_t) { return min_epi32(a); }
uint8_t sse::min(__m128i a, uint8_t) { return min_epu8(a); }
uint16_t sse::min(__m128i a, uint16_t) { return min_epu16(a); }
uint32_t sse::min(__m128i a, uint32_t) { return min_epu32(a); }

__m128i sse::move_epi64(__m128i a) { return _mm_move_epi64(a); }

sse::mask_type sse::movemask_epi8(__m128i a) { return _mm_movemask_epi8(a); }
sse::mask_type sse::movemask_pd(__m128d v) { return _mm_movemask_pd(v); }

sse::mask_type sse::movemask(__m128i v, int8_t) { return movemask_epi8(v); }
sse::mask_type sse::movemask(__m128i v, int32_t) { return movemask_ps(simd_cast<__m128>(v)); }
sse::mask_type sse::movemask(__m128i v, int64_t) { return movemask_pd(simd_cast<__m128d>(v)); }
sse::mask_type sse::movemask(__m128i v, uint8_t) { return movemask(v, int8_t()); }
sse::mask_type sse::movemask(__m128i v, uint32_t) { return movemask(v, int32_t()); }
sse::mask_type sse::movemask(__m128i v, uint64_t) { return movemask(v, int64_t()); }

__m128i sse::mul_epu32(__m128i a, __m128i b) { return _mm_mul_epu32(a, b); }

__m128i sse::mulhi_epi16(__m128i a, __m128i b) { return _mm_mulhi_epi16(a, b); }

__m128i sse::mulhi_epu16(__m128i a, __m128i b) { return _mm_mulhi_epu16(a, b); }

__m128i sse::mullo_epi16(__m128i a, __m128i b) { return _mm_mullo_epi16(a, b); }

__m128i sse::negate_epi8(__m128i a) {
#if WJR_SSSE3
	return sign_epi8(a, ones());
#else
	return sub_epi8(zeros(), a);
#endif // WJR_SSSE3
}

__m128i sse::negate_epi16(__m128i a) {
#if WJR_SSSE3
	return sign_epi16(a, ones());
#else
	return sub_epi16(zeros(), a);
#endif // WJR_SSSE3
}

__m128i sse::negate_epi32(__m128i a) {
#if WJR_SSSE3
	return sign_epi32(a, ones());
#else
	return sub_epi32(zeros(), a);
#endif // WJR_SSSE3
}

__m128i sse::negate_epi64(__m128i a) {
	return sub_epi64(zeros(), a);
}

__m128i sse::negate(__m128i a, int8_t) { return negate_epi8(a); }
__m128i sse::negate(__m128i a, int16_t) { return negate_epi16(a); }
__m128i sse::negate(__m128i a, int32_t) { return negate_epi32(a); }
__m128i sse::negate(__m128i a, int64_t) { return negate_epi64(a); }
__m128i sse::negate(__m128i a, uint8_t) { return negate_epi8(a); }
__m128i sse::negate(__m128i a, uint16_t) { return negate_epi16(a); }
__m128i sse::negate(__m128i a, uint32_t) { return negate_epi32(a); }
__m128i sse::negate(__m128i a, uint64_t) { return negate_epi64(a); }

__m128i sse::Not(__m128i v) { return Xor(v, ones()); }

__m128i sse::Or(__m128i a, __m128i b) { return _mm_or_si128(a, b); }

__m128i sse::packs_epi16(__m128i a, __m128i b) { return _mm_packs_epi16(a, b); }
__m128i sse::packs_epi32(__m128i a, __m128i b) { return _mm_packs_epi32(a, b); }

__m128i sse::packus_epi16(__m128i a, __m128i b) { return _mm_packus_epi16(a, b); }

__m128i sse::preloadu_si16(const void* ptr) { return loadu_si16(ptr); }
__m128i sse::preloadu_si32(const void* ptr) { return loadu_si32(ptr); }

__m128i sse::preloadu_si48(const void* ptr) {
	return insert_epi16<2>(preloadu_si32(ptr), reinterpret_cast<const uint16_t*>(ptr)[2]);
}

__m128i sse::preloadu_si64(const void* ptr) { return loadu_si64(ptr); }

__m128i sse::preloadu_si80(const void* ptr) {
	return insert_epi16<4>(preloadu_si64(ptr), reinterpret_cast<const uint16_t*>(ptr)[4]);
}

__m128i sse::preloadu_si96(const void* ptr) {
#if WJR_SSE4_1
	return insert_epi32<2>(preloadu_si64(ptr), reinterpret_cast<const uint32_t*>(ptr)[2]);
#else
	return insert_epi16<5>(preloadu_si80(ptr), reinterpret_cast<const uint16_t*>(ptr)[5]);
#endif // WJR_SSE4_1
}

__m128i sse::preloadu_si112(const void* ptr) {
	return insert_epi16<6>(preloadu_si96(ptr), reinterpret_cast<const uint16_t*>(ptr)[6]);
}

__m128i sse::preloadu_si128(const void* ptr) { return loadu((__m128i*)ptr); }

__m128i sse::preloadu_si16x(const void* ptr, int n) {
	// preloadu_si(n * 16)
	switch (n) {
	case 0:return zeros();
	case 1:return preloadu_si16(ptr);
	case 2:return preloadu_si32(ptr);
	case 3:return preloadu_si48(ptr);
	case 4:return preloadu_si64(ptr);
	case 5:return preloadu_si80(ptr);
	case 6:return preloadu_si96(ptr);
	case 7:return preloadu_si112(ptr);
	default:return preloadu_si128(ptr);
	}
}

__m128i sse::sad_epu8(__m128i a, __m128i b) { return _mm_sad_epu8(a, b); }

__m128i sse::zeros() { return _mm_setzero_si128(); }
__m128i sse::ones() { return _mm_set1_epi32(-1); }

__m128i sse::set_epi8(
	char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
	char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0) {
	return _mm_set_epi8(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
}

__m128i sse::set_epi16(
	short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0) {
	return _mm_set_epi16(e7, e6, e5, e4, e3, e2, e1, e0);
}
__m128i sse::set_epi32(int e3, int e2, int e1, int e0) {
	return _mm_set_epi32(e3, e2, e1, e0);
}
__m128i sse::set_epi64x(long long e1, long long e0) {
	return _mm_set_epi64x(e1, e0);
}

__m128i sse::setr_epi8(
	char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
	char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0) {
	return _mm_setr_epi8(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
}

__m128i sse::setr_epi16(
	short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0) {
	return _mm_setr_epi16(e7, e6, e5, e4, e3, e2, e1, e0);
}
__m128i sse::setr_epi32(int e3, int e2, int e1, int e0) {
	return _mm_setr_epi32(e3, e2, e1, e0);
}

__m128i sse::set1_epi8(int8_t val) { return _mm_set1_epi8(val); }
__m128i sse::set1_epi16(int16_t val) { return _mm_set1_epi16(val); }
__m128i sse::set1_epi32(int32_t val) { return _mm_set1_epi32(val); }
__m128i sse::set1_epi64(int64_t val) { return _mm_set1_epi64x(val); }

__m128i sse::set1(int8_t val, int8_t) { return set1_epi8(val); }
__m128i sse::set1(int16_t val, int16_t) { return set1_epi16(val); }
__m128i sse::set1(int32_t val, int32_t) { return set1_epi32(val); }
__m128i sse::set1(int64_t val, int64_t) { return set1_epi64(val); }
__m128i sse::set1(uint8_t val, uint8_t) { return set1_epi8(val); }
__m128i sse::set1(uint16_t val, uint16_t) { return set1_epi16(val); }
__m128i sse::set1(uint32_t val, uint32_t) { return set1_epi32(val); }
__m128i sse::set1(uint64_t val, uint64_t) { return set1_epi64(val); }

__m128i sse::setmin_epi8() { return set1_epi8(0x80u); }
__m128i sse::setmin_epi16() { return set1_epi16(0x8000u); }
__m128i sse::setmin_epi32() { return set1_epi32(0x80000000u); }

__m128i sse::setmin(int8_t) { return setmin_epi8(); }
__m128i sse::setmin(int16_t) { return setmin_epi16(); }
__m128i sse::setmin(int32_t) { return setmin_epi32(); }
__m128i sse::setmin(uint8_t) { return set1_epi32(0); }
__m128i sse::setmin(uint16_t) { return set1_epi32(0); }
__m128i sse::setmin(uint32_t) { return set1_epi32(0); }

__m128i sse::setmax_epi8() { return set1_epi8(0x7F); }
__m128i sse::setmax_epi16() { return set1_epi16(0x7FFF); }
__m128i sse::setmax_epi32() { return set1_epi32(0x7FFFFFFF); }

__m128i sse::setmax(int8_t) { return setmax_epi8(); }
__m128i sse::setmax(int16_t) { return setmax_epi16(); }
__m128i sse::setmax(int32_t) { return setmax_epi32(); }
__m128i sse::setmax(uint8_t) { return set1_epi32(0xFFFFFFFF); }
__m128i sse::setmax(uint16_t) { return set1_epi32(0xFFFFFFFF); }
__m128i sse::setmax(uint32_t) { return set1_epi32(0xFFFFFFFF); }

template<int imm8>
__m128i sse::shuffle_epi32(__m128i v) {
	static_assert(imm8 >= 0 && imm8 <= 255, "imm8 must be in range [0, 255]");
	return _mm_shuffle_epi32(v, imm8);
}

template<int imm8>
__m128i sse::shufflehi_epi16(__m128i v) {
	return _mm_shufflehi_epi16(v, imm8);
}

template<int imm8>
__m128i sse::shufflelo_epi16(__m128i v) {
	return _mm_shufflelo_epi16(v, imm8);
}

__m128i sse::sll_epi16(__m128i a, __m128i b) {
	return _mm_sll_epi16(a, b);
}
__m128i sse::sll_epi32(__m128i a, __m128i b) {
	return _mm_sll_epi32(a, b);
}
__m128i sse::sll_epi64(__m128i a, __m128i b) {
	return _mm_sll_epi64(a, b);
}

__m128i sse::sll(__m128i a, __m128i b, int16_t) { return sll_epi16(a, b); }
__m128i sse::sll(__m128i a, __m128i b, int32_t) { return sll_epi32(a, b); }
__m128i sse::sll(__m128i a, __m128i b, int64_t) { return sll_epi64(a, b); }
__m128i sse::sll(__m128i a, __m128i b, uint16_t) { return sll_epi16(a, b); }
__m128i sse::sll(__m128i a, __m128i b, uint32_t) { return sll_epi32(a, b); }
__m128i sse::sll(__m128i a, __m128i b, uint64_t) { return sll_epi64(a, b); }

template<int imm8>
__m128i sse::slli(__m128i v) {
	return _mm_slli_si128(v, imm8);
}
__m128i sse::slli_epi16(__m128i a, int imm8) {
	return _mm_slli_epi16(a, imm8);
}
__m128i sse::slli_epi32(__m128i a, int imm8) {
	return _mm_slli_epi32(a, imm8);
}
__m128i sse::slli_epi64(__m128i a, int imm8) {
	return _mm_slli_epi64(a, imm8);
}

__m128i sse::slli(__m128i a, int imm8, int16_t) { return slli_epi16(a, imm8); }
__m128i sse::slli(__m128i a, int imm8, int32_t) { return slli_epi32(a, imm8); }
__m128i sse::slli(__m128i a, int imm8, int64_t) { return slli_epi64(a, imm8); }
__m128i sse::slli(__m128i a, int imm8, uint16_t) { return slli_epi16(a, imm8); }
__m128i sse::slli(__m128i a, int imm8, uint32_t) { return slli_epi32(a, imm8); }
__m128i sse::slli(__m128i a, int imm8, uint64_t) { return slli_epi64(a, imm8); }

__m128i sse::sra_epi16(__m128i a, __m128i b) { return _mm_sra_epi16(a, b); }
__m128i sse::sra_epi32(__m128i a, __m128i b) { return _mm_sra_epi32(a, b); }

__m128i sse::sra(__m128i a, __m128i b, int16_t) { return sra_epi16(a, b); }
__m128i sse::sra(__m128i a, __m128i b, int32_t) { return sra_epi32(a, b); }

__m128i sse::srai_epi16(__m128i a, int imm8) { return _mm_srai_epi16(a, imm8); }
__m128i sse::srai_epi32(__m128i a, int imm8) { return _mm_srai_epi32(a, imm8); }

__m128i sse::srai(__m128i a, int imm8, int16_t) { return srai_epi16(a, imm8); }
__m128i sse::srai(__m128i a, int imm8, int32_t) { return srai_epi32(a, imm8); }

__m128i sse::srl_epi16(__m128i a, __m128i b) { return _mm_srl_epi16(a, b); }
__m128i sse::srl_epi32(__m128i a, __m128i b) { return _mm_srl_epi32(a, b); }
__m128i sse::srl_epi64(__m128i a, __m128i b) { return _mm_srl_epi64(a, b); }

__m128i sse::srl(__m128i a, __m128i b, int16_t) { return srl_epi16(a, b); }
__m128i sse::srl(__m128i a, __m128i b, int32_t) { return srl_epi32(a, b); }
__m128i sse::srl(__m128i a, __m128i b, int64_t) { return srl_epi64(a, b); }
__m128i sse::srl(__m128i a, __m128i b, uint16_t) { return srl_epi16(a, b); }
__m128i sse::srl(__m128i a, __m128i b, uint32_t) { return srl_epi32(a, b); }
__m128i sse::srl(__m128i a, __m128i b, uint64_t) { return srl_epi64(a, b); }

template<int imm8>
__m128i sse::srli(__m128i v) {
	return _mm_srli_si128(v, imm8);
}
__m128i sse::srli_epi16(__m128i a, int imm8) {
	return _mm_srli_epi16(a, imm8);
}
__m128i sse::srli_epi32(__m128i a, int imm8) {
	return _mm_srli_epi32(a, imm8);
}
__m128i sse::srli_epi64(__m128i a, int imm8) {
	return _mm_srli_epi64(a, imm8);
}

__m128i sse::srli(__m128i a, int imm8, int16_t) { return srli_epi16(a, imm8); }
__m128i sse::srli(__m128i a, int imm8, int32_t) { return srli_epi32(a, imm8); }
__m128i sse::srli(__m128i a, int imm8, int64_t) { return srli_epi64(a, imm8); }
__m128i sse::srli(__m128i a, int imm8, uint16_t) { return srli_epi16(a, imm8); }
__m128i sse::srli(__m128i a, int imm8, uint32_t) { return srli_epi32(a, imm8); }
__m128i sse::srli(__m128i a, int imm8, uint64_t) { return srli_epi64(a, imm8); }

void sse::stream(__m128i* ptr, __m128i v) { _mm_stream_si128(ptr, v); }

void sse::store(__m128i* ptr, __m128i val) { _mm_store_si128(ptr, val); }
void sse::storeu(__m128i* ptr, __m128i val) { _mm_storeu_si128(ptr, val); }

__m128i sse::sub_epi8(__m128i a, __m128i b) { return _mm_sub_epi8(a, b); }
__m128i sse::sub_epi16(__m128i a, __m128i b) { return _mm_sub_epi16(a, b); }
__m128i sse::sub_epi32(__m128i a, __m128i b) { return _mm_sub_epi32(a, b); }
__m128i sse::sub_epi64(__m128i a, __m128i b) { return _mm_sub_epi64(a, b); }

__m128i sse::sub(__m128i a, __m128i b, int8_t) { return sub_epi8(a, b); }
__m128i sse::sub(__m128i a, __m128i b, int16_t) { return sub_epi16(a, b); }
__m128i sse::sub(__m128i a, __m128i b, int32_t) { return sub_epi32(a, b); }
__m128i sse::sub(__m128i a, __m128i b, int64_t) { return sub_epi64(a, b); }
__m128i sse::sub(__m128i a, __m128i b, uint8_t) { return sub_epi8(a, b); }
__m128i sse::sub(__m128i a, __m128i b, uint16_t) { return sub_epi16(a, b); }
__m128i sse::sub(__m128i a, __m128i b, uint32_t) { return sub_epi32(a, b); }
__m128i sse::sub(__m128i a, __m128i b, uint64_t) { return sub_epi64(a, b); }

__m128i sse::subs_epi8(__m128i a, __m128i b) { return _mm_subs_epi8(a, b); }
__m128i sse::subs_epi16(__m128i a, __m128i b) { return _mm_subs_epi16(a, b); }

__m128i sse::subs_epu8(__m128i a, __m128i b) { return _mm_subs_epu8(a, b); }
__m128i sse::subs_epu16(__m128i a, __m128i b) { return _mm_subs_epu16(a, b); }

__m128i sse::subs(__m128i a, __m128i b, int8_t) { return subs_epi8(a, b); }
__m128i sse::subs(__m128i a, __m128i b, int16_t) { return subs_epi16(a, b); }
__m128i sse::subs(__m128i a, __m128i b, uint8_t) { return subs_epu8(a, b); }
__m128i sse::subs(__m128i a, __m128i b, uint16_t) { return subs_epu16(a, b); }

__m128i sse::unpackhi_epi8(__m128i a, __m128i b) { return _mm_unpackhi_epi8(a, b); }
__m128i sse::unpackhi_epi16(__m128i a, __m128i b) { return _mm_unpackhi_epi16(a, b); }
__m128i sse::unpackhi_epi32(__m128i a, __m128i b) { return _mm_unpackhi_epi32(a, b); }
__m128i sse::unpackhi_epi64(__m128i a, __m128i b) { return _mm_unpackhi_epi64(a, b); }

__m128i sse::unpackhi(__m128i a, __m128i b, int8_t) { return unpackhi_epi8(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, int16_t) { return unpackhi_epi16(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, int32_t) { return unpackhi_epi32(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, int64_t) { return unpackhi_epi64(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, uint8_t) { return unpackhi_epi8(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, uint16_t) { return unpackhi_epi16(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, uint32_t) { return unpackhi_epi32(a, b); }
__m128i sse::unpackhi(__m128i a, __m128i b, uint64_t) { return unpackhi_epi64(a, b); }

__m128i sse::unpacklo_epi8(__m128i a, __m128i b) { return _mm_unpacklo_epi8(a, b); }
__m128i sse::unpacklo_epi16(__m128i a, __m128i b) { return _mm_unpacklo_epi16(a, b); }
__m128i sse::unpacklo_epi32(__m128i a, __m128i b) { return _mm_unpacklo_epi32(a, b); }
__m128i sse::unpacklo_epi64(__m128i a, __m128i b) { return _mm_unpacklo_epi64(a, b); }

__m128i sse::unpacklo(__m128i a, __m128i b, int8_t) { return unpacklo_epi8(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, int16_t) { return unpacklo_epi16(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, int32_t) { return unpacklo_epi32(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, int64_t) { return unpacklo_epi64(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, uint8_t) { return unpacklo_epi8(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, uint16_t) { return unpacklo_epi16(a, b); }
__m128i sse::unpacklo(__m128i a, __m128i b, uint32_t) { return unpacklo_epi32(a, b); }

__m128i sse::Xor(__m128i a, __m128i b) { return _mm_xor_si128(a, b); }

#endif // WJR_SSE2

#if WJR_SSE3
__m128i sse::lddqu(const __m128i* ptr) { return _mm_lddqu_si128(ptr); }
#endif // WJR_SSE3

#if WJR_SSSE3

__m128i sse::abs_epi8(__m128i val) { return _mm_abs_epi8(val); }
__m128i sse::abs_epi16(__m128i val) { return _mm_abs_epi16(val); }
__m128i sse::abs_epi32(__m128i val) { return _mm_abs_epi32(val); }

__m128i sse::abs(__m128i val, int8_t) { return abs_epi8(val); }
__m128i sse::abs(__m128i val, int16_t) { return abs_epi16(val); }
__m128i sse::abs(__m128i val, int32_t) { return abs_epi32(val); }
__m128i sse::abs(__m128i val, uint8_t) { return val; }
__m128i sse::abs(__m128i val, uint16_t) { return val; }
__m128i sse::abs(__m128i val, uint32_t) { return val; }

__m128i sse::shuffle_epi8(__m128i v, __m128i imm8) { return _mm_shuffle_epi8(v, imm8); }

__m128i sse::sign_epi8(__m128i a, __m128i b) { return _mm_sign_epi8(a, b); }
__m128i sse::sign_epi16(__m128i a, __m128i b) { return _mm_sign_epi16(a, b); }
__m128i sse::sign_epi32(__m128i a, __m128i b) { return _mm_sign_epi32(a, b); }

__m128i sse::sign(__m128i a, __m128i b, int8_t) { return sign_epi8(a, b); }
__m128i sse::sign(__m128i a, __m128i b, int16_t) { return sign_epi16(a, b); }
__m128i sse::sign(__m128i a, __m128i b, int32_t) { return sign_epi32(a, b); }
__m128i sse::sign(__m128i a, __m128i b, uint8_t) { return sign_epi8(a, b); }
__m128i sse::sign(__m128i a, __m128i b, uint16_t) { return sign_epi16(a, b); }
__m128i sse::sign(__m128i a, __m128i b, uint32_t) { return sign_epi32(a, b); }

#endif // WJR_SSSE3

#if WJR_SSE4_1
template<int imm8>
__m128i sse::blend_epi16(__m128i a, __m128i b) {
	return _mm_blend_epi16(a, b, imm8);
}

__m128i sse::cmpeq_epi64(__m128i a, __m128i b) { return _mm_cmpeq_epi64(a, b); }

__m128i sse::cmpeq(__m128i a, __m128i b, int64_t) { return cmpeq_epi64(a, b); }
__m128i sse::cmpeq(__m128i a, __m128i b, uint64_t) { return cmpeq_epi64(a, b); }

__m128i sse::cmpgt_epi64(__m128i a, __m128i b) { return _mm_cmpgt_epi64(a, b); }

__m128i sse::cmpgt(__m128i a, __m128i b, int64_t) { return cmpgt_epi64(a, b); }

template<int imm8>
__m128i sse::insert_epi8(__m128i a, int i) {
	return _mm_insert_epi8(a, i, imm8);
}

template<int imm8>
__m128i sse::insert_epi32(__m128i a, int i) {
	return _mm_insert_epi32(a, i, imm8);
}

template<int imm8>
__m128i sse::insert_epi64(__m128i a, int64_t i) {
	return _mm_insert_epi64(a, i, imm8);
}

template<int imm8>
__m128i sse::insert(__m128i a, int i, int8_t) { return insert_epi8<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int i, int32_t) { return insert_epi32<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int64_t i, int64_t) { return insert_epi64<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int i, uint8_t) { return insert_epi8<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int i, uint32_t) { return insert_epi32<imm8>(a, i); }
template<int imm8>
__m128i sse::insert(__m128i a, int64_t i, uint64_t) { return insert_epi64<imm8>(a, i); }

__m128i sse::minpos_epu16(__m128i a) { return _mm_minpos_epu16(a); }

__m128i sse::mul_epi32(__m128i a, __m128i b) { return _mm_mul_epi32(a, b); }

__m128i sse::mullo_epi32(__m128i a, __m128i b) { return _mm_mullo_epi32(a, b); }

__m128i sse::packus_epi32(__m128i a, __m128i b) { return _mm_packus_epi32(a, b); }

__m128i sse::stream_load(__m128i* p) { return _mm_stream_load_si128(p); }

int sse::test_all_ones(__m128i a) { return _mm_test_all_ones(a); }

int sse::test_all_zeros(__m128i a, __m128i b) { return _mm_test_all_zeros(a, b); }

int sse::test_all_zeros(__m128i a) { return _mm_test_all_zeros(a, a); }

int sse::test_mix_ones_zeros(__m128i a, __m128i b) { return _mm_test_mix_ones_zeros(a, b); }

int sse::testc(__m128i a, __m128i b) { return _mm_testc_si128(a, b); }

int sse::testnzc(__m128i a, __m128i b) { return _mm_testnzc_si128(a, b); }

int sse::testz(__m128i a, __m128i b) {
	return _mm_testz_si128(a, b);
}
#endif // WJR_SSE4_1

/*------AVX------*/

constexpr size_t avx::width() { return 256; }

constexpr avx::mask_type avx::mask() { return 0xffffffff; }

#if WJR_AVX

__m256i avx::concat(__m128i a, __m128i b) {
	return insert_si128<1>(simd_cast<__m256i>(a), b);
}

template<int imm8>
int avx::extract_epi32(__m256i v) { return _mm256_extract_epi32(v, imm8); }
template<int imm8>
int64_t avx::extract_epi64(__m256i v) { return _mm256_extract_epi64(v, imm8); }

template<int imm8>
int avx::extract(__m256i v, int32_t) { return extract_epi32<imm8>(v); }
template<int imm8>
int64_t avx::extract(__m256i v, int64_t) { return extract_epi64<imm8>(v); }

template<int imm8>
__m128i avx::extract_si128(__m256i v) {
#if WJR_AVX2
	return _mm256_extracti128_si256(v, imm8);
#else
	return _mm256_extractf128_si256(v, imm8);
#endif // WJR_AVX2
}

__m128i avx::getlow(__m256i a) {
	return simd_cast<__m128i>(a);
}

__m128i avx::gethigh(__m256i a) {
	return extract_si128<1>(a);
}

template<int imm8>
__m256i avx::insert_epi8(__m256i v, int8_t i) { return _mm256_insert_epi8(v, i, imm8); }
template<int imm8>
__m256i avx::insert_epi16(__m256i v, int16_t i) { return _mm256_insert_epi16(v, i, imm8); }
template<int imm8>
__m256i avx::insert_epi32(__m256i v, int32_t i) { return _mm256_insert_epi32(v, i, imm8); }
template<int imm8>
__m256i avx::insert_epi64(__m256i v, int64_t i) { return _mm256_insert_epi64(v, i, imm8); }

template<int imm8>
__m256i avx::insert_si128(__m256i a, __m128i b) {
#if WJR_AVX2
	return _mm256_inserti128_si256(a, b, imm8);
#else
	return _mm256_insertf128_si256(a, b, imm8);
#endif // WJR_AVX2
}

__m256i avx::load(const __m256i* p) { return _mm256_load_si256(p); }
__m256i avx::loadu(const __m256i* p) { return _mm256_loadu_si256(p); }

__m256i avx::ones() { return _mm256_set1_epi32(-1); }

__m256i avx::preloadu_si16(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si16(ptr));
}

__m256i avx::preloadu_si32(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si32(ptr));
}

__m256i avx::preloadu_si48(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si48(ptr));
}

__m256i avx::preloadu_si64(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si64(ptr));
}

__m256i avx::preloadu_si80(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si80(ptr));
}

__m256i avx::preloadu_si96(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si96(ptr));
}

__m256i avx::preloadu_si112(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si112(ptr));
}

__m256i avx::preloadu_si128(const void* ptr) {
	return simd_cast<__m256i, __m128i>(sse::preloadu_si128(ptr));
}

__m256i avx::preloadu_si144(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si16((const char*)ptr + 16));
}

__m256i avx::preloadu_si160(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si32((const char*)ptr + 16));
}

__m256i avx::preloadu_si176(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si48((const char*)ptr + 16));
}

__m256i avx::preloadu_si192(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si64((const char*)ptr + 16));
}

__m256i avx::preloadu_si208(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si80((const char*)ptr + 16));
}

__m256i avx::preloadu_si224(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si96((const char*)ptr + 16));
}
__m256i avx::preloadu_si240(const void* ptr) {
	return concat(sse::preloadu_si128(ptr),
		sse::preloadu_si112((const char*)ptr + 16));
}

__m256i avx::preloadu_si256(const void* ptr) {
	return loadu((const __m256i*)ptr);
}

__m256i avx::preloadu_si16x(const void* ptr, int n) {
	switch (n) {
	case 0:return zeros();
	case 1:return preloadu_si16(ptr);
	case 2:return preloadu_si32(ptr);
	case 3:return preloadu_si48(ptr);
	case 4:return preloadu_si64(ptr);
	case 5:return preloadu_si80(ptr);
	case 6:return preloadu_si96(ptr);
	case 7:return preloadu_si112(ptr);
	case 8:return preloadu_si128(ptr);
	case 9:return preloadu_si144(ptr);
	case 10:return preloadu_si160(ptr);
	case 11:return preloadu_si176(ptr);
	case 12:return preloadu_si192(ptr);
	case 13:return preloadu_si208(ptr);
	case 14:return preloadu_si224(ptr);
	case 15:return preloadu_si240(ptr);
	default:return preloadu_si256(ptr);
	}
}

__m256i avx::set_epi8(
	char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24,
	char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16,
	char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
	char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0) {
	return _mm256_set_epi8(
		e31, e30, e29, e28, e27, e26, e25, e24,
		e23, e22, e21, e20, e19, e18, e17, e16,
		e15, e14, e13, e12, e11, e10, e9, e8,
		e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::set_epi16(
	short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8,
	short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0) {
	return _mm256_set_epi16(
		e15, e14, e13, e12, e11, e10, e9, e8,
		e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::set_epi32(
	int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0) {
	return _mm256_set_epi32(e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::set_epi64x(
	long long e3, long long e2, long long e1, long long e0) {
	return _mm256_set_epi64x(e3, e2, e1, e0);
}

__m256i avx::setr_epi8(
	char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24,
	char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16,
	char e15, char e14, char e13, char e12, char e11, char e10, char e9, char e8,
	char e7, char e6, char e5, char e4, char e3, char e2, char e1, char e0) {
	return _mm256_setr_epi8(
		e31, e30, e29, e28, e27, e26, e25, e24,
		e23, e22, e21, e20, e19, e18, e17, e16,
		e15, e14, e13, e12, e11, e10, e9, e8,
		e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::setr_epi16(
	short e15, short e14, short e13, short e12, short e11, short e10, short e9, short e8,
	short e7, short e6, short e5, short e4, short e3, short e2, short e1, short e0) {
	return _mm256_setr_epi16(
		e15, e14, e13, e12, e11, e10, e9, e8,
		e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::setr_epi32(
	int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0) {
	return _mm256_setr_epi32(e7, e6, e5, e4, e3, e2, e1, e0);
}

__m256i avx::setr_epi64x(
	long long e3, long long e2, long long e1, long long e0) {
	return _mm256_setr_epi64x(e3, e2, e1, e0);
}

__m256i avx::set1_epi8(int8_t a) { return _mm256_set1_epi8(a); }
__m256i avx::set1_epi16(int16_t a) { return _mm256_set1_epi16(a); }
__m256i avx::set1_epi32(int32_t a) { return _mm256_set1_epi32(a); }
__m256i avx::set1_epi64(int64_t a) { return _mm256_set1_epi64x(a); }

__m256i avx::set1(int8_t a, int8_t) { return set1_epi8(a); }
__m256i avx::set1(int16_t a, int16_t) { return set1_epi16(a); }
__m256i avx::set1(int32_t a, int32_t) { return set1_epi32(a); }
__m256i avx::set1(int64_t a, int64_t) { return set1_epi64(a); }
__m256i avx::set1(uint8_t a, uint8_t) { return set1_epi8(a); }
__m256i avx::set1(uint16_t a, uint16_t) { return set1_epi16(a); }
__m256i avx::set1(uint32_t a, uint32_t) { return set1_epi32(a); }
__m256i avx::set1(uint64_t a, uint64_t) { return set1_epi64(a); }

__m256i avx::setmin_epi8() { return set1_epi8(0x80u); }
__m256i avx::setmin_epi16() { return set1_epi16(0x8000u); }
__m256i avx::setmin_epi32() { return set1_epi32(0x80000000u); }
__m256i avx::setmin_epi64() { return set1_epi64(0x8000000000000000ull); }

__m256i avx::setmin(int8_t) { return setmin_epi8(); }
__m256i avx::setmin(int16_t) { return setmin_epi16(); }
__m256i avx::setmin(int32_t) { return setmin_epi32(); }
__m256i avx::setmin(int64_t) { return setmin_epi64(); }

__m256i avx::setmax_epi8() { return set1_epi8(0x7f); }
__m256i avx::setmax_epi16() { return set1_epi16(0x7fff); }
__m256i avx::setmax_epi32() { return set1_epi32(0x7fffffff); }
__m256i avx::setmax_epi64() { return set1_epi64(0x7fffffffffffffff); }

__m256i avx::setmax(int8_t) { return setmax_epi8(); }
__m256i avx::setmax(int16_t) { return setmax_epi16(); }
__m256i avx::setmax(int32_t) { return setmax_epi32(); }
__m256i avx::setmax(int64_t) { return setmax_epi64(); }

void avx::stream(__m256i* p, __m256i a) { _mm256_stream_si256(p, a); }

void avx::store(__m256i* p, const __m256i& a) { _mm256_store_si256(p, a); }
void avx::storeu(__m256i* p, const __m256i& a) { _mm256_storeu_si256(p, a); }

int avx::test_all_zeros(__m256i a) { return testz(a, a); }

int avx::testc(__m256i a, __m256i b) { return _mm256_testc_si256(a, b); }

int avx::testnzc(__m256i a, __m256i b) { return _mm256_testnzc_si256(a, b); }

int avx::testz(__m256i a, __m256i b) { return _mm256_testz_si256(a, b); }

__m256i avx::zeros() { return _mm256_setzero_si256(); }

#endif // WJR_AVX

#if WJR_AVX2
__m256i avx::And(__m256i a, __m256i b) { return _mm256_and_si256(a, b); }

__m256i avx::AndNot(__m256i a, __m256i b) { return _mm256_andnot_si256(a, b); }

__m256i avx::Or(__m256i a, __m256i b) { return _mm256_or_si256(a, b); }

__m256i avx::Xor(__m256i a, __m256i b) { return _mm256_xor_si256(a, b); }

__m256i avx::Not(__m256i v) { return _mm256_xor_si256(v, ones()); }

__m256i avx::abs_epi8(__m256i v) { return _mm256_abs_epi8(v); }
__m256i avx::abs_epi16(__m256i v) { return _mm256_abs_epi16(v); }
__m256i avx::abs_epi32(__m256i v) { return _mm256_abs_epi32(v); }

__m256i avx::abs(__m256i v, int8_t) { return abs_epi8(v); }
__m256i avx::abs(__m256i v, int16_t) { return abs_epi16(v); }
__m256i avx::abs(__m256i v, int32_t) { return abs_epi32(v); }
__m256i avx::abs(__m256i v, int64_t) { return abs_epi32(v); }

__m256i avx::add_epi8(__m256i a, __m256i b) { return _mm256_add_epi8(a, b); }
__m256i avx::add_epi16(__m256i a, __m256i b) { return _mm256_add_epi16(a, b); }
__m256i avx::add_epi32(__m256i a, __m256i b) { return _mm256_add_epi32(a, b); }
__m256i avx::add_epi64(__m256i a, __m256i b) { return _mm256_add_epi64(a, b); }

__m256i avx::add(__m256i a, __m256i b, int8_t) { return add_epi8(a, b); }
__m256i avx::add(__m256i a, __m256i b, int16_t) { return add_epi16(a, b); }
__m256i avx::add(__m256i a, __m256i b, int32_t) { return add_epi32(a, b); }
__m256i avx::add(__m256i a, __m256i b, int64_t) { return add_epi64(a, b); }
__m256i avx::add(__m256i a, __m256i b, uint8_t) { return add_epi8(a, b); }
__m256i avx::add(__m256i a, __m256i b, uint16_t) { return add_epi16(a, b); }
__m256i avx::add(__m256i a, __m256i b, uint32_t) { return add_epi32(a, b); }
__m256i avx::add(__m256i a, __m256i b, uint64_t) { return add_epi64(a, b); }

uint8_t avx::add_epu8(__m256i v) {
	return sse::add_epu8(sse::add_epi8(getlow(v), gethigh(v)));
}

uint16_t avx::add_epu16(__m256i v) {
	return sse::add_epu16(sse::add_epi16(getlow(v), gethigh(v)));
}

uint32_t avx::add_epu32(__m256i v) {
	return sse::add_epu32(sse::add_epi32(getlow(v), gethigh(v)));
}

uint64_t avx::add_epu64(__m256i v) {
	return sse::add_epu64(sse::add_epi64(getlow(v), gethigh(v)));
}

int8_t avx::add_epi8(__m256i v) { return add_epu8(v); }
int16_t avx::add_epi16(__m256i v) { return add_epu16(v); }
int32_t avx::add_epi32(__m256i v) { return add_epu32(v); }
int64_t avx::add_epi64(__m256i v) { return add_epu64(v); }

int8_t avx::add(__m256i v, int8_t) { return add_epi8(v); }
int16_t avx::add(__m256i v, int16_t) { return add_epi16(v); }
int32_t avx::add(__m256i v, int32_t) { return add_epi32(v); }
int64_t avx::add(__m256i v, int64_t) { return add_epi64(v); }
uint8_t avx::add(__m256i v, uint8_t) { return add_epu8(v); }
uint16_t avx::add(__m256i v, uint16_t) { return add_epu16(v); }
uint32_t avx::add(__m256i v, uint32_t) { return add_epu32(v); }
uint64_t avx::add(__m256i v, uint64_t) { return add_epu64(v); }

__m256i avx::adds_epi8(__m256i a, __m256i b) { return _mm256_adds_epi8(a, b); }
__m256i avx::adds_epi16(__m256i a, __m256i b) { return _mm256_adds_epi16(a, b); }

__m256i avx::adds_epu8(__m256i a, __m256i b) { return _mm256_adds_epu8(a, b); }
__m256i avx::adds_epu16(__m256i a, __m256i b) { return _mm256_adds_epu16(a, b); }

__m256i avx::adds(__m256i a, __m256i b, int8_t) { return adds_epi8(a, b); }
__m256i avx::adds(__m256i a, __m256i b, int16_t) { return adds_epi16(a, b); }
__m256i avx::adds(__m256i a, __m256i b, uint8_t) { return adds_epu8(a, b); }
__m256i avx::adds(__m256i a, __m256i b, uint16_t) { return adds_epu16(a, b); }

template<int imm8>
__m256i avx::alignr(__m256i a, __m256i b) { return _mm256_alignr_epi8(a, b, imm8); }

__m256i avx::alignr_epi16(__m256i a, __m256i b, int c) {
	return Or(slli_epi16(a, 16 - c), srli_epi16(b, c));
}

__m256i avx::alignr_epi32(__m256i a, __m256i b, int c) {
	return Or(slli_epi32(a, 32 - c), srli_epi32(b, c));
}

__m256i avx::alignr_epi64(__m256i a, __m256i b, int c) {
	return Or(slli_epi64(a, 64 - c), srli_epi64(b, c));
}

__m256i avx::alignr(__m256i a, __m256i b, int c, int16_t) {
	return alignr_epi16(a, b, c);
}

__m256i avx::alignr(__m256i a, __m256i b, int c, int32_t) {
	return alignr_epi32(a, b, c);
}

__m256i avx::alignr(__m256i a, __m256i b, int c, int64_t) {
	return alignr_epi64(a, b, c);
}

__m256i avx::alignr(__m256i a, __m256i b, int c, uint16_t) {
	return alignr_epi16(a, b, c);
}

__m256i avx::alignr(__m256i a, __m256i b, int c, uint32_t) {
	return alignr_epi32(a, b, c);
}

__m256i avx::alignr(__m256i a, __m256i b, int c, uint64_t) {
	return alignr_epi64(a, b, c);
}

__m256i avx::avg_epu8(__m256i a, __m256i b) { return _mm256_avg_epu8(a, b); }
__m256i avx::avg_epu16(__m256i a, __m256i b) { return _mm256_avg_epu16(a, b); }

__m256i avx::avg(__m256i a, __m256i b, int8_t) { return avg_epu8(a, b); }
__m256i avx::avg(__m256i a, __m256i b, int16_t) { return avg_epu16(a, b); }
__m256i avx::avg(__m256i a, __m256i b, uint8_t) { return avg_epu8(a, b); }
__m256i avx::avg(__m256i a, __m256i b, uint16_t) { return avg_epu16(a, b); }

template<int imm8>
__m256i avx::blend_epi16(__m256i a, __m256i b) { return _mm256_blend_epi16(a, b, imm8); }

template<int imm8>
__m256i avx::blend_epi32(__m256i a, __m256i b) { return _mm256_blend_epi32(a, b, imm8); }

__m256i avx::blendv_epi8(__m256i a, __m256i b, __m256i mask) {
	return _mm256_blendv_epi8(a, b, mask);
}

template<int imm8>
__m256i avx::bslli_epi128(__m256i a) { return _mm256_bslli_epi128(a, imm8); }

template<int imm8>
__m256i avx::bsrli_epi128(__m256i a) { return _mm256_bsrli_epi128(a, imm8); }

__m256i avx::cmpeq_epi8(__m256i a, __m256i b) { return _mm256_cmpeq_epi8(a, b); }
__m256i avx::cmpeq_epi16(__m256i a, __m256i b) { return _mm256_cmpeq_epi16(a, b); }
__m256i avx::cmpeq_epi32(__m256i a, __m256i b) { return _mm256_cmpeq_epi32(a, b); }
__m256i avx::cmpeq_epi64(__m256i a, __m256i b) { return _mm256_cmpeq_epi64(a, b); }

__m256i avx::cmpeq(__m256i a, __m256i b, int8_t) { return cmpeq_epi8(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, int16_t) { return cmpeq_epi16(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, int32_t) { return cmpeq_epi32(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, int64_t) { return cmpeq_epi64(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, uint8_t) { return cmpeq_epi8(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, uint16_t) { return cmpeq_epi16(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, uint32_t) { return cmpeq_epi32(a, b); }
__m256i avx::cmpeq(__m256i a, __m256i b, uint64_t) { return cmpeq_epi64(a, b); }

__m256i avx::cmpge_epi8(__m256i a, __m256i b) {
	return cmpeq(min(a, b, int8_t()), b, uint8_t());
}

__m256i avx::cmpge_epi16(__m256i a, __m256i b) {
	return cmpeq(min(a, b, int16_t()), b, uint16_t());
}

__m256i avx::cmpge_epi32(__m256i a, __m256i b) {
	return cmpeq(min(a, b, int32_t()), b, uint8_t());
}

__m256i avx::cmpge_epu8(__m256i a, __m256i b) {
	return cmpeq(min(a, b, uint8_t()), b, uint8_t());
}

__m256i avx::cmpge_epu16(__m256i a, __m256i b) {
	return cmpeq(min(a, b, uint16_t()), b, uint16_t());
}

__m256i avx::cmpge_epu32(__m256i a, __m256i b) {
	return cmpeq(min(a, b, uint32_t()), b, uint32_t());
}

__m256i avx::cmpge(__m256i a, __m256i b, int8_t) { return cmpge_epi8(a, b); }
__m256i avx::cmpge(__m256i a, __m256i b, int16_t) { return cmpge_epi16(a, b); }
__m256i avx::cmpge(__m256i a, __m256i b, int32_t) { return cmpge_epi32(a, b); }
__m256i avx::cmpge(__m256i a, __m256i b, uint8_t) { return cmpge_epu8(a, b); }
__m256i avx::cmpge(__m256i a, __m256i b, uint16_t) { return cmpge_epu16(a, b); }
__m256i avx::cmpge(__m256i a, __m256i b, uint32_t) { return cmpge_epu32(a, b); }

__m256i avx::cmpgt_epi8(__m256i a, __m256i b) { return _mm256_cmpgt_epi8(a, b); }
__m256i avx::cmpgt_epi16(__m256i a, __m256i b) { return _mm256_cmpgt_epi16(a, b); }
__m256i avx::cmpgt_epi32(__m256i a, __m256i b) { return _mm256_cmpgt_epi32(a, b); }
__m256i avx::cmpgt_epi64(__m256i a, __m256i b) { return _mm256_cmpgt_epi64(a, b); }

__m256i avx::cmpgt_epu8(__m256i a, __m256i b) {
	return cmpgt_epi8(Xor(a, setmin_epi8()), Xor(b, setmin_epi8()));
}

__m256i avx::cmpgt_epu16(__m256i a, __m256i b) {
	return cmpgt_epi16(Xor(a, setmin_epi16()), Xor(b, setmin_epi16()));
}

__m256i avx::cmpgt_epu32(__m256i a, __m256i b) {
	return cmpgt_epi32(Xor(a, setmin_epi32()), Xor(b, setmin_epi32()));
}

__m256i avx::cmpgt_epu64(__m256i a, __m256i b) {
	return cmpgt_epi64(Xor(a, setmin_epi64()), Xor(b, setmin_epi64()));
}

__m256i avx::cmpgt(__m256i a, __m256i b, int8_t) { return cmpgt_epi8(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, int16_t) { return cmpgt_epi16(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, int32_t) { return cmpgt_epi32(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, int64_t) { return cmpgt_epi64(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, uint8_t) { return cmpgt_epu8(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, uint16_t) { return cmpgt_epu16(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, uint32_t) { return cmpgt_epu32(a, b); }
__m256i avx::cmpgt(__m256i a, __m256i b, uint64_t) { return cmpgt_epu64(a, b); }

__m256i avx::cmple_epi8(__m256i a, __m256i b) {
	return cmpge_epi8(b, a);
}

__m256i avx::cmple_epi16(__m256i a, __m256i b) {
	return cmpge_epi16(b, a);
}

__m256i avx::cmple_epi32(__m256i a, __m256i b) {
	return cmpge_epi32(b, a);
}

__m256i avx::cmple_epu8(__m256i a, __m256i b) {
	return cmpge_epu8(b, a);
}

__m256i avx::cmple_epu16(__m256i a, __m256i b) {
	return cmpge_epu16(b, a);
}

__m256i avx::cmple_epu32(__m256i a, __m256i b) {
	return cmpge_epu32(b, a);
}

__m256i avx::cmple(__m256i a, __m256i b, int8_t) { return cmple_epi8(a, b); }
__m256i avx::cmple(__m256i a, __m256i b, int16_t) { return cmple_epi16(a, b); }
__m256i avx::cmple(__m256i a, __m256i b, int32_t) { return cmple_epi32(a, b); }
__m256i avx::cmple(__m256i a, __m256i b, uint8_t) { return cmple_epu8(a, b); }
__m256i avx::cmple(__m256i a, __m256i b, uint16_t) { return cmple_epu16(a, b); }
__m256i avx::cmple(__m256i a, __m256i b, uint32_t) { return cmple_epu32(a, b); }

__m256i avx::cmplt_epi8(__m256i a, __m256i b) { return cmpgt_epi8(b, a); }
__m256i avx::cmplt_epi16(__m256i a, __m256i b) { return cmpgt_epi16(b, a); }
__m256i avx::cmplt_epi32(__m256i a, __m256i b) { return cmpgt_epi32(b, a); }

__m256i avx::cmplt_epu8(__m256i a, __m256i b) {
	return cmpgt_epu8(b, a);
}
__m256i avx::cmplt_epu16(__m256i a, __m256i b) {
	return cmpgt_epu16(b, a);
}
__m256i avx::cmplt_epu32(__m256i a, __m256i b) {
	return cmpgt_epu32(b, a);
}

__m256i avx::cmplt(__m256i a, __m256i b, int8_t) { return cmplt_epi8(a, b); }
__m256i avx::cmplt(__m256i a, __m256i b, int16_t) { return cmplt_epi16(a, b); }
__m256i avx::cmplt(__m256i a, __m256i b, int32_t) { return cmplt_epi32(a, b); }
__m256i avx::cmplt(__m256i a, __m256i b, uint8_t) { return cmplt_epu8(a, b); }
__m256i avx::cmplt(__m256i a, __m256i b, uint16_t) { return cmplt_epu16(a, b); }
__m256i avx::cmplt(__m256i a, __m256i b, uint32_t) { return cmplt_epu32(a, b); }

__m256i avx::cmpne_epi8(__m256i a, __m256i b) { return Not(cmpeq_epi8(a, b)); }
__m256i avx::cmpne_epi16(__m256i a, __m256i b) { return Not(cmpeq_epi16(a, b)); }
__m256i avx::cmpne_epi32(__m256i a, __m256i b) { return Not(cmpeq_epi32(a, b)); }

__m256i avx::cmpne(__m256i a, __m256i b, int8_t) { return cmpne_epi8(a, b); }
__m256i avx::cmpne(__m256i a, __m256i b, int16_t) { return cmpne_epi16(a, b); }
__m256i avx::cmpne(__m256i a, __m256i b, int32_t) { return cmpne_epi32(a, b); }
__m256i avx::cmpne(__m256i a, __m256i b, uint8_t) { return cmpne_epi8(a, b); }
__m256i avx::cmpne(__m256i a, __m256i b, uint16_t) { return cmpne_epi16(a, b); }
__m256i avx::cmpne(__m256i a, __m256i b, uint32_t) { return cmpne_epi32(a, b); }

template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::equal_to<>, T) {
	return cmpeq(a, b, T());
}
template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::not_equal_to<>, T) {
	return cmpne(a, b, T());
}
template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::greater<>, T) {
	return cmpgt(a, b, T());
}
template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::greater_equal<>, T) {
	return cmpge(a, b, T());
}
template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::less<>, T) {
	return cmplt(a, b, T());
}
template<typename T>
__m256i avx::cmp(__m256i a, __m256i b, std::less_equal<>, T) {
	return cmple(a, b, T());
}

template<int imm8>
int avx::extract_epi8(__m256i v) { return _mm256_extract_epi8(v, imm8); }
template<int imm8>
int avx::extract_epi16(__m256i v) { return _mm256_extract_epi16(v, imm8); }

template<int imm8>
int avx::extract(__m256i v, int8_t) { return extract_epi8<imm8>(v); }
template<int imm8>
int avx::extract(__m256i v, int16_t) { return extract_epi16<imm8>(v); }

__m256i avx::hadd_epi16(__m256i a, __m256i b) { return _mm256_hadd_epi16(a, b); }
__m256i avx::hadd_epi32(__m256i a, __m256i b) { return _mm256_hadd_epi32(a, b); }

__m256i avx::hadd(__m256i a, __m256i b, int16_t) { return hadd_epi16(a, b); }
__m256i avx::hadd(__m256i a, __m256i b, int32_t) { return hadd_epi32(a, b); }

__m256i avx::hadds_epi16(__m256i a, __m256i b) { return _mm256_hadds_epi16(a, b); }

__m256i avx::hsub_epi16(__m256i a, __m256i b) { return _mm256_hsub_epi16(a, b); }
__m256i avx::hsub_epi32(__m256i a, __m256i b) { return _mm256_hsub_epi32(a, b); }

__m256i avx::hsub(__m256i a, __m256i b, int16_t) { return hsub_epi16(a, b); }
__m256i avx::hsub(__m256i a, __m256i b, int32_t) { return hsub_epi32(a, b); }

__m256i avx::hsubs_epi16(__m256i a, __m256i b) { return _mm256_hsubs_epi16(a, b); }

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m256i avx::logical_and(__m256i a, __m256i b, T) {
	return Not(Or(logical_not(a, T()), logical_not(b, T())));
}

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m256i avx::logical_not(__m256i v, T) {
	auto Zero = zeros();
	return cmpeq(v, Zero, T());
}

template<typename T, std::enable_if_t<wjr::is_any_of_v<T, int8_t, int16_t, int32_t, int64_t,
	uint8_t, uint16_t, uint32_t, uint64_t>, int>>
	__m256i avx::logical_or(__m256i a, __m256i b, T) {
	return Not(logical_not(Or(a, b), T()));
}

__m256i avx::madd_epi16(__m256i a, __m256i b) { return _mm256_madd_epi16(a, b); }

__m256i avx::max_epi8(__m256i a, __m256i b) { return _mm256_max_epi8(a, b); }
__m256i avx::max_epi16(__m256i a, __m256i b) { return _mm256_max_epi16(a, b); }
__m256i avx::max_epi32(__m256i a, __m256i b) { return _mm256_max_epi32(a, b); }

__m256i avx::max_epu8(__m256i a, __m256i b) { return _mm256_max_epu8(a, b); }
__m256i avx::max_epu16(__m256i a, __m256i b) { return _mm256_max_epu16(a, b); }
__m256i avx::max_epu32(__m256i a, __m256i b) { return _mm256_max_epu32(a, b); }

__m256i avx::max(__m256i a, __m256i b, int8_t) { return max_epi8(a, b); }
__m256i avx::max(__m256i a, __m256i b, int16_t) { return max_epi16(a, b); }
__m256i avx::max(__m256i a, __m256i b, uint8_t) { return max_epu8(a, b); }
__m256i avx::max(__m256i a, __m256i b, uint16_t) { return max_epu16(a, b); }
__m256i avx::max(__m256i a, __m256i b, int32_t) { return max_epi32(a, b); }
__m256i avx::max(__m256i a, __m256i b, uint32_t) { return max_epu32(a, b); }

int8_t avx::max_epi8(__m256i a) {
	return sse::max_epi8(sse::max_epi8(getlow(a), gethigh(a)));
}

int16_t avx::max_epi16(__m256i a) {
	return sse::max_epi16(sse::max_epi16(getlow(a), gethigh(a)));
}

int32_t avx::max_epi32(__m256i a) {
	return sse::max_epi32(sse::max_epi32(getlow(a), gethigh(a)));
}

uint8_t avx::max_epu8(__m256i a) {
	return sse::max_epu8(sse::max_epu8(getlow(a), gethigh(a)));
}

uint16_t avx::max_epu16(__m256i a) {
	return sse::max_epu16(sse::max_epu16(getlow(a), gethigh(a)));
}

uint32_t avx::max_epu32(__m256i a) {
	return sse::max_epu32(sse::max_epu32(getlow(a), gethigh(a)));
}

int8_t avx::max(__m256i a, int8_t) { return max_epi8(a); }
int16_t avx::max(__m256i a, int16_t) { return max_epi16(a); }
int32_t avx::max(__m256i a, int32_t) { return max_epi32(a); }
uint8_t avx::max(__m256i a, uint8_t) { return max_epu8(a); }
uint16_t avx::max(__m256i a, uint16_t) { return max_epu16(a); }
uint32_t avx::max(__m256i a, uint32_t) { return max_epu32(a); }

__m256i avx::min_epi8(__m256i a, __m256i b) { return _mm256_min_epi8(a, b); }
__m256i avx::min_epi16(__m256i a, __m256i b) { return _mm256_min_epi16(a, b); }
__m256i avx::min_epi32(__m256i a, __m256i b) { return _mm256_min_epi32(a, b); }

__m256i avx::min_epu8(__m256i a, __m256i b) { return _mm256_min_epu8(a, b); }
__m256i avx::min_epu16(__m256i a, __m256i b) { return _mm256_min_epu16(a, b); }
__m256i avx::min_epu32(__m256i a, __m256i b) { return _mm256_min_epu32(a, b); }

__m256i avx::min(__m256i a, __m256i b, int8_t) { return min_epi8(a, b); }
__m256i avx::min(__m256i a, __m256i b, int16_t) { return min_epi16(a, b); }
__m256i avx::min(__m256i a, __m256i b, uint8_t) { return min_epu8(a, b); }
__m256i avx::min(__m256i a, __m256i b, uint16_t) { return min_epu16(a, b); }
__m256i avx::min(__m256i a, __m256i b, int32_t) { return min_epi32(a, b); }
__m256i avx::min(__m256i a, __m256i b, uint32_t) { return min_epu32(a, b); }

int8_t avx::min_epi8(__m256i a) {
	return sse::min_epi8(sse::min_epi8(getlow(a), gethigh(a)));
}

int16_t avx::min_epi16(__m256i a) {
	return sse::min_epi16(sse::min_epi16(getlow(a), gethigh(a)));
}

int32_t avx::min_epi32(__m256i a) {
	return sse::min_epi32(sse::min_epi32(getlow(a), gethigh(a)));
}

uint8_t avx::min_epu8(__m256i a) {
	return sse::min_epu8(sse::min_epu8(getlow(a), gethigh(a)));
}

uint16_t avx::min_epu16(__m256i a) {
	return sse::min_epu16(sse::min_epu16(getlow(a), gethigh(a)));
}

uint32_t avx::min_epu32(__m256i a) {
	return sse::min_epu32(sse::min_epu32(getlow(a), gethigh(a)));
}

int8_t avx::min(__m256i a, int8_t) { return min_epi8(a); }
int16_t avx::min(__m256i a, int16_t) { return min_epi16(a); }
int32_t avx::min(__m256i a, int32_t) { return min_epi32(a); }
uint8_t avx::min(__m256i a, uint8_t) { return min_epu8(a); }
uint16_t avx::min(__m256i a, uint16_t) { return min_epu16(a); }
uint32_t avx::min(__m256i a, uint32_t) { return min_epu32(a); }

avx::mask_type avx::movemask_epi8(__m256i a) { return _mm256_movemask_epi8(a); }

__m256i avx::mul_epi32(__m256i a, __m256i b) { return _mm256_mul_epi32(a, b); }
__m256i avx::mul_epu32(__m256i a, __m256i b) { return _mm256_mul_epu32(a, b); }

__m256i avx::mulhi_epi16(__m256i a, __m256i b) { return _mm256_mulhi_epi16(a, b); }

__m256i avx::mulhi_epu16(__m256i a, __m256i b) { return _mm256_mulhi_epu16(a, b); }

__m256i avx::mullo_epi16(__m256i a, __m256i b) { return _mm256_mullo_epi16(a, b); }

__m256i avx::packs_epi16(__m256i a, __m256i b) { return _mm256_packs_epi16(a, b); }
__m256i avx::packs_epi32(__m256i a, __m256i b) { return _mm256_packs_epi32(a, b); }

__m256i avx::packus_epi16(__m256i a, __m256i b) { return _mm256_packus_epi16(a, b); }
__m256i avx::packus_epi32(__m256i a, __m256i b) { return _mm256_packus_epi32(a, b); }

__m256i avx::shuffle_epi8(__m256i a, __m256i b) { return _mm256_shuffle_epi8(a, b); }

template<int imm8>
__m256i avx::shuffle_epi32(__m256i a) {
	return _mm256_shuffle_epi32(a, imm8);
}

template<int imm8>
__m256i avx::shufflehi_epi16(__m256i a) {
	return _mm256_shufflehi_epi16(a, imm8);
}

template<int imm8>
__m256i avx::shufflelo_epi16(__m256i a) {
	return _mm256_shufflelo_epi16(a, imm8);
}

__m256i avx::sll_epi16(__m256i a, __m128i b) { return _mm256_sll_epi16(a, b); }
__m256i avx::sll_epi32(__m256i a, __m128i b) { return _mm256_sll_epi32(a, b); }
__m256i avx::sll_epi64(__m256i a, __m128i b) { return _mm256_sll_epi64(a, b); }

__m256i avx::sll(__m256i a, __m128i b, int16_t) { return sll_epi16(a, b); }
__m256i avx::sll(__m256i a, __m128i b, int32_t) { return sll_epi32(a, b); }
__m256i avx::sll(__m256i a, __m128i b, int64_t) { return sll_epi64(a, b); }
__m256i avx::sll(__m256i a, __m128i b, uint16_t) { return sll_epi16(a, b); }
__m256i avx::sll(__m256i a, __m128i b, uint32_t) { return sll_epi32(a, b); }
__m256i avx::sll(__m256i a, __m128i b, uint64_t) { return sll_epi64(a, b); }

__m256i avx::slli_epi16(__m256i a, int imm8) { return _mm256_slli_epi16(a, imm8); }
__m256i avx::slli_epi32(__m256i a, int imm8) { return _mm256_slli_epi32(a, imm8); }
__m256i avx::slli_epi64(__m256i a, int imm8) { return _mm256_slli_epi64(a, imm8); }

__m256i avx::slli(__m256i a, int imm8, int16_t) { return slli_epi16(a, imm8); }
__m256i avx::slli(__m256i a, int imm8, int32_t) { return slli_epi32(a, imm8); }
__m256i avx::slli(__m256i a, int imm8, int64_t) { return slli_epi64(a, imm8); }
__m256i avx::slli(__m256i a, int imm8, uint16_t) { return slli_epi16(a, imm8); }
__m256i avx::slli(__m256i a, int imm8, uint32_t) { return slli_epi32(a, imm8); }
__m256i avx::slli(__m256i a, int imm8, uint64_t) { return slli_epi64(a, imm8); }

__m256i avx::sra_epi16(__m256i a, __m128i b) { return _mm256_sra_epi16(a, b); }
__m256i avx::sra_epi32(__m256i a, __m128i b) { return _mm256_sra_epi32(a, b); }

__m256i avx::sra(__m256i a, __m128i b, int16_t) { return sra_epi16(a, b); }
__m256i avx::sra(__m256i a, __m128i b, int32_t) { return sra_epi32(a, b); }

__m256i avx::srai_epi16(__m256i a, int imm8) { return _mm256_srai_epi16(a, imm8); }
__m256i avx::srai_epi32(__m256i a, int imm8) { return _mm256_srai_epi32(a, imm8); }

__m256i avx::srai(__m256i a, int imm8, int16_t) { return srai_epi16(a, imm8); }
__m256i avx::srai(__m256i a, int imm8, int32_t) { return srai_epi32(a, imm8); }

__m256i avx::stream_load(__m256i const* p) { return _mm256_stream_load_si256(p); }

__m256i avx::srl_epi16(__m256i a, __m128i b) { return _mm256_srl_epi16(a, b); }
__m256i avx::srl_epi32(__m256i a, __m128i b) { return _mm256_srl_epi32(a, b); }
__m256i avx::srl_epi64(__m256i a, __m128i b) { return _mm256_srl_epi64(a, b); }

__m256i avx::srl(__m256i a, __m128i b, int16_t) { return srl_epi16(a, b); }
__m256i avx::srl(__m256i a, __m128i b, int32_t) { return srl_epi32(a, b); }
__m256i avx::srl(__m256i a, __m128i b, int64_t) { return srl_epi64(a, b); }
__m256i avx::srl(__m256i a, __m128i b, uint16_t) { return srl_epi16(a, b); }
__m256i avx::srl(__m256i a, __m128i b, uint32_t) { return srl_epi32(a, b); }
__m256i avx::srl(__m256i a, __m128i b, uint64_t) { return srl_epi64(a, b); }

__m256i avx::srli_epi16(__m256i a, int imm8) { return _mm256_srli_epi16(a, imm8); }
__m256i avx::srli_epi32(__m256i a, int imm8) { return _mm256_srli_epi32(a, imm8); }
__m256i avx::srli_epi64(__m256i a, int imm8) { return _mm256_srli_epi64(a, imm8); }

__m256i avx::srli(__m256i a, int imm8, int16_t) { return srli_epi16(a, imm8); }
__m256i avx::srli(__m256i a, int imm8, int32_t) { return srli_epi32(a, imm8); }
__m256i avx::srli(__m256i a, int imm8, int64_t) { return srli_epi64(a, imm8); }
__m256i avx::srli(__m256i a, int imm8, uint16_t) { return srli_epi16(a, imm8); }
__m256i avx::srli(__m256i a, int imm8, uint32_t) { return srli_epi32(a, imm8); }
__m256i avx::srli(__m256i a, int imm8, uint64_t) { return srli_epi64(a, imm8); }

__m256i avx::sub_epi8(__m256i a, __m256i b) { return _mm256_sub_epi8(a, b); }
__m256i avx::sub_epi16(__m256i a, __m256i b) { return _mm256_sub_epi16(a, b); }
__m256i avx::sub_epi32(__m256i a, __m256i b) { return _mm256_sub_epi32(a, b); }
__m256i avx::sub_epi64(__m256i a, __m256i b) { return _mm256_sub_epi64(a, b); }

__m256i avx::sub(__m256i a, __m256i b, int8_t) { return sub_epi8(a, b); }
__m256i avx::sub(__m256i a, __m256i b, int16_t) { return sub_epi16(a, b); }
__m256i avx::sub(__m256i a, __m256i b, int32_t) { return sub_epi32(a, b); }
__m256i avx::sub(__m256i a, __m256i b, int64_t) { return sub_epi64(a, b); }
__m256i avx::sub(__m256i a, __m256i b, uint8_t) { return sub_epi8(a, b); }
__m256i avx::sub(__m256i a, __m256i b, uint16_t) { return sub_epi16(a, b); }
__m256i avx::sub(__m256i a, __m256i b, uint32_t) { return sub_epi32(a, b); }
__m256i avx::sub(__m256i a, __m256i b, uint64_t) { return sub_epi64(a, b); }

__m256i avx::subs_epi8(__m256i a, __m256i b) { return _mm256_subs_epi8(a, b); }
__m256i avx::subs_epi16(__m256i a, __m256i b) { return _mm256_subs_epi16(a, b); }

__m256i avx::subs_epu8(__m256i a, __m256i b) { return _mm256_subs_epu8(a, b); }
__m256i avx::subs_epu16(__m256i a, __m256i b) { return _mm256_subs_epu16(a, b); }

__m256i avx::subs(__m256i a, __m256i b, int8_t) { return subs_epi8(a, b); }
__m256i avx::subs(__m256i a, __m256i b, int16_t) { return subs_epi16(a, b); }
__m256i avx::subs(__m256i a, __m256i b, uint8_t) { return subs_epu8(a, b); }
__m256i avx::subs(__m256i a, __m256i b, uint16_t) { return subs_epu16(a, b); }

int avx::test_all_ones(__m256i a) { return testc(a, cmpeq_epi32(a, a)); }

__m256i avx::unpackhi_epi8(__m256i a, __m256i b) { return _mm256_unpackhi_epi8(a, b); }
__m256i avx::unpackhi_epi16(__m256i a, __m256i b) { return _mm256_unpackhi_epi16(a, b); }
__m256i avx::unpackhi_epi32(__m256i a, __m256i b) { return _mm256_unpackhi_epi32(a, b); }
__m256i avx::unpackhi_epi64(__m256i a, __m256i b) { return _mm256_unpackhi_epi64(a, b); }

__m256i avx::unpackhi(__m256i a, __m256i b, int8_t) { return unpackhi_epi8(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, int16_t) { return unpackhi_epi16(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, int32_t) { return unpackhi_epi32(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, int64_t) { return unpackhi_epi64(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, uint8_t) { return unpackhi_epi8(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, uint16_t) { return unpackhi_epi16(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, uint32_t) { return unpackhi_epi32(a, b); }
__m256i avx::unpackhi(__m256i a, __m256i b, uint64_t) { return unpackhi_epi64(a, b); }

__m256i avx::unpacklo_epi8(__m256i a, __m256i b) { return _mm256_unpacklo_epi8(a, b); }
__m256i avx::unpacklo_epi16(__m256i a, __m256i b) { return _mm256_unpacklo_epi16(a, b); }
__m256i avx::unpacklo_epi32(__m256i a, __m256i b) { return _mm256_unpacklo_epi32(a, b); }
__m256i avx::unpacklo_epi64(__m256i a, __m256i b) { return _mm256_unpacklo_epi64(a, b); }

__m256i avx::unpacklo(__m256i a, __m256i b, int8_t) { return unpacklo_epi8(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, int16_t) { return unpacklo_epi16(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, int32_t) { return unpacklo_epi32(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, int64_t) { return unpacklo_epi64(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, uint8_t) { return unpacklo_epi8(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, uint16_t) { return unpacklo_epi16(a, b); }
__m256i avx::unpacklo(__m256i a, __m256i b, uint32_t) { return unpacklo_epi32(a, b); }
#endif // WJR_AVX2

_WJR_SIMD_END

#endif // __WJR_SIMD_SIMD_INTRIN_H

#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMCHR)

#define __WJR_MEMCHR_ONE(st, _s)	                            \
	auto r = st::cmp(x, y, pred, T());	                        \
	st::mask_type z = st::movemask_epi8(r);	                    \
	if(z != 0){	                                                \
		return (_s) + wjr::countr_zero(z) / _Mysize;	        \
	}

#define __WJR_MEMCHR_FOUR(st, _s0, _s1, _s2, _s3)	            \
	auto r0 = st::cmp(x0, y, pred, T());	                    \
	auto r1 = st::cmp(x1, y, pred, T());	                    \
	auto r2 = st::cmp(x2, y, pred, T());	                    \
	auto r3 = st::cmp(x3, y, pred, T());	                    \
	                                                            \
	r3 = st::Or(st::Or(r0, r1), st::Or(r2, r3));	            \
	st::mask_type z = st::movemask_epi8(r3);	                \
	if(z != 0){	                                                \
		st::mask_type tmp = st::movemask_epi8(r0);	            \
		if(tmp != 0){	                                        \
			return (_s0) + wjr::countr_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = st::movemask_epi8(r1);	                        \
		if(tmp != 0){	                                        \
			return (_s1) + wjr::countr_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = st::movemask_epi8(r2);	                        \
		if(tmp != 0){	                                        \
			return (_s2) + wjr::countr_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = z;	                                            \
		return (_s3) + wjr::countr_zero(tmp) / _Mysize;	        \
	}

_WJR_ALGO_BEGIN

template<typename T, typename _Pred>
const T* __memchr(const T* s, T val, size_t n, _Pred pred) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	constexpr size_t __constant_threshold = 8 / _Mysize;

	if (is_constant_p(n) && n <= __constant_threshold) {
		for (size_t i = 0; i < n; ++i) {
			if (pred(s[i], val)) {
				return s + i;
			}
		}
		return s + n;
	}

	if (is_unlikely(n == 0)) return s;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* _lst;

			auto y = simd_t::set1(val, T());

			if (is_constant_p(reinterpret_cast<uintptr_t>(s) % bound) &&
				reinterpret_cast<uintptr_t>(s) % bound == 0) {
				// do nothing
			}
			else if (_Mysize == 1 ||
				reinterpret_cast<uintptr_t>(s) % _Mysize == 0) {
				auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

				__WJR_MEMCHR_ONE(simd_t, s);

				auto __align_s = bound - reinterpret_cast<uintptr_t>(s) % bound;
				s += __align_s / _Mysize;
				n -= __align_s / _Mysize;
				if (is_unlikely(n < width * 4)) {
					_lst = s + n;
					goto WJR_MACRO_LABEL(aft_align);
				}
			}
			else {
				// unalign algorithm
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s + width));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s + width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s + width * 3));

					__WJR_MEMCHR_FOUR(simd_t, s, s + width, s + width * 2, s + width * 3);

					s += width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				_lst = s + n;
				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
						s += width;
					}
					case 3: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
						s += width;
					}
					case 2: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst - width));

						__WJR_MEMCHR_ONE(simd_t, _lst - width);
					}
					}
				}
				return _lst;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s + width));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s + width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s + width * 3));

				__WJR_MEMCHR_FOUR(simd_t, s, s + width, s + width * 2, s + width * 3);

				s += width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			_lst = s + n;
			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
					s += width;
				}
				case 3: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
					s += width;
				}
				case 2: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst - width));

					__WJR_MEMCHR_ONE(simd_t, _lst - width);
				}
				}
			}
			return _lst;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto y = simd::avx::set1(val, T());

			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + n - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + n - 32 / _Mysize));

			__WJR_MEMCHR_FOUR(simd::avx, s, s + 32 / _Mysize, s + n - 64 / _Mysize, s + n - 32 / _Mysize);

			return s + n;
		}
#endif // WJR_AVX2

		auto y = simd::sse::set1(val, T());
		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + n - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + n - 16 / _Mysize));

		__WJR_MEMCHR_FOUR(simd::sse, s, s + delta, s + n - 16 / _Mysize - delta, s + n - 16 / _Mysize);

		return s + n;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(*s, val) ? s : s + 1;
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A = *reinterpret_cast<const uint64_t*>(s);
			auto B = *reinterpret_cast<const uint64_t*>(s + n - 4);

			auto x = simd::sse::set_epi64x(B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0)return s + n;
			auto i = wjr::countr_zero(z) / _Mysize;
			auto q = i >= 4 ? i + n - 8 : i;
			return s + q;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A = *reinterpret_cast<const uint32_t*>(s);
			auto B = *reinterpret_cast<const uint32_t*>(s + delta);
			auto C = *reinterpret_cast<const uint32_t*>(s + n - 4 - delta);
			auto D = *reinterpret_cast<const uint32_t*>(s + n - 4);

			auto x = simd::sse::set_epi32(D, C, B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0) return s + n;
			auto i = wjr::countr_zero(z);
			auto q = i >= 8 ? i + (n - 12 - delta) : i;
			return s + q;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (pred(s[0], val)) return s;
		if (n == 1) return s + 1;
		if (pred(s[1], val)) return s + 1;
		if (n == 2) return s + 2;
		return pred(s[2], val) ? s + 2 : s + 3;
	}
}

_WJR_ALGO_END

#undef __WJR_MEMCHR_FOUR
#undef __WJR_MEMCHR_ONE

#endif // _WJR_FAST_MEMCHR
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMCHR)

#define __WJR_MEMRCHR_ONE(st, _s)	                            \
	auto r = st::cmp(x, y, pred, T());	                        \
	st::mask_type z = st::movemask_epi8(r);	                    \
	if(z != 0){	                                                \
		return (_s) - wjr::countl_zero(z) / _Mysize;	        \
	}

#define __WJR_MEMRCHR_FOUR(st, _s0, _s1, _s2, _s3)	            \
	auto r0 = st::cmp(x0, y, pred, T());	                    \
	auto r1 = st::cmp(x1, y, pred, T());	                    \
	auto r2 = st::cmp(x2, y, pred, T());	                    \
	auto r3 = st::cmp(x3, y, pred, T());	                    \
	                                                            \
	r0 = st::Or(st::Or(r0, r1), st::Or(r2, r3));	            \
	st::mask_type z = st::movemask_epi8(r0);	                \
	if(z != 0){	                                                \
		st::mask_type tmp = st::movemask_epi8(r3);	            \
		if(tmp != 0){	                                        \
			return (_s3) - wjr::countl_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = st::movemask_epi8(r2);	                        \
		if(tmp != 0){	                                        \
			return (_s2) - wjr::countl_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = st::movemask_epi8(r1);	                        \
		if(tmp != 0){	                                        \
			return (_s1) - wjr::countl_zero(tmp) / _Mysize;	    \
		}	                                                    \
		tmp = z;	                                            \
		return (_s0) - wjr::countl_zero(tmp) / _Mysize;	        \
	}

_WJR_ALGO_BEGIN

template<typename T, typename _Pred>
const T* __memrchr(const T* s, T val, size_t n, _Pred pred) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	constexpr size_t __constant_threshold = 8 / _Mysize;

	if (is_constant_p(n) && n <= __constant_threshold) {
		for (size_t i = 0; i < n; ++i) {
			if (pred(s[i], val)) {
				return s + i;
			}
		}
		return s + n;
	}

	if (is_unlikely(n == 0)) return s;

	s += n;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* _lst;

			auto y = simd_t::set1(val, T());

			if (is_constant_p(reinterpret_cast<uintptr_t>(s) % bound) &&
				reinterpret_cast<uintptr_t>(s) % bound == 0) {
				// do nothing
			}
			else if (_Mysize == 1 ||
				reinterpret_cast<uintptr_t>(s) % _Mysize == 0) {
				auto x = simd_t::loadu(reinterpret_cast<const sint*>(s - width));

				__WJR_MEMRCHR_ONE(simd_t, s);

				auto __align_s = reinterpret_cast<uintptr_t>(s) % bound;
				s -= __align_s / _Mysize;
				n -= __align_s / _Mysize;
				if (is_unlikely(n < width * 4)) {
					// n = [width * 3, width * 4)
					_lst = s - n;
					goto WJR_MACRO_LABEL(aft_align);
				}
			}
			else {
				// unalign algorithm
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s - width * 4));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s - width * 3));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s - width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s - width));

					__WJR_MEMRCHR_FOUR(simd_t, s - width * 3, s - width * 2, s - width, s);

					s -= width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				_lst = s - n;
				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						s -= width;
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMRCHR_ONE(simd_t, s + width);
					}
					case 3: {
						s -= width;
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMRCHR_ONE(simd_t, s + width);
					}
					case 2: {
						s -= width;
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMRCHR_ONE(simd_t, s + width);
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst));

						__WJR_MEMRCHR_ONE(simd_t, _lst + width);
					}
					}
				}
				return _lst;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s - width * 4));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s - width * 3));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s - width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s - width));

				__WJR_MEMRCHR_FOUR(simd_t, s - width * 3, s - width * 2, s - width, s);

				s -= width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			_lst = s - n;
			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						s -= width;
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMRCHR_ONE(simd_t, s + width);
				}
				case 3: {
					s -= width;
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMRCHR_ONE(simd_t, s + width);
				}
				case 2: {
					s -= width;
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMRCHR_ONE(simd_t, s + width);
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst));

					__WJR_MEMRCHR_ONE(simd_t, _lst + width);
				}
				}
			}
			return _lst;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto y = simd::avx::set1(val, T());

			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s - n));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s - n + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s - 32 / _Mysize));

			__WJR_MEMRCHR_FOUR(simd::avx, s - n + 32 / _Mysize, s - n + 64 / _Mysize, s - 32 / _Mysize, s);

			return s - n;
		}
#endif // WJR_AVX2

		auto y = simd::sse::set1(val, T());
		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s - n));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s - n + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s - 16 / _Mysize));

		__WJR_MEMRCHR_FOUR(simd::sse, s - n + 16 / _Mysize, s - n + delta + 16 / _Mysize, s - delta, s);

		return s - n;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(s[-1], val) ? s : s - 1;
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A = *reinterpret_cast<const uint64_t*>(s - n);
			auto B = *reinterpret_cast<const uint64_t*>(s - 4);

			auto x = simd::sse::set_epi64x(B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0)return s - n;
			auto i = wjr::countl_zero(z) / _Mysize;
			auto q = i >= 4 ? i + n - 4 : i;
			return s - q;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A = *reinterpret_cast<const uint32_t*>(s - n);
			auto B = *reinterpret_cast<const uint32_t*>(s - n + delta);
			auto C = *reinterpret_cast<const uint32_t*>(s - 4 - delta);
			auto D = *reinterpret_cast<const uint32_t*>(s - 4);

			auto x = simd::sse::set_epi32(D, C, B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0) return s - n;
			size_t i = wjr::countl_zero(z);
			auto q = i >= 8 ? i + (n - 12 - delta) : i;
			return s - q;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (pred(s[-1], val)) return s;
		if (n == 1) return s - 1;
		if (pred(s[-2], val)) return s - 1;
		if (n == 2) return s - 2;
		return pred(s[-3], val) ? s - 2 : s - 3;
	}
}

_WJR_ALGO_END

#undef __WJR_MEMRCHR_FOUR
#undef __WJR_MEMRCHR_ONE

#endif // _WJR_FAST_MEMCHR
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif

#if defined(_WJR_FAST_MEMCMP)

#define __WJR_MEMCMP_ONE_NORMAL(st)														\
	auto r = st::cmp(x, y, pred, T());	                                                \
	st::mask_type z = st::movemask_epi8(r);		                                        \
	if(z != st::mask()){	                                                            \
		return false;	                                                                \
	}

#define __WJR_MEMCMP_FOUR_NORMAL(st)													\
	auto r0 = st::cmp(x0, y0, pred, T());	                                            \
	auto r1 = st::cmp(x1, y1, pred, T());	                                            \
	auto r2 = st::cmp(x2, y2, pred, T());	                                            \
	auto r3 = st::cmp(x3, y3, pred, T());	                                            \
		                                                                                \
	r3 = st::And(st::And(r0, r1), st::And(r2, r3));	                                    \
	st::mask_type z = st::movemask_epi8(r3);		                                    \
	if(z != st::mask()){	                                                            \
		return false;	                                                                \
	}

#define __WJR_MEMCMP_ONE(st) __WJR_MEMCMP_ONE_NORMAL(st)
#define __WJR_MEMCMP_FOUR(st) __WJR_MEMCMP_FOUR_NORMAL(st)

#if WJR_SSE4_1
#undef __WJR_MEMCMP_ONE
#undef __WJR_MEMCMP_FOUR

#define __WJR_MEMCMP_ONE(st)															\
	if constexpr(std::is_same_v<_Pred, std::equal_to<>>){	                            \
		auto r = st::Xor(x, y);	                                                        \
		auto z = st::test_all_zeros(r);	                                                \
		if(!z){	                                                                        \
			return false;	                                                            \
		}	                                                                            \
	}	                                                                                \
	else{	                                                                            \
		__WJR_MEMCMP_ONE_NORMAL(st)														\
	}

#define __WJR_MEMCMP_FOUR(st)															\
	if constexpr(std::is_same_v<_Pred, std::equal_to<>>){	                            \
		auto r0 = st::Xor(x0, y0);	                                                    \
		auto r1 = st::Xor(x1, y1);	                                                    \
		auto r2 = st::Xor(x2, y2);	                                                    \
		auto r3 = st::Xor(x3, y3);	                                                    \
				                                                                        \
		r3 = st::Or(st::Or(r0, r1), st::Or(r2, r3));	                                \
		auto z = st::test_all_zeros(r3);	                                            \
		if(!z){	                                                                        \
			return false;	                                                            \
		}	                                                                            \
	}	                                                                                \
	else{	                                                                            \
		__WJR_MEMCMP_FOUR_NORMAL(st)													\
	}
#endif // WJR_SSE4_1

_WJR_ALGO_BEGIN

template<typename T, typename _Pred>
bool __memcmp(const T* s0, const T* s1, size_t n, _Pred pred) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	if (is_unlikely(n == 0)) return true;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* _lst0;
			const T* _lst1;

			auto _off0 = reinterpret_cast<uintptr_t>(s0) % bound;
			auto _off1 = reinterpret_cast<uintptr_t>(s1) % bound;

			// align 2 pointer
			if (_off0 == _off1 &&
				(_Mysize == 1 || _off0 % _Mysize == 0)) {
				if (is_constant_p(_off0) && _off0 == 0) {
					// do nothing
				}
				else {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

					__WJR_MEMCMP_ONE(simd_t);

					auto __align_s = bound - _off0;
					s0 += __align_s / _Mysize;
					s1 += __align_s / _Mysize;
					n -= __align_s / _Mysize;
					if (is_unlikely(n < width * 4)) {
						_lst0 = s0 + n;
						_lst1 = s1 + n;
						goto WJR_MACRO_LABEL(aft_align);
					}
				}
			}
			// unalign algorithm
			else {
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s0));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width * 3));

					auto y0 = simd_t::loadu(reinterpret_cast<const sint*>(s1));
					auto y1 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width));
					auto y2 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width * 2));
					auto y3 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width * 3));

					__WJR_MEMCMP_FOUR(simd_t);

					s0 += width * 4;
					s1 += width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				_lst0 = s0 + n;
				_lst1 = s1 + n;

				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMCMP_ONE(simd_t);
						s0 += width;
						s1 += width;
					}
					case 3: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMCMP_ONE(simd_t);
						s0 += width;
						s1 += width;
					}
					case 2: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMCMP_ONE(simd_t);
						s0 += width;
						s1 += width;
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst0 - width));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(_lst1 - width));

						__WJR_MEMCMP_ONE(simd_t);
					}
					}
				}
				return true;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s0));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s0 + width));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s0 + width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s0 + width * 3));

				auto y0 = simd_t::load(reinterpret_cast<const sint*>(s1));
				auto y1 = simd_t::load(reinterpret_cast<const sint*>(s1 + width));
				auto y2 = simd_t::load(reinterpret_cast<const sint*>(s1 + width * 2));
				auto y3 = simd_t::load(reinterpret_cast<const sint*>(s1 + width * 3));

				__WJR_MEMCMP_FOUR(simd_t);

				s0 += width * 4;
				s1 += width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			_lst0 = s0 + n;
			_lst1 = s1 + n;

			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMCMP_ONE(simd_t);
					s0 += width;
					s1 += width;
				}
				case 3: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMCMP_ONE(simd_t);
					s0 += width;
					s1 += width;
				}
				case 2: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMCMP_ONE(simd_t);
					s0 += width;
					s1 += width;
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst0 - width));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(_lst1 - width));

					__WJR_MEMCMP_ONE(simd_t);
				}
				}
			}

			return true;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + n - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + n - 32 / _Mysize));

			auto y0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1));
			auto y1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + 32 / _Mysize));
			auto y2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + n - 64 / _Mysize));
			auto y3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + n - 32 / _Mysize));

			__WJR_MEMCMP_FOUR(simd::avx);

			return true;
		}
#endif // WJR_AVX2

		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + n - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + n - 16 / _Mysize));

		auto y0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1));
		auto y1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + delta));
		auto y2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + n - 16 / _Mysize - delta));
		auto y3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + n - 16 / _Mysize));

		__WJR_MEMCMP_FOUR(simd::sse);

		return true;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(s0[0], s1[0]);
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A0 = *reinterpret_cast<const uint64_t*>(s0);
			auto B0 = *reinterpret_cast<const uint64_t*>(s0 + n - 4);

			auto A1 = *reinterpret_cast<const uint64_t*>(s1);
			auto B1 = *reinterpret_cast<const uint64_t*>(s1 + n - 4);

			auto x = simd::sse::set_epi64x(B0, A0);
			auto y = simd::sse::set_epi64x(B1, A1);

			__WJR_MEMCMP_ONE(simd::sse);

			return true;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A0 = *reinterpret_cast<const uint32_t*>(s0);
			auto B0 = *reinterpret_cast<const uint32_t*>(s0 + delta);
			auto C0 = *reinterpret_cast<const uint32_t*>(s0 + n - 4 - delta);
			auto D0 = *reinterpret_cast<const uint32_t*>(s0 + n - 4);

			auto A1 = *reinterpret_cast<const uint32_t*>(s1);
			auto B1 = *reinterpret_cast<const uint32_t*>(s1 + delta);
			auto C1 = *reinterpret_cast<const uint32_t*>(s1 + n - 4 - delta);
			auto D1 = *reinterpret_cast<const uint32_t*>(s1 + n - 4);

			auto x = simd::sse::set_epi32(D0, C0, B0, A0);
			auto y = simd::sse::set_epi32(D1, C1, B1, A1);

			__WJR_MEMCMP_ONE(simd::sse);

			return true;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (!pred(s0[0], s1[0])) return false;
		if (n == 1) return true;
		if (!pred(s0[1], s1[1])) return false;
		if (n == 2) return true;
		return pred(s0[2], s1[2]);
	}
}

_WJR_ALGO_END

#undef __WJR_MEMCMP_ONE
#undef __WJR_MEMCMP_FOUR
#undef __WJR_MEMCMP_ONE_NORMAL
#undef __WJR_MEMCMP_FOUR_NORMAL

#endif // _WJR_FAST_MEMCMP
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMMIS)

#define __WJR_MEMMIS_ONE(st, _s)														\
	auto r = st::cmp(x, y, pred, T());	                                                \
	st::mask_type z = st::movemask_epi8(r);		                                        \
	if(z != st::mask()){	                                                            \
		return (_s) + wjr::countr_one(z) / _Mysize;		                                \
	}

#define __WJR_MEMMIS_FOUR(st, _s0, _s1, _s2, _s3)										\
	auto r0 = st::cmp(x0, y0, pred, T());	                                            \
	auto r1 = st::cmp(x1, y1, pred, T());	                                            \
	auto r2 = st::cmp(x2, y2, pred, T());	                                            \
	auto r3 = st::cmp(x3, y3, pred, T());	                                            \
		                                                                                \
	r3 = st::And(st::And(r0, r1), st::And(r2, r3));	                                    \
	st::mask_type z = st::movemask_epi8(r3);		                                    \
	if(z != st::mask()){	                                                            \
		st::mask_type tmp = st::movemask_epi8(r0);	                                    \
		if(tmp != st::mask()){	                                                        \
			return (_s0) + wjr::countr_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = st::movemask_epi8(r1);	                                                \
		if(tmp != st::mask()){	                                                        \
			return (_s1) + wjr::countr_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = st::movemask_epi8(r2);	                                                \
		if(tmp != st::mask()){	                                                        \
			return (_s2) + wjr::countr_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = z;	                                                                    \
		return (_s3) + wjr::countr_one(tmp) / _Mysize;	                                \
	}

_WJR_ALGO_BEGIN

template<typename T, typename _Pred>
const T* __memmis(const T* s0, const T* s1, size_t n, _Pred pred) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	if (is_unlikely(n == 0)) return s0;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* _lst0;
			const T* _lst1;

			auto _off0 = reinterpret_cast<uintptr_t>(s0) % bound;
			auto _off1 = reinterpret_cast<uintptr_t>(s1) % bound;

			// align 2 pointer
			if (_off0 == _off1 &&
				(_Mysize == 1 || _off0 % _Mysize == 0)) {
				if (is_constant_p(_off0) && _off0 == 0) {
					// do nothing
				}
				else {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

					__WJR_MEMMIS_ONE(simd_t, s0);

					auto __align_s = bound - _off0;
					s0 += __align_s / _Mysize;
					s1 += __align_s / _Mysize;
					n -= __align_s / _Mysize;
					if (is_unlikely(n < width * 4)) {
						_lst0 = s0 + n;
						_lst1 = s1 + n;
						goto WJR_MACRO_LABEL(aft_align);
					}
				}
			}
			// unalign algorithm
			else {
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s0));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s0 + width * 3));

					auto y0 = simd_t::loadu(reinterpret_cast<const sint*>(s1));
					auto y1 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width));
					auto y2 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width * 2));
					auto y3 = simd_t::loadu(reinterpret_cast<const sint*>(s1 + width * 3));

					__WJR_MEMMIS_FOUR(simd_t, s0, s0 + width, s0 + width * 2, s0 + width * 3);

					s0 += width * 4;
					s1 += width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				_lst0 = s0 + n;
				_lst1 = s1 + n;

				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMMIS_ONE(simd_t, s0);
						s0 += width;
						s1 += width;
					}
					case 3: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMMIS_ONE(simd_t, s0);
						s0 += width;
						s1 += width;
					}
					case 2: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1));

						__WJR_MEMMIS_ONE(simd_t, s0);
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst0 - width));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(_lst1 - width));

						__WJR_MEMMIS_ONE(simd_t, _lst0 - width);
					}
					}
				}
				return _lst0;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s0));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s0 + width));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s0 + width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s0 + width * 3));

				auto y0 = simd_t::load(reinterpret_cast<const sint*>(s1));
				auto y1 = simd_t::load(reinterpret_cast<const sint*>(s1 + width));
				auto y2 = simd_t::load(reinterpret_cast<const sint*>(s1 + width * 2));
				auto y3 = simd_t::load(reinterpret_cast<const sint*>(s1 + width * 3));

				__WJR_MEMMIS_FOUR(simd_t, s0, s0 + width, s0 + width * 2, s0 + width * 3);

				s0 += width * 4;
				s1 += width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			_lst0 = s0 + n;
			_lst1 = s1 + n;

			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMMIS_ONE(simd_t, s0);
					s0 += width;
					s1 += width;
				}
				case 3: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMMIS_ONE(simd_t, s0);
					s0 += width;
					s1 += width;
				}
				case 2: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1));

					__WJR_MEMMIS_ONE(simd_t, s0);
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst0 - width));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(_lst1 - width));

					__WJR_MEMMIS_ONE(simd_t, _lst0 - width);
				}
				}
			}

			return _lst0;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + n - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 + n - 32 / _Mysize));

			auto y0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1));
			auto y1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + 32 / _Mysize));
			auto y2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + n - 64 / _Mysize));
			auto y3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 + n - 32 / _Mysize));

			__WJR_MEMMIS_FOUR(simd::avx, s0, s0 + 32 / _Mysize, s0 + n - 64 / _Mysize, s0 + n - 32 / _Mysize);

			return s0 + n;
		}
#endif // WJR_AVX2

		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + n - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 + n - 16 / _Mysize));

		auto y0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1));
		auto y1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + delta));
		auto y2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + n - 16 / _Mysize - delta));
		auto y3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 + n - 16 / _Mysize));

		__WJR_MEMMIS_FOUR(simd::sse, s0, s0 + delta, s0 + n - 16 / _Mysize - delta, s0 + n - 16 / _Mysize);

		return s0 + n;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(s0[0], s1[0]) ? s0 + 1 : s0;
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A0 = *reinterpret_cast<const uint64_t*>(s0);
			auto B0 = *reinterpret_cast<const uint64_t*>(s0 + n - 4);

			auto A1 = *reinterpret_cast<const uint64_t*>(s1);
			auto B1 = *reinterpret_cast<const uint64_t*>(s1 + n - 4);

			auto x = simd::sse::set_epi64x(B0, A0);
			auto y = simd::sse::set_epi64x(B1, A1);
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == simd::sse::mask())return s0 + n;
			auto i = wjr::countr_one(z) / _Mysize;
			auto q = i >= 4 ? i + n - 8 : i;
			return s0 + q;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A0 = *reinterpret_cast<const uint32_t*>(s0);
			auto B0 = *reinterpret_cast<const uint32_t*>(s0 + delta);
			auto C0 = *reinterpret_cast<const uint32_t*>(s0 + n - 4 - delta);
			auto D0 = *reinterpret_cast<const uint32_t*>(s0 + n - 4);

			auto A1 = *reinterpret_cast<const uint32_t*>(s1);
			auto B1 = *reinterpret_cast<const uint32_t*>(s1 + delta);
			auto C1 = *reinterpret_cast<const uint32_t*>(s1 + n - 4 - delta);
			auto D1 = *reinterpret_cast<const uint32_t*>(s1 + n - 4);

			auto x = simd::sse::set_epi32(D0, C0, B0, A0);
			auto y = simd::sse::set_epi32(D1, C1, B1, A1);

			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == simd::sse::mask()) return s0 + n;
			auto i = wjr::countr_one(z);
			auto q = i >= 8 ? i + (n - 12 - delta) : i;
			return s0 + q;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (!pred(s0[0], s1[0])) return s0;
		if (n == 1) return s0 + 1;
		if (!pred(s0[1], s1[1])) return s0 + 1;
		if (n == 2) return s0 + 2;
		return pred(s0[2], s1[2]) ? s0 + 3 : s0 + 2;
	}
}

_WJR_ALGO_END

#undef __WJR_MEMMIS_FOUR
#undef __WJR_MEMMIS_ONE

#endif // _WJR_FAST_MEMMIS
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMMIS)

#define __WJR_MEMRMIS_ONE(st, _s)														\
	auto r = st::cmp(x, y, pred, T());	                                                \
	st::mask_type z = st::movemask_epi8(r);		                                        \
	if(z != st::mask()){	                                                            \
		return (_s) - wjr::countl_one(z) / _Mysize;		                                \
	}

#define __WJR_MEMRMIS_FOUR(st, _s0, _s1, _s2, _s3)										\
	auto r0 = st::cmp(x0, y0, pred, T());	                                            \
	auto r1 = st::cmp(x1, y1, pred, T());	                                            \
	auto r2 = st::cmp(x2, y2, pred, T());	                                            \
	auto r3 = st::cmp(x3, y3, pred, T());	                                            \
		                                                                                \
	r0 = st::And(st::And(r0, r1), st::And(r2, r3));	                                    \
	st::mask_type z = st::movemask_epi8(r0);		                                    \
	if(z != st::mask()){	                                                            \
		st::mask_type tmp = st::movemask_epi8(r3);	                                    \
		if(tmp != st::mask()){	                                                        \
			return (_s3) - wjr::countl_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = st::movemask_epi8(r2);	                                                \
		if(tmp != st::mask()){	                                                        \
			return (_s2) - wjr::countl_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = st::movemask_epi8(r1);	                                                \
		if(tmp != st::mask()){	                                                        \
			return (_s1) - wjr::countl_one(tmp) / _Mysize;	                            \
		}	                                                                            \
		tmp = z;	                                                                    \
		return (_s0) - wjr::countl_one(tmp) / _Mysize;	                                \
	}

_WJR_ALGO_BEGIN

template<typename T, typename _Pred>
const T* __memrmis(const T* s0, const T* s1, size_t n, _Pred pred) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	if (is_unlikely(n == 0)) return s0;

	s0 += n;
	s1 += n;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* lst0;
			const T* lst1;

			auto _off0 = reinterpret_cast<uintptr_t>(s0) % bound;
			auto _off1 = reinterpret_cast<uintptr_t>(s1) % bound;

			// align 2 pointer
			if (_off0 == _off1 &&
				(_Mysize == 1 || _off0 % _Mysize == 0)) {
				if (is_constant_p(_off0) && _off0 == 0) {
					// do nothing
				}
				else {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width));

					__WJR_MEMRMIS_ONE(simd_t, s0);

					auto __align_s = _off0;
					s0 -= __align_s / _Mysize;
					s1 -= __align_s / _Mysize;
					n -= __align_s / _Mysize;
					if (is_unlikely(n < width * 4)) {
						lst0 = s0 - n;
						lst1 = s1 - n;
						goto WJR_MACRO_LABEL(aft_align);
					}
				}
			}
			// unalign algorithm
			else {
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width * 4));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width * 3));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width));

					auto y0 = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width * 4));
					auto y1 = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width * 3));
					auto y2 = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width * 2));
					auto y3 = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width));

					__WJR_MEMRMIS_FOUR(simd_t, s0 - width * 3, s0 - width * 2, s0 - width, s0);

					s0 -= width * 4;
					s1 -= width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				lst0 = s0 - n;
				lst1 = s1 - n;

				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width));

						__WJR_MEMRMIS_ONE(simd_t, s0);
						s0 -= width;
						s1 -= width;
					}
					case 3: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width));

						__WJR_MEMRMIS_ONE(simd_t, s0);
						s0 -= width;
						s1 -= width;
					}
					case 2: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s0 - width));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(s1 - width));

						__WJR_MEMRMIS_ONE(simd_t, s0);
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(lst0));
						auto y = simd_t::loadu(reinterpret_cast<const sint*>(lst1));

						__WJR_MEMRMIS_ONE(simd_t, lst0 + width);
					}
					}
				}
				return lst0;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s0 - width * 4));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s0 - width * 3));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s0 - width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s0 - width));

				auto y0 = simd_t::load(reinterpret_cast<const sint*>(s1 - width * 4));
				auto y1 = simd_t::load(reinterpret_cast<const sint*>(s1 - width * 3));
				auto y2 = simd_t::load(reinterpret_cast<const sint*>(s1 - width * 2));
				auto y3 = simd_t::load(reinterpret_cast<const sint*>(s1 - width));

				__WJR_MEMRMIS_FOUR(simd_t, s0 - width * 3, s0 - width * 2, s0 - width, s0);

				s0 -= width * 4;
				s1 -= width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			lst0 = s0 - n;
			lst1 = s1 - n;

			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						auto x = simd_t::load(reinterpret_cast<const sint*>(s0 - width));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1 - width));

					__WJR_MEMRMIS_ONE(simd_t, s0);
					s0 -= width;
					s1 -= width;
				}
				case 3: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0 - width));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1 - width));

					__WJR_MEMRMIS_ONE(simd_t, s0);
					s0 -= width;
					s1 -= width;
				}
				case 2: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s0 - width));
					auto y = simd_t::load(reinterpret_cast<const sint*>(s1 - width));

					__WJR_MEMRMIS_ONE(simd_t, s0);
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(lst0));
					auto y = simd_t::loadu(reinterpret_cast<const sint*>(lst1));

					__WJR_MEMRMIS_ONE(simd_t, lst0 + width);
				}
				}
			}

			return lst0;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 - n));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 - n + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s0 - 32 / _Mysize));

			auto y0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 - n));
			auto y1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 - n + 32 / _Mysize));
			auto y2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 - 64 / _Mysize));
			auto y3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s1 - 32 / _Mysize));

			__WJR_MEMRMIS_FOUR(simd::avx, s0 - n + 32 / _Mysize, s0 - n + 64 / _Mysize, s0 - 32 / _Mysize, s0);

			return s0 - n;
		}
#endif // WJR_AVX2

		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 - n));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 - n + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s0 - 16 / _Mysize));

		auto y0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 - n));
		auto y1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 - n + delta));
		auto y2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 - 16 / _Mysize - delta));
		auto y3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s1 - 16 / _Mysize));

		__WJR_MEMRMIS_FOUR(simd::sse, s0 - n + 16 / _Mysize, s0 - n + delta + 16 / _Mysize, s0 - delta, s0);

		return s0 - n;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(s0[-1], s1[-1]) ? s0 : s0 - 1;
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A0 = *reinterpret_cast<const uint64_t*>(s0 - n);
			auto B0 = *reinterpret_cast<const uint64_t*>(s0 - 4);

			auto A1 = *reinterpret_cast<const uint64_t*>(s1 - n);
			auto B1 = *reinterpret_cast<const uint64_t*>(s1 - 4);

			auto x = simd::sse::set_epi64x(B0, A0);
			auto y = simd::sse::set_epi64x(B1, A1);
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == simd::sse::mask())return s0 - n;
			auto i = wjr::countl_one(z) / _Mysize;
			auto q = i >= 4 ? i + n - 4 : i;
			return s0 - q;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A0 = *reinterpret_cast<const uint32_t*>(s0 - n);
			auto B0 = *reinterpret_cast<const uint32_t*>(s0 - n + delta);
			auto C0 = *reinterpret_cast<const uint32_t*>(s0 - 4 - delta);
			auto D0 = *reinterpret_cast<const uint32_t*>(s0 - 4);

			auto A1 = *reinterpret_cast<const uint32_t*>(s1 - n);
			auto B1 = *reinterpret_cast<const uint32_t*>(s1 - n + delta);
			auto C1 = *reinterpret_cast<const uint32_t*>(s1 - 4 - delta);
			auto D1 = *reinterpret_cast<const uint32_t*>(s1 - 4);

			auto x = simd::sse::set_epi32(D0, C0, B0, A0);
			auto y = simd::sse::set_epi32(D1, C1, B1, A1);

			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == simd::sse::mask()) return s0 - n;
			auto i = wjr::countl_one(z);
			auto q = i >= 8 ? i + (n - 12 - delta) : i;
			return s0 - q;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (!pred(s0[-1], s1[-1])) return s0;
		if (n == 1) return s0 - 1;
		if (!pred(s0[-2], s1[-2])) return s0 - 1;
		if (n == 2) return s0 - 2;
		return pred(s0[-3], s1[-3]) ? s0 - 3 : s0 - 2;
	}
}

_WJR_ALGO_END

#undef __WJR_MEMRMIS_FOUR
#undef __WJR_MEMRMIS_ONE

#endif // _WJR_FAST_MEMMIS
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMCNT)

_WJR_ALGO_BEGIN

template<typename T>
size_t __memcnt(const T* s, T val, size_t n) {
	using namespace wjr::literals;
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2
	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	constexpr auto max_step_4 = std::numeric_limits<T>::max() / width + 1;
	static_assert(max_step_4 >= 4 && max_step_4 % 4 == 0, "invalid _Maxstep");
	constexpr auto max_step = max_step / 4;

	if (is_unlikely(n == 0)) return 0;

	if (n >= 16 / _Mysize) {
		if (n >= width * 4) {
			const T* _lst;

			auto y = simd_t::set1(val, T());

			if (is_constant_p(reinterpret_cast<uintptr_t>(s) % bound) &&
				reinterpret_cast<uintptr_t>(s) % bound == 0) {
				// do nothing
			}
			else if (_Mysize == 1 ||
				reinterpret_cast<uintptr_t>(s) % _Mysize == 0) {
				auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

				__WJR_MEMCHR_ONE(simd_t, s);

				auto __align_s = bound - reinterpret_cast<uintptr_t>(s) % bound;
				s += __align_s / _Mysize;
				n -= __align_s / _Mysize;
				if (is_unlikely(n < width * 4)) {
					_lst = s + n;
					goto WJR_MACRO_LABEL(aft_align);
				}
			}
			else {
				// unalign algorithm
				do {
					auto x0 = simd_t::loadu(reinterpret_cast<const sint*>(s));
					auto x1 = simd_t::loadu(reinterpret_cast<const sint*>(s + width));
					auto x2 = simd_t::loadu(reinterpret_cast<const sint*>(s + width * 2));
					auto x3 = simd_t::loadu(reinterpret_cast<const sint*>(s + width * 3));

					__WJR_MEMCHR_FOUR(simd_t, s, s + width, s + width * 2, s + width * 3);

					s += width * 4;
					n -= width * 4;
				} while (n >= width * 4);

				_lst = s + n;
				if (n != 0) {
					switch ((n + width - 1) / width) {
					default: unreachable(); break;
					case 4: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
						s += width;
					}
					case 3: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
						s += width;
					}
					case 2: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(s));

						__WJR_MEMCHR_ONE(simd_t, s);
					}
					case 1: {
						auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst - width));

						__WJR_MEMCHR_ONE(simd_t, _lst - width);
					}
					}
				}
				return _lst;
			}

			do {
				auto x0 = simd_t::load(reinterpret_cast<const sint*>(s));
				auto x1 = simd_t::load(reinterpret_cast<const sint*>(s + width));
				auto x2 = simd_t::load(reinterpret_cast<const sint*>(s + width * 2));
				auto x3 = simd_t::load(reinterpret_cast<const sint*>(s + width * 3));

				__WJR_MEMCHR_FOUR(simd_t, s, s + width, s + width * 2, s + width * 3);

				s += width * 4;
				n -= width * 4;
			} while (n >= width * 4);

			_lst = s + n;
			if (n != 0) {
				switch ((n + width - 1) / width) {
				default: unreachable(); break;
				case 4: {
					WJR_MACRO_LABEL(aft_align) :
						auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
					s += width;
				}
				case 3: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
					s += width;
				}
				case 2: {
					auto x = simd_t::load(reinterpret_cast<const sint*>(s));

					__WJR_MEMCHR_ONE(simd_t, s);
				}
				case 1: {
					auto x = simd_t::loadu(reinterpret_cast<const sint*>(_lst - width));

					__WJR_MEMCHR_ONE(simd_t, _lst - width);
				}
				}
			}
			return _lst;
		}

#if WJR_AVX2
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n >= 64 / _Mysize) {
			auto y = simd::avx::set1(val, T());

			auto x0 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s));
			auto x1 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + 32 / _Mysize));
			auto x2 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + n - 64 / _Mysize));
			auto x3 = simd::avx::loadu(reinterpret_cast<const __m256i*>(s + n - 32 / _Mysize));

			__WJR_MEMCHR_FOUR(simd::avx, s, s + 32 / _Mysize, s + n - 64 / _Mysize, s + n - 32 / _Mysize);

			return s + n;
		}
#endif // WJR_AVX2

		auto y = simd::sse::set1(val, T());
		auto delta = (n & (32 / _Mysize)) >> 1;

		auto x0 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s));
		auto x1 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + delta));
		auto x2 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + n - 16 / _Mysize - delta));
		auto x3 = simd::sse::loadu(reinterpret_cast<const __m128i*>(s + n - 16 / _Mysize));

		__WJR_MEMCHR_FOUR(simd::sse, s, s + delta, s + n - 16 / _Mysize - delta, s + n - 16 / _Mysize);

		return s + n;
	}

	if constexpr (_Mysize == 8) {
		// n = [1, 2)
		return pred(*s, val) ? s : s + 1;
	}

	if constexpr (_Mysize == 2) {
		// n = [1, 8)
		if (n >= 4) {
			// n = [4, 8)
			auto A = *reinterpret_cast<const uint64_t*>(s);
			auto B = *reinterpret_cast<const uint64_t*>(s + n - 4);

			auto x = simd::sse::set_epi64x(B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0)return s + n;
			auto i = wjr::countr_zero(z) / _Mysize;
			auto q = i >= 4 ? i + n - 8 : i;
			return s + q;
		}
	}

	if constexpr (_Mysize == 1) {
		// n = [1, 16)
		if (n >= 4) {
			// n = [4, 16)
			auto delta = (n & 8) >> 1;

			auto A = *reinterpret_cast<const uint32_t*>(s);
			auto B = *reinterpret_cast<const uint32_t*>(s + delta);
			auto C = *reinterpret_cast<const uint32_t*>(s + n - 4 - delta);
			auto D = *reinterpret_cast<const uint32_t*>(s + n - 4);

			auto x = simd::sse::set_epi32(D, C, B, A);
			auto y = simd::sse::set1(val, T());
			auto r = simd::sse::cmp(x, y, pred, T());
			uint16_t z = simd::sse::movemask_epi8(r);

			if (z == 0) return s + n;
			auto i = wjr::countr_zero(z);
			auto q = i >= 8 ? i + (n - 12 - delta) : i;
			return s + q;
		}
	}

	if constexpr (_Mysize <= 4) {
		// n = [1, 4)
		if (pred(s[0], val)) return s;
		if (n == 1) return s + 1;
		if (pred(s[1], val)) return s + 1;
		if (n == 2) return s + 2;
		return pred(s[2], val) ? s + 2 : s + 3;
	}
}

_WJR_ALGO_END

#endif // _WJR_FAST_MEMCNT
#ifndef __WJR_ALGO_ALOG_H
#error "This file should not be included directly. Include <wjr/algo.h> instead."
#endif 

#if defined(_WJR_FAST_MEMSET)

#if WJR_AVX2
#define __WJR_ALIGN64byte(ptr)	                                    \
	simd_t::storeu(reinterpret_cast<sint*>((ptr)), q);	            \
	simd_t::storeu(reinterpret_cast<sint*>((ptr) + width), q);
#else
#define __WJR_ALIGN64byte(ptr)	                                    \
	simd_t::storeu(reinterpret_cast<sint*>((ptr)), q);	            \
	simd_t::storeu(reinterpret_cast<sint*>((ptr) + width), q);	    \
	simd_t::storeu(reinterpret_cast<sint*>((ptr) + width * 2), q);	\
	simd_t::storeu(reinterpret_cast<sint*>((ptr) + width * 3), q);
#endif // __WJR_MEMSET64byte

_WJR_ALGO_BEGIN

template<typename T>
void __memset(T* s, T val, size_t n) {
	constexpr size_t _Mysize = sizeof(T);

#if WJR_AVX2
	using simd_t = simd::avx;
#else
	using simd_t = simd::sse;
#endif // WJR_AVX2

	using sint = typename simd_t::int_type;
	constexpr uintptr_t width = simd_t::width() / (8 * _Mysize);
	constexpr uintptr_t bound = width * _Mysize;

	if constexpr (_Mysize != 1) {
		if (
			is_constant_p(val) &&
			broadcast<T, uint8_t>(static_cast<uint8_t>(val)) == val) {
			return __memset(reinterpret_cast<uint8_t*>(s), static_cast<uint8_t>(val), n * _Mysize);
		}
	}

	constexpr size_t __constant_threshold = 2048 / _Mysize;

	const bool __use_rep = wjr::is_enhanced_rep();

#if defined(_WJR_NON_TEMPORARY)
	const size_t __nt_threshold = (wjr::max_cache_size() + wjr::max_cache_size() / 8) / _Mysize;
#endif // _WJR_NON_TEMPORARY

	if (is_constant_p(n) && n <= __constant_threshold) {
		for (size_t i = 0; i < n; ++i) {
			s[i] = val;
		}
		return;
	}

	if (n >= 16 / _Mysize) {
		auto qx = simd::sse::set1(val, T());
		if (n >= 128 / _Mysize) {
			// [128, ...)
			auto q = broadcast<sint, __m128i>(qx);

			if (is_likely(reinterpret_cast<uintptr_t>(s) % _Mysize == 0)) {

				if (n < 1024 / _Mysize) {

#if defined(_WJR_FAST_REP)
					if (__use_rep) {
						auto u64v = broadcast<uint64_t, T>(val);
						if (is_constant_p(reinterpret_cast<uintptr_t>(s) % 8) &&
							reinterpret_cast<uintptr_t>(s) % 8 == 0) {
						}
						else {
							*reinterpret_cast<uint64_t*>(s) = u64v;
							auto __align_s = 8 - reinterpret_cast<uintptr_t>(s) % 8;
							s += __align_s / _Mysize;
							n -= __align_s / _Mysize;
						}
						*reinterpret_cast<uint64_t*>(s + n - 8 / _Mysize) = u64v;
						n &= -(8 / _Mysize);
						n /= (8 / _Mysize);
						wjr::masm::rep_stosq(reinterpret_cast<unsigned long long*>(s), u64v, n);
					}
					else {
#endif // _WJR_FAST_REP

						if (is_constant_p(reinterpret_cast<uintptr_t>(s) % bound) &&
							reinterpret_cast<uintptr_t>(s) % bound == 0) {
							// do nothing
						}
						else {
							simd_t::storeu(reinterpret_cast<sint*>(s), q);
							auto __align_s = bound - reinterpret_cast<uintptr_t>(s) % bound;
							s += __align_s / _Mysize;
							n -= __align_s / _Mysize;
							if (n < width * 4) goto WJR_MACRO_LABEL(aft_align);
						}

						do {
							simd_t::store(reinterpret_cast<sint*>(s), q);
							simd_t::store(reinterpret_cast<sint*>(s + width), q);
							simd_t::store(reinterpret_cast<sint*>(s + width * 2), q);
							simd_t::store(reinterpret_cast<sint*>(s + width * 3), q);
							s += width * 4;
							n -= width * 4;
						} while (n >= width * 4);

						WJR_MACRO_LABEL(aft_align) :

							s += n;
						auto ptr = reinterpret_cast<T*>(
							(reinterpret_cast<uintptr_t>(s - width * 3)) & (~(bound - 1)));
						simd_t::store(reinterpret_cast<sint*>(ptr), q);
						simd_t::store(reinterpret_cast<sint*>(ptr + width), q);
						simd_t::store(reinterpret_cast<sint*>(ptr + width * 2), q);
						simd_t::storeu(reinterpret_cast<sint*>(s - width), q);
#if defined(_WJR_FAST_REP)
					}
#endif // _WJR_FAST_REP

					return;
				}

				// align first 64 byte

				if (is_constant_p(reinterpret_cast<uintptr_t>(s) % 64) &&
					reinterpret_cast<uintptr_t>(s) % 64 == 0) {
					// do nothing
				}
				else {
					__WJR_ALIGN64byte(s);
					auto __align_s = 64 - reinterpret_cast<uintptr_t>(s) % 64;
					s += __align_s / _Mysize;
					n -= __align_s / _Mysize;
				}

#if defined(_WJR_NON_TEMPORARY)
				if (n < __nt_threshold) {
#endif // _WJR_NON_TEMPORARY

#if defined(_WJR_FAST_REP)
					if (__use_rep) {
						// align last 64 byte
						__WJR_ALIGN64byte(s + n - (64 / _Mysize));

						n &= -(64 / _Mysize);
						n /= (8 / _Mysize);
						auto u64v = broadcast<uint64_t, T>(val);
						wjr::masm::rep_stosq(reinterpret_cast<unsigned long long*>(s), u64v, n);
						return;
					}
#endif // _WJR_FAST_REP

					do {
						simd_t::store(reinterpret_cast<sint*>(s), q);
						simd_t::store(reinterpret_cast<sint*>(s + width), q);
						simd_t::store(reinterpret_cast<sint*>(s + width * 2), q);
						simd_t::store(reinterpret_cast<sint*>(s + width * 3), q);
						s += width * 4;
						n -= width * 4;
					} while (n >= width * 4);

#if defined(_WJR_NON_TEMPORARY)
				}
				else {
					do {
						simd_t::stream(reinterpret_cast<sint*>(s), q);
						simd_t::stream(reinterpret_cast<sint*>(s + width), q);
						simd_t::stream(reinterpret_cast<sint*>(s + width * 2), q);
						simd_t::stream(reinterpret_cast<sint*>(s + width * 3), q);
						s += width * 4;
						n -= width * 4;
					} while (n >= width * 4);
					simd::sse::sfence();
				}
#endif // _WJR_NON_TEMPORARY

				// store last 64 byte

				s += n;
				auto ptr = reinterpret_cast<T*>(
					(reinterpret_cast<uintptr_t>(s - width * 3)) & (~(bound - 1)));
				simd_t::store(reinterpret_cast<sint*>(ptr), q);
				simd_t::store(reinterpret_cast<sint*>(ptr + width), q);
				simd_t::store(reinterpret_cast<sint*>(ptr + width * 2), q);
				simd_t::storeu(reinterpret_cast<sint*>(s - width), q);

				return;
			}

			// non-aligned algorithm
			do {
				simd_t::storeu(reinterpret_cast<sint*>(s), q);
				simd_t::storeu(reinterpret_cast<sint*>(s + width), q);
				simd_t::storeu(reinterpret_cast<sint*>(s + width * 2), q);
				simd_t::storeu(reinterpret_cast<sint*>(s + width * 3), q);
				s += width * 4;
				n -= width * 4;
			} while (n >= width * 4);
			s += n;
			simd_t::storeu(reinterpret_cast<sint*>(s - width * 4), q);
			simd_t::storeu(reinterpret_cast<sint*>(s - width * 3), q);
			simd_t::storeu(reinterpret_cast<sint*>(s - width * 2), q);
			simd_t::storeu(reinterpret_cast<sint*>(s - width), q);
			return;
		}

#if WJR_AVX2
		// [16, 128)
		static_assert(width * 4 == 128 / _Mysize, "width * 4 == 128 / _Mysize");
		if (n > 32 / _Mysize) {
			// (32, 128)
			auto qy = wjr::broadcast<__m256i, __m128i>(qx);
			auto delta = (n & (64 / _Mysize)) >> 1;
			simd::avx::storeu(reinterpret_cast<__m256i*>(s), qy);
			simd::avx::storeu(reinterpret_cast<__m256i*>(s + delta), qy);
			simd::avx::storeu(reinterpret_cast<__m256i*>(s + n - (32 / _Mysize) - delta), qy);
			simd::avx::storeu(reinterpret_cast<__m256i*>(s + n - (32 / _Mysize)), qy);
			return;
		}
		// [16, 32]
		simd::sse::storeu(reinterpret_cast<__m128i*>(s), qx);
		simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (16 / _Mysize)), qx);
#else
		// [16, 128)
		if (n >= 64) {
			simd::sse::storeu(reinterpret_cast<__m128i*>(s), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + (16 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + (32 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + (48 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (64 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (48 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (32 / _Mysize)), qx);
			simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (16 / _Mysize)), qx);
			return;
		}
		auto delta = (n & (32 / _Mysize)) >> 1;
		simd::sse::storeu(reinterpret_cast<__m128i*>(s), qx);
		simd::sse::storeu(reinterpret_cast<__m128i*>(s + delta), qx);
		simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (16 / _Mysize) - delta), qx);
		simd::sse::storeu(reinterpret_cast<__m128i*>(s + n - (16 / _Mysize)), qx);
#endif // WJR_AVX2
		return;
	}

	if constexpr (_Mysize == 8) {
		if (n != 0) {
			*s = val;
		}
		return;
	}

	if constexpr (_Mysize <= 4) {
		if (n >= 4 / _Mysize) {
			auto u32v = broadcast<uint32_t, T>(val);
			auto delta = (n & (8 / _Mysize)) >> 1;
			*reinterpret_cast<uint32_t*>(s) = u32v;
			*reinterpret_cast<uint32_t*>(s + delta) = u32v;
			if constexpr (_Mysize != 4) {
				*reinterpret_cast<uint32_t*>(s + n - (4 / _Mysize) - delta) = u32v;
			}
			*reinterpret_cast<uint32_t*>(s + n - (4 / _Mysize)) = u32v;
			return;
		}
	}

	if constexpr (_Mysize == 4) {
		return;
	}

	if constexpr (_Mysize == 2) {
		if (n != 0) *s = val;
		return;
	}

	if constexpr (_Mysize == 1) {
		if (n != 0) {
			*s = val;
			if (n != 1) {
				*reinterpret_cast<uint16_t*>(s + n - 2) = broadcast<uint16_t, uint8_t>(val);
			}
		}
		return;
	}
}

_WJR_ALGO_END

#undef __WJR_ALIGN64byte

#endif // _WJR_FAST_MEMSET

_WJR_ALGO_BEGIN

#if defined(_WJR_FAST_MEMCHR)
template<typename T, typename U, typename _Pred>
struct __has_fast_memchr : std::conjunction<
	is_any_of<_Pred, std::equal_to<>, std::not_equal_to<>>,
	is_comparable<T, U, _Pred>,
	is_integrals<T, U>,
	is_any_index_of<sizeof(T), 1, 2, 4>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memchr_v = __has_fast_memchr<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred>
struct __has_fast_memrchr : __has_fast_memchr<T, U, _Pred> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memrchr_v = __has_fast_memrchr<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred, std::enable_if_t<__has_fast_memchr_v<T, U, _Pred>, int> = 0>
const T* memchr(const T* s, U val, size_t n, _Pred pred) {
	auto p = is_possible_memory_comparable<T>(val, pred);
	if (p == ipmc_result::none) {
		return s + n;
	}
	if (p == ipmc_result::all) {
		return s;
	}
	using value_type = std::make_unsigned_t<make_integral_t<T>>;
	auto __s = reinterpret_cast<const value_type*>(s);
	auto __val = static_cast<value_type>(static_cast<T>(val));
	return reinterpret_cast<const T*>(__memchr(__s, __val, n, pred));
}
template<typename T, typename U, typename _Pred, std::enable_if_t<__has_fast_memchr_v<T, U, _Pred>, int> = 0>
const T* memrchr(const T* s, U val, size_t n, _Pred pred) {
	auto p = is_possible_memory_comparable<T>(val, pred);
	if (p == ipmc_result::none) {
		return s;
	}
	if (p == ipmc_result::all) {
		return s + n;
	}
	using value_type = std::make_unsigned_t<make_integral_t<T>>;
	auto __s = reinterpret_cast<const value_type*>(s);
	auto __val = static_cast<value_type>(val);
	return reinterpret_cast<const T*>(__memrchr(__s, __val, n, pred));
}
#else
template<typename T, typename U, typename _Pred>
struct __has_fast_memchr : std::conjunction<
	std::is_same<_Pred, std::equal_to<>>,
	is_comparable<T, U, _Pred>,
	is_integrals<T, U>,
	is_any_index_of<sizeof(T), sizeof(char), sizeof(wchar_t)>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memchr_v = __has_fast_memchr<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred>
struct __has_fast_memrchr : std::false_type {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memrchr_v = __has_fast_memrchr<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred, std::enable_if_t<__has_fast_memchr_v<T, U, _Pred>, int> = 0>
const T* memchr(const T* s, U val, size_t n, _Pred pred) {
	auto p = is_possible_memory_comparable<T>(val, pred);
	if (p == ipmc_result::none) {
		return s + n;
	}
	if (p == ipmc_result::all) {
		return s;
	}
	if constexpr (sizeof(T) == sizeof(char)) {
		using value_type = char;
		auto __s = reinterpret_cast<const value_type*>(s);
		auto __val = static_cast<value_type>(val);
		auto pos = ::memchr(__s, __val, n);
		if (pos == nullptr) {
			return s + n;
		}
		return reinterpret_cast<const T*>(pos);
	}
	else {
		using value_type = wchar_t;
		auto __s = reinterpret_cast<const value_type*>(s);
		auto __val = static_cast<value_type>(val);
		auto pos = ::wmemchr(__s, __val, n);
		if (pos == nullptr) {
			return s + n;
		}
		return reinterpret_cast<const T*>(pos);
	}
}

#endif // _WJR_FAST_MEMCHR

#if defined(_WJR_FAST_MEMCMP)
template<typename T, typename U, typename _Pred>
struct __has_fast_memcmp : std::conjunction<
	is_memory_comparable<T, U, _Pred>,
	is_integrals<T, U>,
	is_any_index_of<sizeof(T), 1, 2, 4>
> {};

template<typename T, typename U>
struct __has_fast_memcmp<T, U, std::equal_to<>> : std::conjunction<
	is_memory_comparable<T, U, std::equal_to<>>
> {};

template<typename T, typename U>
struct __has_fast_memcmp<T, U, std::not_equal_to<>> : std::conjunction<
	is_memory_comparable<T, U, std::not_equal_to<>>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memcmp_v = __has_fast_memcmp<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred, std::enable_if_t<__has_fast_memcmp_v<T, U, _Pred>, int> = 0>
bool memcmp(const T* s0, const U* s1, size_t n, _Pred pred) {
	if constexpr (is_any_of_v<_Pred, std::equal_to<>, std::not_equal_to<>>) {
		using value_type = uint8_t;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		return __memcmp(__s0, __s1, n * sizeof(T), pred);
	}
	else {
		using value_type = make_integral_t<T>;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		return __memcmp(__s0, __s1, n, pred);
	}
}

#else
template<typename T, typename U, typename _Pred>
struct __has_fast_memcmp : std::false_type {};

template<typename T, typename U>
struct __has_fast_memcmp<T, U, std::equal_to<>> : std::conjunction<
	is_memory_comparable<T, U, std::equal_to<>>
> {};

template<typename T, typename U, typename _Pred>
inline constexpr bool __has_fast_memcmp_v = __has_fast_memcmp<T, U, _Pred>::type::value;

template<typename T, typename U, typename _Pred, std::enable_if_t<__has_fast_memcmp_v<T, U, _Pred>, int> = 0>
bool memcmp(const T* s0, const U* s1, size_t n, _Pred pred) {
	return ::memcmp(s0, s1, n * sizeof(T)) == 0;
}

#endif // _WJR_FAST_MEMCMP

#if defined(_WJR_FAST_MEMMIS)
template<typename T, typename U, typename _Pred>
struct __has_fast_memmis : std::conjunction<
	is_memory_comparable<T, U, _Pred>,
	is_integrals<T, U>,
	is_any_index_of<sizeof(T), 1, 2, 4>
> {};

template<typename T, typename U>
struct __has_fast_memmis<T, U, std::equal_to<>> : std::conjunction<
	is_memory_comparable<T, U, std::equal_to<>>
> {};

template<typename T, typename U>
struct __has_fast_memmis<T, U, std::not_equal_to<>> : std::conjunction<
	is_memory_comparable<T, U, std::not_equal_to<>>
> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memmis_v = __has_fast_memmis<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred>
struct __has_fast_memrmis : __has_fast_memmis<T, U, _Pred> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memrmis_v = __has_fast_memrmis<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred, std::enable_if_t<
	__has_fast_memmis_v<T, U, _Pred>, int> = 0>
const T* memmis(const T* s0, const U* s1, size_t n, _Pred pred) {
	if constexpr (is_any_of_v<_Pred, std::equal_to<>, std::not_equal_to<>>) {
		using value_type = uint8_t;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		auto __pos =
			__memmis(__s0, __s1, n * sizeof(T), pred);
		auto __dif = (__pos - __s0) / sizeof(T);
		return s0 + __dif;
	}
	else {
		using value_type = make_integral_t<T>;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		return reinterpret_cast<const T*>(__memmis(__s0, __s1, n, pred));
	}
}

template<typename T, typename U, typename _Pred, std::enable_if_t<
	__has_fast_memmis_v<T, U, _Pred>, int> = 0>
const T* memrmis(const T* s0, const U* s1, size_t n, _Pred pred) {
	if constexpr (is_any_of_v<_Pred, std::equal_to<>, std::not_equal_to<>>) {
		using value_type = uint8_t;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		auto __pos =
			__memrmis(__s0, __s1, n * sizeof(T), pred);
		auto __e0 = __s0 + n * sizeof(T);
		auto __dif = (__e0 - __pos) / sizeof(T);
		return (s0 + n) - __dif;
	}
	else {
		using value_type = make_integral_t<T>;
		auto __s0 = reinterpret_cast<const value_type*>(s0);
		auto __s1 = reinterpret_cast<const value_type*>(s1);
		return reinterpret_cast<const T*>(__memrmis(__s0, __s1, n, pred));
	}
}

#else
template<typename T, typename U, typename _Pred>
struct __has_fast_memmis : std::false_type {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memmis_v = __has_fast_memmis<T, U, _Pred>::value;

template<typename T, typename U, typename _Pred>
struct __has_fast_memrmis : __has_fast_memmis<T, U, _Pred> {};

template<typename T, typename U, typename _Pred>
constexpr bool __has_fast_memrmis_v = __has_fast_memrmis<T, U, _Pred>::value;

#endif // _WJR_FAST_MEMMIS

#if defined(_WJR_FAST_MEMCNT)
template<typename T, typename U>
struct __has_fast_memcnt : std::conjunction<
	is_comparable<T, U, std::equal_to<>>,
	is_integrals<T, U>,
	is_any_index_of<sizeof(T), 1, 2, 4>
> {};

template<typename T, typename U>
constexpr bool __has_fast_memcnt_v = __has_fast_memcnt<T, U>::value;

template<typename T, typename U, std::enable_if_t<__has_fast_memcnt_v<T, U>, int> = 0>
size_t memcnt(const T* s, U val, size_t n) {
	auto p = is_possible_memory_comparable<T>(val, std::equal_to<>{});
	if (p == ipmc_result::none) {
		return 0;
	}
	using value_type = std::make_unsigned_t<make_integral_t<T>>;
	auto __s = reinterpret_cast<const value_type*>(s);
	auto __val = static_cast<value_type>(val);
	return __memcnt(__s, __val, n);
}

#else
template<typename T, typename U>
struct __has_fast_memcnt : std::false_type {};

template<typename T, typename U>
constexpr bool __has_fast_memcnt_v = __has_fast_memcnt<T, U>::value;

#endif // _WJR_FAST_MEMCNT

template<template<typename X, typename Y> typename TEST, typename T, typename U>
struct __has_fast_memset_helper : std::conjunction<
	std::bool_constant<TEST<T, U>::is_fill>
> {};

template<template<typename X, typename Y> typename TEST, typename T, typename U>
constexpr bool __has_fast_memset_helper_v = __has_fast_memset_helper<TEST, T, U>::value;

template<template<typename X, typename Y> typename TEST, typename T, typename U>
static void __memset_helper(T* s, const U& val, size_t n) {

	if (is_constant_p(n) && n <= 4 / sizeof(T)) {
		std::fill_n(s, n, val);
		return;
	}

	const auto& _Val = TEST<T, const U&>::get(val);

	auto __bytes_num = _Get_bytes_num<sizeof(T)>(_Val);

#if defined(_WJR_FAST_MEMSET)
	constexpr auto __max_bytes_num = _Get_max_bytes_num<sizeof(T)>();
	if (__bytes_num == 0) {
		std::fill_n(s, n, val);
		return;
	}
#else
	constexpr auto __max_bytes_num = 1;
	if (__bytes_num != 1) {
		std::fill_n(s, n, val);
		return;
	}
#endif 

	using value_type = uint_t<__max_bytes_num * 8>;
	auto __s = reinterpret_cast<value_type*>(s);
	auto __val = *reinterpret_cast<const value_type*>(&_Val);
	static_assert(std::is_same_v<decltype(__val), value_type>, "type mismatch");

#if defined(_WJR_FAST_MEMSET)
	__memset(__s, __val, n * (sizeof(T) / __max_bytes_num));
#else
	::memset(__s, __val, n * (sizeof(T) / __max_bytes_num));
#endif
}

template<typename T, typename U>
struct __has_fast_construct_memset : __has_fast_memset_helper<is_byte_constructible, T, U> {};

template<typename T, typename U>
constexpr bool __has_fast_construct_memset_v = __has_fast_construct_memset<T, U>::value;

template<typename T, typename U>
void construct_memset(T* s, const U& val, size_t n) {
	__memset_helper<is_byte_constructible>(s, val, n);
}

template<typename T, typename U>
struct __has_fast_assign_memset : __has_fast_memset_helper<is_byte_assignable, T, U> {};

template<typename T, typename U>
constexpr bool __has_fast_assign_memset_v = __has_fast_assign_memset<T, U>::value;

template<typename T, typename U>
void assign_memset(T* s, const U& val, size_t n) {
	__memset_helper<is_byte_assignable>(s, val, n);
}

template<template<typename X, typename Y> typename TEST, typename T, typename U>
struct __has_fast_memcpy_helper : std::conjunction <
	std::bool_constant<TEST<T, U>::is_copy>
> {};

template<template<typename X, typename Y> typename TEST, typename T, typename U>
constexpr bool __has_fast_memcpy_helper_v = __has_fast_memcpy_helper<TEST, T, U>::value;

template<template<typename X, typename Y> typename TEST, typename T, typename U>
static void __memcpy_helper(T* s, const U* t, size_t n) {
	static_assert(sizeof(T) == sizeof(U), "type mismatch");
#if defined(_WJR_FAST_MEMCPY)
#else
	::memcpy(s, t, n * sizeof(T));
#endif
}

template<template<typename X, typename Y> typename TEST, typename T, typename U>
static void __memmove_helper(T* s, const U* t, size_t n) {
	static_assert(sizeof(T) == sizeof(U), "type mismatch");
#if defined(_WJR_FAST_MEMCPY)
#else
	::memmove(s, t, n * sizeof(T));
#endif
}

template<typename T, typename U>
struct __has_fast_construct_memcpy : __has_fast_memcpy_helper<is_byte_constructible, T, U> {};

template<typename T, typename U>
constexpr bool __has_fast_construct_memcpy_v = __has_fast_construct_memcpy<T, U>::value;

template<typename T, typename U>
void construct_memcpy(T* s, const U* t, size_t n) {
	__memcpy_helper<is_byte_constructible>(s, t, n);
}

template<typename T, typename U>
void construct_memmove(T* s, const U* t, size_t n) {
	__memmove_helper<is_byte_constructible>(s, t, n);
}

template<typename T, typename U>
struct __has_fast_assign_memcpy : __has_fast_memcpy_helper<is_byte_assignable, T, U> {};

template<typename T, typename U>
constexpr bool __has_fast_assign_memcpy_v = __has_fast_assign_memcpy<T, U>::value;

template<typename T, typename U>
void assign_memcpy(T* s, const U* t, size_t n) {
	__memcpy_helper<is_byte_assignable>(s, t, n);
}

template<typename T, typename U>
void assign_memmove(T* s, const U* t, size_t n) {
	__memmove_helper<is_byte_assignable>(s, t, n);
}

_WJR_ALGO_END

#endif // __WJR_ALGO_ALOG_H

_WJR_BEGIN

template<typename _Iter, typename _Val, typename _Pred,
	typename _Iter_value = iter_val_t<_Iter>>
	struct __has_fast_find : std::conjunction<
	is_contiguous_iterator<_Iter>,
	std::conditional_t<
	wjr::is_reverse_iterator_v<_Iter>,
	algo::__has_fast_memrchr<_Iter_value, _Val, _Pred>,
	algo::__has_fast_memchr<_Iter_value, _Val, _Pred>
	>
	> {};

template<typename _Iter, typename _Val, typename _Pred>
constexpr bool __has_fast_find_v = __has_fast_find<_Iter, _Val, _Pred>::value;

struct find_fn {

	template<typename _Iter, typename _Ty, typename _Pred = std::equal_to<>>
	WJR_CONSTEXPR20 _Iter operator()(
		_Iter _First, _Iter _Last, const _Ty& _Val, _Pred pred = _Pred()) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_find_v<_Iter, _Ty, _Pred>) {
				const auto n = std::distance(_First, _Last);
				if constexpr (!wjr::is_reverse_iterator_v<_Iter>) {
					const auto first = wjr::get_address(_First);
					return _First + (algo::memchr(first, _Val, n, pred) - first);
				}
#if defined(_WJR_FAST_MEMCHR) // use algo::memchr
				else {
					const auto first = wjr::get_address(_Last - 1);
					return _Last - (algo::memrchr(first, _Val, n, pred) - first);
				}
#endif // _WJR_FAST_MEMCHR
			}
		}
		if constexpr (std::is_same_v<_Pred, std::equal_to<>>) {
			return std::find(_First, _Last, _Val);
		}
		else {
			for (; _First != _Last; ++_First) {
				if (pred(*_First, _Val)) {
					return _First;
				}
			}
			return _Last;
		}
	}

};

constexpr find_fn find{};

struct find_if_fn {
	template<typename _Iter, typename _Pr>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Iter _Last, _Pr _Pred) const {
		return std::find_if(_First, _Last, _Pred);
	}
};

constexpr find_if_fn find_if{};

struct find_if_not_fn {
	template<typename _Iter, typename _Pr>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Iter _Last, _Pr _Pred) const {
		return std::find_if_not(_First, _Last, _Pred);
	}
};

constexpr find_if_not_fn find_if_not{};

template<typename _Iter, typename _Val,
	typename _Iter_value = iter_val_t<_Iter>>
	struct __has_fast_count : std::conjunction<
	wjr::is_contiguous_iterator<_Iter>,
	algo::__has_fast_memcnt<_Iter_value, _Val>
	> {};

template<typename _Iter, typename _Val>
constexpr bool __has_fast_count_v = __has_fast_count<_Iter, _Val>::value;

struct count_fn {

	template<typename _Iter, typename _Ty>
	WJR_CONSTEXPR20 typename std::iterator_traits<_Iter>::difference_type
		operator()(_Iter _First, _Iter _Last, const _Ty& _Val) const {
		if (!wjr::is_constant_evaluated()) {
#if defined(_WJR_FAST_MEMCNT)
			if constexpr (__has_fast_count_v<_Iter, _Ty>) {
				const auto n = _Last - _First;
				if constexpr (!wjr::is_reverse_iterator_v<_Iter>) {
					const auto first = wjr::get_address(_First);
					return algo::memcnt(first, _Val, n);
				}
				else {
					const auto first = wjr::get_address(_Last - 1);
					return algo::memcnt(first, _Val, n);
				}
			}
#endif // _WJR_FAST_MEMCNT
		}
		return std::count(_First, _Last, _Val);
	}
};

constexpr count_fn count{};

struct count_if_fn {

	template<typename _Iter, typename _Pr>
	WJR_CONSTEXPR20 typename std::iterator_traits<_Iter>::difference_type
		operator()(_Iter _First, _Iter _Last, _Pr _Pred) const {
		return std::count_if(_First, _Last, _Pred);
	}
};

constexpr count_if_fn count_if{};

// First use algo::memcmp
// Then use memcmp
template<typename _Iter1, typename _Iter2, typename _Pred,
	typename _Iter_value1 = iter_val_t<_Iter1>,
	typename _Iter_value2 = iter_val_t<_Iter2>>
	struct __has_fast_equal_helper : std::conjunction<
	wjr::is_contiguous_iterator<_Iter1>,
	wjr::is_contiguous_iterator<_Iter2>,
	std::bool_constant<wjr::is_reverse_iterator_v<_Iter1> == wjr::is_reverse_iterator_v<_Iter2>>,
	algo::__has_fast_memcmp<_Iter_value1, _Iter_value2, _Pred>
	> {};

template<typename _Iter1, typename _Iter2, typename _Pred>
struct __has_fast_equal : std::bool_constant<__has_fast_equal_helper<_Iter1, _Iter2, _Pred>::value> {};

template<typename _Iter1, typename _Iter2, typename _Pred>
constexpr bool __has_fast_equal_v = __has_fast_equal<_Iter1, _Iter2, _Pred>::value;

template<typename _Iter1, typename _Iter2, typename _Pred,
	typename _Iter_value1 = iter_val_t<_Iter1>,
	typename _Iter_value2 = iter_val_t<_Iter2>>
	struct __has_fast_mismatch : std::conjunction <
	wjr::is_contiguous_iterator<_Iter1>,
	wjr::is_contiguous_iterator<_Iter2>,
	std::bool_constant<wjr::is_reverse_iterator_v<_Iter1> == wjr::is_reverse_iterator_v<_Iter2>>,
	std::conditional_t<
	wjr::is_reverse_iterator_v<_Iter1>,
	algo::__has_fast_memrmis<_Iter_value1, _Iter_value2, _Pred>,
	algo::__has_fast_memmis<_Iter_value1, _Iter_value2, _Pred>
	>
	> {};

template<typename _Iter1, typename _Iter2, typename _Pred>
constexpr bool __has_fast_mismatch_v = __has_fast_mismatch<_Iter1, _Iter2, _Pred>::value;

struct mismatch_fn {

	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2) const {
		return this->operator()(_First1, _Last1, _First2, std::equal_to<>{});
	}

	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2) const {
		return this->operator()(_First1, _Last1, _First2, _Last2, std::equal_to<>{});
	}

	template<typename _Iter1, typename _Iter2, typename _Pred>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Pred pred) const {
		if (!wjr::is_constant_evaluated()) {
#if defined(_WJR_FAST_MEMMIS)
			if constexpr (__has_fast_mismatch_v<_Iter1, _Iter2, _Pred>) {
				const auto n = std::distance(_First1, _Last1);
				if (is_unlikely(n == 0)) { return std::make_pair(_First1, _First2); }
				if constexpr (!wjr::is_reverse_iterator_v<_Iter1>) {
					const auto first1 = wjr::get_address(_First1);
					const auto first2 = wjr::get_address(_First2);

					auto pos = algo::memmis(first1, first2, n, pred) - first1;
					return std::make_pair(_First1 + pos, _First2 + pos);
				}
				else {
					const auto first1 = wjr::get_address(_Last1 - 1);
					const auto _Last2 = _First2 + n;
					const auto first2 = wjr::get_address(_Last2 - 1);

					auto pos = (first1 + n) - algo::memrmis(first1, first2, n, pred);
					return std::make_pair(_First1 + pos, _First2 + pos);
				}
			}
#endif // _WJR_FAST_MEMMIS
		}
		return std::mismatch(_First1, _Last1, _First2, pred);
	}

	template<typename _Iter1, typename _Iter2, typename _Pred>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2, _Pred pred) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_mismatch_v<_Iter1, _Iter2, _Pred>) {
				const auto n = _Last1 - _First1;
				const auto m = _Last2 - _First2;
				const auto _M = n < m ? n : m;
				return this->operator()(_First1, _First1 + _M, _First2, pred);
			}
		}
		return std::mismatch(_First1, _Last1, _First2, _Last2, pred);
	}

};

constexpr mismatch_fn mismatch;

struct equal_fn {

	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2) const {
		return this->operator()(_First1, _Last1, _First2, std::equal_to<>{});
	}

	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2) const {
		return this->operator()(_First1, _Last1, _First2, _Last2, std::equal_to<>{});
	}

	template<typename _Iter1, typename _Iter2, typename _Pred>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Pred pred) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_equal_v<_Iter1, _Iter2, _Pred>) {
				const auto n = _Last1 - _First1;
				if (is_unlikely(n == 0)) { return true; }
				if constexpr (!wjr::is_reverse_iterator_v<_Iter1>) {
					const auto first1 = wjr::get_address(_First1);
					const auto first2 = wjr::get_address(_First2);
					return algo::memcmp(first1, first2, n, pred);
				}
				else {
					const auto first1 = wjr::get_address(_Last1 - 1);
					const auto _Last2 = _First2 + n;
					const auto first2 = wjr::get_address(_Last2 - 1);
					return algo::memcmp(first1, first2, n, pred);
				}
			}
		}
		return std::equal(_First1, _Last1, _First2, pred);
	}

	template<typename _Iter1, typename _Iter2, typename _Pred>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2, _Pred pred) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_equal_v<_Iter1, _Iter2, _Pred>) {
				const auto n = std::distance(_First1, _Last1);
				const auto m = std::distance(_First2, _Last2);
				if (n != m) { return false; }
				return this->operator()(_First1, _Last1, _First2, pred);
			}
		}
		return std::equal(_First1, _Last1, _First2, _Last2, pred);
	}

};

constexpr equal_fn equal{};

template<typename _Iter1, typename _Iter2, typename _Pred,
	typename _Iter_value1 = iter_val_t<_Iter1>,
	typename _Iter_value2 = iter_val_t<_Iter2>>
	struct __has_fast_lexicographical_compare : std::conjunction<
	wjr::is_any_of<_Pred, std::less<>, std::not_equal_to<>>,
	__has_fast_mismatch<_Iter1, _Iter2, _Pred>
	> {};

template<typename _Iter1, typename _Iter2, typename _Pred>
constexpr bool __has_fast_lexicographical_compare_v = __has_fast_lexicographical_compare<_Iter1, _Iter2, _Pred>::value;

struct lexicographical_compare_fn {
	template<typename _ExPolicy, typename _Iter1, typename _Iter2>
	bool operator()(_ExPolicy&& _Policy, _Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2) const {
		return this->operator()(_Policy, _First1, _Last1, _First2, _Last2, std::less<>{});
	}

	template<typename _ExPolicy, typename _Iter1, typename _Iter2, typename _Pred>
	bool operator()(_ExPolicy&& _Policy, _Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2, _Pred pred) const {
		return std::lexicographical_compare(_Policy, _First1, _Last1, _First2, _Last2, pred);
	}

	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2) const {
		return this->operator()(_First1, _Last1, _First2, _Last2, std::less<>{});
	}

	template<typename _Iter1, typename _Iter2, typename _Pred>
	WJR_CONSTEXPR20 bool operator()(_Iter1 _First1, _Iter1 _Last1, _Iter2 _First2, _Iter2 _Last2, _Pred pred) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_lexicographical_compare_v<_Iter1, _Iter2, _Pred>) {
				const auto n = std::distance(_First1, _Last1);
				const auto m = std::distance(_First2, _Last2);
				auto cl = std::min(n, m);
				auto e = _First1 + cl;
				auto pos = wjr::mismatch(_First1, e, _First2, std::equal_to<>{}).first - _First1;
				if (pos != cl) {
					if (pred(_First1 + pos, _First2 + pos)) {
						return true;
					}
					return false;
				}
				return n < m;
			}
		}
		return std::lexicographical_compare(_First1, _Last1, _First2, _Last2, pred);
	}
};

constexpr lexicographical_compare_fn lexicographical_compare{};

template<typename _Iter, typename _Val,
	typename _Iter_ref = iter_ref_t<_Iter>>
	struct __has_fast_fill : std::conjunction<
	is_contiguous_iterator<_Iter>,
	algo::__has_fast_assign_memset<remove_cref_t<_Iter_ref>, add_cref_t<_Val>>
	> {};

template<typename _Iter, typename _Val>
constexpr bool __has_fast_fill_v = __has_fast_fill<_Iter, _Val>::value;

struct fill_fn {
	template<typename _Iter, typename _Val>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last, const _Val& value) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_fill_v<_Iter, _Val>) {
				const auto n = std::distance(_First, _Last);
				if constexpr (!is_reverse_iterator_v<_Iter>) {
					const auto first = wjr::get_address(_First);
					algo::assign_memset(first, value, n);
				}
				else {
					if (is_unlikely(n == 0)) { return; }
					const auto first = wjr::get_address(_Last - 1);
					algo::assign_memset(first, value, n);
				}
				return;
			}
		}
		return std::fill(_First, _Last, value);
	}

};

constexpr fill_fn fill{};

struct fill_n_fn {
	template<typename _Iter, typename _Size, typename _Val>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Size count, const _Val& value) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_fill_v<_Iter, _Val>) {
				if (count <= 0) { return _First; }
				wjr::fill(_First, _First + count, value);
				return _First + count;
			}
		}
		return std::fill_n(_First, count, value);
	}

};

constexpr fill_n_fn fill_n{};

template<typename _Input, typename _Output,
	typename _Input_ref = iter_ref_t<_Input>,
	typename _Output_ref = iter_ref_t<_Output>>
	struct __has_fast_copy : std::conjunction<
	is_contiguous_iterator<_Input>,
	is_contiguous_iterator<_Output>,
	std::bool_constant<wjr::is_reverse_iterator_v<_Input> == wjr::is_reverse_iterator_v<_Output>>,
	algo::__has_fast_assign_memcpy<remove_ref_t<_Output_ref>, _Input_ref>
	> {};

template<typename _Input, typename _Output>
constexpr bool __has_fast_copy_v = __has_fast_copy<_Input, _Output>::value;

struct copy_fn {
	template<typename _Input, typename _Output>
	WJR_CONSTEXPR20 _Output operator()(_Input _First1, _Input _Last1, _Output _First2) const {
		static_assert(!std::is_const_v<iter_ref_t<_Output>>, "Output iterator must not be const");
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_copy_v<_Input, _Output>) {
				const auto n = std::distance(_First1, _Last1);
				if (is_unlikely(n == 0)) { return _First2; }
				if constexpr (!wjr::is_reverse_iterator_v<_Input>) {
					const auto first1 = wjr::get_address(_First1);
					const auto first2 = wjr::get_address(_First2);

					algo::assign_memmove(first2, first1, n);
				}
				else {
					const auto first1 = wjr::get_address(_Last1 - 1);
					const auto _Last2 = _First2 + n;
					const auto first2 = wjr::get_address(_Last2 - 1);

					algo::assign_memmove(first2, first1, n);
				}
				return _First2 + n;
			}
		}
		return std::copy(_First1, _Last1, _First2);
	}
};

constexpr copy_fn copy{};

struct copy_n_fn {
	template<typename _Input, typename _Size, typename _Output>
	WJR_CONSTEXPR20 _Output operator()(_Input _First1, _Size count, _Output _First2) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_copy_v<_Input, _Output>) {
				if (count <= 0) { return _First2; }
				return wjr::copy(_First1, _First1 + count, _First2);
			}
		}
		return std::copy_n(_First1, count, _First2);
	}
};

constexpr copy_n_fn copy_n{};

struct copy_backward_fn {
	template<typename _Input, typename _Output>
	WJR_CONSTEXPR20 _Output operator()(_Input _First1, _Input _Last1, _Output _Last2) const {
		return wjr::copy(std::make_reverse_iterator(_Last1),
			std::make_reverse_iterator(_First1),
			std::make_reverse_iterator(_Last2)).base();
	}
};

constexpr copy_backward_fn copy_backward{};

struct move_fn {
	template<typename _Input, typename _Output>
	WJR_CONSTEXPR20 _Output operator()(_Input _First1, _Input _Last1, _Output _First2) const {
		return wjr::copy(std::make_move_iterator(_First1), std::make_move_iterator(_Last1), _First2);
	}
};

constexpr move_fn move{};

struct move_backward_fn {
	template<typename _Input, typename _Output>
	WJR_CONSTEXPR20 _Output operator()(_Input _First1, _Input _Last1, _Output _Last2) const {
		return wjr::copy_backward(std::make_move_iterator(_First1), std::make_move_iterator(_Last1), _Last2);
	}
};

constexpr move_backward_fn move_backward{};

struct construct_at_fn {
	template<typename _Iter, typename...Args, std::enable_if_t<is_iterator_v<_Iter>, int> = 0>
	WJR_CONSTEXPR20 void operator()(_Iter iter, Args&&... args) const {
		using value_type = iter_val_t<_Iter>;
		::new (voidify(get_address(iter))) value_type(std::forward<Args>(args)...);
	}

	template<typename _Iter, std::enable_if_t<is_iterator_v<_Iter>, int> = 0>
	WJR_CONSTEXPR20 void operator()(_Iter iter, default_construct_tag) const {
		using value_type = iter_val_t<_Iter>;
		::new (voidify(get_address(iter))) value_type;
	}

	template<typename _Iter, std::enable_if_t<is_iterator_v<_Iter>, int> = 0>
	WJR_CONSTEXPR20 void operator()(_Iter iter, value_construct_tag) const {
		this->operator()(iter);
	}

	template<typename Alloc, typename _Iter, typename...Args, std::enable_if_t<!is_iterator_v<Alloc>, int> = 0>
	WJR_CONSTEXPR20 void operator()(Alloc& al, _Iter iter, Args&&...args) const {
		using pointer = iter_address_t<_Iter>;
		if constexpr (is_default_allocator_construct_v<Alloc, pointer, Args...>) {
			this->operator()(iter, std::forward<Args>(args)...);
		}
		else {
			std::allocator_traits<Alloc>::construct(al, get_address(iter), std::forward<Args>(args)...);
		}
	}

};

constexpr construct_at_fn construct_at;

struct destroy_at_fn {
	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter ptr) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (!std::is_trivially_destructible_v<value_type>) {
			get_address(ptr)->~value_type();
		}
	}

	template<typename Alloc, typename _Iter>
	WJR_CONSTEXPR20 void operator()(Alloc& al, _Iter iter) const {
		if constexpr (is_default_allocator_destroy_v<Alloc, _Iter>) {
			this->operator()(iter);
		}
		else {
			std::allocator_traits<Alloc>::destroy(al, get_address(iter));
		}
	}

};

constexpr destroy_at_fn destroy_at;

struct destroy_fn {
	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (!std::is_trivially_destructible_v<value_type>) {
			for (; _First != _Last; ++_First) {
				wjr::destroy_at(_First);
			}
		}
	}

	template<typename Alloc, typename _Iter>
	WJR_CONSTEXPR20 void operator()(Alloc& al, _Iter _First, _Iter _Last) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (!(is_default_allocator_destroy_v<Alloc, _Iter>
			&& std::is_trivially_destructible_v<value_type>)) {
			for (; _First != _Last; ++_First) {
				wjr::destroy_at(al, _First);
			}
		}
	}
};

constexpr destroy_fn destroy;

struct destroy_n_fn {
	template<typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 void operator()(_Iter _First, const _Diff n) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (!std::is_trivially_destructible_v<value_type>) {
			for (; n > 0; (void)++_First, --n) {
				wjr::destroy_at(_First);
			}
		}
	}

	template<typename Alloc, typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 void operator()(Alloc& al, _Iter _First, _Diff n) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (!(is_default_allocator_destroy_v<Alloc, _Iter> && std::is_trivially_destructible_v<value_type>)) {
			for (; n > 0; (void)++_First, --n) {
				wjr::destroy_at(al, _First);
			}
		}
	}
};

constexpr destroy_n_fn destroy_n;

struct uninitialized_default_construct_fn {

	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last) const {
		std::uninitialized_default_construct(_First, _Last);
	}

	template<typename Alloc, typename _Iter>
	WJR_CONSTEXPR20 void operator()(
		Alloc& al, _Iter _First, _Iter _Last) const {
		using value_type = iter_val_t<_Iter>;
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, default_construct_tag>) {
			this->operator()(_First, _Last);
		}
		else {
			for (; _First != _Last; (void)++_First) {
				wjr::construct_at(al, _First, default_construct_tag{});
			}
		}
	}
};

constexpr uninitialized_default_construct_fn uninitialized_default_construct;

struct uninitialized_default_construct_n_fn {
	template<typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, const _Diff n) const {
		return std::uninitialized_default_construct_n(_First, n);
	}

	template<typename Alloc, typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(
		Alloc& al, _Iter _First, _Diff n) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, default_construct_tag>) {
			return this->operator()(_First, n);
		}
		else {
			for (; n > 0; (void)++_First, --n) {
				wjr::construct_at(al, _First, default_construct_tag{});
			}
			return _First;
		}
	}
};

constexpr uninitialized_default_construct_n_fn uninitialized_default_construct_n;

struct uninitialized_value_construct_fn {
	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last) const {
		std::uninitialized_value_construct(_First, _Last);
	}

	template<typename Alloc, typename _Iter>
	WJR_CONSTEXPR20 void operator()(
		Alloc& al, _Iter _First, _Iter _Last) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, value_construct_tag>) {
			this->operator()(_First, _Last);
		}
		else {
			for (; _First != _Last; (void)++_First) {
				wjr::construct_at(al, _First, value_construct_tag{});
			}
		}
	}
};

constexpr uninitialized_value_construct_fn uninitialized_value_construct;

struct uninitialized_value_construct_n_fn {
	template<typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Diff n) const {
		return std::uninitialized_value_construct_n(_First, n);
	}

	template<typename Alloc, typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(
		Alloc& al, _Iter _First, _Diff n) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, value_construct_tag>) {
			return this->operator()(_First, n);
		}
		else {
			for (; n > 0; (void)++_First, --n) {
				wjr::construct_at(al, _First, value_construct_tag{});
			}
			return _First;
		}
	}
};

constexpr uninitialized_value_construct_n_fn uninitialized_value_construct_n;

template<typename _Input, typename _Output,
	typename _Input_ref = iter_ref_t<_Input>,
	typename _Output_ref = iter_ref_t<_Output>>
	struct __has_fast_uninitialized_copy : std::conjunction<
	is_contiguous_iterator<_Input>,
	is_contiguous_iterator<_Output>,
	std::bool_constant<wjr::is_reverse_iterator_v<_Input> == wjr::is_reverse_iterator_v<_Output>>,
	algo::__has_fast_construct_memcpy<remove_ref_t<_Output_ref>, _Input_ref>
	> {};

template<typename _Input, typename _Output>
constexpr bool __has_fast_uninitialized_copy_v = __has_fast_uninitialized_copy<_Input, _Output>::value;

struct uninitialized_copy_fn {
	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(_Iter1 _First, _Iter1 _Last, _Iter2 _Dest) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_copy_v<_Iter1, _Iter2>) {
				const auto n = std::distance(_First, _Last);
				if (is_unlikely(n == 0)) { return _Dest; }
				if constexpr (!wjr::is_reverse_iterator_v<_Iter1>) {
					const auto first1 = wjr::get_address(_First);
					const auto first2 = wjr::get_address(_Dest);

					algo::construct_memmove(first2, first1, n);
				}
				else {
					const auto first1 = wjr::get_address(_Last - 1);
					const auto _Last2 = _Dest + n;
					const auto first2 = wjr::get_address(_Last2 - 1);

					algo::construct_memmove(first2, first1, n);
				}
				return _Dest + n;
			}
		}
		return std::uninitialized_copy(_First, _Last, _Dest);
	}

	template<typename Alloc, typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(
		Alloc& al, _Iter1 _First, _Iter1 _Last, _Iter2 _Dest) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter2, decltype(*_First)>) {
			return this->operator()(_First, _Last, _Dest);
		}
		else {
			for (; _First != _Last; ++_Dest, (void)++_First) {
				wjr::construct_at(al, _Dest, *_First);
			}
		}
	}
};

constexpr uninitialized_copy_fn uninitialized_copy;

struct uninitialized_copy_n_fn {
	template<typename _Iter1, typename _Diff, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(_Iter1 _First, _Diff n, _Iter2 _Dest) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_copy_v<_Iter1, _Iter2>) {
				if (n <= 0) { return _Dest; }
				return wjr::uninitialized_copy(_First, _First + n, _Dest);
			}
		}
		return std::uninitialized_copy_n(_First, n, _Dest);
	}

	template<typename Alloc, typename _Iter1, typename _Diff, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(Alloc& al, _Iter1 _First, _Diff n, _Iter2 _Dest) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter2, decltype(*_First)>) {
			return this->operator()(_First, n, _Dest);
		}
		else {
			for (; n > 0; ++_First, (void)++_Dest, --n) {
				wjr::construct_at(al, _Dest, *_First);
			}
			return _Dest;
		}
	}
};

constexpr uninitialized_copy_n_fn uninitialized_copy_n;

template<typename _Iter, typename _Val,
	typename _Iter_ref = iter_ref_t<_Iter>>
	struct __has_fast_uninitialized_fill : std::conjunction<
	is_contiguous_iterator<_Iter>,
	algo::__has_fast_construct_memset<remove_cref_t<_Iter_ref>, add_cref_t<_Val>>
	> {};

template<typename _Iter, typename _Val>
constexpr bool __has_fast_uninitialized_fill_v = __has_fast_uninitialized_fill<_Iter, _Val>::value;

struct uninitialized_fill_fn {
	template<typename _Iter, typename _Val>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last, const _Val& val) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_fill_v<_Iter, _Val>) {
				const auto n = std::distance(_First, _Last);
				if constexpr (!is_reverse_iterator_v<_Iter>) {
					const auto first = wjr::get_address(_First);
					algo::construct_memset(first, val, n);
				}
				else {
					if (is_unlikely(n == 0)) { return; }
					const auto first = wjr::get_address(_Last - 1);
					algo::construct_memset(first, val, n);
				}
				return;
			}
		}
		return std::uninitialized_fill(_First, _Last, val);
	}

	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last, default_construct_tag) const {
		wjr::uninitialized_default_construct(_First, _Last);
	}

	template<typename _Iter>
	WJR_CONSTEXPR20 void operator()(_Iter _First, _Iter _Last, value_construct_tag) const {
		wjr::uninitialized_value_construct(_First, _Last);
	}

	template<typename Alloc, typename _Iter, typename _Val>
	WJR_CONSTEXPR20 void operator()(Alloc& al, _Iter _First, _Iter _Last, const _Val& val) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, _Val>) {
			this->operator()(_First, _Last, val);
		}
		else {
			for (; _First != _Last; (void)++_First) {
				wjr::construct_at(al, _First, val);
			}
		}
	}
};

constexpr uninitialized_fill_fn uninitialized_fill;

struct uninitialized_fill_n_fn {
	template<typename _Iter, typename _Diff, typename _Val>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Diff count, const _Val& val) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_fill_v<_Iter, _Val>) {
				if (count <= 0) { return _First; }
				wjr::uninitialized_fill(_First, _First + count, val);
				return _First + count;
			}
		}
		return std::uninitialized_fill_n(_First, count, val);
	}

	template<typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Diff n, default_construct_tag) const {
		return wjr::uninitialized_default_construct_n(_First, n);
	}

	template<typename _Iter, typename _Diff>
	WJR_CONSTEXPR20 _Iter operator()(_Iter _First, _Diff n, value_construct_tag) const {
		return wjr::uninitialized_value_construct_n(_First, n);
	}

	template<typename Alloc, typename _Iter, typename _Diff, typename _Val>
	WJR_CONSTEXPR20 _Iter operator()(Alloc& al, _Iter _First, _Diff n, const _Val& val) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter, _Val>) {
			return this->operator()(_First, n, val);
		}
		else {
			for (; n > 0; (void)++_First, --n) {
				wjr::construct_at(al, _First, val);
			}
		}
	}
};

constexpr uninitialized_fill_n_fn uninitialized_fill_n;

struct uninitialized_move_fn {
	template<typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(_Iter1 _First, _Iter1 _Last, _Iter2 _Dest) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_copy_v<_Iter1, std::move_iterator<_Iter1>>) {
				const auto n = std::distance(_First, _Last);
				if (is_unlikely(n == 0)) { return _Dest; }
				if constexpr (!wjr::is_reverse_iterator_v<_Iter1>) {
					const auto first1 = wjr::get_address(_First);
					const auto first2 = wjr::get_address(_Dest);

					algo::construct_memmove(first2, first1, n);
				}
				else {
					const auto first1 = wjr::get_address(_Last - 1);
					const auto _Last2 = _Dest + n;
					const auto first2 = wjr::get_address(_Last2 - 1);

					algo::construct_memmove(first2, first1, n);
				}
				return _Dest + n;
			}
		}
		return std::uninitialized_move(_First, _Last, _Dest);
	}

	template<typename Alloc, typename _Iter1, typename _Iter2>
	WJR_CONSTEXPR20 _Iter2 operator()(Alloc& al, _Iter1 _First, _Iter1 _Last, _Iter2 _Dest) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter1, decltype(std::move(*_First))>) {
			return this->operator()(_First, _Last, _Dest);
		}
		else {
			for (; _First != _Last; ++_Dest, (void)++_First) {
				wjr::construct_at(al, _Dest, std::move(*_First));
			}
			return _Dest;
		}
	}
};

constexpr uninitialized_move_fn uninitialized_move;

struct uninitialized_move_n_fn {
	template<typename _Iter1, typename _Diff, typename _Iter2>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(_Iter1 _First, _Diff n, _Iter2 _Dest) const {
		if (!wjr::is_constant_evaluated()) {
			if constexpr (__has_fast_uninitialized_copy_v<_Iter1, std::move_iterator<_Iter1>>) {
				if (n <= 0) return std::make_pair(_First, _Dest);
				wjr::uninitialized_move(_First, _First + n, _Dest);
				return std::make_pair(_First + n, _Dest + n);
			}
		}
		return std::uninitialized_move_n(_First, n, _Dest);
	}

	template<typename Alloc, typename _Iter1, typename _Diff, typename _Iter2>
	WJR_CONSTEXPR20 std::pair<_Iter1, _Iter2> operator()(
		Alloc& al, _Iter1 _First, _Diff n, _Iter2 _Dest) const {
		if constexpr (is_default_allocator_construct_v<Alloc, _Iter1, decltype(std::move(*_First))>) {
			return this->operator()(_First, n, _Dest);
		}
		else {
			for (; n > 0; ++_First, (void)++_Dest, --n) {
				wjr::construct_at(al, _Dest, std::move(*_First));
			}
			return std::make_pair(_First, _Dest);
		}
	}
};

constexpr uninitialized_move_n_fn uninitialized_move_n;

template<typename Alloc>
class temporary_allocator_value {
public:
	using value_type = alloc_value_t<Alloc>;
	using traits = std::allocator_traits<Alloc>;

	template<typename...Args>
	constexpr explicit temporary_allocator_value(Alloc& al, Args&&...args) noexcept
		: al(al) {
		traits::construct(al, get_ptr(), std::forward<Args>(args)...);
	}

	temporary_allocator_value(const temporary_allocator_value&) = delete;
	temporary_allocator_value& operator=(const temporary_allocator_value&) = delete;

	~temporary_allocator_value() {
		wjr::destroy_at(al, get_ptr());
	}

	constexpr value_type* get_ptr() {
		return reinterpret_cast<value_type*>(std::addressof(vl));
	}

	constexpr const value_type* get_ptr() const {
		return reinterpret_cast<const value_type*>(std::addressof(vl));
	}

	constexpr value_type& value() {
		return *get_ptr();
	}

	constexpr const value_type& value() const {
		return *get_ptr();
	}

private:

	Alloc& al;
	std::aligned_storage_t<sizeof(value_type), alignof(value_type)> vl;
};

_WJR_END

#endif


_WJR_BEGIN

/*
* vector_data ->
* 1.vector_data()
* 2.vector_data(_Al&al, const size_t _Newsize, const size_t _Newcapacity)
* 4.vector_data(const vector_data&) = delete
* 5.vector_data(vector_data&&) = delete
* 6.static void copyConstruct(_Al& al, const vector_data& _Src, vector_data& _Dest)
* 7.static void moveConstruct(_Al& al, vector_data&& _Src, vector_data& _Dest)
* 8.static void Swap(_Al& al, vector_data& _Left, vector_data& _Right) [noexcept] [optional]
* 9.static void Deallocate(_Al& al, vector_data& _Data)
* 10.static size_t getGrowthCapacity(const size_t _Oldcapacity, const size_t _Newsize) [optinal]
* 11.static void shrinkToFit(_Al&al, vector_data& _Data) [optional]
* 12.size_t size() const;
* 13.size_t capacity() const;
* 14.[const] _Ty* data() [const]
* 15.const _Ty* cdata() const
* 16.void set_size(const size_type);
* 17.void inc_size(const difference_type);
*/

// support small-size-optimize
// don't support copy-on-write yet

template<typename T, typename Alloc>
struct vector_data {
	using _Alty = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;
	using _Alty_traits = std::allocator_traits<_Alty>;
	using value_type = T;
	using pointer = typename _Alty_traits::pointer;
	using const_pointer = typename _Alty_traits::const_pointer;
	using size_type = typename _Alty_traits::size_type;
	using difference_type = typename _Alty_traits::difference_type;

	WJR_INTRINSIC_CONSTEXPR20 vector_data() = default;
	vector_data(const vector_data&) = delete;
	vector_data& operator=(const vector_data&) = delete;
	~vector_data() = default;

	WJR_CONSTEXPR20 vector_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity,
		extend_tag)
		: _Myfirst(_Alty_traits::allocate(al, _Newcapacity)),
		_Mylast(_Myfirst + _Newsize),
		_Myend(_Myfirst + _Newcapacity) {
	}

	WJR_CONSTEXPR20 vector_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity)
		: _Myfirst(_Alty_traits::allocate(al, _Newcapacity)),
		_Mylast(_Myfirst + _Newsize),
		_Myend(_Myfirst + _Newcapacity) {
	}

	WJR_CONSTEXPR20 static void copyConstruct(_Alty& al, const vector_data& _Src, vector_data& _Dest) {
		{
			vector_data data(al, _Src.size(), _Src.size(), extend_tag{});
			_Dest._Myfirst = data._Myfirst;
			_Dest._Mylast = data._Mylast;
			_Dest._Myend = data._Myend;
		}
		wjr::uninitialized_copy(al, _Src._Myfirst, _Src._Mylast, _Dest._Myfirst);
	}

	WJR_INTRINSIC_CONSTEXPR20 static void moveConstruct(_Alty& al, vector_data&& _Src, vector_data& _Dest) noexcept {
		_Dest._Myfirst = _Src._Myfirst;
		_Dest._Mylast = _Src._Mylast;
		_Dest._Myend = _Src._Myend;
		_Src._Myfirst = _Src._Mylast = _Src._Myend = nullptr;
	}

	WJR_CONSTEXPR20 static void Deallocate(_Alty& al, vector_data& _Data) {
		_Alty_traits::deallocate(al, _Data._Myfirst, _Data.capacity());
		_Data._Myfirst = _Data._Mylast = _Data._Myend = nullptr;
	}

	WJR_CONSTEXPR20 static void shrinkToFit(_Alty& al, vector_data& _Data) noexcept {
		if (_Data._Mylast != _Data._Myend) {
			auto _Olddata = _Data._Myfirst;
			const auto _Oldsize = _Data.size();
			if (_Oldsize == 0) {
				Deallocate(al, _Data);
			}
			else {
				vector_data _Newdata(al, _Oldsize, _Oldsize);
				wjr::uninitialized_move_n(al, _Data.data(), _Oldsize, _Newdata.data());
				wjr::destroy_n(al, _Olddata, _Oldsize);
				Deallocate(al, _Data);
				moveConstruct(al, std::move(_Newdata), _Data);
			}
		}
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type size() const noexcept {
		return static_cast<size_type>(_Mylast - _Myfirst);
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type capacity() const noexcept {
		return static_cast<size_type>(_Myend - _Myfirst);
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer data() noexcept {
		return _Myfirst;
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer data() const noexcept {
		return _Myfirst;
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer lastPtr() noexcept {
		return _Mylast;
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer lastPtr() const noexcept {
		return _Mylast;
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer endPtr() noexcept {
		return _Myend;
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer endPtr() const noexcept {
		return _Myend;
	}

	WJR_INTRINSIC_CONSTEXPR20 void set_size(const size_type _Size) noexcept {
		_Mylast = _Myfirst + _Size;
	}

	WJR_INTRINSIC_CONSTEXPR20 void inc_size(const difference_type _Size) noexcept {
		_Mylast += _Size;
	}

	pointer _Myfirst = nullptr;
	pointer _Mylast = nullptr;
	pointer _Myend = nullptr;
};

template<typename T, typename Alloc, size_t N>
struct vector_static_data {
	using _Alty = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;
	using _Alty_traits = std::allocator_traits<_Alty>;
	using value_type = T;
	using pointer = typename _Alty_traits::pointer;
	using const_pointer = typename _Alty_traits::const_pointer;
	using size_type = typename _Alty_traits::size_type;
	using difference_type = typename _Alty_traits::difference_type;

	static_assert(N > 0, "N must be greater than 0");

	constexpr static size_t _MaxAlignment = std::max(alignof(T), alignof(size_type));
	constexpr static size_t _MaxMemroy = (sizeof(T) * N + _MaxAlignment - 1) & (~(_MaxAlignment - 1));
	constexpr static size_t _MaxCapacity = _MaxMemroy / sizeof(T);
	static_assert(_MaxCapacity >= N, "");

	vector_static_data() {}
	vector_static_data(const vector_static_data&) = delete;
	vector_static_data& operator=(const vector_static_data&) = delete;
	~vector_static_data() = default;

	WJR_CONSTEXPR20 static void _lengthError(const size_type _Newcapacity) {
		std::string str = "vector_static_data is too small to hold the requested data";
		str += "\n old capacity = " + std::to_string(_MaxCapacity);
		str += "\n allocate new capacity = " + std::to_string(_Newcapacity);
		throw std::length_error(str);
		unreachable();
	}

	WJR_CONSTEXPR20 vector_static_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity,
		extend_tag) {
		_lengthError(_Newcapacity);
	}

	WJR_CONSTEXPR20 vector_static_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity) : _M_size(_Newsize) {
		if (_Newcapacity > _MaxCapacity) {
			_lengthError(_Newcapacity);
		}
	}

	WJR_CONSTEXPR20 static void copyConstruct(_Alty& al, const vector_static_data& _Src, vector_static_data& _Dest) {
		wjr::uninitialized_copy_n(al, _Src.data(), _Src.size(), _Dest.data());
		_Dest.set_size(_Src.size());
	}

	WJR_CONSTEXPR20 static void moveConstruct(_Alty& al, vector_static_data&& _Src, vector_static_data& _Dest) {
		auto n = _Src.size();
		if (n != 0) {
			wjr::uninitialized_move_n(al, _Src.data(), n, _Dest.data());
			wjr::destroy_n(al, _Src.data(), n);
			_Src.set_size(0);
			_Dest.set_size(n);
		}
	}

	WJR_INTRINSIC_CONSTEXPR20 static void Deallocate(_Alty& al, vector_static_data& _Data) noexcept {
		_Data.set_size(0);
	}

	WJR_INTRINSIC_CONSTEXPR20 static void shrinkToFit(_Alty& al, vector_static_data& _Data) {
		// do nothing
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type size() const noexcept {
		return _M_size;
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type capacity() const noexcept {
		return _MaxCapacity;
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer data() noexcept {
		return reinterpret_cast<pointer>(_M_storage);
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer data() const noexcept {
		return reinterpret_cast<const_pointer>(_M_storage);
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer lastPtr() noexcept {
		return data() + size();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer lastPtr() const noexcept {
		return data() + size();
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer endPtr() noexcept {
		return data() + capacity();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer endPtr() const noexcept {
		return data() + capacity();
	}

	WJR_INTRINSIC_CONSTEXPR20 void set_size(const size_type _Size) noexcept {
		_M_size = _Size;
	}

	WJR_INTRINSIC_CONSTEXPR20 void inc_size(const difference_type _Size) noexcept {
		_M_size += _Size;
	}

	size_type _M_size = 0;
	alignas(_MaxAlignment) uint8_t _M_storage[_MaxMemroy];
};


template<typename T, typename Alloc, size_t N>
struct vector_sso_data {
	using _Alty = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;
	using _Alty_traits = std::allocator_traits<_Alty>;
	using value_type = T;
	using pointer = typename _Alty_traits::pointer;
	using const_pointer = typename _Alty_traits::const_pointer;
	using size_type = typename _Alty_traits::size_type;
	using difference_type = typename _Alty_traits::difference_type;

	static_assert(N > 0, "N must be greater than 0");

	constexpr static size_t _MaxAlignment = std::max(alignof(T),
		std::max(alignof(size_type), alignof(pointer)));
	constexpr static size_t _MaxMemroy = std::max(
		(sizeof(T) * N + _MaxAlignment - 1) & (~(_MaxAlignment - 1)),
		sizeof(size_type));
	constexpr static size_t _MaxCapacity = _MaxMemroy / sizeof(T);
	static_assert(_MaxCapacity >= N, "");

	WJR_INTRINSIC_CONSTEXPR20 vector_sso_data() {}
	vector_sso_data(const vector_sso_data&) = delete;
	vector_sso_data& operator=(const vector_sso_data&) = delete;
	~vector_sso_data() = default;

	WJR_CONSTEXPR20 vector_sso_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity,
		extend_tag)
		: _M_ptr(_Alty_traits::allocate(al, _Newcapacity)),
		_M_size(_Newsize),
		_M_capacity(_Newcapacity) {
		wjr::assume(_Newcapacity > _MaxCapacity);
	}

	WJR_CONSTEXPR20 vector_sso_data(
		_Alty& al,
		const size_type _Newsize,
		const size_type _Newcapacity)
		: _M_size(_Newsize) {
		if (_Newcapacity > _MaxCapacity) {
			_M_ptr = _Alty_traits::allocate(al, _Newcapacity);
			_M_capacity = _Newcapacity;
		}
	}

	WJR_CONSTEXPR20 static void copyConstruct(_Alty& al, const vector_sso_data& _Src, vector_sso_data& _Dest) {
		const auto _Size = _Src._M_size;
		if (!_Src.is_small()) {
			vector_sso_data data(al, _Size, _Size, extend_tag{});
			_Dest._M_ptr = data._M_ptr;
			_Dest._M_capacity = data._M_capacity;
		}
		_Dest._M_size = _Size;
		wjr::uninitialized_copy_n(al, _Src.data(), _Src.size(), _Dest.data());
	}

	WJR_INTRINSIC_CONSTEXPR20 static void moveConstruct(_Alty& al, vector_sso_data&& _Src, vector_sso_data& _Dest) {
		wjr::assume(_Dest.is_small());
		const auto _Size = _Src._M_size;
		if (!_Src.is_small()) {
			_Dest._M_ptr = _Src._M_ptr;
			_Dest._M_capacity = _Src._M_capacity;
		}
		else {
			wjr::assume(_Size <= _MaxCapacity);
			wjr::uninitialized_move_n(al, _Src.data(), _Size, _Dest.data());
			wjr::destroy_n(al, _Src.data(), _Size);
		}

		_Dest._M_size = _Size;

		_Src.reset_ptr();
		_Src._M_size = 0;
	}

	WJR_INTRINSIC_CONSTEXPR20 static void Deallocate(_Alty& al, vector_sso_data& _Data) noexcept {
		if (!_Data.is_small()) {
			_Alty_traits::deallocate(al, _Data.data(), _Data.capacity());
		}
		_Data.reset_ptr();
		_Data._M_size = 0;
	}

	WJR_INTRINSIC_CONSTEXPR20 static void shrinkToFit(_Alty& al, vector_sso_data& _Data) {
		if (!_Data.is_small()) {
			const auto _Oldsize = _Data.size();
			const auto _Oldcapacity = _Data.capacity();
			if (_Oldsize != _Data.capacity()) {
				if (_Oldsize <= _MaxCapacity) {
					wjr::uninitialized_move_n(al, _Data.data(), _Oldsize, reinterpret_cast<pointer>(_Data._M_storage));
					wjr::destroy_n(al, _Data.data(), _Oldsize);
					_Alty_traits::deallocate(al, _Data.data(), _Oldcapacity);
					_Data.reset_ptr();
				}
				else {
					auto _Newdata = _Alty_traits::allocate(al, _Oldsize);
					wjr::uninitialized_move_n(al, _Data.data(), _Oldsize, _Newdata);
					wjr::destroy_n(al, _Data.data(), _Oldsize);
					_Alty_traits::deallocate(al, _Data.data(), _Oldcapacity);
					_Data._M_ptr = _Newdata;
					_Data._M_capacity = _Oldsize;
				}
				_Data._M_size = _Oldsize;
			}
		}
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type size() const noexcept {
		return _M_size;
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type capacity() const noexcept {
		return is_small() ? _MaxCapacity : _M_capacity;
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer data() noexcept {
		return _M_ptr;
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer data() const noexcept {
		return _M_ptr;
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer lastPtr() noexcept {
		return data() + size();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer lastPtr() const noexcept {
		return data() + size();
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer endPtr() noexcept {
		return data() + capacity();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer endPtr() const noexcept {
		return data() + capacity();
	}

	WJR_INTRINSIC_CONSTEXPR20 void set_size(const size_type _Size) noexcept {
		_M_size = _Size;
	}

	WJR_INTRINSIC_CONSTEXPR20 void inc_size(const difference_type _Size) noexcept {
		_M_size += _Size;
	}

	WJR_INTRINSIC_CONSTEXPR20 bool is_small() const noexcept {
		const bool f = static_cast<const void*>(_M_ptr) == static_cast<const void*>(_M_storage);
		return f;
	}

	WJR_INTRINSIC_CONSTEXPR20 void reset_ptr() noexcept {
		_M_ptr = reinterpret_cast<pointer>(_M_storage);
	}

	pointer _M_ptr = reinterpret_cast<pointer>(_M_storage);
	size_type _M_size = 0;
	union {
		alignas(_MaxAlignment) uint8_t _M_storage[_MaxMemroy];
		alignas(_MaxAlignment) size_type _M_capacity;
	};
};


namespace _Vector_helper {
	WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(Swap, Swap);
	WJR_REGISTER_HAS_STATIC_MEMBER_FUNCTION(getGrowthCapacity, getGrowthCapacity);
}

template<typename T, typename Alloc = std::allocator<T>, typename Data = vector_data<T, Alloc>>
class vector {

	using _Alty = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;
	using _Alty_traits = std::allocator_traits<_Alty>;

	static_assert(std::is_same_v<typename _Alty_traits::value_type, T>,
		"Alloc::value_type must be the same as T");

public:

	using value_type = T;
	using allocator_type = _Alty;
	using size_type = typename _Alty_traits::size_type;
	using difference_type = typename _Alty_traits::difference_type;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename _Alty_traits::pointer;
	using const_pointer = typename _Alty_traits::const_pointer;
	using iterator = pointer;
	using const_iterator = const_pointer;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	using data_type = Data;

	WJR_CONSTEXPR20 vector()
		noexcept(std::is_nothrow_default_constructible_v<_Alty>
			&& std::is_nothrow_default_constructible_v<data_type>) : _Myval() {}

	WJR_CONSTEXPR20 explicit vector(const allocator_type& al)
		noexcept(std::is_nothrow_constructible_v<_Alty, const allocator_type&>
			&& std::is_nothrow_default_constructible_v<data_type>)
		: _Myval(std::piecewise_construct_t{},
			std::forward_as_tuple(al),
			std::forward_as_tuple()) {}

	WJR_CONSTEXPR20 explicit vector(const size_type _Count, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_construct_n(_Count, value_construct_tag{});
	}

	WJR_CONSTEXPR20 vector(size_type _Count, const value_type& _Val, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_construct_n(_Count, _Val);
	}

private:
	constexpr static bool _IsNoThrowCopyConstruct =
		noexcept(data_type::copyConstruct(std::declval<_Alty&>(),
			std::declval<const data_type&>(), std::declval<data_type&>()));
	constexpr static bool _IsNoThrowMoveConstruct =
		noexcept(data_type::moveConstruct(std::declval<_Alty&>(),
			std::declval<data_type&&>(), std::declval<data_type&>()));
	struct __vector_copy_tag {};
public:

	template<typename _Alloc>
	WJR_CONSTEXPR20 vector(const vector& other, _Alloc&& al, __vector_copy_tag)
		noexcept(_IsNoThrowCopyConstruct
			&& std::is_nothrow_constructible_v<_Alty, _Alloc&&>)
		: _Myval(std::piecewise_construct_t{},
			std::forward_as_tuple(std::forward<_Alloc>(al)),
			std::forward_as_tuple()) {
		copyConstruct(getAllocator(), other.getData(), getData());
	}

	WJR_CONSTEXPR20 vector(const vector& other)
		: vector(other, _Alty_traits::select_on_container_copy_construction(other.getAllocator()),
			__vector_copy_tag{}) {}

	WJR_CONSTEXPR20 vector(const vector& other, const allocator_type& al)
		: vector(other, al, __vector_copy_tag{}) {}

	WJR_CONSTEXPR20 vector(vector&& other)
		noexcept(_IsNoThrowMoveConstruct
			&& std::is_nothrow_move_constructible_v<_Alty>)
		: _Myval(std::piecewise_construct_t{},
			std::forward_as_tuple(std::move(other.getAllocator())),
			std::forward_as_tuple()) {
		moveConstruct(getAllocator(), std::move(other.getData()), getData());
	}

private:
	WJR_CONSTEXPR20 vector(vector&& other, const allocator_type& al, std::true_type) noexcept
		: _Myval(std::piecewise_construct_t{},
			std::forward_as_tuple(al),
			std::forward_as_tuple()) {
		moveConstruct(getAllocator(), std::move(other.getData()), getData());
	}
	WJR_CONSTEXPR20 vector(vector&& other, const allocator_type& _Al, std::false_type)
		: _Myval(std::piecewise_construct_t{},
			std::forward_as_tuple(_Al),
			std::forward_as_tuple()) {
		auto& al = getAllocator();
		if (al == other.getAllocator()) {
			moveConstruct(al, std::move(other.getData()), getData());
		}
		else {
			const auto _Size = other.size();
			if (_Size != 0) {
				const auto _Oldcapacity = capacity();
				if (_Oldcapacity < _Size) {
					data_type _Data(al, 0, _Size, extend_tag{});
					moveConstruct(al, std::move(_Data), getData());
				}
				set_size(_Size);
				wjr::uninitialized_move_n(al, other.data(), _Size, data());
			}
		}
	}
public:
	WJR_CONSTEXPR20 vector(vector&& other, const allocator_type& al)
		noexcept(noexcept(vector(std::declval<vector&&>(),
			std::declval<const allocator_type&>(), std::declval<typename _Alty_traits::is_always_equal>())))
		: vector(std::move(other), al, typename _Alty_traits::is_always_equal{}) {}

	template<typename _Iter, std::enable_if_t<wjr::is_iterator_v<_Iter>, int> = 0>
	WJR_CONSTEXPR20 vector(_Iter _First, _Iter _Last, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_range_init(_First, _Last, typename std::iterator_traits<_Iter>::iterator_category());
	}

	WJR_CONSTEXPR20 vector(std::initializer_list<value_type> _Ilist, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_range_init(_Ilist.begin(), _Ilist.end(), std::random_access_iterator_tag());
	}

	WJR_CONSTEXPR20 ~vector() noexcept {
		tidy();
	}

	WJR_CONSTEXPR20 vector& operator=(const vector& other) {

		if (is_likely(this != std::addressof(other))) {
			auto& al = getAllocator();
			auto& other_al = other.getAllocator();

			if constexpr (std::conjunction_v<typename _Alty_traits::propagate_on_container_copy_assignment
				, std::negation<typename _Alty_traits::is_always_equal>>) {
				if (al != other_al) {
					tidy();
				}
			}

			if constexpr (_Alty_traits::propagate_on_container_copy_assignment::value) {
				al = other_al;
			}

			assign(other.begin(), other.end());
		}

		return *this;
	}

	WJR_CONSTEXPR20 vector& operator=(vector&& other)
		noexcept(_Alty_traits::propagate_on_container_move_assignment::value
			|| _Alty_traits::is_always_equal::value) {

		using type = std::disjunction<typename _Alty_traits::propagate_on_container_move_assignment,
			typename _Alty_traits::is_always_equal>;

		if (is_likely(this != std::addressof(other))) {
			_M_move_assign(std::move(other), type{});
		}

		return *this;
	}

	WJR_CONSTEXPR20 vector& operator=(std::initializer_list<value_type> _Ilist) {
		_M_assign_aux(_Ilist.begin(), _Ilist.end(), std::random_access_iterator_tag());
		return *this;
	}

	WJR_CONSTEXPR20 vector& assign(size_type _Count, const value_type& _Val) {
		_M_fill_assign(_Count, _Val);
		return *this;
	}

	template<typename iter, std::enable_if_t<is_iterator_v<iter>, int> = 0>
	WJR_CONSTEXPR20 vector& assign(iter _First, iter _Last) {
		_M_assign_aux(_First, _Last, typename std::iterator_traits<iter>::iterator_category());
		return *this;
	}

	WJR_CONSTEXPR20 vector& assign(std::initializer_list<value_type> _Ilist) {
		_M_assign_aux(_Ilist.begin(), _Ilist.end(), std::random_access_iterator_tag());
		return *this;
	}

	WJR_INTRINSIC_CONSTEXPR20 iterator begin() noexcept {
		return data();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_iterator begin() const noexcept {
		return data();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_iterator cbegin() const noexcept {
		return data();
	}

	WJR_INTRINSIC_CONSTEXPR20 iterator end() noexcept {
		return lastPtr();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_iterator end() const noexcept {
		return lastPtr();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_iterator cend() const noexcept {
		return lastPtr();
	}

	WJR_INTRINSIC_CONSTEXPR20 reverse_iterator rbegin() noexcept {
		return reverse_iterator(end());
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reverse_iterator rbegin() const noexcept {
		return const_reverse_iterator(end());
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(cend());
	}

	WJR_INTRINSIC_CONSTEXPR20 reverse_iterator rend() noexcept {
		return reverse_iterator(begin());
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reverse_iterator rend() const noexcept {
		return const_reverse_iterator(begin());
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator(cbegin());
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type size() const noexcept {
		return getData().size();
	}

	WJR_CONSTEXPR20 void resize(const size_type _Newsize) {
		_M_resize(_Newsize, value_construct_tag{});
	}

	WJR_CONSTEXPR20 void resize(const size_type _Newsize, const value_type& _Val) {
		_M_resize(_Newsize, _Val);
	}

	WJR_CONSTEXPR20 void shrink_to_fit() {
		shrinkToFit(getAllocator(), getData());
	}

	WJR_INTRINSIC_CONSTEXPR20 size_type capacity() const noexcept {
		return getData().capacity();
	}

	WJR_INTRINSIC_CONSTEXPR20 bool empty() const noexcept {
		return size() == 0;
	}

	WJR_CONSTEXPR20 void reserve(size_type n) {
		const auto _Oldcapacity = capacity();
		if (_Oldcapacity < n) {
			auto& al = getAllocator();

			const auto _Oldsize = size();
			const auto _Newcapacity = getGrowthCapacity(_Oldcapacity, n);

			data_type _Newdata(al, _Oldsize, _Newcapacity, extend_tag{});
			wjr::uninitialized_move_n(al, data(), _Oldsize, _Newdata.data());

			tidy();
			moveConstruct(al, std::move(_Newdata), getData());
		}
	}

	WJR_INTRINSIC_CONSTEXPR20 reference operator[](size_type _Pos) noexcept {
		return *(data() + _Pos);
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reference operator[](size_type _Pos) const noexcept {
		return *(data() + _Pos);
	}

	WJR_INTRINSIC_CONSTEXPR20 reference at(size_type _Pos) {
		if (_Pos >= size()) {
			throw (std::out_of_range("wjr::vector::at"));
		}
		return (*this)[_Pos];
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reference at(size_type _Pos) const {
		if (_Pos >= size()) {
			throw (std::out_of_range("wjr::vector::at"));
		}
		return (*this)[_Pos];
	}

	WJR_INTRINSIC_CONSTEXPR20 reference front() noexcept {
		return *data();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reference front() const noexcept {
		return *data();
	}

	WJR_INTRINSIC_CONSTEXPR20 reference back() noexcept {
		return *(lastPtr() - 1);
	}

	WJR_INTRINSIC_CONSTEXPR20 const_reference back() const noexcept {
		return *(lastPtr() - 1);
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer data() noexcept {
		return getData().data();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer data() const noexcept {
		return getData().data();
	}

	WJR_INTRINSIC_CONSTEXPR20 const_pointer cdata() const noexcept {
		return getData().data();
	}

	template<typename...Args>
	WJR_INLINE_CONSTEXPR20 reference emplace_back(Args&&... args) {
		auto& al = getAllocator();
		const auto _Myfirst = data();
		const auto _Mylast = lastPtr();
		const auto _Myend = endPtr();
		if (_Mylast != _Myend) {
			wjr::construct_at(al, _Mylast, std::forward<Args>(args)...);
			inc_size(1);
		}
		else {
			_M_realloc_insert_at_end(std::forward<Args>(args)...);
		}
		return back();
	}

	WJR_INLINE_CONSTEXPR20 void push_back(const value_type& _Val) {
		emplace_back(_Val);
	}

	WJR_INLINE_CONSTEXPR20 void push_back(value_type&& _Val) {
		emplace_back(std::move(_Val));
	}

	WJR_INTRINSIC_CONSTEXPR20 void pop_back() noexcept {
		inc_size(-1);
		const pointer _Mylast = lastPtr();
		wjr::destroy_at(getAllocator(), _Mylast);
	}

	template<typename...Args>
	WJR_INLINE_CONSTEXPR20 iterator emplace(const_iterator _Where, Args&&... args) {
		return _M_emplace_aux(_Where, std::forward<Args>(args)...);
	}

	WJR_INLINE_CONSTEXPR20 iterator insert(const_iterator _Where, const value_type& _Val) {
		return emplace(_Where, _Val);
	}

	WJR_INLINE_CONSTEXPR20 iterator insert(const_iterator _Where, value_type&& _Val) {
		return emplace(_Where, std::move(_Val));
	}

	WJR_CONSTEXPR20 iterator insert(const_iterator _Where, std::initializer_list<value_type> _Ilist) {
		const auto __old_pos = _Where - cbegin();
		_M_range_insert(begin() + __old_pos, _Ilist.begin(), _Ilist.end(), std::random_access_iterator_tag());
		return begin() + __old_pos;
	}

	WJR_CONSTEXPR20 iterator insert(const_iterator _Where, size_type _Count, const value_type& _Val) {
		const auto __old_pos = _Where - cbegin();
		_M_fill_insert(begin() + __old_pos, _Count, _Val);
		return begin() + __old_pos;
	}

	template<typename iter, std::enable_if_t<is_iterator_v<iter>, int> = 0>
	WJR_CONSTEXPR20 iterator insert(const_iterator _Where, iter _First, iter _Last) {
		const auto __old_pos = _Where - cbegin();
		_M_range_insert(begin() + __old_pos, _First, _Last, typename std::iterator_traits<iter>::iterator_category());
		return begin() + __old_pos;
	}

	WJR_CONSTEXPR20 iterator erase(const_iterator _Where) {
		return _M_erase(begin() + (_Where - cbegin()));
	}

	WJR_CONSTEXPR20 iterator erase(const_iterator _First, const_iterator _Last) {
		const auto __beg = begin();
		const auto __cbeg = cbegin();
		return _M_erase(__beg + (_First - __cbeg), __beg + (_Last - __cbeg));
	}

	WJR_CONSTEXPR20 void swap(vector& _Right) noexcept {
		Swap(getAllocator(), getData(), _Right.getData());
		if constexpr (_Alty_traits::propagate_on_container_swap::value) {
			std::swap(getAllocator(), _Right.getAllocator());
		}
	}

	WJR_CONSTEXPR20 void clear() {
		_M_erase_at_end(data());
	}

	WJR_CONSTEXPR20 void tidy() noexcept {
		Tidy(getAllocator(), getData());
	}

	WJR_INTRINSIC_CONSTEXPR20 allocator_type& get_allocator() noexcept {
		return getAllocator();
	}
	WJR_INTRINSIC_CONSTEXPR20 const allocator_type& get_allocator() const noexcept {
		return getAllocator();
	}

	// unstandard functions

	WJR_CONSTEXPR20 static void copyConstruct(_Alty& al, const data_type& _Src, data_type& _Dest)
		noexcept(_IsNoThrowCopyConstruct) {
		data_type::copyConstruct(al, _Src, _Dest);
	}

	WJR_CONSTEXPR20 static void moveConstruct(_Alty& al, data_type&& _Src, data_type& _Dest)
		noexcept(_IsNoThrowMoveConstruct) {
		data_type::moveConstruct(al, std::move(_Src), _Dest);
	}

	template<typename _D = data_type, std::enable_if_t<
		_Vector_helper::has_static_member_function_Swap_v<_D, _Alty&, _D&, _D&>, int> = 0>
	WJR_CONSTEXPR20 static void Swap(_Alty& al, _D& _Left, _D& _Right)
		noexcept(noexcept(_D::Swap(al, _Left, _Right))) {
		return _D::Swap(al, _Left, _Right);
	}

	template<typename _D = Data, std::enable_if_t<
		!_Vector_helper::has_static_member_function_Swap_v<_D, _Alty&, _D&, _D&>, int> = 0>
	WJR_CONSTEXPR20 static void Swap(_Alty& al, _D& _Left, _D& _Right)
		noexcept(
			noexcept(moveConstruct(std::declval<_Alty&>(), std::declval<_D&&>(), std::declval<_D&>()))
			&& std::is_nothrow_default_constructible_v<_D>) {
		_D _Tmp;
		moveConstruct(al, std::move(_Left), _Tmp);
		moveConstruct(al, std::move(_Right), _Left);
		moveConstruct(al, std::move(_Tmp), _Right);
	}

	WJR_CONSTEXPR20 static void Destroy(_Alty& al, data_type& _Data) {
		wjr::destroy_n(al, _Data.data(), _Data.size());
	}

	WJR_CONSTEXPR20 static void Deallocate(_Alty& al, data_type& _Data)
		noexcept(noexcept(data_type::Deallocate(al, _Data))) {
		data_type::Deallocate(al, _Data);
		assume(_Data.size() == 0);
	}

	WJR_CONSTEXPR20 static void Tidy(_Alty& al, data_type& _Data) noexcept {
		assume(_Data.size() <= _Data.capacity());
		if (_Data.capacity() != 0) {
			Destroy(al, _Data);
			Deallocate(al, _Data);
		}
		assume(_Data.size() == 0);
	}

	template<typename _D = Data, std::enable_if_t<
		_Vector_helper::has_static_member_function_getGrowthCapacity_v<
		_D, const size_type, const size_type>, int> = 0>
	WJR_INTRINSIC_CONSTEXPR20 static size_type getGrowthCapacity(
		const size_type _Oldcapacity, const size_type _Newsize) noexcept {
		return Data::getGrowthCapacity(_Oldcapacity, _Newsize);
	}
	template<typename _D = Data, std::enable_if_t<
		!_Vector_helper::has_static_member_function_getGrowthCapacity_v<
		_D, const size_type, const size_type>, int> = 0>
	WJR_INTRINSIC_CONSTEXPR20 static size_type getGrowthCapacity(
		const size_type _Oldcapacity, const size_type _Newsize) noexcept {
		wjr::assume(_Newsize > _Oldcapacity);
		const auto _Newcapacity = _Oldcapacity + _Oldcapacity / 2;
		const auto _FixedCapacity = _Newcapacity < _Newsize ? _Newsize : _Newcapacity;
		const auto ret = _FixedCapacity < 32 ? ((_FixedCapacity + 3) & (-4)) :
			_FixedCapacity < 256 ? ((_FixedCapacity + 15) & (-16)) :
			((_FixedCapacity + 63) & (-64));
		wjr::assume(ret >= _Newsize);
		return ret;
	}

	WJR_CONSTEXPR20 static void shrinkToFit(_Alty& al, data_type& _Data) {
		data_type::shrinkToFit(al, _Data);
	}

	WJR_INTRINSIC_CONSTEXPR20 _Alty& getAllocator() noexcept {
		return _Myval.first();
	}
	WJR_INTRINSIC_CONSTEXPR20 const _Alty& getAllocator() const noexcept {
		return _Myval.first();
	}

	WJR_INTRINSIC_CONSTEXPR20 data_type& getData() noexcept {
		return _Myval.second();
	}
	WJR_INTRINSIC_CONSTEXPR20 const data_type& getData() const noexcept {
		return _Myval.second();
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer lastPtr() noexcept {
		return getData().lastPtr();
	}
	WJR_INTRINSIC_CONSTEXPR20 const_pointer lastPtr() const noexcept {
		return getData().lastPtr();
	}

	WJR_INTRINSIC_CONSTEXPR20 pointer endPtr() noexcept {
		return getData().endPtr();
	}
	WJR_INTRINSIC_CONSTEXPR20 const_pointer endPtr() const noexcept {
		return getData().endPtr();
	}

	// non-standard extension functions

	WJR_INTRINSIC_CONSTEXPR20 void set_size(const size_type _Size) noexcept {
		getData().set_size(_Size);
	}

	WJR_INTRINSIC_CONSTEXPR20 void inc_size(const difference_type _Size) noexcept {
		getData().inc_size(_Size);
	}

	WJR_CONSTEXPR20 vector(const size_type _Count, default_construct_tag, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_construct_n(_Count, default_construct_tag{});
	}

	WJR_CONSTEXPR20 vector(const size_type _Count, value_construct_tag, const allocator_type& al = allocator_type())
		: vector(al) {
		_M_construct_n(_Count, value_construct_tag{});
	}

	WJR_CONSTEXPR20 void resize(const size_type _Newsize, default_construct_tag) {
		_M_resize(_Newsize, default_construct_tag{});
	}

	WJR_CONSTEXPR20 void resize(const size_type _Newsize, value_construct_tag) {
		_M_resize(_Newsize, value_construct_tag{});
	}

	WJR_CONSTEXPR20 void append(size_t n, const T& val) {
		_M_append(n, val);
	}

	WJR_CONSTEXPR20 void append(size_t n, default_construct_tag) {
		_M_append(n, default_construct_tag{});
	}

	WJR_CONSTEXPR20 void append(size_t n, value_construct_tag) {
		_M_append(n, value_construct_tag{});
	}

	template<typename _Iter, std::enable_if_t<is_iterator_v<_Iter>, int> = 0>
	WJR_CONSTEXPR20 void append(_Iter _First, _Iter _Last) {
		_M_range_append(_First, _Last, typename std::iterator_traits<_Iter>::iterator_category());
	}

	WJR_CONSTEXPR20 void chop(size_t n) {
		_M_erase_at_end(end() - n);
	}

private:

	template<typename...Args, std::enable_if_t<is_any_index_of_v<sizeof...(Args), 1, 2>, int> = 0>
	WJR_CONSTEXPR20 void _M_construct_n(const size_type _Count, Args&&... args) {
		if (_Count != 0) {
			auto& al = getAllocator();
			const auto _Oldcapacity = capacity();
			if (_Oldcapacity < _Count) {
				data_type _Newdata(al, 0, _Count, extend_tag{});
				moveConstruct(al, std::move(_Newdata), getData());
			}
			set_size(_Count);
			const pointer _Ptr = data();
			if constexpr (sizeof...(Args) == 1) {
				wjr::uninitialized_fill_n(al, _Ptr, _Count, std::forward<Args>(args)...);
			}
			else if constexpr (sizeof...(Args) == 2) {
				wjr::uninitialized_copy(al, std::forward<Args>(args)..., _Ptr);
			}
		}
	}

	WJR_CONSTEXPR20 void _M_construct_reserve(const size_type _Count) {
		if (_Count != 0) {
			auto& al = getAllocator();
			const auto _Oldcapacity = capacity();
			if (_Oldcapacity < _Count) {
				data_type _Newdata(al, 0, _Count, extend_tag{});
				moveConstruct(al, std::move(_Newdata), getData());
			}
			set_size(_Count);
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_init(iter _First, iter _Last, std::input_iterator_tag) {
		for (; _First != _Last; ++_First) {
			emplace_back(*_First);
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_init(iter _First, iter _Last, std::forward_iterator_tag) {
		const auto _Count = static_cast<size_type>(std::distance(_First, _Last));
		_M_construct_n(_Count, _First, _Last);
	}

	WJR_CONSTEXPR20 void _M_erase_at_end(const pointer _Where) noexcept {
		const auto _Myfirst = data();
		const pointer _Mylast = lastPtr();
		wjr::destroy(getAllocator(), _Where, _Mylast);
		const auto __new_size = static_cast<size_type>(_Where - _Myfirst);
		set_size(__new_size);
	}

	WJR_CONSTEXPR20 iterator _M_erase(iterator _Where) noexcept {
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();
		if (_Where + 1 != _Mylast) {
			wjr::move(_Where + 1, _Mylast, _Where);
		}
		wjr::destroy_at(getAllocator(), _Mylast - 1);
		inc_size(-1);
		return _Where;
	}

	WJR_CONSTEXPR20 iterator _M_erase(iterator _First, iterator _Last) noexcept {
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();
		if (_First != _Last) {
			if (_Last != _Mylast) {
				wjr::move(_Last, _Mylast, _First);
			}
			_M_erase_at_end(_Mylast - (_Last - _First));
		}
		return _First;
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_insert(iterator _Where, iter _First, iter _Last, std::input_iterator_tag) {
		if (_Where == end()) {
			_M_range_append(_First, _Last, std::input_iterator_tag{});
		}
		else if (_First != _Last) {
			vector _Tmp(_First, _Last, getAllocator());
			insert(_Where, _Tmp.begin(), _Tmp.end());
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_insert(iterator _Where, iter _First, iter _Last, std::forward_iterator_tag) {
		if (_First != _Last) {
			auto& al = getAllocator();
			const pointer _Myfirst = data();
			const pointer _Mylast = lastPtr();
			const pointer _Myend = endPtr();

			const auto n = static_cast<size_type>(std::distance(_First, _Last));
			const auto __rest = static_cast<size_type>(_Myend - _Mylast);

			if (__rest >= n) {
				const auto __elements_after = static_cast<size_type>(_Mylast - _Where);
				auto __old_last = _Mylast;
				if (__elements_after > n) {
					wjr::uninitialized_move(al, _Mylast - n, _Mylast, _Mylast);
					wjr::move_backward(_Where, __old_last - n, __old_last);
					wjr::copy(_First, _Last, _Where);
				}
				else {
					auto _Mid = _First;
					std::advance(_Mid, __elements_after);
					wjr::uninitialized_copy(al, _Mid, _Last, _Mylast);
					wjr::uninitialized_move(al, _Where, __old_last, _Mylast + n - __elements_after);
					wjr::copy(_First, _Mid, _Where);
				}
				inc_size(n);
			}
			else {
				const auto __old_size = static_cast<size_type>(_Mylast - _Myfirst);
				const auto __old_pos = static_cast<size_type>(_Where - _Myfirst);
				const auto _Newcapacity = getGrowthCapacity(capacity(), __old_size + n);
				data_type _Newdata(al, __old_size + n, _Newcapacity, extend_tag{});
				const pointer _Newfirst = _Newdata.data();

				wjr::uninitialized_copy(al, _First, _Last, _Newfirst + __old_pos);
				wjr::uninitialized_move(al, _Myfirst, _Where, _Newfirst);
				wjr::uninitialized_move(al, _Where, _Mylast, _Newfirst + __old_pos + n);

				tidy();
				moveConstruct(al, std::move(_Newdata), getData());
			}
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_append(iter _First, iter _Last, std::input_iterator_tag) {
		for (; _First != _Last; ++_First) {
			emplace_back(*_First);
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_range_append(iter _First, iter _Last, std::forward_iterator_tag) {
		if (_First != _Last) {
			auto& al = getAllocator();
			const pointer _Myfirst = data();
			const pointer _Mylast = lastPtr();
			const pointer _Myend = endPtr();

			const auto n = static_cast<size_type>(std::distance(_First, _Last));
			const auto __rest = static_cast<size_type>(_Myend - _Mylast);

			if (__rest >= n) {
				wjr::uninitialized_copy(al, _First, _Last, _Mylast);
				inc_size(n);
			}
			else {
				const auto __old_size = static_cast<size_type>(_Mylast - _Myfirst);
				const auto _Newcapacity = getGrowthCapacity(capacity(), __old_size + n);

				data_type _Newdata(al, __old_size + n, _Newcapacity, extend_tag{});
				const pointer _Newfirst = _Newdata.data();

				wjr::uninitialized_copy(al, _First, _Last, _Newfirst + __old_size);
				wjr::uninitialized_move(al, _Myfirst, _Mylast, _Newfirst);

				tidy();
				moveConstruct(al, std::move(_Newdata), getData());
			}
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_assign_aux(iter _First, iter _Last, std::input_iterator_tag) {
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();

		pointer cur = _Myfirst;

		for (; _First != _Last && cur != _Mylast; ++_First, ++cur) {
			*cur = *_First;
		}

		if (_First == _Last) {
			_M_erase_at_end(cur);
		}
		else {
			_M_range_append(_First, _Last, std::input_iterator_tag{});
		}
	}

	WJR_CONSTEXPR20 void _M_fill_assign(size_type _Count, const value_type& _Val) {
		auto& al = getAllocator();
		if (_Count > capacity()) {
			tidy();
			data_type _Newdata(al, _Count, _Count, extend_tag{});
			moveConstruct(al, std::move(_Newdata), getData());
			wjr::uninitialized_fill_n(al, data(), _Count, _Val);
			return;
		}
		if (_Count > size()) {
			wjr::fill(begin(), end(), _Val);
			wjr::uninitialized_fill_n(al, end(), _Count - size(), _Val);
			set_size(_Count);
		}
		else {
			_M_erase_at_end(wjr::fill_n(begin(), _Count, _Val));
		}
	}

	template<typename iter>
	WJR_CONSTEXPR20 void _M_assign_aux(iter _First, iter _Last, std::forward_iterator_tag) {
		auto _Count = static_cast<size_type>(std::distance(_First, _Last));
		auto& al = getAllocator();
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();

		if (_Count <= size()) {
			wjr::copy(_First, _Last, _Myfirst);
			_M_erase_at_end(_Myfirst + _Count);
		}
		else if (_Count <= capacity()) {
			auto _Mid = _First;
			std::advance(_Mid, size());
			wjr::copy(_First, _Mid, begin());
			wjr::uninitialized_copy(al, _Mid, _Last, _Mylast);
			set_size(_Count);
		}
		else {
			auto _Newcapacity = getGrowthCapacity(capacity(), _Count);
			data_type _Newdata(al, _Count, _Newcapacity, extend_tag{});
			const pointer _Newfirst = _Newdata.data();
			wjr::uninitialized_copy(al, _First, _Last, _Newfirst);

			tidy();
			moveConstruct(al, std::move(_Newdata), getData());
		}
	}

	WJR_CONSTEXPR20 void _M_move_assign(vector&& other, std::true_type) {
		auto& al = getAllocator();
		tidy();
		moveConstruct(al, std::move(other.getData()), getData());
		if constexpr (_Alty_traits::propagate_on_container_move_assignment::value) {
			al = std::move(other.getAllocator());
		}
	}

	WJR_CONSTEXPR20 void _M_move_assign(vector&& other, std::false_type) {
		if (getAllocator() == other.getAllocator()) {
			_M_move_assign(std::move(other), std::true_type{});
		}
		else {
			_M_assign_aux(
				std::make_move_iterator(other.begin()),
				std::make_move_iterator(other.end()),
				std::random_access_iterator_tag{});
			clear();
		}
	}

	template<typename...Args>
	WJR_CONSTEXPR20 void _M_realloc_insert(iterator _Where, Args&&...args) {
		auto& al = getAllocator();
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();

		const auto __old_pos = static_cast<size_type>(_Where - _Myfirst);
		const auto __old_size = static_cast<size_type>(_Mylast - _Myfirst);
		const auto __new_size = __old_size + 1;
		const auto _Newcapacity = getGrowthCapacity(__old_size, __new_size);

		data_type _Newdata(al, __new_size, _Newcapacity, extend_tag{});

		const pointer _Newfirst = _Newdata.data();
		const pointer _Newwhere = _Newfirst + __old_pos;

		wjr::construct_at(al, _Newwhere, std::forward<Args>(args)...);

		wjr::uninitialized_move(al, _Myfirst, _Where, _Newfirst);
		wjr::uninitialized_move(al, _Where, _Mylast, _Newwhere + 1);

		tidy();
		moveConstruct(al, std::move(_Newdata), getData());
	}

	template<typename...Args>
	WJR_CONSTEXPR20 void _M_realloc_insert_at_end(Args&&...args) {
		auto& al = getAllocator();
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();

		const auto __old_size = static_cast<size_type>(_Mylast - _Myfirst);
		const auto __new_size = __old_size + 1;
		const auto _Newcapacity = getGrowthCapacity(__old_size, __new_size);

		data_type _Newdata(al, __new_size, _Newcapacity, extend_tag{});
		const pointer _Newfirst = _Newdata.data();

		const pointer _Newwhere = _Newfirst + __old_size;
		wjr::construct_at(al, _Newwhere, std::forward<Args>(args)...);

		wjr::uninitialized_move_n(al, _Myfirst, __old_size, _Newfirst);

		tidy();
		moveConstruct(al, std::move(_Newdata), getData());
	}

	WJR_CONSTEXPR20 void _M_fill_insert(iterator _Where, size_type n, const value_type& _Val) {
		if (n == 0) {
			return;
		}

		auto& al = getAllocator();
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();
		const pointer _Myend = endPtr();

		const auto __rest = static_cast<size_type>(_Myend - _Mylast);

		if (__rest >= n) {
			temporary_allocator_value<Alloc> _Tmp(al, _Val);
			auto& _Copy = _Tmp.value();
			const auto __elements_after = static_cast<size_type>(_Mylast - _Where);
			if (__elements_after > n) {
				wjr::uninitialized_move(al, _Mylast - n, _Mylast, _Mylast);
				wjr::move_backward(_Where, _Mylast - n, _Mylast);
				wjr::fill_n(_Where, n, _Copy);
			}
			else {
				wjr::uninitialized_fill_n(al, _Mylast, n - __elements_after, _Copy);
				wjr::uninitialized_move(al, _Where, _Mylast, _Where + n);
				wjr::fill(_Where, _Mylast, _Copy);
			}
			inc_size(n);
		}
		else {
			const auto _Newcapacity = getGrowthCapacity(capacity(), size() + n);
			data_type _Newdata(al, size() + n, _Newcapacity, extend_tag{});
			const pointer _Newfirst = _Newdata.data();

			const auto __old_pos = static_cast<size_type>(_Where - _Myfirst);

			wjr::uninitialized_fill_n(al, _Newfirst + __old_pos, n, _Val);
			wjr::uninitialized_move(al, _Myfirst, _Where, _Newfirst);
			wjr::uninitialized_move(al, _Where, _Mylast, _Newfirst + __old_pos + n);

			tidy();
			moveConstruct(al, std::move(_Newdata), getData());
		}
	}

	template<typename _Ty>
	WJR_CONSTEXPR20 void _M_resize(const size_type _Newsize, const _Ty& _Val) {
		const auto _Oldsize = size();
		if (_Newsize > _Oldsize) {
			_M_append(_Newsize - _Oldsize, _Val);
		}
		else if (_Newsize < _Oldsize) {
			_M_erase_at_end(data() + _Newsize);
		}
	}

	template<typename _Ty>
	WJR_CONSTEXPR20 void _M_append(size_type n, const _Ty& _Val) {
		auto& al = getAllocator();

		const auto _Oldsize = size();
		const auto _Oldcapacity = capacity();

		const pointer _Myfirst = data();
		const pointer _Mylast = _Myfirst + _Oldsize;
		const pointer _Myend = _Myfirst + _Oldcapacity;

		const auto __rest = _Oldcapacity - _Oldsize;
		const auto _Newsize = _Oldsize + n;

		if (__rest >= n) {
			wjr::uninitialized_fill_n(al, _Mylast, n, _Val);
			set_size(_Newsize);
		}
		else {
			auto _Newcapacity = getGrowthCapacity(_Oldcapacity, _Newsize);
			data_type _Newdata(al, _Newsize, _Newcapacity, extend_tag{});
			const pointer _Newfirst = _Newdata.data();

			wjr::uninitialized_fill_n(al, _Newfirst + _Oldsize, n, _Val);
			wjr::uninitialized_move(al, _Myfirst, _Mylast, _Newfirst);

			tidy();
			moveConstruct(al, std::move(_Newdata), getData());
		}
	}

	template<typename Args>
	WJR_CONSTEXPR20 void _M_insert_aux(iterator _Where, Args&& args) {
		auto& al = getAllocator();
		const pointer _Mylast = lastPtr();

		wjr::construct_at(al, _Mylast, std::move(*(_Mylast - 1)));

		wjr::move_backward(_Where, _Mylast - 1, _Mylast);
		*_Where = std::forward<Args>(args);

		inc_size(1);
	}

	template<typename...Args>
	WJR_CONSTEXPR20 iterator _M_emplace_aux(const_iterator _Where, Args&&...args) {
		const auto __offset = _Where - cbegin();

		auto& al = getAllocator();
		const pointer _Myfirst = data();
		const pointer _Mylast = lastPtr();
		const pointer _Myend = lastPtr();

		if (_Mylast != _Myend) {
			if (_Where == _Mylast) {
				wjr::construct_at(al, _Mylast, std::forward<Args>(args)...);
				inc_size(1);
			}
			else {
				temporary_allocator_value<Alloc> _Tmp(al, std::forward<Args>(args)...);
				_M_insert_aux(begin() + __offset, std::move(_Tmp.value()));
			}
		}
		else {
			_M_realloc_insert(begin() + __offset, std::forward<Args>(args)...);
		}

		return begin() + __offset;
	}

private:
	wjr::pair<_Alty, data_type> _Myval;
};

template<typename iter,
	typename v = typename std::iterator_traits<iter>::value_type,
	typename Alloc = std::allocator<v>,
	typename Data = vector_data<v, Alloc>,
	std::enable_if_t<is_iterator_v<iter>, int> = 0>
vector(iter, iter, Alloc = Alloc()) -> vector<v, Data>;

template<typename T, size_t N, typename Alloc = std::allocator<T>>
using static_vector = vector<T, Alloc, vector_static_data<T, Alloc, N>>;

template<typename T, size_t N, typename Alloc = std::allocator<T>>
using sso_vector = vector<T, Alloc, vector_sso_data<T, Alloc, N>>;

template<typename T, typename Alloc, typename Data>
bool operator==(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Alloc, typename Data>
bool operator!=(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return !(lhs == rhs);
}

template<typename T, typename Alloc, typename Data>
bool operator<(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return wjr::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Alloc, typename Data>
bool operator>(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return rhs < lhs;
}

template<typename T, typename Alloc, typename Data>
bool operator<=(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return !(rhs < lhs);
}

template<typename T, typename Alloc, typename Data>
bool operator>=(const vector<T, Alloc, Data>& lhs, const vector<T, Alloc, Data>& rhs) {
	return !(lhs < rhs);
}

//template<typename T, typename Alloc, size_t C = 0>
//using sso_vector = vector<T, Alloc, vector_sso_Data<T, Alloc, C>>;

_WJR_END

namespace std {
	template<typename T, typename Alloc, typename Data>
	WJR_CONSTEXPR20 void swap(wjr::vector<T, Alloc, Data>& lhs, wjr::vector<T, Alloc, Data>& rhs)
		noexcept(noexcept(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	template<typename T, typename Alloc, typename Data>
	WJR_CONSTEXPR20 typename wjr::vector<T, Alloc, Data>::size_type erase(wjr::vector<T, Alloc, Data>& c, const T& value) {
		auto it = std::remove(c.begin(), c.end(), value);
		const auto n = std::distance(it, c.end());
		c.erase(it, c.end());
		return n;
	}

	template<typename T, typename Alloc, typename Data, typename Pred>
	WJR_CONSTEXPR20 typename wjr::vector<T, Alloc, Data>::size_type erase_if(wjr::vector<T, Alloc, Data>& c, Pred pred) {
		auto it = std::remove_if(c.begin(), c.end(), pred);
		const auto n = std::distance(it, c.end());
		c.erase(it, c.end());
		return n;
	}

}

#pragma pop_macro("new")

#endif // !__WJR_VECTOR_H

_WJR_BEGIN

#if defined(_WJR_CPUINFO)
const cpu_features::X86Info cpuinfo = cpu_features::GetX86Info();
const cpu_features::CacheInfo cacheinfo = cpu_features::GetX86CacheInfo();
const cpu_features::X86Microarchitecture microarchitecture = cpu_features::GetX86Microarchitecture(&cpuinfo);
const size_t __max_cache_size = []() {
	size_t max_size = 0;
	for (int i = 0; i < cacheinfo.size; ++i) {
		if (cacheinfo.levels[i].cache_type != cpu_features::CacheType::CPU_FEATURE_CACHE_NULL) {
			max_size = max_size < cacheinfo.levels[i].cache_size ?
				cacheinfo.levels[i].cache_size : max_size;
		}
	}
	return max_size;
}();
const bool __is_intel = []() {
	return microarchitecture >= cpu_features::INTEL_80486 && microarchitecture <= cpu_features::INTEL_NETBURST;
}();
const bool __is_amd = []() {
	return microarchitecture >= cpu_features::AMD_HAMMER && microarchitecture <= cpu_features::AMD_ZEN3;
}();
#endif // _WJR_CPUINFO

_WJR_END

#include <stdio.h>

_WJR_BEGIN
#if defined(WJR_TEST_ALLOCATOR)
__test_allocator::~__test_allocator() {
	if (_Count != 0) {
		printf("memory leak: %lld bytes", _Count);
	}
}
__test_allocator __test_allocator_instance;
#endif
_WJR_END