#include "playlistwidget.hpp"
#include "ui_playlistwidget.h"
#include "QFileDialog"
#include <QListWidgetItem>
#include <fstream>
#define LIBRARY_FILE "videoLibrary"
PlayListWidget *PlayListWidget::_instance = 0;

PlayListWidget::PlayListWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PlayListWidget),
        currentPlayListPath("")
{
    ui->setupUi(this);
    this->listvideos();
    QObject::connect(this->ui->btnAddFolder, SIGNAL(clicked()),this,SLOT(addNewFolder()));
    QObject::connect(this->ui->btnAdd, SIGNAL(clicked()), this, SLOT(addToPlayList()));
    QObject::connect(this->ui->btnLoad, SIGNAL(clicked()), this, SLOT(loadPlayList()));
    QObject::connect(this->ui->btnSave, SIGNAL(clicked()), this, SLOT(savePlayList()));
    QObject::connect(this->ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteFromPlayList()));
}

PlayListWidget::~PlayListWidget()
{
    delete ui;
}

PlayListWidget* PlayListWidget::GetInstance()
{
    if (!_instance)
        _instance = new PlayListWidget;
    return _instance;
}

void PlayListWidget::DelInstance()
{
    if (_instance)
        delete _instance;
}
#include <iostream>
void PlayListWidget::addNewFolder()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Folder that contains videos"),QDir::homePath());
    std::cout << folder.toStdString().c_str() << std::endl;
    paths.push_back(folder.toStdString());
    std::ofstream ofs(LIBRARY_FILE);
    std::list<std::string>::iterator it = paths.begin();
    std::list<std::string>::iterator end = paths.end();
    while (it != end)
    {
        ofs << *it << std::endl;
        ++it;
    }
    ofs.close();
    this->listvideos();
}

void PlayListWidget::listvideos()
{
    if (QFile::exists(LIBRARY_FILE))
    {
        paths.clear();
        std::ifstream ifs(LIBRARY_FILE);
        std::string line;
        while(std::getline(ifs,line))
        {
            QDir current(line.c_str());
            foreach (QString s, current.entryList())
                this->ui->myList->addItem(line.c_str() + QString("/") + s);
            paths.push_back(line);
        }
        ifs.close();
    }
}

void PlayListWidget::addToPlayList()
{
    if (this->ui->myList->currentItem())
        this->ui->currentList->addItem(this->ui->myList->currentItem()->text());
}

void PlayListWidget::deleteFromPlayList()
{
    if (this->ui->myList->currentItem())
        delete this->ui->myList->currentItem();//        this->ui->currentList->removeItemWidget(this->ui->myList->currentItem());
}

void PlayListWidget::loadPlayList()
{
    this->currentPlayListPath = QFileDialog::getOpenFileName(this, tr("Open a playlist"), QDir::homePath(), tr("Epitivo playlist file (*.pepitivo)")).toStdString();

    QString path(this->currentPlayListPath.c_str());
    path = path.mid(path.lastIndexOf("/") + 1);
    path = path.replace(".pepitivo", "");
    this->ui->lblPlayList->setText(path);

    paths.clear();
    std::ifstream ifs(this->currentPlayListPath.c_str());
    std::string line;
    while(std::getline(ifs,line))
    {

 /*       QDir current(line.c_str());
        foreach (QString s, current.entryList())
            this->ui->myList->addItem(line.c_str() + QString("/") + s);
        paths.push_back(line);*/
        this->ui->currentList->addItem(line.c_str());
    }
    ifs.close();

/*
    QFile f();
    while (f.canReadLine())
    {
        QString line(f.readLine());

    }
    f.close();
    */
}

void PlayListWidget::savePlayList()
{
    if (this->currentPlayListPath == "")
        this->currentPlayListPath = QFileDialog::getSaveFileName(this, tr("Open a playlist"), QDir::homePath(), tr("Epitivo playlist file (*.pepitivo)")).toStdString();

    QString path(this->currentPlayListPath.c_str());
    path = path.mid(path.lastIndexOf("/") + 1);
    path = path.replace(".pepitivo", "");
    this->ui->lblPlayList->setText(path);
    if (!QString(this->currentPlayListPath.c_str()).contains(".pepitivo"))
        this->currentPlayListPath = std::string(this->currentPlayListPath.c_str() + std::string(".pepitivo"));
    std::ofstream ofs(this->currentPlayListPath.c_str());
    for (int i = 0; i < this->ui->currentList->count(); i++)
    {
        ofs << this->ui->currentList->item(i)->text().toStdString().c_str() << std::endl;
    }
    ofs.close();
}
