#include "chunkGenerator.h"

int chunkGenerator::seed = 34627;

int chunkGenerator::generateHeight(double x, double y, double interval)
{
	double small = PNoiseSmoth2D(x, y, 0.025, 4, interval) * 24 + 24;
	double large = PNoiseSmoth2D(-x, -y, 0.025, 2, interval) / 2 + 1;
	int h = (int)(small * large) + 2;
	//std::cout << h <<std:: endl;
	return h > waterheight ? h : waterheight;
}

Block::blockType chunkGenerator::generateBlockType(int x, int y, int z, int h) {
	if (z > h) { //��ǰ����λ�ø���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�� 
		return Block::Air;
	}
	if (h > sandheight) {
		if (z == h) { //��ǰ����λ�õ���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�ݵ� 
			return Block::Grass;
		}
		//��ǰ����λ��С��������ɵĸ߶�ֵ �� ���� genHeight - 5ʱ����ǰ��������Ϊ���� 
		if (z < h && z > h - 5) {
			return Block::Soil;
		}
		else return Block::Stone; //�����������ǰ��������Ϊ��ʯ
	}
	else if (h > waterheight) {
		if (z <= h && z > h - 5) {
			return Block::Sand;
		}
		else return Block::Stone;
	}
	else {
		if (z <= h && z > h - 5) {
			return Block::Water;
		}
		else return Block::Sand;
	}
}

void chunkGenerator::generateBlock(Chunk& chunk)
{
	//render a chunk
	// ���ɸ߶�
	for (int i = -1; i < Chunk::width + 1; ++i) {
		double radio = 1.0;
		for (int j = -1; j < Chunk::width + 1; ++j) {
			int h = generateHeight(chunk.x * radio + i * radio / Chunk::width, chunk.y * radio + j * radio / Chunk::width, 1.0 * radio / Chunk::width); //��ȡ��ǰλ�÷���������ɵĸ߶�ֵ 
			chunk.visibleHeight[i + 1][j + 1] = h;//write down random visible height
		}
	}
	// ���ɻ�����������
	for (int i = 0; i < Chunk::width; ++i) {
		for (int j = 0; j < Chunk::width; ++j) {
			for (int k = 0; k < Chunk::height; ++k) {
				chunk.blocks[i][j][k] = generateBlockType(i, j, k, chunk.visibleHeight[i + 1][j + 1]);
			}
		}
	}
	// �ɼ��б�
	for (int i = 0; i < Chunk::width; ++i) {
		double radio = 3;
		for (int j = 0; j < Chunk::width; ++j) {
			for (int k = 0; k < Chunk::height; ++k) {
				chunk.isRender[i][j][k] = false;
				if (k <= chunk.visibleHeight[i + 1][j + 1]) {
					chunk.isRender[i][j][k] = isVisible(chunk, i, j, k);
				}
			}
		}
	}

	// �����ƶ�
	for (int i = 0; i < Chunk::width; ++i) {
		double radio = 3;
		for (int j = 0; j < Chunk::width; ++j) {
			if (PerlinNoise2D(chunk.x * radio + i * radio / Chunk::width, chunk.y * radio + j * radio / Chunk::width, 0.5, 1) > 0.2) {
				chunk.blocks[i][j][Chunk::height - 1] = Block::Cloud;
				chunk.isRender[i][j][Chunk::height - 1] = true;
			}
		}
	}

	// ���ɻ�����ľ
	for (int i = 0; i < Chunk::width; ++i) {
		for (int j = 0; j < Chunk::width; ++j) {
			if (chunk.visibleHeight[i + 1][j + 1] > sandheight) {
				if (PerlinNoise2D(chunk.x * Chunk::width + i, chunk.y * Chunk::width + j, 2, 1) > 0.47) {
					makePalmTree(chunk, i * j + seed, i, j, chunk.visibleHeight[i + 1][j + 1]);
				}
			}
			else if (chunk.visibleHeight[i + 1][j + 1] > waterheight) {
				if (PerlinNoise2D(chunk.x * Chunk::width + i, chunk.y * Chunk::width + j, 2, 1) > 0.45) {
					makeCactus(chunk, i * j + seed, i, j, chunk.visibleHeight[i + 1][j + 1]);
				}
			}
		}
	}
	seed += 1;
}

bool chunkGenerator::isVisible(Chunk& chunk, int x, int y, int z)       //block��chunk�е�����
{	//flag==true, render; flag==false, not render
	if (chunk.blocks[x][y][z] == Block::Air) {
		return false;
	}
	else {
		bool flag = false;
		if (z >= chunk.visibleHeight[x + 1][y + 1]) {
			flag = true;
		}
		if (z > chunk.visibleHeight[x][y + 1]) {
			flag = true;
		}
		if (z > chunk.visibleHeight[x + 1][y]) {
			flag = true;
		}
		if (z >= chunk.visibleHeight[x + 2][y + 1]) {
			flag = true;
		}
		if (z >= chunk.visibleHeight[x + 1][y + 2]) {
			flag = true;
		}
		return flag;
	}
}