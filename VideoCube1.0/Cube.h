#pragma once

class Cube
{
private:
	int data[4][4][4];
	int rotateData[4][4][4];
	double _piToAngle;
	double _angleToPi;
	double M0;
	double Mx;
	double My;
	double Mt;
	double COSA;
	double COSB;
	double COSR;

	double weightA4;
	double weightB4;
	double weightC4;
	double weightD4;
	double weightA3;
	double weightB3;
	double weightC3;
	double weightD3;

	double h1;
	double h2;
	double p1;
	double p2;
	int threshold;

	double L;
	double L1;
	double L2;
	double L3;
	
	int _numberOfFrame;

	void computeM0();
	void computeMx();
	void computeMy();
	void computeMt();

	void computeCOSA();
	void computeCOSB();
	void computeCOSR();

public:
	
	Cube(void);
	~Cube(void);
	void fillPixel(int planeIndex, int tIndex, int pixel);

	double getM0();

	double getMx();

	double getMy();

	double getMt();

	double getCOSA();

	double getCOSB();

	double getCOSR();

	double getP1();

	double getP2();

	double getH1();

	double getH2();

	int getThreshold();

	double getL();

	void momentPreserving();

	void computeL();

	int cubeAverageF();

	//int computeF(int x, int y, int t);

	int* photoH();

	void choiceL();

	void go();

	double planeIndexToX(int planeIndex);
	double planeIndexToY(int planeIndex);
	int tToTIndex(double rt);
	double tIndexToT(int t);
	int getCubePixel(int planeIndex, int tIndex);
};
