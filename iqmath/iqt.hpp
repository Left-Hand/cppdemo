#ifndef __IQT_HPP__

#define __IQT_HPP__

#include <stdint.h>
#include <type_traits>
#include <concepts>

#include "_IQNdiv.hpp"
#include "_IQNatan2.hpp"
#include "_IQNtoF.hpp"
#include "_IQNsqrt.hpp"

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
#include "IQmathLib.hpp"
#include "rts_support.h"
#include <numeric>

// #define __fast_inline constexpr __fast_inline constexpr
#define CMP_EPSILON 0.0001
#define RSHIFT(x,s) ((x) >> (s))
#define LSHIFT(x,s) ((x) << (s))
#define FPU_PRESENT
#define IQ_USE_LOG
#define IQ_GENERAL_LOG
// #define IQ_CH32_LOG

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept floating = std::is_floating_point_v<T>;

template<typename T>
concept integral = std::is_integral_v<T>;

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


struct iq_t;

namespace std{
    template <>
    struct is_arithmetic<iq_t> : std::true_type {};

    template <>
    struct is_floating_point<iq_t> : std::false_type {};
}

struct iq_t{
private:
    // __fast_inline static constexpr _iq float_to_iq(const float fv){
    //     int32_t d = std::bit_cast<int32_t>(fv);
    //     int32_t exponent = ((d >> 23) & 0xff);
    //     uint64_t mantissa = (exponent == 0) ? (0) : ((d & ((1 << 23) - 1)) | (1 << 23));

    //     uint64_t temp = (exponent == 0 or exponent == 0xff) ? 0 : LSHIFT(mantissa, exponent - 127);

    //     uint64_t  uresult = RSHIFT(temp, (23 - GLOBAL_Q));
    //     int32_t result = d > 0 ? uresult : -uresult;

    //     if((bool(d > 0) ^ bool(result > 0)) or (uresult > (uint64_t)0x80000000)){//OVERFLOW
    //         result = (d > 0) ? 0x7FFFFFFF : 0x80000000;
    //     }

    //     {
    //         return _iq(result);
    //     }
    // }
public:
    _iq value;

    __fast_inline constexpr iq_t():value(0){;}

    __fast_inline constexpr iq_t(const _iq & other) : value(other){;}
    __fast_inline constexpr iq_t(_iq && other) : value(other){;}

    template<typename T>
    requires std::is_integral_v<T>
    __fast_inline constexpr iq_t(const T intValue) : value(_IQ(intValue)) {;}

    #ifdef STRICT_IQ
    __fast_inline consteval explicit iq_t(const float fv):value((std::is_constant_evaluated()) ? float_to_iq(fv) : float_to_iq(fv)){};
    // __fast_inline consteval iq_t(const float fv):value((std::is_constant_evaluated()) ? float_to_iq(fv) : float_to_iq(fv)){};
    #else
    // __fast_inline constexpr iq_t(const float fv):value((std::is_constant_evaluated()) ? float_to_iq(fv) : float_to_iq(fv)){};
    __fast_inline constexpr iq_t(const float fv):value(_IQ(fv)){};
    #endif

    static __fast_inline constexpr iq_t form (const floating auto fv){iq_t ret; ret.value = float_to_iq(fv); return ret;}

    __fast_inline constexpr iq_t operator+(const iq_t other) const {
        return iq_t(_iq(int32_t(value) + int32_t(other.value)));
    }

    __fast_inline constexpr iq_t operator-(const iq_t other) const {
        return iq_t(_iq(int32_t(value) - int32_t(other.value)));
    }

    __fast_inline constexpr iq_t operator-() const {
        return iq_t(_iq(-int32_t(value)));
    }

    __fast_inline constexpr iq_t& operator+=(const iq_t other) {
        value = _iq((int32_t)value + (int32_t)other.value);
        return *this;
    }

    __fast_inline constexpr iq_t& operator-=(const iq_t other) {
        value = _iq(int32_t(value) - int32_t(other.value));
        return *this;
    }

    __fast_inline constexpr iq_t& operator*=(const iq_t other) {
        *this = *this * other;
        return *this;
    }

    __fast_inline constexpr iq_t& operator/=(const iq_t other) {
        *this = *this / other;
        return *this;
    }

    template<integral T>
    __fast_inline constexpr iq_t operator*(const T other) const {
        return iq_t(_iq(int32_t(value) * other));
    }

    __fast_inline constexpr iq_t operator*(const iq_t other) const {
        return iq_t((_iq)(((int64_t)value * (int64_t)other.value) >> GLOBAL_Q));
    }


    template<integral T>
    __fast_inline constexpr iq_t operator/(const T other) const {
        return iq_t(_iq((int32_t(value) / other)));
    }


