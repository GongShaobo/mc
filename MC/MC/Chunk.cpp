#include"Chunk.h"

int Chunk::generateHeight(double x, double y)
{	
	int small = (PerlinNoise2D(x, y, 0.025, 4) + 1) * 10;
	return small;
}

Block::blockType Chunk::generateBlockType(int x, int y, int z, int h) {
	if (z > h) { //��ǰ����λ�ø���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�� 
		return Block::Air;
	} 
	else if (z == h) { //��ǰ����λ�õ���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�ݵ� 
		return Block::Grass;
	} 
	//��ǰ����λ��С��������ɵĸ߶�ֵ �� ���� genHeight - 5ʱ����ǰ��������Ϊ���� 
	else if (z < h && z > h - 5) { 
		return Block::Soil;
	}  
	else return Block::Stone; //�����������ǰ��������Ϊ��ʯ
}

bool Chunk::isVisible(int x, int y, int z)//block��chunk�е�����
{	//flag==true, render; flag==false, not render
	if (blocks[x][y][z] == Block::Air) {
		return false;
	}
	else {
		bool flag = false;
		Block::blockType type;
		if (x > 0) {
			type = blocks[x - 1][y][z];
			if (type == Block::Air || type == Block::Water) {//adjacent to Air/Water, render
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (x < width-1) {
			type = blocks[x + 1][y][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (y > 0) {
			type = blocks[x][y-1][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (y < width - 1) {
			type = blocks[x][y+1][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (z > 0) {
			type = blocks[x][y][z-1];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		if (z < height-1) {
			type = blocks[x][y][z + 1];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		return flag;
	}
}

Chunk::Chunk(int x, int y, int width, int height):width(width), height(height)
{
	this->x = x;
	this->y = y;
	isLoad = true;
	double radio = 3.0;
	//render a chunk
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			int h = generateHeight(x * radio + i * radio / width, y * radio + j * radio / width); //��ȡ��ǰλ�÷���������ɵĸ߶�ֵ 
			visibleHeight[i][j] = h;//write down random visible height
			for (int k = 0; k < height; ++k) {
				this->blocks[i][j][k] = generateBlockType(i, j, k, h);
			}
		}
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			for (int k = 0; k < height; ++k) {
				this->isRender[i][j][k] = isVisible(i, j, k);
			}
		}
	}
}


void Chunk::renderChunk(glm::mat4 model,unsigned int VAO, Shader* myShader)
{	
	Block::blockType type;
	Block::blockType lasttype = Block::Air;
	for (int k = 0; k < height; k++) {//1-4,x axis,height
		for (int i = 0; i < width; i++) {//z axis
			for (int j = 0; j < width; j++) {//y axis
					if (isRender[i][j][k]) {
						myShader->setMat4("model", glm::value_ptr(model));
						type = blocks[i][j][k];
						if (type != lasttype) {
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(Block::textures[type].Type, Block::textures[type].ID);
							lasttype = type;
						}
						if (type != Block::Water) {
							//��������Ԫ�� 
							glBindVertexArray(VAO);
							glDrawArrays(GL_TRIANGLES, 0, 36);
						}
					}
				model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); //y axis
			}
			model = glm::translate(model, glm::vec3(0.0f, -width * 1.0f, 1.0f)); //z axis
		}
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -width * 1.0f)); //height,x
	}
	model = glm::translate(model, glm::vec3((height) * 1.0f, 0.0f, 0.0f)); //y axis
}