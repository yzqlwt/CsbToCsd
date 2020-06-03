#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class ButtonSerializer :
	public ISerializer
{
public:
	static ButtonSerializer* createInstance(const flatbuffers::WidgetOptions* options){
		return new ButtonSerializer(options);
	}
	ButtonSerializer(const flatbuffers::WidgetOptions* options)
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
		return absNode;
	};
	void setProperties() override
	{
		auto spriteOptions = (flatbuffers::ImageViewOptions*)m_widgetOptions;
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
		return node;
	}
	
};

