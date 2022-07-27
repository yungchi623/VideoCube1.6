#include "StdAfx.h"
#include "Cube.h"
#include <math.h>
#include <stdlib.h>

Cube::Cube(void)
{
	_piToAngle = 180 / 3.14159;
	_angleToPi = 3.14159 / 180;
	M0 = 0.0;
	Mx = 0.0;
	My = 0.0;
	Mt = 0.0;
	COSA = 0.0;
	COSB = 0.0;
	COSR = 0.0;


	weightA4 = 0.822364184;
	weightB4 = 0.23697052;
	weightC4 = 0.01549212;
	weightD4 = 0.23697052;
	weightA3 = 1.0;
	weightB3 = 0.822364184;
	weightC3 = 0.23697052;
	weightD3 = 0.822364184;
}

Cube::~Cube(void)
{
}

void Cube::fillPixel(int planeIndex, int tIndex, int pixel)
{
	double planeIndexDiv4 = planeIndex / 4.0;
	if(planeIndexDiv4 <= 1.0)
	{
		  data[0][(planeIndex-1) % 4][tIndex] = pixel;
	}
	else if((planeIndexDiv4 > 1.0) && (planeIndexDiv4 <=2.0))
	{
		  data[1][(planeIndex-1) % 4][tIndex] = pixel;
	}
	else if((planeIndexDiv4 > 2.0) && (planeIndexDiv4 <=3.0))
	{
		  data[2][(planeIndex-1) % 4][tIndex] = pixel;
	}
	else if(planeIndexDiv4 > 3.0)
	{
		  data[3][(planeIndex-1) % 4][tIndex] = pixel;
	}
}

double Cube::getM0()
{
      return M0;
}

double Cube::getMx()
{
      return Mx;
}

double Cube::getMy()
{
      return My;
}

double Cube::getMt()
{
      return Mt;
}

double Cube::getCOSA()
{
      return COSA;
}

double Cube::getCOSB()
{
      return COSB;
}

double Cube::getCOSR()
{
      return COSR;
}

double Cube::getP1()
{
      return p1;
}

double Cube::getP2()
{
      return p2;
}

double Cube::getH1()
{
      return h1;
}

double Cube::getH2()
{
      return h2;
}

int Cube::getThreshold()
{
      return threshold;
}

double Cube::getL()
{
      return L;
}

void Cube::momentPreserving()
{
	int cubeWidth = 4;
	int cubeHeight = 4;
	int cubeLength = 4;

	int p;
	int r;
	int g;
	int b;
	int h;

	double m0 = 1.0;
	double m1 = 0.0;
	double m2 = 0.0;
	double m3 = 0.0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				int Temp = data[i][j][k];
				m1 = m1 + Temp;
				Temp *= data[i][j][k];
				m2 = m2 + Temp;
				Temp *= data[i][j][k];
				m3 = m3 + Temp;
			} 
		}
	}
	int CubeSize = (cubeWidth * cubeHeight * cubeLength);
	m1 /= CubeSize;
	m2 /= CubeSize;
	m3 /= CubeSize;

	double cd = (m0 * m2) - pow(m1, 2.0);
	double c0 = (m1 * m3 - pow(m2, 2.0)) / cd;
	double c1 = (m1 * m2 - m0 * m3) / cd;
	double A = c1;
	double B = sqrt(c1 * c1 - 4 * c0);
	double C = -0.5;
	h1 = (A + B) * C;
	h2 = (A - B) * C;
	//h1 = (c1 + sqrt(c1 * c1 - 4 * c0)) * -1 / 2;
	//h2 = (c1 - sqrt(c1 * c1 - 4 * c0)) * -1 / 2;      
	
	double pd = h2 - h1;
	p1 = (h2-m1) / pd;
	p2 = 1-p1;

	int v0 = (int)(p1 * CubeSize);
	int v1 = (int)(p2 * CubeSize);

	int* hist = photoH();
	int pv = 0;
	threshold = 0;

	if(h1<=h2)
	{
		for(int i = 0; i < 256; i++)
		{
			pv += hist[i];
			if(pv >= v0)
			{
				threshold = i;
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < 256; i++)
		{
			pv += hist[i];
			if(pv >= v1)
			{
				threshold = i;
				break;
			}
		}
	}

	if(cd == 0)   //cube is a uniform cube, and h1=h2=cubeAverageF()
	{
		 h1 = cubeAverageF();
		 h2 = cubeAverageF();
	}

}

void Cube::computeL()
{
	double temp1 = (2.0 * p2) - 1;
	double temp2 = acos(temp1);

	temp2 *= _piToAngle;

	double temp3 = (temp2 / 3) + 120;
	temp3 *= _angleToPi;
	L1 = cos(temp3) * 2.0;

	temp3 = (temp2 / 3) + 240;
	temp3 *= _angleToPi;
	L2 = cos(temp3) * 2.0;

	temp3 = (temp2 / 3);
	temp3 *= _angleToPi;
	L3 = cos(temp3) * 2.0;

	choiceL();
}

