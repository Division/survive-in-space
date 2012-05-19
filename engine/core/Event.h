//
//  Event.h
//  SurviveInSpace
//
//  Created by Nikita on 5/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef EVENT_H
#define EVENT_H

#include "Utils.h"
#include <set>
#include <map>

#define GENERATE_EVENT_ID(eventName) \
static int ID() { return utils::Hash(#eventName); } \
\
virtual int GetID() const { return \
eventName::ID(); \
} \
\
static bool Match(Event *event, eventName **castEvent) { \
bool match = event->GetID() == ID(); \
if (match) *castEvent = static_cast<eventName *>(event); \
return match; \
} \
\
static bool Match(Event *event) { return event->GetID() == ID(); }


class Component;

class Event {
public:
    enum {EventDefault = 0};
    
    Event(int messageType = EventDefault);

    virtual int GetID() const = 0;
    int MessageType() const { return _messageType; }
    
protected:
    int _messageType;
    
};

//------------------------------------------------------------------------------

class EventDispatcher {
public:
    
    //--------------------------
    // Event register/remove
    void RegisterEvent(int eventID, Component *component);
    void RemoveEvent(int eventID, Component *component);
    void RemoveAllEvents(Component *component);
    void RemoveEventForAllComponents(int eventID);
    
    //--------------------------
    // Event dispatching
    void DispatchEvent(Event *event);

    
private:
    typedef std::set<Component *> ComponentSet;
    typedef std::map<int, ComponentSet> EventHash;
    
    // int key, ComponentSet value
    EventHash _eventHash;
};

#endif
