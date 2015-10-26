#pragma once
class BufferHelper
{
public:
    static void* PtrFromIBuffer(Windows::Storage::Streams::IBuffer^ buffer);
};