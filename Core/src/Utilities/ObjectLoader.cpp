#include "ObjectLoader.h"
#include "MeshFactory.h"
#include "Mesh.h"
#include <iostream>
#include <format>
#include <string>
#include <sstream>
#include <GLM/glm/geometric.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"
#include <GLM/glm/gtx/matrix_decompose.hpp>
#include <GLM/glm/gtc/type_ptr.hpp>

ObjectLoader::ObjectLoader()
{
	
}

ObjectLoader::~ObjectLoader()
{

}

void exportFromTransformationMatrix(const glm::mat4& transformationMatrix, std::shared_ptr<Transform> transform) noexcept
{
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;
	glm::vec3 skew;
	glm::vec4 perspective;
	if(glm::decompose(transformationMatrix, scale, rot, pos, skew, perspective))
	{
		transform->position = pos;
		transform->rotation = rot;
		transform->scale = scale;
	}
	else
	{
		assert(false);
	}
	/*transform->position = glm::vec3(transformationMatrix[3]);
	const glm::vec3 baseX = transformationMatrix[0];
	const glm::vec3 baseY = transformationMatrix[1];
	const glm::vec3 baseZ = transformationMatrix[2];
	transform->scale.x = baseX.length();
	transform->scale.y = baseY.length();
	transform->scale.z = baseZ.length();*/

}

void processChildNode(Scene* scene, const aiScene* model, std::shared_ptr<GameObject> gameObject, aiNode* node, std::unordered_map<std::string, std::shared_ptr<Texture>>& loadedTexturesMap) noexcept
{
	if(node)
	{
		std::cout << node->mName.C_Str() << std::endl;
        std::shared_ptr<MeshRenderer> meshRenderer = gameObject->AddComponent<MeshRenderer>(false);
        exportFromTransformationMatrix(glm::make_mat4(&node->mTransformation.Transpose().a1), gameObject->transform);
		for(unsigned int i = 0U; i < node->mNumMeshes; i++)
		{
			std::vector<MeshFactory::TexturedVertex> vertexList;
			std::vector<unsigned int> indexList;
			for(unsigned int j = 0U; j < model->mMeshes[node->mMeshes[i]]->mNumVertices; j++)
			{
				aiVector3D vertice = model->mMeshes[node->mMeshes[i]]->mVertices[j];
				aiVector3D normal = model->mMeshes[node->mMeshes[i]]->mNormals[j];
				aiVector3D texCoord = model->mMeshes[node->mMeshes[i]]->mTextureCoords[0][j];
				
				vertexList.push_back(MeshFactory::TexturedVertex{glm::vec3(vertice.x, vertice.y, vertice.z), glm::vec2(texCoord.x, texCoord.y), glm::vec3(normal.x, normal.y, normal.z)});
			}
			for(unsigned int j = 0U; j < model->mMeshes[node->mMeshes[i]]->mNumFaces; j++)
			{
				for(unsigned int k = 0U; k < model->mMeshes[node->mMeshes[i]]->mFaces[j].mNumIndices; k++)
				{
					indexList.push_back(model->mMeshes[node->mMeshes[i]]->mFaces[j].mIndices[k]);
				}
			}

			aiMaterial* material = model->mMaterials[model->mMeshes[node->mMeshes[i]]->mMaterialIndex];
			
			aiString path;
			std::shared_ptr<Texture> texturePtr = nullptr;
			aiColor4D color;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			if((material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS))
			{
				const std::string pathStr = std::string(path.C_Str());
				const auto it = loadedTexturesMap.find(pathStr);
				if(it != loadedTexturesMap.end())
				{
					texturePtr = it->second;
				}
				else if(!pathStr.empty())
				{
					const aiTexture* embeddedTexture = model->GetEmbeddedTexture(pathStr.c_str());
					if(embeddedTexture)
					{	
						texturePtr = TextureLoader::LoadTexture((void*)embeddedTexture->pcData, embeddedTexture->mWidth, embeddedTexture->mHeight, GL_RGBA, GL_RGBA);
					}
					else
					{
						texturePtr = TextureLoader::LoadTexture(TEXTURES_DIRECTORY + pathStr);
					}

					loadedTexturesMap[pathStr] = texturePtr;
				}
                else
                {
                    assert(false);
                }
			}
			
            // std::shared_ptr<GameObject> child = scene->CreateObject(std::string(model->mMeshes[node->mMeshes[i]]->mName.C_Str()), Vector3(), Quaternion(), Vector3(1.0f), gameObject->transform);

            // if(texturePtr)
            // {
            // 	child->AddComponent<MeshRenderer>(std::make_shared<Mesh>(vertexList, indexList), texturePtr);
            // }
            // else
            // {
            // 	child->AddComponent<MeshRenderer>(std::make_shared<Mesh>(vertexList, indexList), glm::vec3(color.r, color.g, color.b));
            // }

            if(texturePtr)
            {
                meshRenderer->AddMesh(std::make_shared<Mesh>(vertexList, indexList), texturePtr);
            }
            else
            {
                meshRenderer->AddMesh(std::make_shared<Mesh>(vertexList, indexList), glm::vec3(color.r, color.g, color.b));
            }
		}
		

		for(unsigned int i = 0U; i < node->mNumChildren; i++)
		{
            processChildNode(scene, model, scene->CreateObject(std::string(node->mChildren[i]->mName.C_Str()), Vector3(), Quaternion(), Vector3(1.0f), gameObject->transform), node->mChildren[i], loadedTexturesMap);
		}
	}
}

std::shared_ptr<GameObject> ObjectLoader::LoadGameObject(Scene* scene, _STRING_CR_ path)
{
	std::vector<unsigned int> indexList;
	std::vector<MeshFactory::TexturedVertex> vertexList;

	Assimp::Importer importer;
    // importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, 0.001f);
    // importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
    // importer.SetPropertyFloat(AI_CONFIG_APP_SCALE_KEY, 1.0f);
    const aiScene* model = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals | aiProcess_GlobalScale);
	std::cerr << importer.GetErrorString() << std::endl;
	assert(scene);
	std::unordered_map<std::string, std::shared_ptr<Texture>> loadedTexturesMap;
	std::shared_ptr<GameObject> gameObject = scene->CreateObject("Character");
	processChildNode(scene, model, gameObject, model->mRootNode, loadedTexturesMap);

	return gameObject;
}
