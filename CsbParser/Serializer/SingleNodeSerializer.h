#pragma once

#include "ISerializer.h"
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include <memory>

class SingleNodeSerializer :
	public ISerializer
{
public:
	static SingleNodeSerializer* createInstance(const flatbuffers::WidgetOptions* options) {
		return new SingleNodeSerializer(options);
	}
	SingleNodeSerializer(const flatbuffers::WidgetOptions* options)
	{
		m_widgetOptions = options;
	}

protected:
	pugi::xml_node& toXmlNode(pugi::xml_node& xmlNode) override
	{
		auto options = (flatbuffers::SingleNodeOptions* )m_widgetOptions;
		setWidgetOptionsProperties(options->nodeOptions());
		setProperties();
		auto absNode = createAbstractNodeData(xmlNode);
		absNode.append_attribute("ctype").set_value("SingleNodeObjectData");
		absNode.attribute("IconVisible").set_value("True");
		return absNode;
	};
	void setProperties() override
	{
		
	}

};

