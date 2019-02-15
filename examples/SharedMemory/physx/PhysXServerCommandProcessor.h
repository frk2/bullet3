#ifndef PHYSX_SERVER_COMMAND_PROCESSOR_H
#define PHYSX_SERVER_COMMAND_PROCESSOR_H

#include "../PhysicsCommandProcessorInterface.h"
#include "PxSimulationEventCallback.h"
#include <stdio.h>
#include <vector>
#include <tuple>
#include <mutex>
using namespace physx;

class PhysXServerCommandProcessor : public PhysicsCommandProcessorInterface, public PxSimulationEventCallback
{
	struct PhysXServerCommandProcessorInternalData* m_data;

	bool processSyncBodyInfoCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processRequestInternalDataCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processSyncUserDataCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processLoadURDFCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processRequestBodyInfoCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processForwardDynamicsCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processSendPhysicsParametersCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processRequestActualStateCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processResetSimulationCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processInitPoseCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processSendDesiredStateCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processChangeDynamicsInfoCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processRequestPhysicsSimulationParametersCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processRequestContactpointInformationCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);
	bool processCustomCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);

	void resetSimulation();
	bool processStateLoggingCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);

	// PxSimulationEventCallback
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
	{
		PX_UNUSED(constraints);
		PX_UNUSED(count);
	}

	void onWake(PxActor** actors, PxU32 count)
	{
		PX_UNUSED(actors);
		PX_UNUSED(count);
	}

	void onSleep(PxActor** actors, PxU32 count)
	{
		PX_UNUSED(actors);
		PX_UNUSED(count);
	}

	void onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		PX_UNUSED(pairs);
		PX_UNUSED(count);
	}

	void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) {}

public:
	PhysXServerCommandProcessor();

	virtual ~PhysXServerCommandProcessor();

	virtual bool connect();

	virtual void disconnect();

	virtual bool isConnected() const;

	virtual bool processCommand(const struct SharedMemoryCommand& clientCmd, struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);

	virtual bool receiveStatus(struct SharedMemoryStatus& serverStatusOut, char* bufferServerToClient, int bufferSizeInBytes);

	virtual void renderScene(int renderFlags) {}
	virtual void physicsDebugDraw(int debugDrawFlags) {}
	virtual void setGuiHelper(struct GUIHelperInterface* guiHelper) {}
	virtual void setTimeOut(double timeOutInSeconds) {}

	virtual void reportNotifications() {}
	std::vector<std::tuple<std::string, std::string, PxContactPairPoint>> contactPoints;
	std::recursive_mutex contacts_lock;

};

#endif  //PHYSX_SERVER_COMMAND_PROCESSOR_H
