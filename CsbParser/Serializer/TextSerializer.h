#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class TextSerializer :
	public ISerializer
{
public:
	static TextSerializer* createInstance(const flatbuffers::WidgetOptions* options){
		return new TextSerializer(options);
	}
	TextSerializer(const flatbuffers::WidgetOptions* options)
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
		return absNode;
	};
	void setProperties() override
	{

	}

	
};

