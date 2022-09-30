#ifndef SINGLETON_HDR
#define SINGLETON_HDR

#include <memory>

namespace acid 
{
    template <typename T>
    class Singleton 
    {
    public:
        Singleton(Singleton&& str) = delete;
        Singleton& operator=(Singleton&& str) = delete;
        Singleton& operator=(const Singleton& str) = delete;
        Singleton(const Singleton& str) = delete;

        static void createInstance()
        {
            _instance = new T();
        }

        static void destroyInstance() 
        {
            delete _instance;
            _instance = nullptr;
        }

        static T& getInstance() 
        {
            if (_instance == nullptr) 
            {
                createInstance();
            }
            return *_instance;
        }

        static void setInstance(T* newInstance) 
        {
            if (_instance) 
            {
                destroyInstance();
            }
            _instance = newInstance;
        }

    private:
        static T* _instance;

        Singleton() = default;
        ~Singleton() = default;
    };

    template<typename T>
    T* Singleton<T>::_instance = nullptr;
}

#endif // !SINGLETON_HDR
