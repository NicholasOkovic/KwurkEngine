#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Physics;
using namespace KwurkEngine::Graphics;

RigidBody::~RigidBody()
{
	ASSERT(mRigidBody == nullptr, "RigidBody: terminate must be called");
}

void RigidBody::Initialize(KwurkEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	mGraphicsTransform = &graphicsTransform;
	mMass = mass;

	mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	mRigidBody = new btRigidBody(mMass, mMotionState, shape.mCollisionShape);
	PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
	PhysicsWorld::Get()->UnRegister(this);
	SafeDelete(mRigidBody);
	SafeDelete(mMotionState);
}

void RigidBody::SetPosition(const KwurkEngine::Math::Vector3& position)
{
	mRigidBody->activate();
	mGraphicsTransform->position = position;
	mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const KwurkEngine::Math::Vector3& velocity)
{
	mRigidBody->activate();
	mRigidBody->setLinearVelocity(TobtVector3(velocity));
}

bool RigidBody::IsDynamic() const
{
	return mMass > 0.0f;
}

void RigidBody::SyncWithGraphics()
{
	btTransform& worldTransform = mRigidBody->getWorldTransform();
	mGraphicsTransform->position = ToVector3(worldTransform.getOrigin());
	mGraphicsTransform->rotation = ToQuaternion(worldTransform.getRotation());
}

btRigidBody* RigidBody::GetRigidBody()
{
	return mRigidBody;
}
