#ifndef __CENTRALVM_HPP__
# define __CENTRALVM_HPP__

# include <QObject>
# include <QString>

namespace vm
{
  class CentralVM : public QObject
  {
    //TODO uncomment if slot or signals
    //Q_OBJECT

 public:
    static CentralVM* GetInstance();
    static void DelInstance();

    void LoadFile(QString const &);

  public slots:
	
  signals:

  private:
    static CentralVM* _instance;

    CentralVM(); 
    ~CentralVM();

    QString _currentMediaPath;

    void loadImage(QString const &);
    void loadMusic(QString const &);
    void loadVideo(QString const &);
  };
}
#endif // !__CENTRALVM_HPP__
