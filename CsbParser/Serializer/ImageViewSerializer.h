#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class ImageViewSerializer :
	public ISerializer
{
public:
	static ImageViewSerializer* createInstance(const flatbuffers::WidgetOptions* options){
		return new ImageViewSerializer(options);
	}
	ImageViewSerializer(const flatbuffers::WidgetOptions* options)
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
		addExtendAttr(&absNode);
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
		auto scale9Enabled = spriteOptions->scale9Enabled() != 0 ;
		auto capHeight = spriteOptions->capInsets()->height();
		auto capWidth = spriteOptions->capInsets()->width();
		auto capX = spriteOptions->capInsets()->x();
		auto capY = spriteOptions->capInsets()->y();
		std::string resType = "Default";
		if (type == 0)
			resType = "Normal";
		else if (type == 1)
			resType = "PlistSubImage";
		m_properties.insert(std::pair<std::string, boost::any>("Scale9Enable", scale9Enabled == 0 ? "True" : "False"));
		m_properties.insert(std::pair<std::string, boost::any>("Scale9OriginX", capX));
		m_properties.insert(std::pair<std::string, boost::any>("Scale9OriginY", capY));
		m_properties.insert(std::pair<std::string, boost::any>("Scale9Width", capWidth));
		m_properties.insert(std::pair<std::string, boost::any>("Scale9Height", capHeight));
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

	void addExtendAttr(pugi::xml_node* absNode)
	{
		auto spriteOptions = (flatbuffers::ImageViewOptions*)m_widgetOptions;
		auto width = spriteOptions->scale9Size()->width();
		auto height = spriteOptions->scale9Size()->height();
		auto scale9Enabled = spriteOptions->scale9Enabled() != 0;
		auto capHeight = spriteOptions->capInsets()->height();
		auto capWidth = spriteOptions->capInsets()->width();
		auto capX = spriteOptions->capInsets()->x();
		auto capY = spriteOptions->capInsets()->y();
		absNode->append_attribute("ctype").set_value("ImageViewObjectData");
		absNode->append_attribute("Scale9Enable").set_value(scale9Enabled == 0 ? "True" : "False");
		absNode->append_attribute("Scale9OriginX").set_value(capX);
		absNode->append_attribute("Scale9OriginY").set_value(capY);
		absNode->append_attribute("Scale9Width").set_value(capWidth);
		absNode->append_attribute("Scale9Height").set_value(capHeight);
	}
	
};

