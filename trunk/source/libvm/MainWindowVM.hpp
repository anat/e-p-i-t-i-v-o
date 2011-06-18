#ifndef __MAINWINDOWVM_HPP__
# define __MAINWINDOWVM_HPP__

# include <QObject>

namespace vm
{
  class MainWindowVM : public QObject
  {
    Q_OBJECT

    public:
      MainWindowVM();
      ~MainWindowVM();

      public slots:
        signals:
    private:
  };
}
#endif // !__MAINWINDOWVM_HPP__
