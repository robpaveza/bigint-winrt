#include "pch.h"
#include "BufferHelper.h"
#include <robuffer.h>
#include <wrl.h>
#include <windows.storage.streams.h>

using namespace Microsoft::WRL;
using namespace Windows::Storage::Streams;

void* BufferHelper::PtrFromIBuffer(Windows::Storage::Streams::IBuffer^ buf)
{
    if (buf == nullptr)
        throw ref new Platform::InvalidArgumentException(L"buf");

    auto pBuf = reinterpret_cast<ABI::Windows::Storage::Streams::IBuffer*>(buf);
    ComPtr<IBufferByteAccess> pBBA;
    HRESULT hr = pBuf->QueryInterface(__uuidof(Windows::Storage::Streams::IBufferByteAccess), &pBBA);
    if (FAILED(hr))
        throw ref new Platform::Exception(hr);
    byte* result;
    hr = pBBA->Buffer(&result);
    if (FAILED(hr))
        throw ref new Platform::Exception(hr);

    return (void*)result;
}