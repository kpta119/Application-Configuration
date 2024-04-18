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