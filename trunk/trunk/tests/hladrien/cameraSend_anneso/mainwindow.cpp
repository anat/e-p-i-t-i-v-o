#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cameras = 0;
    isFlip = false;
    isStop  = true;
    breakCapture = true;
    ui->containersFrame->setVisible(false);
//    imageq = QImage((const uchar *)cvimage->imageData, cvimage->width, cvimage->height, QImage::Format_RGB888).rgbSwapped();
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::ClickBtn()
{    
    if(isStop)
    {
        breakCapture = true;
    ui->btnCapture->setText("Stop");
    isStop = false;
    CvCapture* capture = cvCaptureFromCAM(cameras);
    if( !capture )
    {
      return;
    }
    IplImage* frame = 0;    
    for(;breakCapture;)
    {
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        cvNamedWindow( "Image Face", CV_WINDOW_AUTOSIZE );
        if(isFlip)
          cvFlip(frame, frame,1);
        cvShowImage( "Image Face", frame );
        int t = cvWaitKey(2);
        if(t!=-1)
        {
            switch(t)
            {
              case 27:
                  breakCapture = false;
                   ui->btnCapture->setText("Capture");
                 break;
              case 32:
                 ui->containersFrame->setVisible(true);
                 image = cvCloneImage(frame);
                 QImage snapshot = ConvertIplImgtoQBitmpat(frame).scaled(size());
                 ui->lbImage->setPixmap(QPixmap::fromImage(snapshot).scaled(ui->lbImage->size()));                
                 break;
            }
        }        
    }
   }
    else
    {
        ui->btnCapture->setText("Capture");
         isStop = true;
         breakCapture = false;
    }
}


QImage MainWindow::ConvertIplImgtoQBitmpat(IplImage* img)
{    
    return QImage((const uchar *)img->imageData, img->width, img->height, QImage::Format_RGB888).rgbSwapped();
}


void MainWindow::SliderChangeValue()
{
  IplImage* cloneImg = cvCloneImage(image);
  int p = ui->tbSlider->value();
  int w = cloneImg->width;
  int h = cloneImg->height;
  for(int i=0;i<h;i++)
  {
      for(int j=0;j<w;j++)
      {
          uchar* temp_ptr = &((uchar*)(cloneImg->imageData + cloneImg->widthStep*i))[j*3];
          int nVal =temp_ptr[0] + p;
          if (nVal < 0)
              nVal = 0;
          if (nVal > 255)
              nVal = 255;
          temp_ptr[0] = nVal;
          nVal =temp_ptr[1] + p;
                    if (nVal < 0)
                        nVal = 0;
                    if (nVal > 255)
                        nVal = 255;
                    temp_ptr[1] = nVal;
                    nVal =temp_ptr[2] + p;
                              if (nVal < 0)
                                  nVal = 0;
                              if (nVal > 255)
                                  nVal = 255;
                              temp_ptr[2] = nVal;

      }
  }

  QImage img = ConvertIplImgtoQBitmpat(cloneImg).scaled(size());
  ui->lbImage->setPixmap(QPixmap::fromImage(img).scaled(ui->lbImage->size()));
 }


void MainWindow::BtnFaceDectector()
{
    static CvMemStorage* storage = cvCreateMemStorage(0);
    static CvHaarClassifierCascade* cascade = 0;
    char* fileName = "D:/Work/Software/Codes/trunk/QtManageCamera/TestCamera/debug/Cascade/haarcascade_frontalface_alt2.xml";
    cascade = (CvHaarClassifierCascade*)cvLoad(fileName,0,0,0);

    IplImage* img = cvCloneImage(image); img->origin = 0;
    if( !isFlip )
        cvFlip(img, img);
    cvClearMemStorage(storage );
    CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20) );
    for( int i = 0; i < (faces ? faces->total : 0); i++ )
    {
        CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
        cvRectangle( img, cvPoint(r->x,r->y), cvPoint(r->x+r->width,r->y+r->height), CV_RGB(255,0,0), 3 );
    }
    QImage imgAux = ConvertIplImgtoQBitmpat(img);
    ui->lbImage->setPixmap(QPixmap::fromImage(imgAux).scaled(ui->lbImage->size()));
    cvReleaseImage( &img );

}

void MainWindow::FlipImage()
{    
    isFlip = ui->cbFlip->isChecked();
}


