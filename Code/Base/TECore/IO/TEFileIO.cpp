#include <TEFileIO.h>
#include <assert.h>
#include <cstring>
#include <fstream>

TE::IO::FileIO::~FileIO() {}

void TE::IO::WriteU32ToU8Vector(U32 u32val, std::vector<U8> &data) {
    data.resize(data.size() + 4);

    memcpy(&data[0], &u32val, sizeof(U32));
}

void TE::IO::ReadU32FromU8Array(U32 &u32val, const U8 *data) { memcpy(&u32val, data, sizeof(U32)); }
