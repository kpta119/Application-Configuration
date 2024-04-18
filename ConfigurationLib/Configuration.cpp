#include "Configuration.h"
#include "KeyValuePair.h"
#include <vector>
#include <string>
#include <iostream>

Configuration::Configuration() 
{
	writeProtected = false;
}

void Configuration::setWriteProtected() noexcept
{
	writeProtected = true;
}

std::vector<KeyValuePair> Configuration::getConfig() const noexcept
{
	return config;
}

bool Configuration::hasKey(std::string const& key) const noexcept
{
	for (KeyValuePair const& pair : config)
	{
		if (pair.getKey() == key)
		{
			return true;
		}
	}
	return false;
}

std::string Configuration::operator[](std::string const& key) const noexcept
{
	for (KeyValuePair const& pair : config)
	{
		if (pair.getKey() == key)
		{
			return pair.getValue();
		}
	}
	return "";
}

bool Configuration::write(std::string const& key, std::string const& value) noexcept
{
	if (writeProtected)
	{
		return false;
	}
	for (KeyValuePair & pair : config)
	{
		if (pair.getKey() == key)
		{
			pair.setValue(value);
			return true;
		}
	}
	config.push_back(KeyValuePair(key, value));
	return true;
}


Configuration Configuration::operator+(Configuration const& configuration2) const
{
	Configuration newConfig = *this;
	newConfig += configuration2;
	return newConfig;
}


void Configuration::operator+=(Configuration const& configuration2)
{
	if (writeProtected)
	{
		throw std::logic_error("Object is read-only");
	}
	for (KeyValuePair const& pair : configuration2.config)
	{	if (!hasKey(pair.getKey()))
		{
			write(pair.getKey(), pair.getValue());
		}
	}
}


Configuration Configuration::operator-(Configuration const& configuration2) const
{
	Configuration newConfig = *this;
	newConfig -= configuration2;
	return newConfig;
}


void Configuration::operator-=(Configuration const& configuration2)
{
	if (writeProtected)
	{
		throw std::logic_error("Object is read-only");
	}
	for (std::vector<KeyValuePair>::iterator it = config.begin(); it != config.end(); ++it)
	{
		if (configuration2.hasKey((*it).getKey()))
		{
			config.erase(it);
		}
	}
}

std::ostream& operator<<(std::ostream& os, Configuration const& c)
{
	for (KeyValuePair const& pair : c.config)
	{
		os << pair.getKey() << " : " << pair.getValue() << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Configuration& c)
{
	std::string key;
	std::string value;
	while (is >> key >> value)
	{
		c.write(key, value);
	}
	return is;
}