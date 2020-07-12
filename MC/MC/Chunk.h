#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#include<list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Block.h"

class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	static const int width = 64; //ÿ��Chunk�ĳ���Size 
	static const int height = 3; //ÿ��Chunk�ĸ߶� 
	int seed; //������� 
	float baseHeight = 0; //��С���ɸ߶� 
	bool isLoad;//true,loaded; false,not loaded
	//float frequency = 0.025;  //����Ƶ�ʣ���������ʱ���õ��� 
	//float amplitude = 1; //�����������������ʱ���õ���
	//void buildChunk();
	Chunk();
	void renderChunk();


private:
	int generateHeight(double x, double y, double z);
	Block::blockType generateBlockType(double Pos[3]);
//	BlockType[,,] map; //Chunk������
	//Mesh chunkMesh; //�洢�Ŵ�Chunk�ڵ�����Block��Ϣ 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
};
#endif 