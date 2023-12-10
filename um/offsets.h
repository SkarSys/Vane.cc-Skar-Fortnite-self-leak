#pragma once
#include <Windows.h>

#define OFFSET_UWORLD 0x117392A8
#define VIEW_POINT 0xE49C7E0

namespace OFFSETS
{
    uintptr_t WorldSettings = 0x2A0;
    uintptr_t CurrentVehicle = 0x25B8;
    uintptr_t CachedFuelComponent = 0x10F8;
    uintptr_t bUseGravity = 0x6EA;
    uintptr_t CurrentWeapon = 0xa20;
    uintptr_t entity_actor = 0x310;
    uintptr_t GlobalAnimRateScale = 0xA80;
    uintptr_t LocalPlayer = 0xE9F9A60;
    uintptr_t UWorld = 0x117392A8;
    uintptr_t ViewPoint = 0xE49C7E0;
    uintptr_t Gameinstance = 0x1d0;
    uintptr_t LocalPlayers = 0x38;
    uintptr_t PlayerController = 0x30;
    uintptr_t PlayerCameraManager = 0x348;
    uintptr_t LocalPawn = 0x338;
    uintptr_t PlayerState = 0x2b0;
    uintptr_t RootComponet = 0x198;
    uintptr_t RelativeLocation = 0x128;
    uintptr_t GameState = 0x158;
    uintptr_t PlayerArray = 0x2A8;
    uintptr_t WeaponData = 0x450;
    uintptr_t PawnPrivate = 0x308;
    uintptr_t TeamIndex = 0x10e0;
    uintptr_t bIsReloadingWeapon = 0x358;
    uintptr_t AmmoCount = 0x0D08;
    uintptr_t ItemType = 0x70;
    uintptr_t DisplayName = 0x98;
    uintptr_t FText = 0x38;
    uintptr_t Tier = 0x73;
    uintptr_t Mesh = 0x318;
    uintptr_t LastSubmitTime = 0x360;
    uintptr_t LastRenderTimeOnScreen = 0x370;
    uintptr_t bIsDying = 0x750;
    uintptr_t isDBNO = 0x9A3;
    uintptr_t BoneArray = 0x608;
    uintptr_t BoneArrayCache = 0x658;
    uintptr_t pNameStructure = 0xAE0;
    uintptr_t ComponentToWorld = 0x230;
    uintptr_t SkeletalMeshes = 0xb40;
    uintptr_t PawnMaterials_ALL = 0x5b80;
    uintptr_t Wireframe = 0x7ce;
    uintptr_t PersistentLevel = 0x30;
    uintptr_t ActorCount = 0xA0;
    uintptr_t AActor = 0xa0;
    uintptr_t CurrentActor = 0xa8;
    uintptr_t TeamId = 0x10e0;
    uintptr_t Levels = 0x170;
    uintptr_t IsCached = 0x648;
    uintptr_t ReviveFromDBNOTime = 0x4b68;
}
