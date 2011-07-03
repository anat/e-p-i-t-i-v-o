#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LlenarListView();
    void LLenarListWidget();
    void LLenarListWidget2();
    void LlenarTableView();

private:
    Ui::MainWindow *ui;
    QStringList canciones;
};

#endif // MAINWINDOW_H
