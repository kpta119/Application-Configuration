#include "KeyValuePair.h"
#include <string>
#include <iostream>

KeyValuePair::KeyValuePair(std::string key, std::string value) {
	this->key = key;
	this->value = value;
}

std::string KeyValuePair::getKey() const noexcept
{
	return key;
}

std::string KeyValuePair::getValue() const noexcept
{
	return value;
}

void KeyValuePair::setValue(std::string value) noexcept
{
	this->value = value;
}

void KeyValuePair::setKey(std::string key) noexcept
{
	this->key = key;
}
