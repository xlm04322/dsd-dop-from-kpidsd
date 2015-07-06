#pragma once

/* Based on "Direct Stream Digital Interchange File Format, DSDIFF, version 1.5" from Philips */

#include "dff_types.h"
#include "CLargeFile.h"
#include <stack>

struct ChunkStep
{
	uint64_t headerOffset;
	DFFChunkHeader header;
	uint64_t dataOffset;
	uint64_t dataEndOffset;
};

class CDFFFile: public CLargeFile
{
private:
	FRM8Chunk	frm8;
	std::stack<ChunkStep> stack;

	bool CDFFFile::readChunkHeader(DFFChunkHeader& header, ChunkStep& step);


	bool CDFFFile::readFRM8(ChunkStep& step, DFFChunkHeader& hdr);
	bool CDFFFile::readPROP(ChunkStep& step, DFFChunkHeader& hdr);
	bool CDFFFile::readDIIN(ChunkStep& step, DFFChunkHeader& hdr);
public:
	CDFFFile();
	~CDFFFile();

	FRM8Chunk& FRM8() { return frm8; }

	void Reset() { Seek(frm8.dsd.OffsetToData(), NULL, FILE_BEGIN); }
	BOOL Open(LPCSTR cszFileName);
	void Close();

};
