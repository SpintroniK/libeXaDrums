/*
 * Xml.h
 *
 *  Created on: 11 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_XML_H_
#define SOURCE_UTIL_XML_H_

#include <tinyxml2.h>

#include <sstream>
#include <string>
#include <vector>

namespace Util
{

    struct XmlAttr
    {
        template <typename T>
        XmlAttr(std::string name_, const T& val) : name(std::move(name_))
        {
            std::ostringstream oss;
            oss << val;
            value = std::move(oss.str());
        }

        std::string name;
        std::string value;
    };


    template <typename T = std::string>
    tinyxml2::XMLElement* CreateXmlElement(tinyxml2::XMLDocument& doc, const std::string name, const T& text = "", const std::vector<XmlAttr>& attributes = {})
    {
        namespace xml = tinyxml2;

        xml::XMLElement* element = doc.NewElement(name.data());

        std::ostringstream oss;
        oss << text;

        if(!oss.str().empty())
        {
            element->SetText(oss.str().data());
        }

        for(const auto& itAttr : attributes)
        {
            element->SetAttribute(itAttr.name.data(), itAttr.value.data());
        }

        return element;
    }


    template <typename T>
    void GetXmlElementValue(tinyxml2::XMLElement* root, const std::string& name, T& text)
    {

        tinyxml2::XMLElement* xmlElement = root->FirstChildElement(name.data());
        std::istringstream iss(xmlElement->GetText());

        iss >> text;
    }

    template <typename T>
    void GetXmlElementAttribute(tinyxml2::XMLElement* root, const std::string& name, const std::string& attributeName, T& attributeValue)
    {
        tinyxml2::XMLElement* xmlElement = root->FirstChildElement(name.data());
        std::istringstream iss(xmlElement->Attribute(attributeName.data()));

        iss >> attributeValue;
    }
}


#endif /* SOURCE_UTIL_XML_H_ */
