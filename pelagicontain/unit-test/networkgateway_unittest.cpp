/*
 *   Copyright (C) 2014 Pelagicore AB
 *   All rights reserved.
 */
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "networkgateway.h"
#include "debug.h"
#include "log_console.h"

using namespace pelagicore;

class MockController :
    public ControllerAbstractInterface
{
public:

    virtual bool startApp()
    {
            return true;
    }

    virtual bool shutdown()
    {
        return true;
    }

    virtual bool setEnvironmentVariable(const std::string &variable,
        const std::string &value)
    {
        return true;
    }

    MOCK_METHOD1(systemCall,
        bool(const std::string &cmd));
};

using ::testing::InSequence;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;


/*! Test NetworkGateway calls ControllerInterface::systemCall when
 * NetworkGateway::setConfig() has been called
 *
 * The NetworkGateway::setConfig() should try to issue a ifconfig
 * system call inside the container in order to set the containers IP
 * address.
 */
TEST(NetworkGatewayTest, TestSetConfig) {
    /* Nice mock, i.e. don't warn about uninteresting calls on this mock */
    NiceMock<MockController> controllerInterface;
    NetworkGateway gw(&controllerInterface);

    bool success = gw.setConfig("foo");
    ASSERT_TRUE(success);
}

/*! Test NetworkGateway::activate is successful.
 */
TEST(NetworkGatewayTest, TestActivate) {
    NiceMock<MockController> controllerInterface;
    NetworkGateway gw(&controllerInterface);

    std::string cmd_1 = "ifconfig eth0 10.0.3.42 netmask 255.255.255.0 up";
    std::string cmd_2 = "route add default gw 10.0.3.1";
    std::string cmd_3 = "ping www.google.com";

    {
	InSequence sequence;
	EXPECT_CALL(controllerInterface, systemCall(cmd_1)).Times(1);
	EXPECT_CALL(controllerInterface, systemCall(cmd_2)).Times(1);
	EXPECT_CALL(controllerInterface, systemCall(cmd_3)).Times(1);
    }

    ASSERT_TRUE(gw.setConfig("foo"));
    bool success = gw.activate();
    ASSERT_TRUE(success);
}

/*! Test NetworkGateway::activate is successful.
 */
TEST(NetworkGatewayTest, TestActivateNoConfig) {
    NiceMock<MockController> controllerInterface;
    NetworkGateway gw(&controllerInterface);

    bool success = gw.activate();
    ASSERT_TRUE(success);
}
