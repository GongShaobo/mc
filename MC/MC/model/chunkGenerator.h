#pragma once
#ifndef CHUNK_GE_
#define CHUNK_GE_
#include "../viewmodel/Chunk.h"
#include "plantGenerator.h"
#include "Block.h"

class chunkGenerator
{
private:
	// �������Ե������ɵ�˽�к�����������һ���ع�Ӧ��Ҫ���
	// �ɼ������б��㷨
	static bool isVisible(Chunk& chunk, int x, int y, int z);

	static int generateHeight(double x, double y, double interval);
	static Block::blockType generateBlockType(int x, int y, int z, int h);

	const static int sandheight = 23;
	const static int waterheight = 20;

	static int seed;

public:
	static void generateBlock(Chunk& chunk);
};

#endif