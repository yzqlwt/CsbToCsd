#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class SpriteSerializer :
	public ISerializer
{
public:
	static SpriteSerializer* createInstance(const flatbuffers::WidgetOptions* options){
		return new SpriteSerializer(options);
	}
	SpriteSerializer(const flatbuffers::WidgetOptions* options)
	{
		m_widgetOptions = options;
	}
	
protected:
	pugi::xml_node& toXmlNode(pugi::xml_node& xmlNode) override
	{
		auto spriteOptions = (flatbuffers::SpriteOptions*)m_widgetOptions;
		setWidgetOptionsProperties(spriteOptions->nodeOptions());
		setProperties();
		auto absNode = createAbstractNodeData(xmlNode);
		auto fileNode = createFileDataNode(&absNode);
		auto blendNode = createBlendNode(&absNode);
		return absNode;
	};
	void setProperties() override
	{
		auto spriteOptions = (flatbuffers::SpriteOptions*)m_widgetOptions;
		auto fileNameData = spriteOptions->fileNameData();
		std::string path = fileNameData->path()->c_str();
		std::string plistFile = fileNameData->plistFile()->c_str();
		int type = fileNameData->resourceType();
		std::string resType = "Default";
		if (type == 0)
			resType = "Normal";
		else if (type == 1)
			resType = "PlistSubImage";
		m_properties.insert(std::pair<std::string, boost::any>("FileDataType", resType));
		m_properties.insert(std::pair<std::string, boost::any>("FileDataPath", path));
		m_properties.insert(std::pair<std::string, boost::any>("FileDataPlist", plistFile));
		auto src = spriteOptions->blendFunc()->src();
		auto dst = spriteOptions->blendFunc()->dst();
		m_properties.insert(std::pair<std::string, boost::any>("Src", src));
		m_properties.insert(std::pair<std::string, boost::any>("Dst", dst));
	}
	pugi::xml_node& createFileDataNode(pugi::xml_node* absNode)
	{
		auto node = absNode->append_child("FileData");
		auto path = boost::any_cast<std::string>(getProperty("FileDataPath"));
		node.append_attribute("Path").set_value(path.c_str());
		auto plist = boost::any_cast<std::string>(getProperty("FileDataPlist"));
		node.append_attribute("Plist").set_value(plist.c_str());
		auto type = boost::any_cast<std::string>(getProperty("FileDataType"));
		node.append_attribute("Type").set_value(type.c_str());
		absNode->append_attribute("ctype").set_value("SpriteObjectData");
		return node;
	}

	pugi::xml_node& createBlendNode(pugi::xml_node* absNode)
	{
		auto node = absNode->append_child("BlendFunc");
		auto src = boost::any_cast<int>(getProperty("Src"));
		node.append_attribute("Src").set_value(src);
		auto dst = boost::any_cast<int>(getProperty("Dst"));
		node.append_attribute("Dst").set_value(dst);
		return node;
	}
	
};

