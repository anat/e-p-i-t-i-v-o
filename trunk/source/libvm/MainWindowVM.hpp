#ifndef __MAINWINDOWVM_HPP__
# define __MAINWINDOWVM_HPP__

# include <QObject>

namespace vm
{
  class MainWindowVM : public QObject
  {
    //TODO uncomment if slot + signals
    //Q_OBJECT

    public:
    static MainWindowVM* GetInstance();
    static void DelInstance();

      public slots:
        signals:

    private:
      MainWindowVM();
      ~MainWindowVM();
    static MainWindowVM* _instance;
  };
}
#endif // !__MAINWINDOWVM_HPP__
