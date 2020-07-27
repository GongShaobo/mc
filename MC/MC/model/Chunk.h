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
#include "PerlinNoise.h"
#include "../view/Shader.h"

class Chunk {
public:
	//List<Chunk> chunks = new List<Chunk>(); 
	const static int width = 32; //ÿ��Chunk�ĳ���Size 
	const static int height = 64; //ÿ��Chunk�ĸ߶� 
	//int seed; //������� 
	bool isLoad;//true,loaded; false,not loaded

	//float frequency = 0.025;  //����Ƶ�ʣ���������ʱ���õ��� 
	//float amplitude = 1; //�����������������ʱ���õ���
	//void buildChunk();
	Chunk(int x, int y);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[width][width][height]; //Chunk������
	bool isRender[width][width][height];
	int visibleHeight[width + 2][width + 2]; //������ɵĿɼ��ر�߶� 
	//chunk��map�е����꣺
	int x;
	int y;

private:
	//BlockType[,,] map; 
	//Mesh chunkMesh; //�洢�Ŵ�Chunk�ڵ�����Block��Ϣ 
	//MeshRenderer meshRenderer; 
	//MeshCollider meshCollider; 
	//MeshFilter meshFilter; 
};
#endif 