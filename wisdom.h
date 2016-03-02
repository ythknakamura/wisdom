#pragma once

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<complex>
#include<numeric>
#include<algorithm>
#include<chrono>
#include<cassert>
#include<memory>
#include<limits>
#include<fftw3.h>
#include<lapacke.h>
#include<omp.h>

using dvector = std::vector<double>;
using Complex = std::complex<double>;

inline lapack_complex_double* lcomplex(std::vector<Complex>& f){ return reinterpret_cast<lapack_complex_double*>(f.data()); }
inline fftw_complex* fcomplex(std::vector<Complex>& f){ return reinterpret_cast<fftw_complex*>(f.data()); }

template <class T>
inline constexpr T square(T d){return d*d;}

template<class T>
inline T GetValueLin(T MinVal, T MaxVal, int Step, int s){
	return MinVal + (MaxVal-MinVal)*s/(Step-1);
}

template<class T> 
inline T GetValueLog(T MinVal, T MaxVal, int Step, int s){
	return exp(log(MinVal) + (log(MaxVal)-log(MinVal))*s/(Step-1));
}

namespace WisdomInternal{
	using namespace std;
	template<class O, class T> inline void printOne(O& out, T value){out << value;}
	template<class O> inline void printOne(O& out, bool value){ out << boolalpha << value << "\t"; }
	template<class O> inline void printOne(O& out, double value){ out << value << "\t"; }
	template<class O> inline void printOne(O& out, int value){ out << value << "\t"; }
	template<class O> inline void printOne(O& out, const string value){ out << value << "\t"; }
	template<class O> inline void printOne(O& out, const char* value){ out << value << "\t"; }
	template<class O, class T> inline void printOne(O& out, complex<T> value){
		out << value.real() << "\t" << value.imag();
	}

	template<class O> inline void println(O& out ){ out << endl; }
	template<class O, class T, class ... Args> inline void println(O& out, const T& value, const Args& ... args){
		printOne(out, value);
		println(out, args...);
	}
}
template<class O, class ... Args> inline void Println(O &out, const Args&...args){
	auto flags = out.flags();
	out.width(8);
	WisdomInternal::println(out, args...);
	out.flags(flags);
}
