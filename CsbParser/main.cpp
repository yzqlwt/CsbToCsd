// CsbParser.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "CSParseBinary_generated.h"
#include "ObjectFactory.h"
#include "Serializer/SpriteSerializer.h"
#include "Serializer/NodeSerializer.h"
#include "Serializer/SingleNodeSerializer.h"
#include "Serializer/ImageViewSerializer.h"
#include "Serializer/ButtonSerializer.h"
#include "Serializer/PanelSerializer.h"
#include "Serializer/TextSerializer.h"
#include "Plugins/tinyxml2.h"
using namespace std;

#define CREATE_CLASS(className) \
    ObjectFactory::TInfo(#className, &className::createInstance) \

const char* csdStr = 
"<?xml version=\"1.0\"?> \
<GameFile> \
	<PropertyGroup Name = \"Layer\" Type = \"Layer\" ID = \"w52uj8ste7qpo6xizmykbhfndrg3cv4a19l - \" Version = \"3.10.0.0\" /> \
	<Content ctype = \"GameProjectContent\" > \
		<Content /> \
	</Content> \
</GameFile> \
";

char* buffer = nullptr;
char* initBufferByCsb(string filePath);
void Parse(const flatbuffers::NodeTree* tree, pugi::xml_node& node);
void registerClass();


int main()
{
	registerClass();
	const char* filePath = "C:\\Users\\yzqlwt\\Documents\\WorkSpace\\cocos-ui\\mangomath-ui\\publish\\res\\ui\\games\\game150\\skin01\\Layer.csb";
	initBufferByCsb(filePath);
	auto csbBin = flatbuffers::GetCSParseBinary(buffer);
	pugi::xml_document xml_doc;
	pugi::xml_parse_result result = xml_doc.load_string(csdStr);
	auto Content = xml_doc.child("GameFile").child("Content").child("Content");
	Parse(csbBin->nodeTree(), Content);
	xml_doc.save_file("C:\\Users\\yzqlwt\\Documents\\WorkSpace\\cocos-ui\\mangomath-ui\\cocosstudio\\Test.csd");
	return 0;
}

char* initBufferByCsb(string filePath){
	long size;
	ifstream in(filePath, ios::in | ios::binary | ios::ate);
	size = in.tellg();
	in.seekg(0, ios::beg);
	buffer = new char[size];
	in.read(buffer, size);
	in.close();
	return buffer;
}
void registerClass(){
	CREATE_CLASS(SpriteSerializer);
	CREATE_CLASS(NodeSerializer);
	CREATE_CLASS(SingleNodeSerializer);
	CREATE_CLASS(ImageViewSerializer);
	//CREATE_CLASS(TextSerializer);
	//CREATE_CLASS(ButtonSerializer);
	//CREATE_CLASS(PanelSerializer);
}

void Parse(const flatbuffers::NodeTree* tree, pugi::xml_node& parentNode){
	auto widgetOption = tree->options()->data();
	auto className = tree->classname();
	auto customClassName = tree->customClassName();
	auto children = tree->children();
	auto childrenNum = children->Length();

	cout << className->c_str() << " -- " <<customClassName->c_str()<< endl;
	string suffix = "Serializer";
	auto serizlizerName = string(className->c_str()) + suffix;
	auto object = ObjectFactory::getInstance()->createObject(serizlizerName.c_str(), widgetOption);
	if(object!=nullptr)
	{
		auto temp = object->toXmlNode(parentNode);
		if (childrenNum>0)
		{
			auto childrenNode = temp.append_child("Children");
			for (auto index = 0; index < childrenNum; index++)
			{
				auto child = children->Get(index);
				Parse(child, childrenNode);
			}
		}

	}else
	{
		cout << "暫不支持" <<className->c_str() << endl;
	}

}
