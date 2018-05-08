#ifndef MYBASESINGLETON_H
#define MYBASESINGLETON_H
#include <QCoreApplication>
#include <QAtomicPointer>
#include <QReadWriteLock>
#include <QMutex>
#include <QDebug>

#define MY_DECLARE_SINGLETON(T) \
    public:\
        static T* instance() \
    {\
        return MyBaseSingleton<T>::instance();\
    }

template<class T>
// 单例 - 懒汉式/饿汉式公用
class MyBaseSingleton
{
public:
    static T* instance(void);

private:
    MyBaseSingleton(); // 构造函数（被保护）

private:
    static T *m_instance;  // 指向单例对象的指针
    static QMutex m_mutex;  // 锁
};

template<class T>
QMutex MyBaseSingleton<T>::m_mutex(QMutex::Recursive);//一个线程可以多次锁同一个互斥量

template<class T>
T* MyBaseSingleton<T>::m_instance = NULL;//原子指针，默认初始化是0

template<typename T>
T* MyBaseSingleton<T>::instance(void)
{
    if (m_instance == NULL)
    {
        QMutexLocker locker(&m_mutex);//互斥锁
        if (m_instance == NULL)
        {
            m_instance = new T();
        }
    }
    return m_instance;
}


#endif // MYBASESINGLETON_H
