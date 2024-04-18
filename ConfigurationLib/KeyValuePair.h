#pragma once
#include <string>

class KeyValuePair
{
private:
	std::string key;
	std::string value;

public:
	KeyValuePair(std::string key, std::string value);
	~KeyValuePair() = default;
	std::string getKey() const noexcept;
	std::string getValue() const noexcept;
	void setKey(std::string key) noexcept;
	void setValue(std::string value) noexcept;
};

