// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerRobot.h"
#include "GameFramework/HUD.h"

ARobotsGameModeBase::ARobotsGameModeBase()
	: Super()
{
	DefaultPawnClass = APlayerRobot::StaticClass();


}


