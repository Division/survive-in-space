//
//  Event.cpp
//  SurviveInSpace
//
//  Created by Nikita on 5/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Event.h"
#include "Component.h"

//******************************************************************************
//
//  Event
//
//******************************************************************************


Event::Event(int messageType) {
    
    _messageType = messageType;
}


//******************************************************************************
//
//  EventDispatcher
//
//******************************************************************************

//******************************************************************************
// Event register/remove

void EventDispatcher::RegisterEvent(int eventID, Component *component) {

    if (!_eventHash.count(eventID)) {
		_eventHash[eventID] = ComponentSet();
    }
	
	ComponentSet &set = _eventHash[eventID];
	set.insert(component);

}

//------------------------------------------------------------------------------

void EventDispatcher::RemoveEvent(int eventID, Component *component) {
    
    if (_eventHash.count(eventID)) {
        ComponentSet &set = _eventHash[eventID];
        set.erase(component);
    }
}

//------------------------------------------------------------------------------

void EventDispatcher::RemoveAllEvents(Component *component) {
    
    for (EventHash::iterator it = _eventHash.begin(); it != _eventHash.end(); it++) {
        ComponentSet &set = it->second;
        set.erase(component);
    }
}

//------------------------------------------------------------------------------

void EventDispatcher::RemoveEventForAllComponents(int eventID) {
    
    _eventHash.erase(eventID);
}

//******************************************************************************
// Event dispatching

void EventDispatcher::DispatchEvent(Event *event) {
    
    int eventID = event->GetID();
    
    if (_eventHash.count(eventID)) {
        
		// Here is COPYING of whole set
		// Because events could be removed in ProcessEvent method
        ComponentSet set = _eventHash[eventID]; 
		
        for (ComponentSet::iterator it = set.begin(); it != set.end(); it++) {
            Component *component = *it;
            component->ProcessEvent(event);
        }
    }
}