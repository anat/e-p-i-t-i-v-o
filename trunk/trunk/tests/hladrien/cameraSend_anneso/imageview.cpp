#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
}

ImageView::~ImageView()
{
    delete ui;
}

void ImageView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
