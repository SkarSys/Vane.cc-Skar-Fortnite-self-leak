#include "config.h"

// DYNAMIC FOV
bool dynamicEsp = true;
float decreaseStep = 0.1f;
bool isButtonPressed = false;
int steps = 300;

// AIM
bool Aimbot = false;
bool fovcircle = false;
bool humanAim = false;

// ESP
bool lobby = false;
bool Esp = false;
bool slefESP = false;
bool BoxEsp = false;
bool CorneredBoxEsp = false;
bool FilledBoxEsp = false;
bool DistanceEsp = false;
bool SkeletonEsp = false;
bool bigDickEsp = false;
bool tinyDickEsp = false;
bool CrosshairLines = false;
bool ClosestSnaplines = false;
bool VisibleCheck = false;
float NotVisColor[3] = { 0.0f, 1.0f, 1.0f }; // Cyan color
float VisColor[3] = { 1.0f, 0.58f, 0.0f };   // Orange color
float EspThickness = 2.5f;
bool headCircleEsp = false;
bool reloadEsp = false;
bool weaponEsp = false;
bool outlinedBoxEsp = true;
bool nameEsp = false;

// MISC
bool ShowMenu = true;
bool particles = false;
bool StreamProof = false;
bool Crosshair = false;
bool showFps = true;

// EXPLOITS
bool carFly = false;
bool noRecoil = false;
bool bigPlayer = false;
bool playerFly = false;

// ADDITIONAL VARIABLES
float BoxWidthValue = 0.550;
float ChangerFOV = 80;
int aimkeypos = 3;
int aimbone = 1;
float smooth = 5.0f;
int VisDist = 500;
float AimFOV = 150;
int aimkey;
int hitbox;
int hitboxpos = 0;
float CrossHair[3];
float CrossThickness = 1.5f;