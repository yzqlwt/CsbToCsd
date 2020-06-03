#pragma once
#include "../CSParseBinary_generated.h"
#include "../Plugins/pugixml.hpp"
#include "../Plugins/tinyxml2.h"
#include <iostream>
#include <map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp> 
#include <iomanip>

class ISerializer :public boost::noncopyable{
public:
	virtual pugi::xml_node& toXmlNode(pugi::xml_node&) = 0;
	virtual void setProperties() = 0;
protected:
	void setWidgetOptionsProperties(const flatbuffers::WidgetOptions* widgetOptions)
	{
		auto options = widgetOptions;
		std::string name = options->name()->c_str();
		float x = options->position()->x();
		float y = options->position()->y();
		float scalex = options->scale()->scaleX();
		float scaley = options->scale()->scaleY();
		float rotationSkewX = options->rotationSkew()->rotationSkewX();
		float rotationSkewY = options->rotationSkew()->rotationSkewY();
		float anchorx = options->anchorPoint()->scaleX();
		float anchory = options->anchorPoint()->scaleY();
		int colorA = options->color()->a();
		int colorR = options->color()->r();
		int colorG = options->color()->g();
		int colorB = options->color()->b();
		int zorder = options->zOrder();
		int tag = options->tag();
		int actionTag = options->actionTag();
		bool visible = options->visible() != 0;
		float w = options->size()->width();
		float h = options->size()->height();
		int alpha = options->alpha();
		std::string customProperty = options->customProperty()->c_str();
		m_properties.insert(std::pair<std::string, boost::any>("Name", name));
		m_properties.insert(std::pair<std::string, boost::any>("PositionX", x));
		m_properties.insert(std::pair<std::string, boost::any>("PositionY", y));
		m_properties.insert(std::pair<std::string, boost::any>("ScaleX", scalex));
		m_properties.insert(std::pair<std::string, boost::any>("ScaleY", scaley));
		m_properties.insert(std::pair<std::string, boost::any>("RotationSkewX", rotationSkewX));
		m_properties.insert(std::pair<std::string, boost::any>("RotationSkewY", rotationSkewY));
		m_properties.insert(std::pair<std::string, boost::any>("AnchorX", anchorx));
		m_properties.insert(std::pair<std::string, boost::any>("AnchorY", anchory));
		m_properties.insert(std::pair<std::string, boost::any>("ZOrder", zorder));
		m_properties.insert(std::pair<std::string, boost::any>("Tag", tag));
		m_properties.insert(std::pair<std::string, boost::any>("ActionTag", actionTag));
		m_properties.insert(std::pair<std::string, boost::any>("Visible", visible));
		m_properties.insert(std::pair<std::string, boost::any>("Width", w));
		m_properties.insert(std::pair<std::string, boost::any>("Height", h));
		m_properties.insert(std::pair<std::string, boost::any>("Alpha", alpha));
		m_properties.insert(std::pair<std::string, boost::any>("ColorA", colorA));
		m_properties.insert(std::pair<std::string, boost::any>("ColorR", colorR));
		m_properties.insert(std::pair<std::string, boost::any>("ColorG", colorG));
		m_properties.insert(std::pair<std::string, boost::any>("ColorB", colorB));
		setLayoutComponentTable(widgetOptions);
	}

	void setLayoutComponentTable(const flatbuffers::WidgetOptions* widgetOptions)
	{
		auto layoutComponentTable = widgetOptions->layoutComponent();
		float leftMargin = layoutComponentTable->leftMargin();
		float rightMargin = layoutComponentTable->rightMargin();
		float topMargin = layoutComponentTable->topMargin();
		float bottomMargin = layoutComponentTable->bottomMargin();
		bool positionXPercentEnabled = layoutComponentTable->positionXPercentEnabled();
		bool positionYPercentEnabled = layoutComponentTable->positionYPercentEnabled();
		float positionXPercent = layoutComponentTable->positionXPercent();
		float positionYPercent = layoutComponentTable->positionYPercent();
		bool sizeXEnabled = layoutComponentTable->sizeXPercentEnable();
		bool sizeYEnabled = layoutComponentTable->sizeYPercentEnable();
		float sizeXPercent = layoutComponentTable->sizeXPercent();
		float sizeYPercent = layoutComponentTable->sizeYPercent();
		m_properties.insert(std::pair<std::string, boost::any>("LeftMargin", leftMargin));
		m_properties.insert(std::pair<std::string, boost::any>("RightMargin", rightMargin));
		m_properties.insert(std::pair<std::string, boost::any>("TopMargin", topMargin));
		m_properties.insert(std::pair<std::string, boost::any>("BottomMargin", bottomMargin));
		m_properties.insert(std::pair<std::string, boost::any>("PositionXPercentEnabled", positionXPercentEnabled));
		m_properties.insert(std::pair<std::string, boost::any>("PositionYPercentEnabled", positionYPercentEnabled));
		m_properties.insert(std::pair<std::string, boost::any>("PositionXPercent", positionXPercent));
		m_properties.insert(std::pair<std::string, boost::any>("PositionYPercent", positionYPercent));
		m_properties.insert(std::pair<std::string, boost::any>("SizeXPercentEnable", sizeXEnabled));
		m_properties.insert(std::pair<std::string, boost::any>("SizeYPercentEnable", sizeYEnabled));
		m_properties.insert(std::pair<std::string, boost::any>("SizeXPercent", sizeXPercent));
		m_properties.insert(std::pair<std::string, boost::any>("SizeYPercent", sizeYPercent));
	}