    #ifdef  STRICT_IQ
    
    iq_t operator*(const floating auto other) = delete;
    iq_t operator/(const floating auto other) = delete;
    #endif
    

    __fast_inline constexpr iq_t operator/(const iq_t other) const {
        if (std::is_constant_evaluated()) {
            return iq_t((_iq)((int32_t)value / (int32_t)other.value << GLOBAL_Q));
        }else{
            return iq_t(_iq(_IQNdiv<GLOBAL_Q>(int32_t(value), int32_t(other.value))));
        }
    }

    __fast_inline constexpr bool operator==(const iq_t other) const {
        return int32_t(value) == int32_t(other.value);
    }

    __fast_inline constexpr bool operator!=(const iq_t other) const {
        return int32_t(value) != int32_t(other.value);
    }

    __fast_inline constexpr bool operator>(const iq_t other) const {
        return int32_t(value) > int32_t(other.value);
    }

    __fast_inline constexpr bool operator<(const iq_t other) const {
        return int32_t(this->value) < int32_t(other.value);
    }

    __fast_inline constexpr bool operator>=(const iq_t other) const {
       return int32_t(value) >= int32_t(other.value);
    }

    __fast_inline constexpr bool operator<=(const iq_t other) const {
       return int32_t(value) <= int32_t(other.value);
    }

    __fast_inline constexpr iq_t operator<<(int shift) const {
        return iq_t(_iq(int32_t(value) << shift));
    }

    __fast_inline constexpr iq_t operator>>(int shift) const {
        return iq_t(_iq(int32_t(value) >> shift));
    }

    #undef IQ_OPERATOR_TEMPLATE

    __fast_inline constexpr explicit operator bool() const {
        return bool(int32_t(value));
    }

    #define IQ_TOINT_TEMPLATE(op)\
    __fast_inline constexpr explicit operator op() const {\
        return op(int32_t(value) >> GLOBAL_Q);\
    }

    // IQ_TOINT_TEMPLATE(int);
    IQ_TOINT_TEMPLATE(int8_t);
    IQ_TOINT_TEMPLATE(int16_t);
    IQ_TOINT_TEMPLATE(int32_t);
    IQ_TOINT_TEMPLATE(uint8_t);
    IQ_TOINT_TEMPLATE(uint16_t);
    IQ_TOINT_TEMPLATE(uint32_t);

    #undef IQ_TOINT_TEMPLATE

    __inline constexpr explicit operator float() const{
        if(std::is_constant_evaluated()){
            return float(int32_t(value)) / (1 << GLOBAL_Q);
        }else{
            return _IQNtoF<GLOBAL_Q>(int32_t(value));
        }
    }

    __inline constexpr explicit operator double() const{
        return float(*this);
    }

};

// #define IQ_OP_TEMPLATE(type, op)\
// __fast_inline constexpr iq_t operator op (const type val, const iq_t iq_v) {\
// 	return iq_t(val) op iq_v;\
// }\

// #define IQ_OPS_TEMPLATE(type)\
// IQ_OP_TEMPLATE(type, +)\
// IQ_OP_TEMPLATE(type, -)\
// IQ_OP_TEMPLATE(type, *)\
// IQ_OP_TEMPLATE(type, /)\

// IQ_OPS_TEMPLATE(int);
// #ifndef STRICT_IQ
// #else
// #define IQ_OP_DELETE(op)\
// iq_t operator op (const float val, const iq_t iq_v) = delete;\

// IQ_OP_DELETE(+)
// IQ_OP_DELETE(-)
// IQ_OP_DELETE(*)
// IQ_OP_DELETE(/)

// #undef IQ_OP_DELETE

// #endif


#define IQ_BINA_TEMPLATE(type, op)\
__fast_inline constexpr bool operator op (const type val, const iq_t iq_v) {\
	return iq_t(val) op iq_v;\
}\

#define IQ_BINAS_TEMPLATE(type)\
IQ_BINA_TEMPLATE(type, ==)\
IQ_BINA_TEMPLATE(type, !=)\
IQ_BINA_TEMPLATE(type, >)\
IQ_BINA_TEMPLATE(type, >=)\
IQ_BINA_TEMPLATE(type, <)\
IQ_BINA_TEMPLATE(type, <=)\

IQ_BINAS_TEMPLATE(int)
#ifndef STRICT_IQ
#else
#define IQ_BINA_DELETE(op)\
bool operator op (const float val, const iq_t iq_v) = delete;\

IQ_BINA_DELETE(==)
IQ_BINA_DELETE(!=)
IQ_BINA_DELETE(>)
IQ_BINA_DELETE(>=)

#undef IQ_BINA_DELETE
#endif

