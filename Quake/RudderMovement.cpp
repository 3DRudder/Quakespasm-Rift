#include "RudderMovement.h"


float RudderMovement::GetPitch()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	ns3dRudder::Axis sAxis;
	if (pSDK->IsDeviceConnected(0))
	{
		pSDK->GetAxis(0, ns3dRudder::NormalizedValueNonSymmetricalPitch, &sAxis);
		return pSDK->CalcCurveValue(2.0f / 18.0f, 1.0f, 1.0f, 1.0f, sAxis.GetPhysicalPitch());
	}

	return 0.0f;
	
}

float RudderMovement::GetRoll()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	ns3dRudder::Axis sAxis;
	if (pSDK->IsDeviceConnected(0))
	{
		pSDK->GetAxis(0, ns3dRudder::NormalizedValueNonSymmetricalPitch, &sAxis);
		return pSDK->CalcCurveValue(2.0f / 18.0f, 1.0f, 1.0f, 1.0f, sAxis.GetPhysicalRoll());
	}

	return 0.0f;
}

float RudderMovement::GetYaw()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	ns3dRudder::Axis sAxis;
	if (pSDK->IsDeviceConnected(0))
	{
		pSDK->GetAxis(0, ns3dRudder::NormalizedValueNonSymmetricalPitch, &sAxis);
		return pSDK->CalcCurveValue(3.0f / 25.0f, 1.0f, 1.0f, 1.0f, sAxis.GetPhysicalYaw());
	}

	return 0.0f;
}

float RudderMovement::GetYawAngle()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	ns3dRudder::Axis sAxis;
	if (pSDK->IsDeviceConnected(0))
	{
		pSDK->GetAxis(0, ns3dRudder::UserRefAngle, &sAxis);
		return pSDK->CalcCurveValue(3.0f , 25.0f, 25.0f, 1.0f, sAxis.GetPhysicalYaw());
	}

	return 0.0f;
}

float RudderMovement::GetUpDown()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	ns3dRudder::Axis sAxis;
	if (pSDK->IsDeviceConnected(0))
	{
		pSDK->GetAxis(0, ns3dRudder::NormalizedValueNonSymmetricalPitch, &sAxis);
		return pSDK->CalcCurveValue(0.08, 1.0f, 1.0f, 1.0f, sAxis.GetUpDown());
	}

	return 0.0f;
}

int RudderMovement::GetSDKVersion()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	return pSDK->GetSDKVersion();
}

int RudderMovement::GetNumberOfConnectedDevice()
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	return pSDK->GetNumberOfConnectedDevice();
}

int RudderMovement::IsDeviceConnected(int i)
{
	ns3dRudder::CSdk* pSDK = ns3dRudder::GetSDK();
	if (pSDK->IsDeviceConnected(i))
		return 1;
	else
		return 0;
}

EXPORT_C RudderMovement_t* RudderMovementNew()
{
	return new RudderMovement();
}

EXPORT_C void RudderMovementDelete(RudderMovement_t* t)
{
	delete t;
}

EXPORT_C float RudderMovementGetPitch(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetPitch();
}

EXPORT_C float RudderMovementGetRoll(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetRoll();
}

EXPORT_C float RudderMovementGetYaw(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetYaw();
}

EXPORT_C float RudderMovementGetYawAngle(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetYawAngle();
}

EXPORT_C float RudderMovementGetUpDown(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetUpDown();
}

EXPORT_C int RudderMovementGetSDKVersion(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetSDKVersion();
}

EXPORT_C int RudderMovementGetNumberOfConnectedDevice(RudderMovement_t* t)
{
	return ((RudderMovement*)t)->GetNumberOfConnectedDevice();
}

EXPORT_C int RudderMovementIsDeviceConnected(RudderMovement_t* t, int i)
{
	return ((RudderMovement*)t)->IsDeviceConnected(i);
}

EXPORT_C void RUD_Move(usercmd_t *cmd, cvar_t forwardspeed, cvar_t sidespeed, cvar_t backspeed)
{

	RudderMovement_t* rMovement = RudderMovementNew();

	cmd->sidemove += sidespeed.value * RudderMovementGetRoll(rMovement);
	cmd->sidemove -= sidespeed.value * (-1 * RudderMovementGetRoll(rMovement));

	cmd->forwardmove += forwardspeed.value * RudderMovementGetPitch(rMovement);
	cmd->forwardmove -= backspeed.value * (-1 * RudderMovementGetPitch(rMovement));

}

EXPORT_C void RUD_AddRudderYawToViewAngles(client_state_t *cl)
{
	RudderMovement_t* rMovement = RudderMovementNew();

	cl->viewangles[YAW] = fmod(cl->viewangles[YAW] + RudderMovementGetYaw(rMovement) * -2, 360);
	cl->aimangles[YAW] = fmod(cl->aimangles[YAW] + RudderMovementGetYaw(rMovement) * -2, 360);
}

float originalplayeryaw = 0;

EXPORT_C void RUD_AddRudderYawToPlayerMovement(edict_t *player, double servertime)
{
	RudderMovement_t *rMovement = RudderMovementNew();

	if (servertime <= 2.0f)
	{
		originalplayeryaw = player->v.angles[YAW];
	}

	player->rudderyaw += RudderMovementGetYaw(rMovement);

	player->v.angles[YAW] = fmod(originalplayeryaw + (player->rudderyaw * -2), 360);
}
