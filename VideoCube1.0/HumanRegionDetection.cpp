#include "StdAfx.h"
#include "HumanRegionDetection.h"


HumanRegionDetection::HumanRegionDetection(void)
{

}

HumanRegionDetection::~HumanRegionDetection(void)
{
}

void HumanRegionDetection::SaveVideo(char *Path,char* FileName)
{
	char AviFileName[300];
	sprintf(AviFileName,"%s\\%s",Path,FileName);
	CvCapture *capture;
    IplImage *frame;

   
    cvNamedWindow("Webcam",0);

    CvVideoWriter *writer;
   
    CvSize AviSize = cvSize(_width,_height);
    int AviColor = 1;
    writer=cvCreateVideoWriter(AviFileName,_AviForamt,_FPS,AviSize,AviColor);

	for(int f = 0 ; f < _numberOfFrame; f++)
	{
        cvWriteFrame(writer,_subFrames[f]);
        cvShowImage("Webcam",_subFrames[f]);
        printf("%d\n",f);
        cvWaitKey(27);
    }

    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);
    cvDestroyWindow("Webcam");

}

void HumanRegionDetection::ComputeHumanRegion(char *FileName)
{
	sprintf(_videoFileName,"%s",FileName);
	CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_frames = new IplImage*[_numberOfFrame];
	_subFrames = new IplImage*[_numberOfFrame];
	IplImage* tempFrames;
	

	for(int f = 0 ; f < _numberOfFrame; f++)
	{
			_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
			//_frames[f]->origin = 1;
			tempFrames = cvQueryFrame(Capture);
			cvCopy(tempFrames, _frames[f]);
			//cvNamedWindow ("src", 1);
			//cvShowImage ("src", _frames[f]);
		   // cvWaitKey(27);

	}
	cvReleaseCapture(&Capture);
	//RotationVideo(30,_frames,_subFrames);
	//AddNoise(_frames,_subFrames);
	//ReSize(2.0, _frames, _subFrames);

}
void HumanRegionDetection::AddNoise(char *FileName)
{
	//IplImage** _subFrames;

	sprintf(_videoFileName,"%s",FileName);
	CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_frames = new IplImage*[_numberOfFrame];
	_subFrames = new IplImage*[_numberOfFrame];
	IplImage* tempFrames;
	_FPS =cvGetCaptureProperty(Capture,CV_CAP_PROP_FPS);
	_AviForamt = cvGetCaptureProperty(Capture,CV_CAP_PROP_FOURCC);
	

	for(int f = 0 ; f < _numberOfFrame; f++)
	{
			_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
			//_frames[f]->origin = 1;
			tempFrames = cvQueryFrame(Capture);
			cvCopy(tempFrames, _frames[f]);
			//cvNamedWindow ("src", 1);
			//cvShowImage ("src", _frames[f]);
		   // cvWaitKey(27);

	}
	cvReleaseCapture(&Capture);

	for(int f = 0 ; f < _numberOfFrame; f++)
	{

		_subFrames[f] = cvCreateImage(cvSize(_frames[0]->width,_frames[0]->height),IPL_DEPTH_8U,3);
		_subFrames[f]=cvCloneImage(_frames[f]);
		CvRNG rng;
		rng = cvRNG(cvGetTickCount());

		double IterFactor=0.1;

		cvRandShuffle(_subFrames[f],&rng,IterFactor);

		cvNamedWindow("Bicycle",1);
		cvShowImage("Bicycle",_frames[f]);
		cvNamedWindow("Bicycle Rand Shuffle",1);
		cvShowImage("Bicycle Rand Shuffle",_subFrames[f]);
		cvWaitKey(27);	
		
	}
	//return _subFrames;

}
void HumanRegionDetection::ReSize(double scale,char *FileName)
{

	sprintf(_videoFileName,"%s",FileName);
	CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_frames = new IplImage*[_numberOfFrame];
	_subFrames = new IplImage*[_numberOfFrame];
	IplImage* tempFrames;
	_FPS =cvGetCaptureProperty(Capture,CV_CAP_PROP_FPS);
	_AviForamt = cvGetCaptureProperty(Capture,CV_CAP_PROP_FOURCC);
	

	for(int f = 0 ; f < _numberOfFrame; f++)
	{
			_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
			//_frames[f]->origin = 1;
			tempFrames = cvQueryFrame(Capture);
			cvCopy(tempFrames, _frames[f]);
			//cvNamedWindow ("src", 1);
			//cvShowImage ("src", _frames[f]);
		   // cvWaitKey(27);

	}
	cvReleaseCapture(&Capture);

	//IplImage** _subFrames;
	CvSize dst_cvsize;			//目標圖像尺寸
	dst_cvsize.width = _frames[0]->width * scale;		//目標圖像的寬為源圖象寬的scale倍
	dst_cvsize.height = _frames[0]->height * scale;	//目標圖像的高為源圖象高的scale倍


	for(int f = 0 ; f < _numberOfFrame; f++)
	{
		//_subFrames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
	 
		_subFrames[f] = cvCreateImage( dst_cvsize, IPL_DEPTH_8U, 3);	//構造目標圖象
		cvResize(_frames[f], _subFrames[f], CV_INTER_LINEAR);	//縮放源圖像到目標圖像
	 
		cvNamedWindow( "src",   CV_WINDOW_AUTOSIZE );	//創建用於顯示源圖像的視窗
		cvNamedWindow( "dst",   CV_WINDOW_AUTOSIZE );	//創建用於顯示目標圖像的視窗
	 
		cvShowImage( "src", _frames[f] );		//顯示源圖像
		cvShowImage( "dst", _subFrames[f]);		//顯示目標圖像
	 
		cvWaitKey(27);		//等待用戶響應
	 
		//cvDestroyWindow( "src" );	//銷毀視窗“src”
		//cvDestroyWindow( "dst" );	//銷毀視窗“dst”
		
	}

	//return _subFrames;
}
void HumanRegionDetection::RotationVideo(int RotationAngle,char *FileName)
{

	sprintf(_videoFileName,"%s",FileName);
	CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_frames = new IplImage*[_numberOfFrame];
	_subFrames = new IplImage*[_numberOfFrame];
	IplImage* tempFrames;
	_FPS =cvGetCaptureProperty(Capture,CV_CAP_PROP_FPS);
	_AviForamt = cvGetCaptureProperty(Capture,CV_CAP_PROP_FOURCC);
	

	for(int f = 0 ; f < _numberOfFrame; f++)
	{
			_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
			//_frames[f]->origin = 1;
			tempFrames = cvQueryFrame(Capture);
			cvCopy(tempFrames, _frames[f]);
			//cvNamedWindow ("src", 1);
			//cvShowImage ("src", _frames[f]);
		   // cvWaitKey(27);

	}
	cvReleaseCapture(&Capture);
	
	//IplImage** _subFrames;
	 int delta = 1;
     int angle = RotationAngle;
     int opt = 0;		// 1： 旋轉加縮放
      // 0:  僅僅旋轉
     double factor;

	//double angle = 180*RotationAngle/3.14159;
	for(int f = 0 ; f < _numberOfFrame; f++)
	{

		_subFrames[f] = cvCreateImage(cvSize(_frames[0]->width,_frames[0]->height),IPL_DEPTH_8U,3);
		//_subFrames[f]->origin = 1;

			
		  float m[6];
		  // Matrix m looks like:
		  //
		  // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
		  // [ m3  m4  m5 ]       [ A21  A22   b2 ]
		  //
		  CvMat M = cvMat (2, 3, CV_32F, m);
		  int w = _width;
		  int h = _height;
		  if (opt)		// 旋轉加縮放
			factor = (cos (angle * CV_PI / 180.) + 1.0) * 2;
		  else			//  僅僅旋轉
			factor = 1;
		  m[0] = (float) (factor * cos (-angle * 2 * CV_PI / 180.));
		  m[1] = (float) (factor * sin (-angle * 2 * CV_PI / 180.));
		  m[3] = -m[1];
		  m[4] = m[0];
		  // 將旋轉中心移至圖像中間
		  m[2] = w * 0.5f;
		  m[5] = h * 0.5f;
		  //  dst(x,y) = A * src(x,y) + b
		  cvZero (_subFrames[f]);
		  cvGetQuadrangleSubPix (_frames[f],_subFrames[f], &M);
		  cvNamedWindow ("dst", 1);
		  cvShowImage ("dst", _subFrames[f]);
		  if (cvWaitKey (1) == 27)	//ESC
			break;
		 // angle = (int) (angle + delta) % 360;
		
	}

	//return _subFrames;

}