#undef IQ_OP_TEMPLATE
#undef IQ_OPS_TEMPLATE
#undef IQ_BINA_TEMPLATE
#undef IQ_BINAS_TEMPLATE

__fast_inline iq_t sinf(const iq_t iq){
    {
        return iq_t(_iq(_IQsin(int32_t(iq.value))));
    }
}

__fast_inline iq_t cosf(const iq_t iq){
    {
        return iq_t(_iq(_IQcos(int32_t(iq.value))));
    }
}

__fast_inline iq_t sin(const iq_t iq){return sinf(iq);}

__fast_inline iq_t cos(const iq_t iq){return cosf(iq);}

__fast_inline iq_t tanf(const iq_t iq) {return sin(iq) / cos(iq);}
__fast_inline iq_t tan(const iq_t iq) {return tanf(iq);}

__fast_inline iq_t asin(const iq_t iq) {
    {
        return iq_t(_iq(_IQasin(int32_t(iq.value))));
    }
}

__fast_inline iq_t acos(const iq_t iq) {
    {
        return iq_t(_iq(_IQacos(int32_t(iq.value))));
    }
}

__fast_inline iq_t atan(const iq_t iq) {
    {
        return iq_t(_iq(_IQNatan2<GLOBAL_Q>(int32_t(iq.value), _IQ(1))));
    }
}

__fast_inline iq_t atan2f(const iq_t a, const iq_t b) {
    {
        return iq_t(_iq(_IQNatan2<GLOBAL_Q>(int32_t(a.value),int32_t(b.value))));
    }
}

__fast_inline iq_t atan2(const iq_t a, const iq_t b) {
    return atan2f(a, b);
}

__fast_inline iq_t sqrt(const iq_t iq){
    {
        return iq_t(_iq(_IQNsqrt<GLOBAL_Q>(int32_t(iq.value))));
    }
}

__fast_inline constexpr iq_t abs(const iq_t iq){
    if(int32_t(iq.value) > 0){
        return iq;
    }else{
        return -iq;
    }
}

__fast_inline constexpr bool isnormal(const iq_t iq){return bool(int32_t(iq.value));}

__fast_inline constexpr bool signbit(const iq_t iq){return bool(int32_t(iq.value) < 0);}

__fast_inline constexpr iq_t sign(const iq_t iq){
    if(int32_t(iq.value)){
        if(int32_t(iq.value) > 0){
            return iq_t(1);
        }else{
            return iq_t(-1);
        }
    }else return iq_t(0);
}

__fast_inline constexpr iq_t fmod(const iq_t a, const iq_t b){return iq_t(_iq(int32_t(a.value) % int32_t(b.value)));}


__fast_inline constexpr iq_t lerp(const iq_t x, const iq_t a, const iq_t b){return a * (iq_t(1) - x) + b * x;}
__fast_inline constexpr iq_t mean(const iq_t a, const iq_t b){return iq_t(_iq((int32_t(a.value) + int32_t(b.value)) >> 1));}

__fast_inline constexpr iq_t frac(const iq_t iq){
    return iq_t(_iq(int32_t(iq.value) & ((1 << GLOBAL_Q) - 1)));
}

__fast_inline constexpr iq_t floor(const iq_t iq){return int(iq);}
__fast_inline constexpr iq_t ceil(const iq_t iq){return (iq > int(iq)) ? int(iq) + 1 : int(iq);}

__fast_inline constexpr iq_t round(const iq_t iq){return iq_t((int)_IQint(int32_t(iq.value) + int32_t(1 << (GLOBAL_Q - 1))));}

bool is_equal_approx(const iq_t a,const iq_t b);

bool is_equal_approx_ratio(const iq_t a, const iq_t b, iq_t epsilon = iq_t(CMP_EPSILON), iq_t min_epsilon = iq_t(CMP_EPSILON));

#ifdef IQ_USE_LOG

__fast_inline iq_t log10(const iq_t iq) {
    {
        #ifdef IQ_CH32_LOG
        return iq_t(_iq(_IQlog10(iq.value)));
        #else
        return iq_t(_iq(_IQlog(int32_t(iq.value)))) / iq_t(_iq(_IQlog(int32_t(_IQ(10)))));
        #endif
    }
}

__fast_inline iq_t log(const iq_t iq) {
    {
        #ifdef IQ_CH32_LOG
        return iq_t(_iq(_IQdiv(_IQlog10(iq.value), _IQlog10(_IQ(M_E)))));
        #else
            return iq_t(_iq(_IQlog(int32_t(iq.value))));
        #endif
    }
}

__fast_inline iq_t exp(const iq_t iq) {
    {
        return iq_t(_iq(_IQexp(int32_t(iq.value))));
    }
}

