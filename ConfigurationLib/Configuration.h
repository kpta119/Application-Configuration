#include <vector>
#include <string>
#include <iostream>
#include "KeyValuePair.h"

class Configuration
{
private:
	std::vector<KeyValuePair> config;
	bool writeProtected;

public:
	Configuration();
	void setWriteProtected() noexcept;
	bool hasKey(std::string const& key) const noexcept;
	bool write(std::string const& key, std::string const& value) noexcept;
	std::string operator[](std::string const& key) const noexcept;
	Configuration operator+(Configuration const& configuration2) const;
	void operator+=(Configuration const& configuration2);
	Configuration operator-(Configuration const& configuration2) const;
	void operator-=(Configuration const& configuration2);
	friend std::ostream& operator<<(std::ostream& os, Configuration const& p);
};

