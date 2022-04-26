#pragma once

#include "../utils/logger.h"
#include "../utils/assert.h"
#include "../maths/maths.h"

#include "resourceloader.h" 

#include "../graphics/renderables/renderable2D.h"		// serialize renderable
#include "../graphics/scenes/scene.h"              // serialize scene

#include <yaml-cpp/emitterstyle.h>
#include <yaml-cpp/eventhandler.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <sstream>

namespace golden {

	// overload operators for vectors
	YAML::Emitter& operator<<(YAML::Emitter& out, const maths::Vec3& vec3)
	{
		out << YAML::Flow; // [x, y, z]
		out << YAML::BeginSeq << vec3.x << vec3.y << vec3.z << YAML::EndSeq;
		return out;
	}

	// static class which handles serialization of obeject in game
	class SerializationService
	{
	protected:
		SerializationService() { }

	public:
		// old serialization to json file
		#pragma region SERIALIZATION_SERVICE_FUNCS
#if 0
		/*---------------- MATHS ----------------*/
		inline static void serialize(
			& vec3, std::string nameofvec)
		{
			std::string textureOutTemplate = R"json({
			"value" : [xValue, yValue, zValue]
})json";

			//textureOutTemplate.replace(textureOutTemplate.find("namevar"), sizeof("namevar") - 1, nameoftexture);
			textureOutTemplate.replace(textureOutTemplate.find("xValue"), sizeof("xValue") - 1, std::to_string(vec3.x));
			textureOutTemplate.replace(textureOutTemplate.find("yValue"), sizeof("yValue") - 1, std::to_string(vec3.y));
			textureOutTemplate.replace(textureOutTemplate.find("zValue"), sizeof("zValue") - 1, std::to_string(vec3.z));

			std::string outDir = ResourceLoader::getProjectPath() + "projectData/serialized";

			if (!std::filesystem::exists(outDir))
			{
				FileManager::create_dir("projectData/serialized");
			}

			std::ofstream ofFile;
			std::string ofdir = outDir + "/" + "vec - " + nameofvec + ".json";
			ofFile.open(ofdir);

			Logger::logInfo(textureOutTemplate);

			ofFile << textureOutTemplate << std::endl;

