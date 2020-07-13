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
#include"PerlinNoise.h"
#include "Shader.h"

class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	static const int width = 16; //ÿ��Chunk�ĳ���Size 
	static const int height = 64; //ÿ��Chunk�ĸ߶� 
	int seed; //������� 
	float baseHeight = 0; //��С���ɸ߶� 
	bool isLoad;//true,loaded; false,not loaded
	
	//float frequency = 0.025;  //����Ƶ�ʣ���������ʱ���õ��� 
	//float amplitude = 1; //�����������������ʱ���õ���
	//void buildChunk();
	Chunk(int x,int y);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[width][width][height]; //Chunk������
	bool isRender[width][width][height];

	int x;
	int y;

private:
	int generateHeight(double x, double y);
	Block::blockType generateBlockType(int x, int y, int z, int h);
	//BlockType[,,] map; 
	//Mesh chunkMesh; //�洢�Ŵ�Chunk�ڵ�����Block��Ϣ 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
	bool isVisible(int x, int y, int z);
};
#endif 