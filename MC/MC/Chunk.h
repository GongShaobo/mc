#pragma once
#ifndef CHUNK_H
#define CHUNK_H
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 64
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
	int width; //ÿ��Chunk�ĳ���Size 
	int height; //ÿ��Chunk�ĸ߶� 
	//int seed; //������� 
	bool isLoad;//true,loaded; false,not loaded
	
	//float frequency = 0.025;  //����Ƶ�ʣ���������ʱ���õ��� 
	//float amplitude = 1; //�����������������ʱ���õ���
	//void buildChunk();
	Chunk(int x,int y, int width, int height);
	void renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader);

	Block::blockType blocks[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_HEIGHT]; //Chunk������
	bool isRender[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_HEIGHT];
	int visibleHeight[CHUNK_WIDTH][CHUNK_WIDTH]; //������ɵĿɼ��ر�߶� 
	//chunk��map�е����꣺
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