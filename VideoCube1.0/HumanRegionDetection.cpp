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
	CvSize dst_cvsize;			//�ؼйϹ��ؤo
	dst_cvsize.width = _frames[0]->width * scale;		//�ؼйϹ����e�����϶H�e��scale��
	dst_cvsize.height = _frames[0]->height * scale;	//�ؼйϹ����������϶H����scale��


	for(int f = 0 ; f < _numberOfFrame; f++)
	{
		//_subFrames[f] = cvCreateImage(cvSize(_width,_height),IPL_DEPTH_8U,3);
	 
		_subFrames[f] = cvCreateImage( dst_cvsize, IPL_DEPTH_8U, 3);	//�c�y�ؼй϶H
		cvResize(_frames[f], _subFrames[f], CV_INTER_LINEAR);	//�Y�񷽹Ϲ���ؼйϹ�
	 
		cvNamedWindow( "src",   CV_WINDOW_AUTOSIZE );	//�ЫإΩ���ܷ��Ϲ�������
		cvNamedWindow( "dst",   CV_WINDOW_AUTOSIZE );	//�ЫإΩ���ܥؼйϹ�������
	 
		cvShowImage( "src", _frames[f] );		//��ܷ��Ϲ�
		cvShowImage( "dst", _subFrames[f]);		//��ܥؼйϹ�
	 
		cvWaitKey(27);		//���ݥΤ��T��
	 
		//cvDestroyWindow( "src" );	//�P��������src��
		//cvDestroyWindow( "dst" );	//�P��������dst��
		
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
     int opt = 0;		// 1�G ����[�Y��
      // 0:  �ȶȱ���
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
		  if (opt)		// ����[�Y��
			factor = (cos (angle * CV_PI / 180.) + 1.0) * 2;
		  else			//  �ȶȱ���
			factor = 1;
		  m[0] = (float) (factor * cos (-angle * 2 * CV_PI / 180.));
		  m[1] = (float) (factor * sin (-angle * 2 * CV_PI / 180.));
		  m[3] = -m[1];
		  m[4] = m[0];
		  // �N���त�߲��ܹϹ�����
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
