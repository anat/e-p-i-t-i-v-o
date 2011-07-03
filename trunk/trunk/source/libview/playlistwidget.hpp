#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <list>
#include <QModelIndex>

namespace Ui {
    class PlayListWidget;
}

class PlayListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayListWidget(QWidget *parent = 0);
    ~PlayListWidget();
    static PlayListWidget* GetInstance();
    static void DelInstance();
    std::list<std::string> paths;
    std::list<std::string> files;
    std::string currentPlayListPath;
private:
    static PlayListWidget* _instance;
    Ui::PlayListWidget *ui;
    void listvideos();
public slots:
    void addNewFolder();
    void addToPlayList();
    void loadPlayList();
    void savePlayList();
    void deleteFromPlayList();
    void startFromIndex(QModelIndex i);

};

#endif // PLAYLISTWIDGET_H