			ofFile.close();
		}

		inline static void deserialize(maths::Vec3& vec3, std::string nameofvec) // deserialize json file
		{
			std::string inputdir = ResourceLoader::getProjectPath() + "projectData/serialized/" + "vec - " + nameofvec + ".json";
			std::string sourceData = FileManager::read_file(inputdir.c_str());

			maths::Vec3Spec to_vec;

			JS::ParseContext context(sourceData);

			//std::cout << context << std::endl;

			//std::cout << to_vec << std::endl;

			GE_ASSERT(context.parseTo(to_vec) != JS::Error::NoError, "Error prasing struct " + context.makeErrorString()); // if error occurs

			std::cout << "vec " << to_vec.data[0] << ", " << to_vec.data[1] << ", " << to_vec.data[2] << std::endl;
		}

		/*---------------- TEXTURE ----------------*/
		inline static void serialize(graphics::Texture* texture, std::string nameoftexture)
		{
			std::string textureOutTemplate = R"json({
	"name"    : "namevar",
	"ImgPath" : "ImgPathVariable"
})json";

			textureOutTemplate.replace(textureOutTemplate.find("namevar"), sizeof("namevar") - 1, nameoftexture);
			textureOutTemplate.replace(textureOutTemplate.find("ImgPathVariable"), sizeof("ImgPathVariable") - 1, texture->getImagePath());

			std::string outDir = ResourceLoader::getProjectPath() + "projectData/serialized";

			if (!std::filesystem::exists(outDir))
			{
				FileManager::create_dir("projectData/serialized");
			}

			std::ofstream ofFile;
			std::string ofdir = outDir + "/" + "texture-" + nameoftexture + ".json";
			ofFile.open(ofdir);

			ofFile << textureOutTemplate << std::endl;

			ofFile.close();
		}
		inline static void deserialize(graphics::Texture* texture, std::string nameoftexture) // deserialize json file
		{
			std::string inputdir = ResourceLoader::getProjectPath() + "projectData/serialized/" + "texture-" + nameoftexture + ".json";
			std::string sourceData = FileManager::read_file(inputdir.c_str());

			graphics::TextureSpec texSpec;

			JS::ParseContext context(sourceData);

			GE_ASSERT(context.parseTo(texSpec) != JS::Error::NoError, "Error prasing struct " + context.makeErrorString()); // if error occurs

			//std::cout << "deserialization\n" << "imgPath : " << texSpec.imagePath << std::endl;

			*texture = texSpec.convertToTexture();
		}

		/*---------------- COMPONENT ----------------*/
		inline static void serialize(const ecs::Component* comp, const std::string& nameOfRenderable)
		{
			std::string textureOutTemplate = R"json({
	"name" : "namevar"
})json";

			textureOutTemplate.replace(textureOutTemplate.find("namevar"), sizeof("namevar") - 1, comp->getName());
			std::string outDir = ResourceLoader::getProjectPath() + "projectData/serialized";

			if (!std::filesystem::exists(outDir))
			{
				FileManager::create_dir("projectData/serialized");
			}

			std::ofstream ofFile;

			std::string ofdir = outDir + "/" + "comp-" + comp->getName() + "_" + nameOfRenderable + ".json";

			ofFile.open(ofdir);
			ofFile << textureOutTemplate << std::endl;
			ofFile.close();
		}
		inline static void deserialize(ecs::Component* comp, const std::string& nameOfRenderable) // deserialize json file
		{
			std::string inputdir = ResourceLoader::getProjectPath() + "projectData/serialized/" + "comp-" + comp->getName() + "_" + nameOfRenderable + ".json";
			std::string sourceData = FileManager::read_file(inputdir.c_str());

			ecs::ComponentSpec compSpec;

			JS::ParseContext context(sourceData);

			GE_ASSERT(context.parseTo(compSpec) != JS::Error::NoError, "Error parsing struct " + context.makeErrorString());

			*comp = compSpec.convertToComponent();
		}

		/*---------------- SHADER ----------------*/
		inline static void serialize(const graphics::Shader* shader, const std::string& nameOfShader = "empty")
		{
			std::string textureOutTemplate = R"json({
	"name"     : "namevar",
	"vertPath" : "nameofvert",
	"fragPath" : "nameoffrag"
})json";

			// insert variables
			textureOutTemplate.replace(textureOutTemplate.find("namevar"), sizeof("namevar") - 1, nameOfShader);
			textureOutTemplate.replace(textureOutTemplate.find("nameofvert"), sizeof("nameofvert") - 1, shader->getVertPath());
			textureOutTemplate.replace(textureOutTemplate.find("nameoffrag"), sizeof("nameoffrag") - 1, shader->getFragPath());

			std::string outDir = ResourceLoader::getProjectPath() + "projectData/serialized";

			if (!std::filesystem::exists(outDir))
			{
				FileManager::create_dir("projectData/serialized");
			}

			std::ofstream ofFile;

			std::string ofdir = outDir + "/" + "shader - " + ((shader->getName() != "empty") ? shader->getName() : nameOfShader) + ".json";

			ofFile.open(ofdir);
			ofFile << textureOutTemplate << std::endl;
			ofFile.close();
		}
		inline static void deserialize(graphics::Shader* shader, const std::string& nameOfShader) // deserialize json file
		{
			std::string inputdir = ResourceLoader::getProjectPath() + "projectData/serialized/" + "shader-" + nameOfShader + ".json";
			std::string sourceData = FileManager::read_file(inputdir.c_str());

			graphics::ShaderSpec shaderSpec;

			JS::ParseContext context(sourceData);

			GE_ASSERT(context.parseTo(shaderSpec) != JS::Error::NoError, "Error parsing struct " + context.makeErrorString());

			//std::cout << "deserialization\n" << "name : " << shaderSpec.name << "\nvertPath : " << shaderSpec.vertPath << "\nfragPath : " << shaderSpec.fragPath << std::endl;
			*shader = shaderSpec.convertToShader();
		}

