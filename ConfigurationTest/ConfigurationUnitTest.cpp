#include "gtest/gtest.h"
#include "../ConfigurationLib/Configuration.h"
#include "../ConfigurationLib/KeyValuePair.h"
#include <iostream>

TEST(ConstructorConfigurationTest, CreatingConfigurationObject) 
{
	Configuration c;
	EXPECT_EQ(0, c.getConfig().size());
}

