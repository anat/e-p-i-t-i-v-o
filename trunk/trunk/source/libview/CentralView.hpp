#ifndef CENTRALVIEW_HPP
#define CENTRALVIEW_HPP

#include <QWidget>

namespace Ui {
    class CentralView;
}

class CentralView : public QWidget
{
    Q_OBJECT

public:
    explicit CentralView(QWidget *parent = 0);
    ~CentralView();

private:
    Ui::CentralView *ui;
};

#endif // CENTRALVIEW_HPP
