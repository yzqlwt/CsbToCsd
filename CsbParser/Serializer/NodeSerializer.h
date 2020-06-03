#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class NodeSerializer :
	public ISerializer
{
public:
	static NodeSerializer* createInstance(const flatbuffers::WidgetOptions* options) {
		return new NodeSerializer(options);
	}
	NodeSerializer(const flatbuffers::WidgetOptions* options)
	{
		m_widgetOptions = options;
	}

protected:
	pugi::xml_node& toXmlNode(pugi::xml_node& xmlNode) override
	{
		auto options = m_widgetOptions;
		auto absNode = xmlNode.append_child("ObjectData");
		std::string name = options->name()->c_str();
		absNode.append_attribute("Name").set_value(name.c_str());
		absNode.set_name("ObjectData");
		absNode.append_attribute("ctype").set_value("GameLayerObjectData");
		auto sizeNode = absNode.append_child("Size");
		float w = options->size()->width();
		float h = options->size()->height();
		sizeNode.append_attribute("X").set_value(std::to_string(w).c_str());
		sizeNode.append_attribute("Y").set_value(std::to_string(h).c_str());
		return absNode;
	};
	void setProperties() override
	{
		
	}


};

