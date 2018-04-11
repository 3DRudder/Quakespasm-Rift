#ifndef __RUDDER_MOVEMENT__  
#include "quakedef.h"
#include <math.h>

#ifdef  __cplusplus
#define _3DRUDDER_SDK_STATIC
#include "3dRudderSDK.h"

class RudderMovement
{
public:
	float GetPitch();
	float GetRoll();
	float GetYaw();
	float GetYawAngle();
	float GetUpDown();
	int GetSDKVersion();
	int GetNumberOfConnectedDevice();
	int IsDeviceConnected(int);

};

#endif // __cplusplus

typedef void RudderMovement_t;

#ifdef __cplusplus
	#define EXPORT_C extern "C"
#else
	#define EXPORT_C extern 
#endif // __cplusplus*/

EXPORT_C RudderMovement_t* RudderMovementNew();
EXPORT_C void RudderMovementDelete(RudderMovement_t*);
EXPORT_C float RudderMovementGetPitch(RudderMovement_t*);
EXPORT_C float RudderMovementGetRoll(RudderMovement_t*);
EXPORT_C float RudderMovementGetYaw(RudderMovement_t*);
EXPORT_C float RudderMovementGetYawAngle(RudderMovement_t*);
EXPORT_C float RudderMovementGetUpDown(RudderMovement_t*);
EXPORT_C int RudderMovementGetSDKVersion(RudderMovement_t*);
EXPORT_C int RudderMovementGetNumberOfConnectedDevice(RudderMovement_t*);
EXPORT_C int RudderMovementIsDeviceConnected(RudderMovement_t*, int);

EXPORT_C void RUD_Move(usercmd_t *cmd, cvar_t forwardspeed, cvar_t sidespeed, cvar_t backspeed);
EXPORT_C void RUD_AddRudderYawToViewAngles(client_state_t *cl);
EXPORT_C void RUD_AddRudderYawToPlayerMovement(edict_t *player, double servertime);

#define __RUDDER_MOVEMENT__
#endif // ! 


