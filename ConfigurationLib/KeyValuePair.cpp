#include "KeyValuePair.h"
#include <string>

KeyValuePair::KeyValuePair(std::string key, std::string value) {
	this->key = key;
	this->value = value;
}

std::string KeyValuePair::getKey() {
	return key;
}

std::string KeyValuePair::getValue() {
	return value;
}

void KeyValuePair::setValue(std::string value) {
	this->value = value;
}

void KeyValuePair::setKey(std::string key) {
	this->key = key;
}
