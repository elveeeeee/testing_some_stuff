#ifndef E_SCAPE_CLIENT_EVENT_TYPE_CONVERTER
#define E_SCAPE_CLIENT_EVENT_TYPE_CONVERTER

#include <memory>

template<typename Base, typename Derived>
class EventTypeConverter
{
    public :
        static std::shared_ptr<Derived> downcastEvent(std::shared_ptr<Base>&& basePtr)
        {
            // TODO: wrap in std::move(); check with debugger if a copy is made here (move is warranted)
            return std::dynamic_pointer_cast<Derived>(basePtr);
        };
};

#endif