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



	/**
	 * Structure that holds an xml attribute: a name and a value.
	 */
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

    /**
     * Creates a new xml element.
     * @param doc Xml document in which the xml element is to be inserted.
     * @param name Tag name of the xml element.
     * @param text Contents.
     * @param attributes Xml attributes.
     * @return
     */
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

    /**
     * Gets the value (contents) of an xml element.
     * @param element Pointer to the parent element.
     * @param name Name of the xml element.
     * @param text Variable in which the element's value is copied.
     */
    template <typename T>
    void GetXmlElementValue(tinyxml2::XMLElement* element, const std::string& name, T& text)
    {

        tinyxml2::XMLElement* xmlElement = element->FirstChildElement(name.data());
        std::istringstream iss(xmlElement->GetText());

        iss >> text;
    }

    /**
     * Get the value of an xml attribute.
     * @param element Pointer to the parent element.
     * @param name Name of the xml element.
     * @param attributeName Name of the xml attribute.
     * @param attributeValue Variable in which the attribute's value is copied.
     */
    template <typename T>
    void GetXmlElementAttribute(tinyxml2::XMLElement* element, const std::string& name, const std::string& attributeName, T& attributeValue)
    {
        tinyxml2::XMLElement* xmlElement = element->FirstChildElement(name.data());
        std::istringstream iss(xmlElement->Attribute(attributeName.data()));

        iss >> attributeValue;
    }
}


#endif /* SOURCE_UTIL_XML_H_ */
