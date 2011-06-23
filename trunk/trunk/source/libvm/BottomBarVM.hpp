#ifndef __BOTTOMBARVM_HPP__
# define __BOTTOMBARVM_HPP__

# include <QObject>

namespace vm
{
  class BottomBarVM : public QObject
  {
    //TODO uncomment if slot + signals
    //Q_OBJECT

    public:
    static BottomBarVM* GetInstance();
    static void DelInstance();

   	void Record();
   	void Play();
   	void Pause();
   	void Stop();
   	void Forward();
   	void Backward();

    private:
      BottomBarVM();
      ~BottomBarVM();
    static BottomBarVM* _instance;
  };
}
#endif // !__BOTTOMBARVM_HPP__
