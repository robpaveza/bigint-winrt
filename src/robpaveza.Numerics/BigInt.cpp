#include "pch.h"
#include "BigInt.h"
#include "bigint/BigIntegerLibrary.hh"
#include "BufferHelper.h"

#define CP_USASCII 20127

using namespace robpaveza::Numerics;
using namespace Platform;
using namespace Windows::Storage::Streams;

BigInt^ BigInt::FromString(String^ hexString)
{
    auto pSrc = hexString->Begin();
    auto req = ::WideCharToMultiByte(CP_USASCII, 0, pSrc, hexString->Length(), nullptr, 0, nullptr, nullptr);

    auto mem = ::CoTaskMemAlloc(req);
    if (mem == nullptr)
        throw ref new OutOfMemoryException();

    ZeroMemory(mem, req);
    req = ::WideCharToMultiByte(CP_USASCII, 0, pSrc, hexString->Length(), (char*)mem, req, nullptr, nullptr);
    if (req == 0)
    {
        ::CoTaskMemFree(mem);
        throw ref new Exception(E_FAIL);
    }

    try 
    {
        auto bi = stringToBigInteger(std::string((char*)mem));

        return ref new BigInt(bi);
    }
    catch (...)
    {
        throw ref new InvalidArgumentException();
    }
}

BigInt^ BigInt::FromBuffer(IBuffer^ buffer)
{
    return FromBuffer(buffer, buffer->Length);
}

BigInt^ BigInt::FromBuffer(IBuffer^ buffer, uint32 byteLength)
{
    if (byteLength % 4 != 0)
        throw ref new InvalidArgumentException(L"Buffer size must be a multiple of 4 bytes.");

    auto ptr = BufferHelper::PtrFromIBuffer(buffer);
    auto blkPtr = (unsigned long*)ptr;

    BigInteger result(blkPtr, byteLength / 4);
    return ref new BigInt(result);
}

IBuffer^ BigInt::ToBuffer()
{
    auto result = ref new Buffer(ByteLength);
    auto ptr = BufferHelper::PtrFromIBuffer(result);
    auto iptr = (uint32*)ptr;

    auto len = actual_.getLength();
    for (uint32 i = 0; i < len; i++)
    {
        iptr[i] = actual_.getBlock(i);
    }

    return result;
}


BigInt^ BigInt::FromInt16(int16 x)
{
    return ref new BigInt(BigInteger(x));
}

BigInt^ BigInt::FromUInt16(uint16 x)
{
    return ref new BigInt(BigInteger(x));
}

BigInt^ BigInt::FromInt32(int32 x)
{
    return ref new BigInt(BigInteger(x));
}

BigInt^ BigInt::FromUInt32(uint32 x) 
{
    return ref new BigInt(BigInteger(x));
}

bool BigInt::IsPositive::get()
{
    return actual_.getSign() != -1;
}

uint32 BigInt::ByteLength::get()
{
    return actual_.getLength() * 4;
}

int32 BigInt::CompareTo(BigInt^ other)
{
    auto result = actual_.compareTo(other->actual_);
    if (result == BigInteger::less)
        return -1;
    else if (result == BigInteger::equal)
        return 0;
    else
        return 1;
}

bool BigInt::Equals(BigInt^ other)
{
    return actual_ == other->actual_;
}

BigInt^ BigInt::Add(BigInt^ addend)
{
    auto result = actual_ + addend->actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::Subtract(BigInt^ subtrahend)
{
    auto result = actual_ - subtrahend->actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::Multiply(BigInt^ multiplicand)
{
    auto result = actual_ * multiplicand->actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::Divide(BigInt^ divisor)
{
    auto result = actual_ / divisor->actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::Modulus(BigInt^ divisor)
{
    auto result = actual_ % divisor->actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::Negate()
{
    auto result = -actual_;

    return ref new BigInt(result);
}

BigInt^ BigInt::ModPow(BigInt^ exponent, BigInt^ modulus)
{
    auto result = modexp(actual_, exponent->actual_.getMagnitude(), modulus->actual_.getMagnitude());

    return ref new BigInt(result);
}

BigInt^ BigInt::ModInv(BigInt^ modulus)
{
    try {
        auto result = modinv(actual_, modulus->actual_.getMagnitude());
        return ref new BigInt(result);
    }
    catch (...) {
        throw ref new InvalidArgumentException(L"Value and modulus have a common factor.");
    }
}
