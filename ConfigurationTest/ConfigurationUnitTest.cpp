#include "gtest/gtest.h"
#include "../ConfigurationLib/Configuration.h"
#include "../ConfigurationLib/KeyValuePair.h"
#include <iostream>

TEST(ConstructorConfigurationTest, CreatingConfigurationObject) 
{
	Configuration c;
	EXPECT_EQ(0, c.getConfig().size());
}

TEST(HasKeyTest, CheckingIfKeyExistsInConfiguration)
{
	Configuration c;
	std::string key = "k";
	std::string value= "v";
	c.write(key, value);
	EXPECT_TRUE(c.hasKey(key));
}

TEST(HasKeyTest, CheckingIfKeyDoesNotExistInConfiguration)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	c.write(key, value);
	EXPECT_FALSE(c.hasKey("k2"));
}

TEST(HasKeyTest, CheckingIfKeyExistsInConfigurationWithEmptyConfiguration)
{
	Configuration c;
	EXPECT_FALSE(c.hasKey("k"));
}

TEST(SetWriteProtectedTest, SettingConfigurationWriteProtected)
{
	Configuration c;
	c.setWriteProtected();
	std::string key = "k";
	std::string value = "v";
	EXPECT_FALSE(c.write(key, value));
}

TEST(SetWriteProtectedTest, SettingConfigurationWriteProtectedWithAlreadyOneKeyValuePair)
{
	Configuration c; 
	std::string key = "k";
	std::string value = "v";
	EXPECT_TRUE(c.write(key, value));
	c.setWriteProtected();
	std::string key2 = "k2";
	std::string value2 = "v2";
	EXPECT_FALSE(c.write(key2, value2));
}

TEST(WriteKeyValuePairTest, AddingKeyValuePairToConfiguration)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	c.write(key, value);
	EXPECT_EQ(1, c.getConfig().size());
	for (KeyValuePair pair : c.getConfig())
	{
		EXPECT_EQ("k", pair.getKey());
		EXPECT_EQ("v", pair.getValue());
	}
}

TEST(WriteKeyValuePairTest, AddingKeyValuePairToConfigurationWithAlreadyOneKeyValuePair)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	EXPECT_TRUE(c.write(key, value));
	std::string key2 = "k2";
	std::string value2 = "v2";
	EXPECT_TRUE(c.write(key2, value2));
	EXPECT_EQ(2, c.getConfig().size());
	KeyValuePair pair1 = c.getConfig()[0];
	KeyValuePair pair2 = c.getConfig()[1];
	EXPECT_EQ("k", pair1.getKey());
	EXPECT_EQ("v", pair1.getValue());
	EXPECT_EQ("k2", pair2.getKey());
	EXPECT_EQ("v2", pair2.getValue());
}

TEST(WriteKeyValuePairTest, AddingKeyValuePairToConfigurationPairWithTheSameKey)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	EXPECT_TRUE(c.write(key, value));
	std::string key2 = "k";
	std::string value2 = "v2";
	EXPECT_TRUE(c.write(key2, value2));
	EXPECT_EQ(1, c.getConfig().size());
	KeyValuePair pair = c.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v2", pair.getValue());
}