int Cube::cubeAverageF()
{
	float f = 0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				f += data[i][j][k];
			}
		}
	}

	f /= 64;

	return f;
}

int* Cube::photoH()
{
	int h = 0;
	int histogram[256];

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				h = data[i][j][k];
				histogram[h]++;
			}
		}
	}

	return histogram;
}

void Cube::choiceL()
{
	if((L1 >= -1) && (L1 <= 1))
	{
		L = L1;
	}
	else if((L2 >= -1) && (L2 <= 1))
	{
		L = L2;
	}
	else if((L3 >= -1) && (L3 <= 1))
	{
		L = L3;
	}
}

void Cube::go()
{
	computeM0();
	computeMx();
	computeMy();
	computeMt();

	computeCOSA();
	computeCOSB();
	computeCOSR();
}

void Cube::computeM0()
{
	M0 = 0.0;
	int planeIndex = 0;
	int tIndex = 0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				planeIndex = (i * 4) + j + 1;
				tIndex = k + 1;

				if((tIndex == 1) || (tIndex == 4))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						M0 = M0 + (weightA4 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						M0 = M0 + (weightB4 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						M0 = M0 + (weightC4 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						M0 = M0 + (weightD4 * data[i][j][k]);
				}

				if((tIndex == 2) || (tIndex == 3))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						M0 = M0 + (weightA3 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						M0 = M0 + (weightB3 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						M0 = M0 + (weightC3 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						M0 = M0 + (weightD3 * data[i][j][k]);
				}
			}
		}
	}


	//M0 = M0 / 64;
	//M0 = M0 / 8;
	M0 = M0 / (4 * 3.14159 / 3);
}
       
void Cube::computeMx()
{
	Mx = 0.0;
	int planeIndex = 0;
	int tIndex = 0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				planeIndex = (i * 4) + j + 1;
				tIndex = k + 1;

				if((tIndex == 1) || (tIndex == 4))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						Mx = Mx + (planeIndexToX(planeIndex) * weightA4 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						Mx = Mx + (planeIndexToX(planeIndex) * weightB4 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						Mx = Mx + (planeIndexToX(planeIndex) * weightC4 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						Mx = Mx + (planeIndexToX(planeIndex) * weightD4 * data[i][j][k]);
				}

				if((tIndex == 2) || (tIndex == 3))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						Mx = Mx + (planeIndexToX(planeIndex) * weightA3 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						Mx = Mx + (planeIndexToX(planeIndex) * weightB3 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						Mx = Mx + (planeIndexToX(planeIndex) * weightC3 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						Mx = Mx + (planeIndexToX(planeIndex) * weightD3 * data[i][j][k]);
				}
			}
		}
	}

//Mx = Mx / 64;
//Mx = Mx / 8;
	Mx = Mx / (4 * 3.14159 / 3);

	if(abs(Mx) < 0.000000001)
		Mx = 0;
}
       
void Cube::computeMy()
{
	My = 0.0;
	int planeIndex = 0;
	int tIndex = 0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				planeIndex = (i * 4) + j + 1;
				tIndex = k + 1;

				if((tIndex == 1) || (tIndex == 4))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						My = My + (planeIndexToY(planeIndex) * weightA4 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						My = My + (planeIndexToY(planeIndex) * weightB4 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						My = My + (planeIndexToY(planeIndex) * weightC4 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						My = My + (planeIndexToY(planeIndex) * weightD4 * data[i][j][k]);
				}

				if((tIndex == 2) || (tIndex == 3))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						My = My + (planeIndexToY(planeIndex) * weightA3 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						My = My + (planeIndexToY(planeIndex) * weightB3 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						My = My + (planeIndexToY(planeIndex) * weightC3 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						My = My + (planeIndexToY(planeIndex) * weightD3 * data[i][j][k]);
				}
			}
		}
	}

//My = My / 64;
//My = My / 8;
	My = My / (4 * 3.14159 / 3);

	if(abs(My) < 0.000000001)
		My = 0;
}
       
void Cube::computeMt()
{
	Mt = 0.0;
	int planeIndex = 0;
	int tIndex = 0;

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				planeIndex = (i * 4) + j + 1;
				tIndex = k + 1;

				if((tIndex == 1) || (tIndex == 4))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						Mt = Mt + (tIndexToT(tIndex) * weightA4 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						Mt = Mt + (tIndexToT(tIndex) * weightB4 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						Mt = Mt + (tIndexToT(tIndex) * weightC4 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						Mt = Mt + (tIndexToT(tIndex) * weightD4 * data[i][j][k]);
				}

				if((tIndex == 2) || (tIndex == 3))
				{
					if((planeIndex == 6) || (planeIndex == 7) || (planeIndex == 10) || (planeIndex == 11))
						Mt = Mt + (tIndexToT(tIndex) * weightA3 * data[i][j][k]);

					if((planeIndex == 8) || (planeIndex == 12) || (planeIndex == 5) || (planeIndex == 9))
						Mt = Mt + (tIndexToT(tIndex) * weightB3 * data[i][j][k]);

					if((planeIndex == 1) || (planeIndex == 4) || (planeIndex == 13) || (planeIndex == 16))
						Mt = Mt + (tIndexToT(tIndex) * weightC3 * data[i][j][k]);

					if((planeIndex == 2) || (planeIndex == 3) || (planeIndex == 14) || (planeIndex == 15))
						Mt = Mt + (tIndexToT(tIndex) * weightD3 * data[i][j][k]);
				}
			}
		}
	}

	//Mt = Mt / 64;
	//Mt = Mt / 8;
	Mt = Mt / (4 * 3.14159 / 3);

	if(abs(Mt) < 0.000000001)
	    Mt = 0;
}

void Cube::computeCOSA()
{
	double temp = sqrt(Mx * Mx + My * My + Mt * Mt);

	if(abs(temp) < 0.000000001)
	{
		COSA = 0.0;
	}
	else
	{
		COSA = Mx / temp;
	}
}
       
void Cube::computeCOSB()
{
	double temp = sqrt(Mx * Mx + My * My + Mt * Mt);

	if(abs(temp) < 0.000000001)
	{
		COSB = 0.0;
	}
	else
	{
		COSB = My / temp;
	}
}
       
void Cube::computeCOSR()
{
	double temp = sqrt(Mx * Mx + My * My + Mt * Mt);

	if(abs(temp) < 0.000000001)
	{
		COSR = 0.0;
	}
	else
	{
		COSR = Mt / temp;
	}
}

double Cube::planeIndexToX(int planeIndex)
{
	double x = 0.0;
	double PlaneIndexMod4 = planeIndex % 4;
	if(PlaneIndexMod4 == 0)
	{
		x = 0.75;
	}
	else if(PlaneIndexMod4 == 1)
	{
		x = -0.75;
	}
	else if(PlaneIndexMod4 == 2)
	{
		x = -0.25;
	}
	else if(PlaneIndexMod4 == 3)
	{
		x = 0.25;
	}

	return x;
}

double Cube::planeIndexToY(int planeIndex)
{
	double Y = 0.0;

	if((planeIndex >= 1) && (planeIndex <= 4))
	{
		Y = 0.75;
	}
	else if((planeIndex >= 5) && (planeIndex <= 8))
	{
		Y = 0.25;
	}
	else if((planeIndex >= 9) && (planeIndex <= 12))
	{
		Y = -0.25;
	}
	else if((planeIndex >= 13) && (planeIndex <= 16))
	{
		Y = -0.75;
	}

	return Y;
}

int Cube::tToTIndex(double rt)
{
	int TIndex = 0;

	if(rt < -1.0)
	{
		rt = -1.0;
	}
	if(rt > 1.0)
	{
		rt = 1.0;
	}

	if((rt >= -1.0) && (rt < -0.5))
	{
		TIndex = 1;
	}
	else if((rt >= -0.5) && (rt < 0.0))
	{
		TIndex = 2;
	}
	else if((rt >= 0.0) && (rt <= 0.5))
	{
		TIndex = 3;
	}
	else if((rt > 0.5) && (rt <= 1.0))
	{
		TIndex = 4;
	}

	return TIndex;
}
       
double Cube::tIndexToT(int t)
{
	double T = 0.0;

	if(t == 1)
	{
		T = -0.75;
	}
	else if(t == 2)
	{
		T = -0.25;
	}
	else if(t == 3)
	{
		T = 0.25;
	}
	else if(t == 4)
	{
		T = 0.75;
	}

	return T;
}

int Cube::getCubePixel(int planeIndex, int tIndex)
{
	int pixel = 0;
	double PlaneIndexDiv4 = planeIndex/4.0;
	if(PlaneIndexDiv4 <= 1.0)
	{
		pixel = data[0][(planeIndex-1) % 4][tIndex-1];
	}
	else if((PlaneIndexDiv4 > 1.0) && (PlaneIndexDiv4 <=2.0))
	{
		pixel = data[1][(planeIndex-1) % 4][tIndex-1];
	}
	else if((PlaneIndexDiv4 > 2.0) && (PlaneIndexDiv4 <=3.0))
	{
		pixel = data[2][(planeIndex-1) % 4][tIndex-1];
	}
	else if(PlaneIndexDiv4 > 3.0)
	{
		pixel = data[3][(planeIndex-1) % 4][tIndex-1];
	}

	return pixel;
}