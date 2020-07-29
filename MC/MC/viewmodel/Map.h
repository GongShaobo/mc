#pragma once
#ifndef MAP_H
#define MAP_H
#define MAP_SIZE 9
#include <map>
#include <vector>
#include <string>
//#include "../view/particleGenerator.h"
#include "../view/resource_manager.h"
#include "Chunk.h"
#include "../view/Shader.h"
#include "../model/PerlinNoise.h"
#include "../model/plantGenerator.h"
#include "../model/chunkGenerator.h"
#include "../view/Camera.h"

/*
	��������ϵͳ��
	����MC����ͳһ��һ����ά���꣨��openGL���������겻ͬ
	����ÿ������Ϊһ������������ֵ��

	block�Ƿ����࣬����������صĶ�������ԣ��Լ��ͷ���������صĲ��ʣ���ʱ����ʵ��������

	chunk�ǵ�ͼ�洢����Ⱦ�Ļ�����λ��

	Map����Ƶ�ͼ���ɣ����������chunk�洢�����ת����
	����Ӧ��Ҫ��������һ����ͼ������Ĳ��֣�����ࣩ

	openGL����������Ķ�Ӧ��һ������ 1:1
	y ��Ӧ y
	z ��Ӧ x

	ʹ����������ڵ�λ�����ж���Ҫ���صķ��飬�����������Χ��Ӧ��13�鷽�飨�ݶ���

	������Ҫʹ��openGL�Ļ�������ʵ�ּ���

 */

class Map
{
private:
	std::vector<Chunk*> chunks;

	unsigned int VBO, VAO;
	Shader* myShader;
	Camera* myCamera;

	int chunkSize;//amount of chunks in map

	int currentChunkMinX;
	int currentChunkMaxX;
	int currentChunkMinY;
	int currentChunkMaxY;

	int startPosX;
	int startPosY;


	// ����ת��ϵ��

	// ͨ��block�����������ȡ chunk �±�
	int getBlockIndex(int x, int y);

public:
	Map(Camera* myCamera);
	~Map();

	// ��������ˢ������Ҫ���õ�Ψһһ��������������Ⱦ��ͼ
	void renderMap(operateBlock* changeBlock);

	// ��������ı�λ�û��߷���ש������
	void updateMap();
	void limitCamera();//������������ᴩ͸���

	// ��������
	static int loadTextures();
	static std::vector<Texture> textures;
private:
	// ��mc��������ת��Ϊchunk�洢���꣬Ȼ���������
	// ���������ʱ����
	void setBlock(int worldPos[], Block::blockType type);//xyz��block�������꣬���÷���
	Block::blockType getBlockType(int x, int y, int z);//xyz��block�������꣬�õ���λ��block����
	int getBlockHeight(int x, int y);//�õ��������ر�Ŀ�����������
	// Ԥ���ӿڣ���û�������
	// ͨ��������ͷ���Ľ����ж�ɾ�����飻û����
	// ͨ��������ͷ���Ľ����ж���ӷ��飻û����
	// ���߿��Ժϲ���һ��

	const static float vertices[];
	const static size_t vsize;
};

#endif 