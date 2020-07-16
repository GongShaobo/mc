#pragma once
#ifndef MAP_H
#define MAP_H
#define MAP_SIZE 9
#include <map>
#include <vector>
#include <string>
#include "Chunk.h"
#include"Shader.h"
#include"PerlinNoise.h"
#include"plantGenerator.h"
#include"Camera.h"

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

	const static int sandheight = 23;
	const static int waterheight = 20;

	int chunkSize;//amount of chunks in map

	int currentChunkMinX;
	int currentChunkMaxX;
	int currentChunkMinY;
	int currentChunkMaxY;

	int startPosX;
	int startPosY;

	// �������Ե������ɵ�˽�к�����������һ���ع�Ӧ��Ҫ���
	// �ɼ������б��㷨
	bool isVisible(int index,int x, int y, int z);

	int generateHeight(double x, double y, double interval);
	Block::blockType generateBlockType(int x, int y, int z, int h);
	void generateBlock(int index);

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

	// ��mc��������ת��Ϊchunk�洢���꣬Ȼ���������
	// ���������ʱ����
	void setBlock(int worldPos[], Block::blockType type);//xyz��block�������꣬���÷���
	Block::blockType getBlockType(int x, int y, int z);//xyz��block�������꣬�õ���λ��block����
	int getBlockHeight(int x, int y);//�õ��������ر�Ŀ�����������
	// Ԥ���ӿڣ���û�������
	// ͨ��������ͷ���Ľ����ж�ɾ�����飻û����
	// ͨ��������ͷ���Ľ����ж���ӷ��飻û����
	// ���߿��Ժϲ���һ��
};

#endif 