void HumanRegionDetection::SaveImage(char* InputPath,char* FileName,char* OutputPath,int Frame,double scaling,char* tempAction)
{
	/*char SaveFileName[150];
	sprintf(_videoFileName,"%s%.1lf\\%s\\%s",InputPath,scaling,tempAction,FileName);
	CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	IplImage* SaveFrame;
	sprintf(SaveFileName,"%s%.1lf\\%s\\%s.jpg",OutputPath,scaling,tempAction,FileName);
	for(int f = 0 ; f < _numberOfFrame; f++)
	{
		SaveFrame = cvQueryFrame(Capture);
	    if(f == Frame)
		{
			cvSaveImage(SaveFileName,SaveFrame);

			break;
		}
	}
	
	cvReleaseCapture(&Capture);*/
	//cvReleaseImage(&SaveFrame);
}

void HumanRegionDetection::BackgroundDifference()
{
	/*CvCapture* Capture = cvCaptureFromAVI(_videoFileName);
	_height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	_width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	_numberOfFrame = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	_frames = new IplImage*[_numberOfFrame];
	_subFrames = new IplImage*[_numberOfFrame-1];
	IplImage* tempFrames;



	for(int f = 0 ; f < _numberOfFrame; f++)
	{
			_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
			_frames[f]->origin = 1;
			tempFrames = cvQueryFrame(Capture);
			cvCopy(tempFrames, _frames[f]);
	}
	cvReleaseCapture(&Capture);
	//cvNamedWindow("Histogram1",1);
    int Gray1,Gray2;
	for(int f = 1; f < _numberOfFrame; f++)
	{
		_subFrames[f-1] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
		_subFrames[f-1]->origin = 1;
		for(int IH = 0 ; IH < _height; IH++)
		{
			for(int IW = 0 ; IW < _subFrames[f-1]->widthStep; IW += 3)
			{
				int Loc = IH * _frames[f]->widthStep + IW;

				Gray1 =(int)((_frames[f]->imageData[Loc] + _frames[f]->imageData[Loc + 1] +  _frames[f]->imageData[Loc + 2])/3.0);
				Gray2 =(int)((_frames[f-1]->imageData[Loc] + _frames[f-1]->imageData[Loc + 1] +  _frames[f-1]->imageData[Loc + 2])/3.0);

				_subFrames[f-1]->imageData[Loc] = abs(Gray1-Gray2);
				_subFrames[f-1]->imageData[Loc + 1] = abs(Gray1-Gray2);
				_subFrames[f-1]->imageData[Loc + 2] = abs(Gray1-Gray2);

			}
		}
		//cvShowImage("Histogram1",_subFrames[f-1]);
		//cvWaitKey(0);
		cvReleaseImage(&_frames[f-1]);
	}
    cvReleaseImage(&_frames[_numberOfFrame-1]);	*/

}

