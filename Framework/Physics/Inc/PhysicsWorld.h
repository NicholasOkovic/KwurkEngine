#pragma once


namespace KwurkEngine::Physics
{
	class PhysicsObject;

	class PhysicsWorld final
	{
	public:
		struct Settings
		{
			KwurkEngine::Math::Vector3 gravity = { 0.0f, -9.81, 0.0f };
			uint32_t simulationSteps = 10;
			float fixedTimeStep = 1.0f / 60.0f;
		};

		static void StaticInitialize(const Settings& settings);
		static void StaticTerminate();
		static PhysicsWorld* Get();

		PhysicsWorld() = default;
		~PhysicsWorld();

		void Initialize(const Settings& settings);
		void Terminate();

		void Update(float deltaTime);
		void Debug();

		void Register(PhysicsObject* physicsObject);
		void UnRegister(PhysicsObject* physicsObject);

		void SetGravity(const KwurkEngine::Math::Vector3& gravity);

	private:
		Settings mSettings;

		//bullet object
		btBroadphaseInterface* mInterface = nullptr;
		btCollisionDispatcher* mDispatcher = nullptr;
		btDefaultCollisionConfiguration* mCollisionConfiguration = nullptr;
		btDiscreteDynamicsWorld* mDynamicsWorld = nullptr;
		btSequentialImpulseConstraintSolver* mSolver = nullptr;

		using PhysicsObjects = std::vector<PhysicsObject*>;
		PhysicsObjects mPhysicsObjects;


	};

	
}