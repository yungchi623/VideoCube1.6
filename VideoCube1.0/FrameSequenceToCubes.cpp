#include "StdAfx.h"
#include "FrameSequenceToCubes.h"

FrameSequenceToCubes::FrameSequenceToCubes(int numberOfFrame, int height, int width)
{
	_numberOfFrame = numberOfFrame;
	_height = height;
	_width = width;

	// 初始化Frame暫存器
	_frameInfo = new FrameInfo[_numberOfFrame];
	for(int i = 0, Length = _height * _width; i < numberOfFrame; i++)
	{
		_frameInfo[i].R = new double[Length];
		_frameInfo[i].G = new double[Length];
		_frameInfo[i].B = new double[Length];
		_frameInfo[i].Gray = new double[Length];
	}
	//

	// 初始化Cube暫存器
	_numberOfCube = (_width/_numberOfFrame)*(_height/_numberOfFrame);
	_cubeInfo = new CubeInfo[_numberOfCube];
}

FrameSequenceToCubes::~FrameSequenceToCubes(void)
{
}

void FrameSequenceToCubes::Transform(IplImage* frames[], int t)
{
	int debug = 0;
	// 儲存frame資訊至_frameInfo
	for(int i = 0; i < _numberOfFrame; i++)
	{
		for(int c = 0; c < _height; c++)
		{
			for(int r = 0; r < frames[i]->widthStep; r += 3)
			{
				uchar B = frames[i]->imageData[c * frames[i]->widthStep + r];
				uchar G = frames[i]->imageData[c * frames[i]->widthStep + r + 1];
				uchar R = frames[i]->imageData[c * frames[i]->widthStep + r + 2];
				
				int loc = c * _width + (r / 3);
				
				if(loc >=  _height * _width)
				{
					debug++;
					continue;
				}
				_frameInfo[i].R[loc] = R;
				_frameInfo[i].G[loc] = G;
				_frameInfo[i].B[loc] = B;
				_frameInfo[i].Gray[loc] = 0.299 * R + 0.587 * G + 0.114 * B;
				//_frameInfo[i].Gray[loc] = (R + G+ B)/3;

			}
		}
	}
	// END // 儲存frame資訊至_frameInfo
	
	// 儲存 Cube資訊
	int planeIndex = 0;
	int Next = 0;
	 debug = 0;
	 int ModHeight = _height-_height%4;
	 int ModWidth = _width-_width%4;
	for(int i = 0; i < ModHeight; i += _numberOfFrame)//46
	{
		for(int j = 0; j < ModWidth; j += _numberOfFrame)//
		{
			double AverageGrayValue = 0;
			for(int m = 0; m < _numberOfFrame; m++)
			{
				for(int n = 0; n < _numberOfFrame; n++)
				{
					int temp2 = ((i + m)* _width) + (j + n);
				             	     
					if(temp2 >=  _height * _width)
					{
						debug++;
						continue;
					}
				    planeIndex = (m * 4) + n + 1;
			        
					for(int f = 0; f < _numberOfFrame; f++)
					{
						AverageGrayValue += _frameInfo[f].Gray[temp2];
						_cube.fillPixel(planeIndex, f, _frameInfo[f].Gray[temp2]);
					}
				}
		     }
		     AverageGrayValue /= 64;       
		     _cube.go();
			 double COSA = _cube.getCOSA();
			 double COSB = _cube.getCOSB();
			 double COSR = _cube.getCOSR();
			 int threshold = 0;
			 if(abs(COSA) < threshold)
				  COSA = 0.0;
			 if(abs(COSB) < threshold)
				  COSB = 0.0;

			 if(abs(COSR) < threshold)
				  COSR = 0.0;
       	    
             _cube.momentPreserving();
             _cube.computeL();
             double L = _cube.getL();
            
             if(abs(L) < threshold)
                  L = 0.0;
			 double H1 = _cube.getH1();
			 double H2 = _cube.getH2();

			 _cubeInfo[Next].COSA = COSA;
			 _cubeInfo[Next].COSB = COSB;
			 _cubeInfo[Next].COSR = COSR;
			 _cubeInfo[Next].L = L;
			 _cubeInfo[Next].H1 = H1;
			 _cubeInfo[Next].H2 = H2;
			 _cubeInfo[Next].IndexHeight = i;
			 _cubeInfo[Next].IndexWidth = j;
			 _cubeInfo[Next].IndexTime = t;
			 _cubeInfo[Next].M0 = _cube.getM0();
			 _cubeInfo[Next].MX = _cube.getMx();
			 _cubeInfo[Next].MY = _cube.getMy();
			 _cubeInfo[Next].MT = _cube.getMt();

			 _cubeInfo[Next].AverageGrayValue = AverageGrayValue;
			 if(AverageGrayValue == 0)
			 {
				 int Stop = 0;
				 Stop = 1;
			 }
			 _cubeInfo[Next].CubeGradient = (H1-H2) / AverageGrayValue;
			 Next++;
			 
		} // END for(int j = 0; j < _width; j += 4)
	} // END for(int i = 0; i < _height; i += 4)
}

