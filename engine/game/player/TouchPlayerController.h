//
//  TouchPlayerController.h
//  Cpptest
//
//  Created by Nikita on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"
#include "MyMath.h"
#include "Input.h"

class PlayerShip;

class TouchPlayerController : public Component {
public:
	GENERATE_COMPONENT_ID(TouchPlayerController)
	
	virtual void Start();
	virtual void PreUpdate();
	virtual void ProcessEvent(Event *event);
	
    Vector3 StickerValue() const { return _normalizedStickerValue; }
    Vector3 InitialStickerPos() const { return _initialStickerPos; }
    Vector3 CurrentStickerPos() const { return _initialStickerPos + _stickerValue; }
    bool StickerEnabled() const { return _stickerEnabled; }
	float StickerRadius() const;
    float SpeedControlValue() const { return _speedControlValue; }
    
    
private:
    void SetSpeedButtonsState(bool speedUpEnabled, bool speedDownEnabled);
	void ProcessDeviceInput();
	bool IsStickerPart(const Vector3 &pos);
	bool IsButtonPart(const Vector3 &pos);
	
	void ProcessStickerTouch(input::Touch *touch);
	
	void SetStickerValue(const Vector3 &value);
	
private:
	Vector3 _initialStickerPos;
	bool _stickerEnabled;
	Vector3 _normalizedStickerValue;
	Vector3 _stickerValue;
    int _touchID;
    float _speedControlValue;
};

#endif
