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
	KeyValuePair pair = c.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
	
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

TEST(IndexOperatorTest, GettingValueByKey)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	c.write(key, value);
	EXPECT_EQ("v", c["k"]);
}

TEST(IndexOperatorTest, GettingValueByKeyWithEmptyConfiguration)
{
	Configuration c;
	EXPECT_EQ("", c["k"]);
}

TEST(IndexOperatorTest, GettingValueByKeyWithNonExistingKey)
{
	Configuration c;
	std::string key = "k";
	std::string value = "v";
	c.write(key, value);
	EXPECT_EQ("", c["k2"]);
}


TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoEmptyConfigurations)
{
	Configuration c1;
	Configuration c2;
	c1 += c2;
	EXPECT_EQ(0, c1.getConfig().size());
}

TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoConfigurationsOneIsEmpty)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	c1 += c2;
	EXPECT_EQ(1, c1.getConfig().size());
	KeyValuePair pair = c1.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoConfigurationsOneIsEmpty2)
{
	Configuration c1;
	Configuration c2;
	std::string key = "k";
	std::string value = "v";
	c2.write(key, value);
	c1 += c2;
	EXPECT_EQ(1, c1.getConfig().size());
	KeyValuePair pair = c1.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoConfigurations)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1 += c2;
	EXPECT_EQ(2, c1.getConfig().size());
	KeyValuePair pair1 = c1.getConfig()[0];
	KeyValuePair pair2 = c1.getConfig()[1];
	EXPECT_EQ("k", pair1.getKey());
	EXPECT_EQ("v", pair1.getValue());
	EXPECT_EQ("k2", pair2.getKey());
	EXPECT_EQ("v2", pair2.getValue());
}

TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoConfigurationsWithTheSameKey)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1 += c2;
	EXPECT_EQ(1, c1.getConfig().size());
	KeyValuePair pair = c1.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddAndAssignOperatorTest, AddAndAssignOperatorTwoConfigurationsLeftConfigurationIsReadOnly)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1.setWriteProtected();
	EXPECT_THROW(c1 += c2; , std::logic_error);
	
}
TEST(AddOperatorTest, AddOperatorTwoEmptyConfigurations)
{
	Configuration c1;
	Configuration c2;
	Configuration c3 = c1 + c2;
	EXPECT_EQ(0, c3.getConfig().size());
}

TEST(AddOperatorTest, AddOperatorTwoConfigurationsOneIsEmpty)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	Configuration c3 = c1 + c2;
	EXPECT_EQ(1, c3.getConfig().size());
	KeyValuePair pair = c3.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddOperatorTest, AddOperatorTwoConfigurationsOneIsEmpty2)
{
	Configuration c1;
	Configuration c2;
	std::string key = "k";
	std::string value = "v";
	c2.write(key, value);
	Configuration c3 = c1 + c2;
	EXPECT_EQ(1, c3.getConfig().size());
	KeyValuePair pair = c3.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddOperatorTest, AddOperatorTwoConfigurations)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	Configuration c3 = c1 + c2;
	EXPECT_EQ(2, c3.getConfig().size());
	KeyValuePair pair1 = c3.getConfig()[0];
	KeyValuePair pair2 = c3.getConfig()[1];
	EXPECT_EQ("k", pair1.getKey());
	EXPECT_EQ("v", pair1.getValue());
	EXPECT_EQ("k2", pair2.getKey());
	EXPECT_EQ("v2", pair2.getValue());
}

