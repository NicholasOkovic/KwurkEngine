#include "Precompiled.h"
#include "SimpleDraw.h"

#include "GraphicsSystem.h"
#include"VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "Camera.h"
#include "VertexTypes.h"
#include "BlendState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Math::Constants;


namespace
{
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Vector3& v0, const Vector3& v1, const Color color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color color);

		void Render(const Camera& camera);

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		std::unique_ptr<VertexPC[]> mLinevertices;
		std::unique_ptr<VertexPC[]> mFacevertices;

		uint32_t mLineVertexCount = 0;
		uint32_t mFaceVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
	};

	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		std::filesystem::path shaderFile = "../../Assets/Shaders/DoTransform.fx";
		mVertexShader.Initialize<Vertex>(shaderFile);
		mPixelShader.Initialize(shaderFile);
		mConstantBuffer.Initialize(sizeof(Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
		

		mLinevertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFacevertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLinevertices = 0;
		mFacevertices = 0;
		mMaxVertexCount = maxVertexCount;

	}

	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}

	void SimpleDrawImpl::AddLine(const Vector3& v0, const Vector3& v1, const Color color)
	{
		if (mLineVertexCount + 2 <= mMaxVertexCount)
		{
			mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
		}


	}

	void SimpleDrawImpl::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color color)
	{
		if (mFaceVertexCount + 3 <= mMaxVertexCount)
		{
			mFaceVertices[mLineVertexCount++] = VertexPC{ v0, color };
			mFaceVertices[mLineVertexCount++] = VertexPC{ v1, color };
			mFaceVertices[mLineVertexCount++] = VertexPC{ v2, color };
		}
	}

	void SimpleDrawImpl::Render(const Camera& camera)
	{
		const Matrix4 matView = camera.GetViewMatrix();
		const Matrix4 matProj = camera.GetProjectionMatrix();
		const Matrix4 transform = camera.GetProjectionMatrix();
	}
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void SimpleDraw::StaticTerminate()
{
	sInstance.Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3 v1, const Color& color)
{

	sInstance->AddFace(v0, v1, v2, color);

}

void SimpleDraw::AddFace(const Math::Vector3& v0, const Math::Vector3 v1, const Math::Vector3 v2, const Color& color)
{

}

void SimpleDraw::AddAABB(const Math::Vector3& min, const Math::Vector3 max, const Color& color)
{
	AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
	const Vector3 blf = { minX, minY, minZ };
	const Vector3 tlf = { minX, maxY, minZ };
	const Vector3 trf = { maxX, maxY, minZ };
	const Vector3 brf = { maxX, minY, minZ };

	const Vector3 blb = { minX, minY, maxZ };
	const Vector3 tlb = { minX, maxY, maxZ };
	const Vector3 trb = { maxX, maxY, maxZ };
	const Vector3 brb = { maxX, minY, maxZ };

	//front
	AddLine(blf, tlf, color);
	AddLine(tlf, trf, color);
	AddLine(trf, brf, color);
	AddLine(brf, blf, color);

	//back
	AddLine(blb, tlb, color);
	AddLine(tlb, trb, color);
	AddLine(trb, brb, color);
	AddLine(brb, blb, color);

	//top
	AddLine(tlf, tlb, color);
	AddLine(trf, trb, color);


	AddLine(blf, blb, color);
	AddLine(brf, brb, color);	///
}

void SimpleDraw::AddFilledAABB(const Math::Vector3& min, const Math::Vector3 max, const Color& color)
{
	AddFilledAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void SimpleDraw::AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
	const Vector3 blf = { minX, minY, minZ };
	const Vector3 tlf = { minX, maxY, minZ };
	const Vector3 trf = { maxX, maxY, minZ };
	const Vector3 brf = { maxX, minY, minZ };

	const Vector3 blb = { minX, minY, maxZ };
	const Vector3 tlb = { minX, maxY, maxZ };
	const Vector3 trb = { maxX, maxY, maxZ };
	const Vector3 brb = { maxX, minY, maxZ };

	AddFace(blf, tlf, trf, color);
	AddFace(blf, tlf, brf, color);

	AddFace(brb, trb, tlb, color);
	AddFace(brb, tlb, blb, color);

	AddFace(brf, trf, brf, color);
	AddFace(brf, trb, brb, color);

	AddFace(blb, tlb, tlf, color);
	AddFace(blb, tlf, blf, color);

	AddFace(tlf, tlb, trb, color);
	AddFace(tlf, trb, trf, color);

	AddFace(brf, brb, blb, color);
	AddFace(brf, blb, blf, color);
}

void SimpleDraw::AddSphere(int slices, int rings, float radius, const Math::Vector3& pos, const Color& color)
{
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;

	const float  vertRot = (Pi / static_cast<float>(rings));
	const float  horzRot = (TwoPi / static_cast<float>(slices));
	for (int r = 0; r < rings; r++)
	{
		int ring = static_cast<float>(r);
		float phi = ring * vertRot;
		for (int s = 0; s < slices; s++)
		{
			float slice0 = static_cast<float>(s);
			float rot0 = slice0 * horzRot;

			float slice1 = static_cast<float>(s + 1);
			float rot1 = slice1 * horzRot;

			v0 =
			{
				sin(rot0) * sin(phi) * radius,
				cos(phi) * radius,
				cos(rot0) * sin(phi) * radius
			};
			v1 =
			{
				sin(rot1) * sin(phi) * radius,
				cos(phi) * radius,
				cos(rot1) * sin(phi) * radius
			};
			AddLine(v0 + pos, v1 + pos, color);

			v0 =
			{
				cos(phi) * radius,
				cos(rot0)* sin(phi) * radius,
				sin(rot0) * sin(phi) * radius
			};
			v1 =
			{
				cos(phi) * radius,
				cos(rot1) * sin(phi) * radius,
				sin(rot1) * sin(phi) * radius
			};
			AddLine(v0 + pos, v1 + pos, color);
		}
	}


}

void SimpleDraw::AddGroundCircle(int slices, int radius, const Math::Vector3& pos, const Color& color)
{
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;
	const float horzRot = (TwoPi / static_cast<float>(slices));
	for (int s = 0; s < slices; s++)
	{
		float slice0 = static_cast<float>(s);
		float rot0 = slice0 * horzRot;

		float slize1 = static_cast<float>(s + 1);
		float rot1 = slize1 * horzRot;

		v0 = {
			sin(rot0) * radius,
			0.0f,
			cos(rot0) * radius
		};

		v1 = {
			sin(rot1) * radius,
			0.0f,
			cos(rot1) * radius
		};
		AddLine(v0 + pos, v1 + pos, color);
	}
}

void SimpleDraw::AddGroundPlane(int size, Color& color)
{
	const float hs = size * 0.5f;
	for (int i = 0; i <= size; i++)
	{
		AddLine({ i - hs, 0.0f, -hs }, { i - hs, 0.0f, hs }, color);
		AddLine({-hs, 0.0f, i -hs }, { hs, 0.0f, i - hs }, color);
	}
}

void SimpleDraw::AddTransform(int slices, int rings, const Color& color)
{
	const Vector3 side = { m._11, m._12, m._13 };
	const Vector3 up = { m._11, m._12, m._13 };
	const Vector3 look = { m._11, m._12, m._13 };
	const Vector3 pos = { m._11, m._12, m._13 };


	AddLine(pos, pos + side, color); //////////

}

void KwurkEngine::Graphics::SimpleDraw::Render(const Camera& camera)
{
}

void SimpleDraw::AddTransform(int slices, int rings, const Color& color)
{

}