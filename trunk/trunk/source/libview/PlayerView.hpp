#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <QWidget>
#include <QString>

#include "libvm/PlayerVM.hpp"

namespace Ui {
    class PlayerView;
}

class PlayerView : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerView(QWidget *parent = 0);
    ~PlayerView();

    public slots:

      void Play();
    void Pause();
    void Stop();

    void setFilepath(QString const & file);

private:
    Ui::PlayerView *ui;

    vm::PlayerVM * _vm;
    
    //void setPlayingState();
    //void setPausedState();
    //void setStoppedState();
};

#endif // PLAYERVIEW_HPP
