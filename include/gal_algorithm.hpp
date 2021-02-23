#ifndef GALLIBRARY_ALGORITHM_HPP
#define GALLIBRARY_ALGORITHM_HPP

#include <gal_type_traits.hpp>

namespace gal
{
	// Determine whether all data meets the conditions
	// such as
	//      bool less_than_42 = unary_determine([](auto& val){return val < 42;}, a, b, c, d, e, f);
	template<typename Pred, typename T, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, T, More...>>>
	constexpr bool unary_determine(Pred pred, T&& t, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			return pred(std::forward<T>(t));
		}
		else
		{
			return unary_determine(pred, t) && unary_determine(pred, more...);
		}
	}

	// Determine whether all data meets the conditions
	// such as
	//      bool ascending = binary_determine([](auto& val1, auto& val2){return val2 > val2;}, a, b, c, d, e, f);
	template<typename Pred, typename A, typename B, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, gal::wrap_type_t<A, B>>>>
	constexpr bool binary_determine(Pred pred, A&& a, B&& b, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			return pred(std::forward<A>(a), std::forward<B>(b));
		}
		else
		{
			return binary_determine(pred, a, b) && binary_determine(pred, b, more...);
		}
	}

	// traverse all the data to find the first matching result, return it, you also need to set a default value
	// such as
	//      auto find_42 = unary_process([](auto& val){return val == 42;}, 42, a, b, c, d, e, f);
	// if no matching value exist, return default value
	template<typename Pred, typename U, typename T, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, T, More...>>>
	constexpr decltype(auto) unary_process(Pred pred, U&& default_value, T&& t, More&&... more)
	{
		if(pred(t))
		{
			// find the first matching result
			return t;
		}
		if constexpr (sizeof...(more) == 0)
		{
			// if not result matched, return default_value
			return default_value;
		}
		else
		{
			return unary_process(pred, default_value, more...);
		}
	}

	// compare the first two data, get a qualified value, and then get the data one by one and compare with it
	// such as
	//      auto find_max = binary_process([](auto& val1, auto& val2){return val1 > val2 ? val1 : val2;}, a, b, c, d, e, f);
	// return the best matching value
	template<typename Pred, typename A, typename B, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, gal::wrap_type_t<A, B>>>>
	constexpr decltype(auto) binary_process(Pred pred, A&& a, B&& b, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			// compare two data, get a qualified value
			return pred(std::forward<A>(a), std::forward<B>(b));
		}
		else
		{
			// get the data one by one and compare with it
			return binary_process(pred, binary_process(pred, a, b), more...);
		}
	}

	// invoke pred with given parameter
	// such as
	//      unary_invoke([](auto& val){if(val > 42) val = 42;}, a, b, c, d, e, f);
	template<typename Pred, typename T, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, T, More...>>>
	constexpr void unary_invoke(Pred pred, T&& t, More&&... more)
	{
		pred(std::forward<T>(t));
		if constexpr (sizeof...(more) == 0)
		{
			return;
		}
		else
		{
			unary_invoke(pred, more...);
		}
	}

	// invoke pred with given parameter
	// such as:
	//      binary_invoke([](auto& val1, auto& val2){auto tmp = val1; val1 = val2; val2 = tmp;}, a, b, c, d, e, f);
	template<typename Pred, typename A, typename B, typename... More, typename = gal::enable_if_t<gal::is_invocable_v<Pred, gal::wrap_type_t<A, B>>>>
	constexpr void binary_invoke(Pred pred, A&& a, B&& b, More&&... more)
	{
		pred(std::forward<A>(a), std::forward<B>(b));
		if constexpr (sizeof...(more) == 0)
		{
			return;
		}
		else
		{
			binary_invoke(pred, b, more...);
		}
	}

	template<typename T, typename... More, typename = gal::enable_if_t<gal::is_arithmetic_v<T, More...>>>
	constexpr T max(T t, More... more)
	{
		return binary_process([](const auto& a, const auto& b){return a > b ? a : b;}, t, more...);
	}

	template<typename T, typename... More, typename = gal::enable_if_t<gal::is_arithmetic_v<T, More...>>>
	constexpr T min(T t, More... more)
	{
		return binary_process([](const auto& a, const auto& b){return b > a ? a : b;}, t, more...);
	}

	template<typename Max, typename T, typename... More, typename = gal::enable_if_t<gal::is_arithmetic_v<T, More...> && gal::is_convertible_v<Max, T, More...>>>
	constexpr void clamp_max(Max max, T& val, More&... more)
	{
		unary_invoke([max](auto& val){if(val > max) val = max;}, val, more...);
	}

	template<typename Min, typename T, typename... More, typename = gal::enable_if_t<gal::is_arithmetic_v<T, More...> && gal::is_convertible_v<Min, T, More...>>>
	constexpr void clamp_min(Min min, T& val, More&... more)
	{
		unary_invoke([min](auto& val){if(min > val) val = min;}, val, more...);
	}

	template<typename Max, typename Min, typename T, typename... More, typename = gal::enable_if_t<is_arithmetic_v<T, More...> && gal::is_convertible_v<gal::wrap_type_t<Max, Min>, gal::wrap_type_t<gal::wrap_type<T, More...>, gal::wrap_type<T, More...>>>>>
	constexpr void clamp(Max max, Min min, T& val, More&... more)
	{
		clamp_max(max, val, more...);
		clamp_min(min, val, more...);
	}

	template<typename Max, typename Min, typename T, typename... More, typename = gal::enable_if_t<is_arithmetic_v<T, More...> && gal::is_convertible_v<gal::wrap_type_t<Max, Min>, gal::wrap_type_t<gal::wrap_type<T, More...>, gal::wrap_type<T, More...>>>>>
	constexpr bool within(Max max, Min min, T& val, More&... more)
	{
		return unary_determine([max, min](const auto& val){return max >= val && val >= min;}, val, more...);
	}

	template<typename T, typename... More, typename = gal::enable_if_t<gal::is_integral_v<T, More...>>>
	constexpr void abs(T& val, More&... more)
	{
		unary_invoke(
				[](auto& val)
				{
				  constexpr auto bit_length = sizeof(T) * 8;
				  val = (val ^ (val >> (bit_length - 1))) - (val >> (bit_length - 1));
				}
				, val, more...
		);
	}

	// safe version:
	//  template<template<typename> class OutStream, typename Delimiter, typename T, typename... More, typename = std::enable_if_t<std::is_base_of_v<std::basic_ostream<T>, OutStream<T>>>>
	//  todo: type T deduce fail
	template<typename OutStream, typename Delimiter, typename T, typename... More>
	OutStream& print_out(OutStream& stream, Delimiter delimiter, T text, More... more)
	{
		unary_invoke([&stream, delimiter](const auto& text){stream << text << delimiter;}, text, more...);
		return stream;
	}

	// safe version:
	//  template<template<typename> class InStream, typename T, typename... More, typename = std::enable_if_t<std::is_base_of_v<std::basic_istream<T>, InStream<T>>>>
	//  todo: type T deduce fail
	template<typename InStream, typename T, typename... More>
	InStream& print_in(InStream& stream, T& text, More&... more)
	{
		unary_invoke([&stream](auto& text){stream >> text;}, text, more...);
		return stream;
	}

	// equal(str1, str2)
	constexpr bool equal(const char* lhs, const char* rhs)
	{
		// the same address
		if(lhs == rhs) return true;
		// invalid address
		if(!lhs || !rhs) return false;
		// compare each character
		// even the length may not equal, if the the sub-string is equal, we think these two string is equal
		while(*lhs && *rhs)
		{
			if(*lhs++ != *rhs++) return false;
		}

		return true;
	}
}

#endif
