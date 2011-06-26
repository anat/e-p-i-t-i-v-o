#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

namespace Ui {
    class ImageView;
}

class ImageView : public QWidget {
    Q_OBJECT
public:
    ImageView(QWidget *parent = 0);
    ~ImageView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ImageView *ui;
};

#endif // IMAGEVIEW_H
