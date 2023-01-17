#ifndef POINTEVENT_H
#define POINTEVENT_H


enum class EventType :short
{
   DOWN,
   MOVE,
   UP
};
class PointEvent{
public:
    PointEvent():x(0),y(0),type(EventType::DOWN){}

    PointEvent(int x,int y,EventType type):x(x),y(y),type(type){};
    int x;
    int y;
    EventType type;
};
#endif // POINTEVENT_H