__fast_inline iq_t exp2(const iq_t iq) {
    // if(std::is_constant_evaluated()){
    //     return iq_t(cem::pow(2.0, double(iq)));
    // }else
    {
        return iq_t(_iq(_IQexp2(int32_t(iq.value))));
    }
}

__fast_inline iq_t pow(const iq_t base, const iq_t exponent) {
    // if(std::is_constant_evaluated()){
    //     return iq_t(cem::pow(double(base), double(exponent)));
    // }else
    {
        return exp(exponent * log(base));
    }
}

#endif

__fast_inline constexpr void u16_to_uni(const uint16_t data, iq_t & qv){
#if GLOBAL_Q > 16
    qv.value = data << (GLOBAL_Q - 16);
#elif(GLOBAL_Q < 16)
    qv.value = data >> (16 - GLOBAL_Q);
#else
    qv.value = _iq(data);
#endif

}


__fast_inline constexpr void u32_to_uni(const uint32_t data, iq_t & qv){
#if GLOBAL_Q > 16
    qv.value = data << (GLOBAL_Q - 16);
#elif(GLOBAL_Q < 16)
    qv.value = data >> (16 - GLOBAL_Q);
#else
    qv.value = _iq(data);
#endif

}

__fast_inline constexpr void s16_to_uni(const int16_t data, iq_t & qv){
    qv.value = _iq(data << GLOBAL_Q);
}

__fast_inline constexpr void uni_to_u16(const iq_t qv, uint16_t & data){
#if GLOBAL_Q >= 16
    data = int32_t(qv.value) >> (GLOBAL_Q - 16);
#else
    data = qv.value << (16 - GLOBAL_Q);
#endif
    if(data == 0 && int32_t(qv.value) != 0) data = 0xffff;
}


namespace std{
    template<>
    class numeric_limits<iq_t> {
    public:
        __fast_inline constexpr static iq_t infinity() noexcept {return iq_t(_iq(0x80000000));}
        __fast_inline constexpr static iq_t lowest() noexcept {return iq_t(_iq(0x7FFFFFFF));}

        __fast_inline constexpr static iq_t min() noexcept {return iq_t(_iq(0x80000000));}
        __fast_inline constexpr static iq_t max() noexcept {return iq_t(_iq(0x7FFFFFFF));}
    };

    #ifndef STRICT_IQ
    typedef std::common_type<iq_t, float>::type iq_t;
    typedef std::common_type<iq_t, double>::type iq_t;

    typedef std::common_type<float, iq_t>::type iq_t;
    typedef std::common_type<double, iq_t>::type iq_t;
    #endif

    typedef std::common_type<iq_t, int>::type iq_t;
    typedef std::common_type<int, iq_t>::type iq_t;

    __fast_inline iq_t sinf(const iq_t iq){return ::sinf(iq);}
    __fast_inline iq_t cosf(const iq_t iq){return ::cosf(iq);}
    __fast_inline iq_t sin(const iq_t iq){return ::sin(iq);}
    __fast_inline iq_t cos(const iq_t iq){return ::cos(iq);}
    __fast_inline iq_t tanf(const iq_t iq){return ::tanf(iq);}
    __fast_inline iq_t tan(const iq_t iq){return ::tan(iq);}
    __fast_inline iq_t asinf(const iq_t iq){return ::asin(iq);}
    __fast_inline iq_t asin(const iq_t iq){return ::asin(iq);}
    __fast_inline iq_t acos(const iq_t iq){return ::acos(iq);}
    __fast_inline iq_t atan(const iq_t iq){return ::atan(iq);}
    __fast_inline iq_t atan2f(const iq_t a, const iq_t b){return ::atan2f(a,b);}
    __fast_inline iq_t atan2(const iq_t a, const iq_t b){return ::atan2(a,b);}
    __fast_inline iq_t sqrt(const iq_t iq){return ::sqrt(iq);}
    __fast_inline iq_t abs(const iq_t iq){return ::abs(iq);}
    __fast_inline bool isnormal(const iq_t iq){return ::isnormal(iq);}
    __fast_inline bool signbit(const iq_t iq){return ::signbit(iq);}
    __fast_inline iq_t fmod(const iq_t a, const iq_t b){return ::fmod(a, b);}
    __fast_inline iq_t mean(const iq_t a, const iq_t b){return ::mean(a, b);}
    __fast_inline iq_t frac(const iq_t iq){return ::frac(iq);}
    __fast_inline iq_t floor(const iq_t iq){return ::floor(iq);}
    __fast_inline iq_t ceil(const iq_t iq){return ::ceil(iq);}

    #ifdef IQ_USE_LOG
    __fast_inline iq_t log10(const iq_t iq){return ::log10(iq);}
    __fast_inline iq_t log(const iq_t iq){return ::log(iq);}
    #endif
}

#endif