TEST(AddOperatorTest, AddOperatorTwoConfigurationsWithTheSameKey)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k";
	std::string value2 = "v2";
	c2.write(key2, value2);
	Configuration c3 = c1 + c2;
	EXPECT_EQ(1, c3.getConfig().size());
	KeyValuePair pair = c3.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(AddOperatorTest, AddOperatorTwoConfigurationsLeftConfigurationIsReadOnly)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1.setWriteProtected();
	Configuration c3 = c1 + c2;
	EXPECT_EQ(2, c3.getConfig().size());
	KeyValuePair pair1 = c3.getConfig()[0];
	KeyValuePair pair2 = c3.getConfig()[1];
	EXPECT_EQ("k", pair1.getKey());
	EXPECT_EQ("v", pair1.getValue());
	EXPECT_EQ("k2", pair2.getKey());
	EXPECT_EQ("v2", pair2.getValue());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoEmptyConfigurations)
{
	Configuration c1;
	Configuration c2;
	c1 -= c2;
	EXPECT_EQ(0, c1.getConfig().size());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoConfigurationsOneIsEmpty)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	c1 -= c2;
	EXPECT_EQ(1, c1.getConfig().size());
	KeyValuePair pair = c1.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoConfigurationsSecondIsEmpty)
{
	Configuration c1;
	Configuration c2;
	std::string key = "k";
	std::string value = "v";
	c2.write(key, value);
	c1 -= c2;
	EXPECT_EQ(0, c1.getConfig().size());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoConfigurationsWithTheSameKey)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1 -= c2;
	EXPECT_EQ(0, c1.getConfig().size());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoConfigurationsWithDifferentKeys)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1 -= c2;
	EXPECT_EQ(1, c1.getConfig().size());
	KeyValuePair pair = c1.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(SubtractAndAssignOperatorTest, SubtractAndAssignOperatorTwoConfigurationsLeftConfigurationIsReadOnly)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k2";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1.setWriteProtected();
	EXPECT_THROW(c1 -= c2;, std::logic_error);
}

TEST(SubtractOperatorTest, SubtractOperatorTwoEmptyConfigurations)
{
	Configuration c1;
	Configuration c2;
	Configuration c3 = c1 - c2;
	EXPECT_EQ(0, c3.getConfig().size());
}

TEST(SubtractOperatorTest, SubtractOperatorTwoConfigurationsOneIsEmpty)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	Configuration c3 = c1 - c2;
	EXPECT_EQ(1, c3.getConfig().size());
	KeyValuePair pair = c3.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(SubtractOperatorTest, SubtractOperatorTwoConfigurationsSecondIsEmpty)
{
	Configuration c1;
	Configuration c2;
	std::string key = "k";
	std::string value = "v";
	c2.write(key, value);
	Configuration c3 = c1 - c2;
	EXPECT_EQ(0, c3.getConfig().size());
}

TEST(SubtractOperatorTest, SubtractOperatorTwoConfigurationsWithTheSameKey)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k";
	std::string value2 = "v2";
	c2.write(key2, value2);
	Configuration c3 = c1 - c2;
	EXPECT_EQ(0, c3.getConfig().size());
}

TEST(SubtractOperatorTest, SubtractOperatorTwoConfigurationsRemoveOnePairFromTwoPairsInConfiguration)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	std::string key2 = "k2";
	std::string value2 = "v2";
	c1.write(key, value);
	c1.write(key2, value2);
	Configuration c2;
	std::string key3 = "k2";
	std::string value3 = "v";
	c2.write(key2, value2);
	Configuration c3 = c1 - c2;
	EXPECT_EQ(1, c3.getConfig().size());
	KeyValuePair pair = c3.getConfig()[0];
	EXPECT_EQ("k", pair.getKey());
	EXPECT_EQ("v", pair.getValue());
}

TEST(SubtractOperatorTest, SubtractOperatorTwoConfigurationsLeftConfigurationIsReadOnly)
{
	Configuration c1;
	std::string key = "k";
	std::string value = "v";
	c1.write(key, value);
	Configuration c2;
	std::string key2 = "k";
	std::string value2 = "v2";
	c2.write(key2, value2);
	c1.setWriteProtected();
	Configuration c3 = c1 - c2;
	EXPECT_EQ(0, c3.getConfig().size());
}