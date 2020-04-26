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
	 * Xml Element wrapper, very useful for range-based for loops.
	 */
	class XmlElement
	{

	public:

		XmlElement(tinyxml2::XMLElement* element_, const std::string& name_) : element{element_}, name{name_} {}
		XmlElement(tinyxml2::XMLElement* element_) : element{element_}, name{} {}

		inline XmlElement begin() const
		{
			if(name.empty())
			{
				return XmlElement{element->FirstChildElement()};
			}

			return XmlElement{element->FirstChildElement(name.data())};
		}

		inline XmlElement end() const
		{
			return XmlElement{nullptr};
		}

		inline XmlElement operator++()
		{
			if(name.empty())
			{
				element = element->NextSiblingElement();
			}
			else
			{
				element = element->NextSiblingElement(name.data());
			}

			return *this;
		}

		inline XmlElement operator*() const
		{
			return *this;
		}

		inline bool operator!=(const XmlElement& xe) const
		{
			return element != xe.element;
		}

		inline const char* GetText() const
		{
			return element->GetText();
		}

		template <typename T>
		inline bool GetValue(T& value) const
		{
			if(!element)
			{
				value = T{};
				return false;
			}
			auto text = element->GetText();
			if(text == nullptr)
			{
				value = T{};
				return false;
			}
			std::istringstream iss{text};
			iss >> value;
			return true;
		}

		template <typename T>
		inline T GetValue() const
		{
			T value{};
			GetValue(value);
			return value;
		}

		template <typename T>
		inline void Attribute(const std::string& name, T& value) const
		{
			std::istringstream iss{element->Attribute(name.data())};
			iss >> value;
		}

		template <typename T>
		inline T Attribute(const std::string& name) const
		{
			T value{};
			Attribute<T>(name, value);
			return value;
		}

		inline XmlElement FirstChildElement(const std::string& childName) const
		{
			return XmlElement{element->FirstChildElement(childName.data())};
		}

	private:

		tinyxml2::XMLElement* element;
		std::string name;
	};

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
            value = oss.str();
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


}


#endif /* SOURCE_UTIL_XML_H_ */
