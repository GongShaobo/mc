#pragma once
#ifndef PERLIN_H
#define PERLIN_H

double PerlinNoise3D(double x, double y, double z);
double PerlinNoise2D(double x, double y,double persistence, int Number_Of_Octaves);
double fade(double t);//ƽ��
double lerp(double t, double a, double b);//��ֵ
double grad(int hash, double x, double y, double z);//�ݶ�
void prepare();
#endif // !PERLIN_H