#endif
#pragma endregion

		static void serializeRenderable(graphics::Renderable2D* sprite, YAML::Emitter& out)
		{
			out << YAML::BeginMap; // Renderable2D
			out << YAML::Key << "Renderable"  << YAML::Value << sprite->getRenderable2dID();
			out << YAML::Key << "Name"		  << YAML::Value << sprite->getName();
			if(sprite->getTexturePath() != "empty")
				out << YAML::Key << "TexturePath" << YAML::Value << sprite->getTexturePath();

			if (sprite->hasComponent<ecs::TagComponent>())
			{
				out << YAML::Key << "TagComponent";
				out << YAML::BeginMap; // Tag Component

				auto& tag = sprite->getComponent<ecs::TagComponent>()->tag;
				out << YAML::Key << "Tag" << YAML::Value << tag;

				out << YAML::EndMap;	// Tag Component
			}

			if (sprite->hasComponent<ecs::TransformComponent>())
			{
				out << YAML::Key << "TransformComponent";
				out << YAML::BeginMap; // Transform Component

				auto& trns = sprite->getComponent<ecs::TransformComponent>();
				out << YAML::Key << "Position" << YAML::Value << trns->position;
				out << YAML::Key << "Rotation" << YAML::Value << trns->rotation;
				out << YAML::Key << "Scale" << YAML::Value << trns->scale;

				out << YAML::EndMap;	// Transform Component
			}

			out << YAML::EndMap;  // Renderable2D
		}

		/* --- SCENE --- */
		static void serializeScene(graphics::Scene* scene)
		{
			YAML::Emitter out;
			out << YAML::BeginMap; // scene
			out << YAML::Key << "Scene"  << YAML::Value << scene->getName();
			out << YAML::Key << "Layers" << YAML::BeginSeq; // layers
			
			for (auto& layer : scene->getLayers())
			{
				out << YAML::BeginMap; // layer
				out << YAML::Key << "Layer" << YAML::Value << layer.first;
				out << YAML::Key << "Renderables" << YAML::BeginSeq; // renderables

				for (graphics::Renderable2D* renderable : layer.second->getRenderables())
				{
					serializeRenderable(renderable, out);
				}

				out << YAML::EndSeq; // renderables
				out << YAML::EndMap; // layer
			}

			out << YAML::EndSeq; // layers
			out << YAML::EndMap; // scene

			std::string outDir = ResourceLoader::getResourcePath() + "scenes";

			if (!std::filesystem::exists(outDir))
				FileManager::create_dir("assets/scenes");

			std::ofstream oFile(outDir + "/" + scene->getName() + ".GoldenEngine");
			oFile << out.c_str();

			oFile.close();
		}

		static bool deserializeScene(const std::string& scene_name)
		{
			std::string filepath = ResourceLoader::getResourcePath() + "scenes/" + scene_name + ".GoldenEngine";
			std::ifstream istream(filepath);
			std::stringstream ss;
			ss << istream.rdbuf();

			YAML::Node data = YAML::Load(ss.str());
			if (!data["Scene"])
				return false;

			std::string scenename = data["Scene"].as<std::string>();

			auto renderables = data["Renderables"];

			if (renderables)
			{
				for (auto renderable : renderables)
				{
					uint32_t rid		 = renderable["Renderable"].as<uint32_t>();
					std::string name	 = renderable["Name"].as<std::string>();
					std::string textpath = renderable["TexturePath"].as<std::string>();
					std::string tag      = "empty";

					auto tagComp = renderable["TagComponent"];
					if (tagComp)
						tag = tagComp["Tag"].as<std::string>();

					//std::cout << "name is " << name << ", textpath is " << textpath << ", tag is " << tag << std::endl;
				}
			}
			return true;
		}

#if 0
		inline static void clearDataFolder()
		{
			std::filesystem::remove_all(ResourceLoader::getProjectPath() + "projectData/serialized/");
		}
#endif
	};
}