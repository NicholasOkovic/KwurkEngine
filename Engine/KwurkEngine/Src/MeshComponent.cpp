#include "Precompiled.h"
#include "MeshComponent.h"
#include "SaveUtil.h"

using namespace KwurkEngine;

void MeshComponent::Deserialize(const rapidjson::Value& value)
{
	RenderObjectComponent::Deserialize(value);

	ASSERT(value.HasMember("Shape") || !mMeshModel.meshData.empty(), "MeshCompoennt: either needs mesh data or has data already");
	Graphics::Model::MeshData& meshData = value.HasMember("Shape") ? mMeshModel.meshData.emplace_back() : mMeshModel.meshData.back();
	Graphics::Model::MaterialData& matData = value.HasMember("Shape") ? mMeshModel.materialData.emplace_back() : mMeshModel.materialData.back();
	if (value.HasMember("Shape"))
	{
		const auto& shapeData = value["Shape"].GetObj();
		if (shapeData.HasMember("Type"))
		{
			std::string shapeType = shapeData["Type"].GetString();
			if (shapeType == "Sphere")
			{
				uint32_t slices = static_cast<uint32_t>(shapeData["Slices"].GetInt());
				uint32_t rings = static_cast<uint32_t>(shapeData["Rings"].GetInt());
				float radius = shapeData["Radius"].GetFloat();
				meshData.mesh = Graphics::MeshBuilder::CreateSphere(slices, rings, radius);
			}
			else if (shapeType == "Plane")
			{
				uint32_t rows = static_cast<uint32_t>(shapeData["Rows"].GetInt());
				uint32_t columns = static_cast<uint32_t>(shapeData["Columns"].GetInt());
				float spacing = shapeData["Spacing"].GetFloat();
				bool horizontal = true;
				//SaveUtil::ReadBool("Vertical", horizontal, shapeData);
				meshData.mesh = Graphics::MeshBuilder::CreateGroundPlane(rows, columns, spacing/*, horizontal*/);	//differetn createplane(may need horizontal modifications)
			}
			else
			{
				ASSERT(false, "Meshcomponent: unrecognized shape type %s", shapeType.c_str());
			}
		}
		else
		{
			ASSERT(false, "Meshcomponent: Must specigy a shaope type");

		}
	}
	if (value.HasMember("Material"))
	{
		const auto& materialData = value["Material"].GetObj();
		SaveUtil::ReadColor("Emissive", matData.material.emissive, materialData);
		SaveUtil::ReadColor("Ambient", matData.material.ambient, materialData);
		SaveUtil::ReadColor("Diffuse", matData.material.diffuse, materialData);
		SaveUtil::ReadColor("Specular", matData.material.specular, materialData);
		SaveUtil::ReadFloat("Shininess", matData.material.power, materialData);  ///shininess??????


	}
	if (value.HasMember("Textures"))
	{
		const auto& textureData = value["Textures"].GetObj();
		SaveUtil::ReadString("DiffuseMap", matData.diffuseMapName, textureData);
		SaveUtil::ReadString("NormalMap", matData.normalMapName, textureData);
		SaveUtil::ReadString("SpecMap", matData.specMapName, textureData);
		SaveUtil::ReadString("BumpMap", matData.bumpMapName, textureData);
		
	}

}

const Graphics::Model& KwurkEngine::MeshComponent::GetModel() const
{
	return mMeshModel;
}
