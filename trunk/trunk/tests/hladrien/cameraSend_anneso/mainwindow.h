#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string.h>
#include <ui_mainwindow.h>
#include <cv.h>
#include <cv.hpp>
#include <cvaux.h>
//#include <cvcam.h>
#include <highgui.h>
#include <imageview.h>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    public slots:
    void ClickBtn();
    void SliderChangeValue();
    void BtnFaceDectector();
    void FlipImage();
    protected:
        void changeEvent(QEvent *e);

    private:
        IplImage* image;
        Ui::MainWindow *ui;
        int cameras;        
        QImage ConvertIplImgtoQBitmpat(IplImage* img);
        bool isFlip;
        bool isStop;
        bool breakCapture;
};

#endif // MAINWINDOW_H
