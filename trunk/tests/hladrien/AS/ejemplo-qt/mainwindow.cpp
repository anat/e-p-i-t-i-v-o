#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setAlternatingRowColors(true);
    canciones = QStringList();
    canciones << "Cancion 1" << "Cancion 2" << "Cancion 3";
    canciones.append("Cancion 4");

    LlenarListView();
    LLenarListWidget();
    LLenarListWidget2();
    LlenarTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LlenarListView()
{
    QStandardItemModel *modelo = new QStandardItemModel;
    QStandardItem *item1 = new QStandardItem(canciones[0]);
    QStandardItem *item2 = new QStandardItem(QIcon(":/rating.png"),canciones[1]);
    QStandardItem *item3 = new QStandardItem(QIcon(":/rating.png"),canciones[2]);
    modelo->appendRow(item1);
    modelo->appendRow(item2);
    modelo->appendRow(item3);
    ui->listView->setModel(modelo);
}

void MainWindow::LLenarListWidget()
{
    ui->listWidget->addItems(canciones);
}

void MainWindow::LLenarListWidget2()
{
    QListWidgetItem *item1 = new QListWidgetItem;
    item1->setText(canciones[0]);
    item1->setIcon(QIcon(":/rating.png"));

    QListWidgetItem *item2 = new QListWidgetItem;
    item2->setText(canciones[1]);
    item2->setIcon(QIcon(":/rating.png"));

    QListWidgetItem *item3 = new QListWidgetItem;
    item3->setText(canciones[2]);
    item3->setIcon(QIcon(":/games-highscores.png"));

    ui->listWidget->addItem(item1);
    ui->listWidget->addItem(item2);
    ui->listWidget->addItem(item3);
}

void MainWindow::LlenarTableView()
{
    QStandardItemModel *modelo = new QStandardItemModel;
    QStringList cabeceras;
    cabeceras << "#" << "Cancion" << "Puntuacion";
    modelo->setHorizontalHeaderLabels(cabeceras);
    for (int i = 0; i < canciones.size(); ++i)
    {
        QList<QStandardItem*> fila;
        fila.append(new QStandardItem(QString::number(i+1)));
        fila.append(new QStandardItem(QIcon(":/rating.png"),canciones[i]));
        fila.append(new QStandardItem(QIcon(":/games-highscores.png"),QString::number(i+2)));
        modelo->appendRow(fila);
    }

    ui->tableView->setModel(modelo);
}
