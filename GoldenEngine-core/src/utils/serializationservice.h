#pragma once

#include "../utils/logger.h"

#include "../../extLibs/json_struct/json_struct.h" // serialize to json
#include "resourceloader.h" 
#include "../graphics/texture.h" // serialize texture
#include "../components/components_pack.h" // serialize component
#include "../graphics/shader.h" // serialize shader

#include <fstream>

namespace golden {

	// static class which handles serialization of obeject in game
	class SerializationService
	{
	protected:
		SerializationService() { }

	public:
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

			if (context.parseTo(texSpec) != JS::Error::NoError) // if error appears
			{
				std::string errorStr = context.makeErrorString();
				fprintf(stderr, "Error parsing struct %s\n", errorStr.c_str());
			}

			std::cout << "deserialization\n" << "imgPath : " << texSpec.imagePath << std::endl;

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

			if (context.parseTo(compSpec) != JS::Error::NoError) // if error appears
			{
				std::string errorStr = context.makeErrorString();
				fprintf(stderr, "Error parsing struct %s\n", errorStr.c_str());
			}

			*comp = compSpec.convertToComponent();
		}

		/*---------------- SHADER ----------------*/
		inline static void serialize(const graphics::Shader* shader, const std::string& nameOfShader)
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

			std::string ofdir = outDir + "/" + "shader-" + nameOfShader + ".json";

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

			if (context.parseTo(shaderSpec) != JS::Error::NoError) // if error appears
			{
				std::string errorStr = context.makeErrorString();
				fprintf(stderr, "Error parsing struct %s\n", errorStr.c_str());
			}

			//std::cout << "deserialization\n" << "name : " << shaderSpec.name << "\nvertPath : " << shaderSpec.vertPath << "\nfragPath : " << shaderSpec.fragPath << std::endl;
			*shader = shaderSpec.convertToShader();
		}	

		inline static void clearDataFolder() // TODO : in future add removing sub folders
		{
			std::filesystem::remove_all(ResourceLoader::getProjectPath() + "projectData/serialized/");
		}
	};
}