void HumanRegionDetection::RegionGrowing(uchar treshold)
{
   /*int **Label = new int*[_height];
   IplImage* SaveFrame;
	SaveFrame = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
   for(int i=0;i<_height;i++)
      Label[i] = new int[_width];

	srand((unsigned)time(NULL));

	int count = 0;
	 Label[1][1] = count;
	 SaveFrame->imageData[3] = (uchar)(rand()%255+1);
	 SaveFrame->imageData[4] = (uchar)(rand()%255+1);
	 SaveFrame->imageData[5] = (uchar)(rand()%255+1);

	 cvNamedWindow("Histogram1",1);
	for(int f = 0; f < _numberOfFrame-1; f++)
	{
		for(int IH = 0 ; IH < _height; IH++)
		{
			for(int IW = 0 ; IW < _subFrames[f]->widthStep; IW += 3)
			{
				if(IH == 0 || IW == 0)
					continue;
				int Loc = IH * _subFrames[f]->widthStep + IW;
				for(int i = -1; i <=1; i++)
				{
					for(int j = -1; j < -1; j++)
					{
						if(i == 0 && j == 0)
							continue;
						int  neighborLoc = (IH+i) * _subFrames[f]->widthStep + (IW+j);
						if(abs(_subFrames[f]->imageData[Loc] - _subFrames[f]->imageData[neighborLoc]) < treshold)
						{
							Label[IH+i][IW+j] = Label[IH][IW];
							SaveFrame->imageData[neighborLoc] = SaveFrame->imageData[Loc];
							SaveFrame->imageData[neighborLoc+1] = SaveFrame->imageData[Loc+1];
							SaveFrame->imageData[neighborLoc+2] = SaveFrame->imageData[Loc+2];

						}
						else
						{
							count++;
							Label[IH+i][IW+j] = count;
							SaveFrame->imageData[neighborLoc] = (uchar)(rand()%255+1);
							SaveFrame->imageData[neighborLoc+1] = (uchar)(rand()%255+1);
							SaveFrame->imageData[neighborLoc+2] = (uchar)(rand()%255+1);
						}
					}
				}
				
			}
		}
		cvShowImage("Histogram1",SaveFrame);
		cvWaitKey(0);
	}
	 cvReleaseImage(&SaveFrame);	*/
}

