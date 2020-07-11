#include"Chunk.h"
#include"PerlinNoise.h"
int Chunk::generateHeight(double Pos[3]) { //��������ӣ������Ƶ�ʣ�Ӧ�������ǵ������������ 
	return PerlinNoise(Pos[0], Pos[1], Pos[2]) + baseHeight;
} 
blockType Chunk::generateBlockType(double Pos[3]) { 
	if (Pos[1] >= height) { //y�����Ƿ���Chunk�� 
		return Air; 
	} 
	float genHeight = generateHeight(Pos); //��ȡ��ǰλ�÷���������ɵĸ߶�ֵ 
	if (Pos[1] > genHeight) { //��ǰ����λ�ø���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�� 
		return Air; 
	} 
	else if (Pos[1] == genHeight) { //��ǰ����λ�õ���������ɵĸ߶�ֵʱ����ǰ��������Ϊ�ݵ� 
		return Grass; 
	} 
	//��ǰ����λ��С��������ɵĸ߶�ֵ �� ���� genHeight - 5ʱ����ǰ��������Ϊ���� 
	else if (Pos[1] < genHeight && Pos[1] > genHeight - 5) { 
		return Soil; 
	}  
	else return Stone; //�����������ǰ��������Ϊ��ʯ
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