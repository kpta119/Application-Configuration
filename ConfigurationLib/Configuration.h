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
	std::vector<KeyValuePair> getConfig() const noexcept;
	void setWriteProtected() noexcept;
	bool hasKey(std::string const& key) const noexcept;
	bool write(std::string const& key, std::string const& value) noexcept;
	std::string operator[](std::string const& key) const noexcept;

	Configuration operator+(Configuration const& configuration2) const;
	void operator+=(Configuration const& configuration2);
	Configuration operator-(Configuration const& configuration2) const;
	void operator-=(Configuration const& configuration2);

	friend std::ostream& operator<<(std::ostream& os, Configuration const& c);
	friend std::istream& operator>>(std::istream& is, Configuration& c);
};