void FrameSequenceToCubes::Decode()
{
	for(int i = 0; i < _numberOfCube; i++)
	{
		double COSA = _cubeInfo[i].COSA;
		double COSB = _cubeInfo[i].COSB;
        double COSR = _cubeInfo[i].COSR;
        int h1 = _cubeInfo[i].H1;
        int h2 = _cubeInfo[i].H2;
		double L = _cubeInfo[i].L;
		Cube cubeGray = decoding(COSA, COSB, COSR, h1, h2, L);
		int m = _cubeInfo[i].IndexHeight;
		int n = _cubeInfo[i].IndexWidth;
		int iw = _width;
		int planeIndex = 0;
		for(int p = 0; p < 4; p++)
        {
			for(int q = 0; q < 4; q++)
            {
				planeIndex = (p * 4) + q + 1;

				int tempGray1 = cubeGray.getCubePixel(planeIndex, 1);
				int tempGray2 = cubeGray.getCubePixel(planeIndex, 2);
				int tempGray3 = cubeGray.getCubePixel(planeIndex, 3);
				int tempGray4 = cubeGray.getCubePixel(planeIndex, 4);
				
				int temp = ((m + p) * iw) + (n + q);
				
				_frameInfo[0].Gray[temp] = tempGray1;
				_frameInfo[1].Gray[temp] = tempGray2;
				_frameInfo[2].Gray[temp] = tempGray3;
				_frameInfo[3].Gray[temp] = tempGray4;
            }
        }
	}
	img[0] = pixelsToImage(_frameInfo[0].Gray, _width, _height);
	img[1] = pixelsToImage(_frameInfo[1].Gray, _width, _height);
	img[2] = pixelsToImage(_frameInfo[2].Gray, _width, _height);
	img[3] = pixelsToImage(_frameInfo[3].Gray, _width, _height);
}

Cube FrameSequenceToCubes::decoding(double COSA, double COSB, double COSR, int h1, int h2, double L)
{
      Cube reCube;
      
      double temp = sqrt(pow((double)COSA, 2.0) + pow((double)COSB, 2.0) + pow((double)COSR, 2.0));
      if(abs(temp) < 0.000000001)   //Cube no edge
      {
      	      int pixelF = h1;
      	      
      	      int planeIndex = 0;
              int tIndex = 0;
      	      for(int k=0;k<4;k++)
              {
      	              for(int i=0;i<4;i++)
      	              {
      	      	              for(int j=0;j<4;j++)
      	      	              {
      	                              planeIndex = (i*4)+j+1;
      	      	      	              tIndex = k+1;
      	      	      	              
      	      	      	              reCube.fillPixel(planeIndex, tIndex, pixelF);
      	      	      	      }
      	      	      }
      	      }
      }
      else
      {
              int pixelH1 = h1;
              int pixelH2 = h2;
              
              
              
              int planeIndex = 0;
              int tIndex = 0;
              for(int k=0;k<4;k++)
              {
      	              for(int i=0;i<4;i++)
      	              {
      	      	              for(int j=0;j<4;j++)
      	      	              {
      	      	      	              planeIndex = (i*4)+j+1;
      	      	      	              tIndex = k+1;
      	      	      	      
      	      	      	              double temp1 = (COSA * reCube.planeIndexToX(planeIndex)) + (COSB * reCube.planeIndexToY(planeIndex)) + (COSR * reCube.tIndexToT(tIndex)) - L;
      	      	      	      
                                      if(temp1 < 0)
                                      {
                              	             reCube.fillPixel(planeIndex, tIndex, pixelH1);
                                      }
                                      else
                                      {
                                             reCube.fillPixel(planeIndex, tIndex, pixelH2);
                                      }
                              }
                      }
              }
      }
      
      return reCube;
}


IplImage* FrameSequenceToCubes::pixelsToImage(double* pixels, int iw, int ih)
{
	//Canvas can = new Canvas();
	CvSize size =cvSize(iw,ih);
	IplImage* ig = cvCreateImage(size,8,3);

	for(int c=0;c<ig->height;c++)
	{
		for(int r=0;r<ig->widthStep;r=r+3)
		{
			ig->imageData[c*ig->widthStep+r] = (pixels[c * iw + (r/3)]);
			ig->imageData[c*ig->widthStep+r+1] = (pixels[c * iw + (r/3)]);
			ig->imageData[c*ig->widthStep+r+2] = (pixels[c * iw + (r/3)]);
		}
	}
	ig->origin = 1;
	return ig;
}

CubeInfo* FrameSequenceToCubes::GetCubeInfo()
{
	return _cubeInfo;
}

int FrameSequenceToCubes::GetNumberOfCubeInfo()
{
	return _numberOfCube;
}

double* FrameSequenceToCubes::GetCubeGradient()
{
	double* RetureGradients = new double[_numberOfCube];
	for(int i = 0; i < _numberOfCube; i++)
		RetureGradients[i] = _cubeInfo[i].CubeGradient;
	return RetureGradients;
}

void FrameSequenceToCubes::ReleaseBuffer()
{
	for(int i = 0; i < _numberOfFrame; i++)
	{
		delete _frameInfo[i].R;
		delete _frameInfo[i].G;
		delete _frameInfo[i].B;
		delete _frameInfo[i].Gray;
	}
	delete _frameInfo;
	delete _cubeInfo;
	_frameInfo = NULL;
	_cubeInfo = NULL;
}