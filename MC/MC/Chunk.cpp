#include"Chunk.h"

int Chunk::generateHeight(double x, double y, double z) { //��������ӣ������Ƶ�ʣ�Ӧ�������ǵ������������ 
	return PerlinNoise3D(x,y,z) + baseHeight;
} 
Block::blockType Chunk::generateBlockType(double Pos[3]) {
	if (Pos[1] >= height) { //y�����Ƿ���Chunk�� 
		return Block::Air;
	} 
	float genHeight = generateHeight(Pos[0],Pos[1],Pos[2]); //��ȡ��ǰλ�÷���������ɵĸ߶�ֵ 
	if (Pos[1] > genHeight) { //��ǰ����λ�ø���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�� 
		return Block::Air;
	} 
	else if (Pos[1] == genHeight) { //��ǰ����λ�õ���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�ݵ� 
		return Block::Grass;
	} 
	//��ǰ����λ��С��������ɵĸ߶�ֵ �� ���� genHeight - 5ʱ����ǰ��������Ϊ���� 
	else if (Pos[1] < genHeight && Pos[1] > genHeight - 5) { 
		return Block::Soil;
	}  
	else return Block::Stone; //�����������ǰ��������Ϊ��ʯ
}

Chunk::Chunk()
{

}

void Chunk::renderChunk(glm::mat4 model,unsigned int VAO, Shader* myShader)
{
	int z = 0, x = 0, y = 0;//block position in chunk	

	for (int i = 0; i < width; i++) {//z axis
		for (int j = 0; j < width; j++) {//y axis
			z = (int)((PerlinNoise2D(x * 0.3, y * 0.3) + 1) * 10);
			for (int k = 0; k < z + baseHeight; k++) {//1-4,x axis,height
				/*if (k == 0 || k == x+chunk.baseHeight || j == 0 || i == chunk.width) {
					glCullFace(GL_BACK);
				}
				else glCullFace(GL_FRONT_AND_BACK);*/
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f)); //height,x
				myShader->setMat4("model", glm::value_ptr(model));
			}
			model = glm::translate(model, glm::vec3((z + baseHeight) * 1.0f, 1.0f, 0.0f)); //y axis
			x++;
		}
		model = glm::translate(model, glm::vec3(0.0f, -width * 1.0f, 1.0f)); //z axis
		y++;
		x -= width;
	}
}

int Chunk::generateChunk(double x, double y)
{
	return 0;
}

/*void Chunk::buildChunk() {
	chunkMesh = new Mesh(); 
	List<Vector3> verts = new List<Vector3>(); 
	List<Vector2> uvs = new List<Vector2>(); 
	List<int> tris = new List<int>(); //����chunk, �������е�ÿһ��Block 
	for (int x = 0; x < width; x ) { 
		for (int y = 0; y < height; y ) { 
			for (int z = 0; z < width; z ) { 
				buildBlock(x, y, z, verts, uvs, tris); 
			} 
		} 
	} 
	chunkMesh.vertices = verts.ToArray(); 
	chunkMesh.uv = uvs.ToArray(); 
	chunkMesh.triangles = tris.ToArray(); 
	chunkMesh.RecalculateBounds(); 
	chunkMesh.RecalculateNormals(); 
	meshFilter.mesh = chunkMesh; 
	meshCollider.sharedMesh = chunkMesh; 
} */