void HumanRegionDetection::CatchImage(char* Path,int CatchFrame,char *InputFileName,char* FileName)
{
	/*CvCapture* Capture = cvCaptureFromAVI(InputFileName);
	char FrameFileName[200];
	int Height = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_HEIGHT);
	int Width = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_WIDTH);
	int Time = cvGetCaptureProperty(Capture, CV_CAP_PROP_FRAME_COUNT);
	IplImage* SaveFrame;
	SaveFrame = cvCreateImage(cvSize(Width,Height),IPL_DEPTH_8U,3);
	
	for(int f = 0 ; f < Time; f++)
	{
		//SaveFrame = cvQueryFrame(Capture);
		cvCopy(cvQueryFrame(Capture), SaveFrame);
		SaveFrame->origin = 1;
		if(f == CatchFrame)
		{
			sprintf(FrameFileName,"%s\\%s_%d.jpg",Path,FileName,f);
			cvSaveImage(FrameFileName,SaveFrame);
		}
	}
	cvReleaseImage(&SaveFrame);	
	cvReleaseCapture(&Capture);*/
}


void HumanRegionDetection::GrayHistogramThreshold()
{
	/*int *WidthAvg = new int[_width];
	int *HeightAvg = new int[_height];
	_frames = new IplImage*[_numberOfFrame];

	for(int i = 0; i < _width; i++)
	{
		WidthAvg[i] = 0;
	}

	for(int i = 0; i < _height; i++)
	{
		HeightAvg[i] = 0;
	}
	cvNamedWindow("Histogram1",1);
	for(int f = 0; f < _numberOfFrame; f++)
	{
		_frames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
		_frames[f]->origin = 1;
		cvThreshold(_subFrames[f],_frames[f],100,255,CV_THRESH_BINARY);
		cvReleaseImage(&_subFrames[f]);
		cvShowImage("Histogram1",_frames[f]);
		cvWaitKey(0);
	}


	for(int f = 0; f < _numberOfFrame; f++)
	{		
		for(int IH = 0 ; IH < _height; IH++)
		{
			for(int IW = 0 ; IW < _subFrames[f]->widthStep; IW += 3)
			{
				int Loc = IH * _frames[f]->widthStep + IW;
				//_subFrames[f-1]->imageData[Loc];
				HeightAvg[]++;
			}
		}
	}*/

}