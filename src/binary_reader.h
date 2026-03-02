#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const uint8_t* buffer;
    size_t size;
    size_t position;
} BinaryReader;

BinaryReader BinaryReader_create(const uint8_t* buffer, size_t size);

uint8_t BinaryReader_readUint8(BinaryReader* reader);
int16_t BinaryReader_readInt16(BinaryReader* reader);
uint16_t BinaryReader_readUint16(BinaryReader* reader);
int32_t BinaryReader_readInt32(BinaryReader* reader);
uint32_t BinaryReader_readUint32(BinaryReader* reader);
float BinaryReader_readFloat32(BinaryReader* reader);
uint64_t BinaryReader_readUint64(BinaryReader* reader);
bool BinaryReader_readBool32(BinaryReader* reader);

// Reads a uint32 absolute file offset and returns a pointer to the null-terminated string at that offset.
// Returns nullptr if the offset is 0.
const char* BinaryReader_readStringPtr(BinaryReader* reader);

// Copies 'count' bytes from the current position into 'dest'.
void BinaryReader_readBytes(BinaryReader* reader, void* dest, size_t count);

void BinaryReader_skip(BinaryReader* reader, size_t bytes);
void BinaryReader_seek(BinaryReader* reader, size_t position);
size_t BinaryReader_getPosition(BinaryReader* reader);