	pugi::xml_node& createAbstractNodeData(pugi::xml_node& parent)
	{
		auto node = parent.append_child("AbstractNodeData");
		std::string name = boost::any_cast<std::string>(getProperty("Name"));
		node.append_attribute("Name").set_value(name.c_str());
		int actionTag = boost::any_cast<int>(getProperty("ActionTag"));
		node.append_attribute("ActionTag").set_value(std::to_string(actionTag).c_str());
		int tag = boost::any_cast<int>(getProperty("Tag"));
		node.append_attribute("Tag").set_value(std::to_string(tag).c_str());
		node.append_attribute("IconVisible").set_value("False");
		auto positionPercentXEnabled = boost::any_cast<bool>(getProperty("PositionXPercentEnabled"));
		node.append_attribute("PositionXPercentEnabled").set_value(positionPercentXEnabled ? "True":"False");
		auto leftMargin = boost::any_cast<float>(getProperty("LeftMargin"));
		node.append_attribute("LeftMargin").set_value(std::to_string(leftMargin).c_str());
		auto rightMargin = boost::any_cast<float>(getProperty("RightMargin"));
		node.append_attribute("RightMargin").set_value(std::to_string(rightMargin).c_str());
		auto topMargin = boost::any_cast<float>(getProperty("TopMargin"));
		node.append_attribute("TopMargin").set_value(std::to_string(topMargin).c_str());
		auto bottomMargin = boost::any_cast<float>(getProperty("BottomMargin"));
		node.append_attribute("BottomMargin").set_value(std::to_string(bottomMargin).c_str());
		createLayoutNode(&node);
		return node;
	}
	
	void createLayoutNode(pugi::xml_node* parent)
	{
		auto sizeNode = parent->append_child("Size");
		auto anchrPointNode = parent->append_child("AnchorPoint");
		auto positionNode = parent->append_child("Position");
		auto scaleNode = parent->append_child("Scale");
		auto colorNode = parent->append_child("CColor");
		auto prePositionNode = parent->append_child("PrePosition");
		auto preSizeNode = parent->append_child("PreSize");
		
		auto width = boost::any_cast<float>(getProperty("Width"));
		auto height = boost::any_cast<float>(getProperty("Height"));
		sizeNode.append_attribute("X").set_value(std::to_string(width).c_str());
		sizeNode.append_attribute("Y").set_value(std::to_string(height).c_str());

		auto anchrScaleX = boost::any_cast<float>(getProperty("AnchorX"));
		auto anchrScaleY = boost::any_cast<float>(getProperty("AnchorY"));
		anchrPointNode.append_attribute("ScaleX").set_value(std::to_string(anchrScaleX).c_str());
		anchrPointNode.append_attribute("ScaleY").set_value(std::to_string(anchrScaleY).c_str());

		auto posX = boost::any_cast<float>(getProperty("PositionX"));
		auto posY = boost::any_cast<float>(getProperty("PositionY"));
		positionNode.append_attribute("X").set_value(std::to_string(posX).c_str());
		positionNode.append_attribute("Y").set_value(std::to_string(posY).c_str());

		auto sacleX = boost::any_cast<float>(getProperty("ScaleX"));
		auto sacleY = boost::any_cast<float>(getProperty("ScaleY"));
		scaleNode.append_attribute("ScaleX").set_value(std::to_string(sacleX).c_str());
		scaleNode.append_attribute("ScaleY").set_value(std::to_string(sacleY).c_str());

		auto colorA = boost::any_cast<int>(getProperty("ColorA"));
		auto colorR = boost::any_cast<int>(getProperty("ColorR"));
		auto colorG = boost::any_cast<int>(getProperty("ColorG"));
		auto colorB = boost::any_cast<int>(getProperty("ColorB"));
		colorNode.append_attribute("A").set_value(std::to_string(colorA).c_str());
		colorNode.append_attribute("R").set_value(std::to_string(colorR).c_str());
		colorNode.append_attribute("G").set_value(std::to_string(colorG).c_str());
		colorNode.append_attribute("B").set_value(std::to_string(colorB).c_str());

		auto positionXPercent = boost::any_cast<float>(getProperty("PositionXPercent"));
		auto positionYPercent = boost::any_cast<float>(getProperty("PositionYPercent"));
		prePositionNode.append_attribute("X").set_value(std::to_string(positionXPercent).c_str());
		prePositionNode.append_attribute("Y").set_value(std::to_string(positionYPercent).c_str());

		auto sizeXPercent = boost::any_cast<float>(getProperty("SizeXPercent"));
		auto sizeYPercent = boost::any_cast<float>(getProperty("SizeYPercent"));
		preSizeNode.append_attribute("X").set_value(std::to_string(sizeXPercent).c_str());
		preSizeNode.append_attribute("Y").set_value(std::to_string(sizeYPercent).c_str());
	}
	
	boost::any getProperty(const char* key)
	{
		auto iter = m_properties.find(key);
		return iter != m_properties.end() ? iter->second : NULL;
	}

	std::string toString(float number, int bits)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(bits) << number;
		return ss.str();
	}




protected:
	const flatbuffers::WidgetOptions* m_widgetOptions;
	std::map<std::string, boost::any> m_properties;
};
