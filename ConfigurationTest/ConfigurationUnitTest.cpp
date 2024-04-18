#include "gtest/gtest.h"
#include "../ConfigurationLib/Configuration.h"
#include "../ConfigurationLib/KeyValuePair.h"
#include <iostream>

TEST(ConstructorConfigurationTest, CreatingConfigurationObject) 
{
	Configuration c;
	EXPECT_EQ(0, c.getConfig().size());
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
	c.write(key, value);
	std::string key2 = "k2";
	std::string value2 = "v2";
	c.write(key2, value2);
	EXPECT_EQ(2, c.getConfig().size());
	KeyValuePair pair1 = c.getConfig()[0];
	KeyValuePair pair2 = c.getConfig()[1];
	EXPECT_EQ("k", pair1.getKey());
	EXPECT_EQ("v", pair1.getValue());
	EXPECT_EQ("k2", pair2.getKey());
	EXPECT_EQ("v2", pair2.getValue());
}