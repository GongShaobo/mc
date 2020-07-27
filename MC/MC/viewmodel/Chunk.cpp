#include"Chunk.h"
#include "map.h"

Chunk::Chunk(int x, int y)
{
	this->x = x;
	this->y = y;
	isLoad = true;
}


void Chunk::renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader)
{//�ص�vec3(0.0f,0.0f,0.0f)���
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
						glBindTexture(Map::textures[type].Type, Map::textures[type].ID);
						lasttype = type;
					}
					//��������Ԫ�� 
					glBindVertexArray(VAO);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); //y axis
			}
			model = glm::translate(model, glm::vec3(0.0f, -width * 1.0f, 1.0f)); //z axis
		}
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -width * 1.0f)); //height,x
	}
	model = glm::translate(model, glm::vec3((height) * 1.0f, 0.0f, 0.0f)); //y axis
}