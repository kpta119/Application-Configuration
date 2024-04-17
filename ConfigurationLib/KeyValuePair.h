#include <string>
class KeyValuePair
{
private:
	std::string key;
	std::string value;
public:
	KeyValuePair(std::string key, std::string value);
	~KeyValuePair();
	std::string getKey();
	std::string getValue();
	void setKey(std::string key);
	void setValue(std::string value);
};

