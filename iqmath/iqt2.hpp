#pragma once

#include <stdint.h>
#include <type_traits>
#include <concepts>

#include "_IQNdiv.hpp"
#include "_IQNatan2.hpp"
#include "_IQNtoF.hpp"
#include "_IQNsqrt.hpp"
#include "_IQNexp.hpp"
#include "_IQNasin_acos.hpp"
#include "_IQNsin_cos.hpp"
#include "_IQNlog.hpp"


#ifndef LOG_E
#define LOG_E (0.434294481903)
#endif


#if defined(YUMUD)
// #include "sys/core/platform.h"
// #include "sys/math/float/fp32.hpp"

// #include "dsp/constexprmath/ConstexprMath.hpp"
#endif

#if defined(RISCV)
#include "riscv/IQmath_RV32.h"
#endif

#if defined(WIN32)

#include "rts_support.h"
#include <numeric>

// #define __fast_inline constexpr __fast_inline constexpr
#define CMP_EPSILON 0.0001
#define RSHIFT(x,s) ((x) >> (s))
#define LSHIFT(x,s) ((x) << (s))
#define FPU_PRESENT
#define IQ_USE_LOG
#define IQ_GENERAL_LOG

#ifndef _IQ
#define _IQ(x) (x * (1 << Q))
#endif

#endif


#include <bit>
#include <bits.h>


struct _iq{
protected:
    int32_t value = 0;
public:
    __fast_inline constexpr explicit _iq(const int32_t _value) : value(_value){;}
    __fast_inline constexpr explicit operator int32_t() const{return value;}
    __fast_inline constexpr explicit operator int64_t() const{return value;}
};

template<int Q>
requires ((Q >= 1) && (Q < 32))
struct iq2_t;

namespace std{
    template <size_t Q>
    struct is_arithmetic<iq2_t<Q>> : std::true_type {};

    template <size_t Q>
    struct is_floating_point<iq2_t<Q>> : std::false_type {};;
}

template<int Q>
requires ((Q >= 1) && (Q < 32))
struct iq2_t{
public:
    _iq value;

    __fast_inline constexpr iq2_t():value(0){;}

    __fast_inline constexpr iq2_t(const _iq & other) : value(other){;}
    __fast_inline constexpr iq2_t(_iq && other) : value(other){;}

    template<typename T>
    requires std::is_integral_v<T>
    __fast_inline constexpr iq2_t(const T intValue) : value(intValue << Q) {;}

    __fast_inline constexpr iq2_t(const float fv):value(fv * (1 << Q)){};

    template<int P>
    __fast_inline constexpr operator iq2_t<P>() const {return iq2_t<P>(_iq((int64_t(value) << Q) >> P));}

    __fast_inline constexpr iq2_t(const iq2_t<Q> & other):value(other.value){};

    //#region addsub
    #define IQ_ADD_SUB_TEMPLATE(op)\
    template<int P>\
    __fast_inline constexpr iq2_t operator op(const iq2_t<P> other) const {\
        if constexpr (Q == P){\
            return iq2_t(_iq(int32_t(value) op int32_t(other.value)));\
        }else{\
            return iq2_t(_iq(int32_t(value) op ((int64_t(other.value) << Q) >> P )));\
        }\
    }\
    __fast_inline constexpr iq2_t & operator op##=(iq2_t other) {\
        return *this = *this op other;\
    }\
    
    IQ_ADD_SUB_TEMPLATE(+)
    IQ_ADD_SUB_TEMPLATE(-)
    #undef IQ_ADD_SUB_TEMPLATE
    //#endregion addsub

    //#region multiply
    template<typename T>
    requires std::is_integral_v<T>
    __fast_inline constexpr iq2_t operator*(const T other) const {
        return iq2_t(_iq(int32_t(value) * other));
    }

    template<int P>
    __fast_inline constexpr iq2_t operator*(const iq2_t<P> other) const {
        return iq2_t((_iq)(((int64_t)value * (int64_t)other.value) >> P));
    }

    template<int P>
    __fast_inline constexpr iq2_t& operator*=(const iq2_t<P> other) {
        *this = *this * other;
        return *this;
    }
    
    //#endregion

    //#region division
    template<typename T>
    requires std::is_integral_v<T>
    __fast_inline constexpr iq2_t operator/(const T other) const {
        return iq2_t(_iq((int32_t(value) / other)));
    }

    template<int P>
    __fast_inline constexpr iq2_t operator/(const iq2_t<P> other) const {
        if (std::is_constant_evaluated()) {
            return iq2_t((_iq)((int32_t)value / (int32_t)other.value << Q));
        }else{
            return iq2_t(_iq(_IQNdiv<Q>(int32_t(value), ((int64_t(other.value) << Q) >> P))));
        }
    }

    template<int P>
    __fast_inline constexpr iq2_t& operator/=(const iq2_t<P> other) {
        *this = *this / other;
        return *this;
    }
    //#endregion

    //#region comparisons
    #define IQ_COMP_TEMPLATE(op)\
    template<int P>\
    __fast_inline constexpr bool operator op (const iq2_t<P> other) const {\
        if constexpr (Q == P){\
            return (int32_t(value) op int32_t(other.value));\
        }else{\
            return (int32_t(value) op ((int64_t(other.value) << Q) >> P));\
        }\
    }\
    \
    template<typename T>\
    requires std::is_floating_point_v<T>\
    __fast_inline constexpr bool operator op (const T other) const {\
        return (*this op iq2_t<Q>(other));\
    }\
    \
    template<typename T>\
    requires std::is_integral_v<T>\
    __fast_inline constexpr bool operator op (const T other) const {\
        return ((int32_t(this->value) >> Q) op other);\
    }\


    IQ_COMP_TEMPLATE(==)
    IQ_COMP_TEMPLATE(!=)
    IQ_COMP_TEMPLATE(>)
    IQ_COMP_TEMPLATE(<)
    IQ_COMP_TEMPLATE(>=)
    IQ_COMP_TEMPLATE(<=)
    #undef IQ_COMP_TEMPLATE
    //#endregion

    //#region shifts
    __fast_inline constexpr iq2_t operator<<(int shift) const {
        return iq2_t(_iq(int32_t(value) << shift));
    }

    __fast_inline constexpr iq2_t operator>>(int shift) const {
        return iq2_t(_iq(int32_t(value) >> shift));
    }


    //#endregion

    __fast_inline constexpr explicit operator bool() const {
        return bool(int32_t(value));
    }

    template<typename T>
    requires std::is_integral_v<T>
    __fast_inline constexpr explicit operator T() const {
        return int32_t(value) >> Q;
    }
    

    template<typename T>
    requires std::is_floating_point_v<T>
    __inline constexpr explicit operator T() const{
        if(std::is_constant_evaluated()){
            return float(int32_t(value)) / (1 << Q);
        }else{
            return _IQNtoF<Q>(int32_t(value));
        }
    }

};