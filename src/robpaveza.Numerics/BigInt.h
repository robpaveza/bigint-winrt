#pragma once
#include "bigint/BigInteger.hh"

namespace robpaveza
{
    namespace Numerics
    {
        public ref class BigInt sealed
        {
        private:
            ::BigInteger actual_;

        private:
            BigInt(::BigInteger value) :
                actual_(value) { }
            BigInt(::BigUnsigned value) :
                actual_(value) { }

        public:
            static BigInt^ FromString(Platform::String^ hexString);
            static BigInt^ FromBuffer(Windows::Storage::Streams::IBuffer^ buffer);
            static BigInt^ FromBuffer(Windows::Storage::Streams::IBuffer^ buffer, uint32 byteLength);
            static BigInt^ FromUInt32(uint32 x);
            static BigInt^ FromInt32(int32 x);
            static BigInt^ FromUInt16(uint16 x);
            static BigInt^ FromInt16(int16 x);

            property uint32 ByteLength
            {
                uint32 get();
            }

            property bool IsZero
            {
                bool get() { return actual_.isZero(); }
            }

            property bool IsPositive
            {
                bool get();
            }

            int32 CompareTo(BigInt^ other);
            bool Equals(BigInt^ other);

            BigInt^ Add(BigInt^ addend);
            BigInt^ Subtract(BigInt^ subtrahend);
            BigInt^ Multiply(BigInt^ multiplicand);
            BigInt^ Divide(BigInt^ dividend);
            BigInt^ Modulus(BigInt^ dividend);
            BigInt^ Negate();

            BigInt^ ModPow(BigInt^ exponent, BigInt^ modulus);
            BigInt^ ModInv(BigInt^ modulus);

            Windows::Storage::Streams::IBuffer^ ToBuffer();
        };
    }
}