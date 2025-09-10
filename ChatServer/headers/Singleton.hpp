#include <mutex>
#include <memory>

template <typename T>
class Singleton
{
public:
    virtual ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static std::shared_ptr<T> getInstance()
    {
        static std::once_flag onceFlag;
        std::call_once(onceFlag, [&](){
            _ins = std::make_shared<T>();
        });
        return _ins;
    }
protected:
    Singleton() = default;
    static std::shared_ptr<T> _ins;    
};
template<typename T>
std::shared_ptr<T> Singleton<T>::_ins = nullptr;