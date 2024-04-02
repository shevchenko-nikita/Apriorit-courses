#include "pch.h"

// Suppose you have some login function

class HttpRequest
{
public:
    virtual std::string Get(const std::string& url)
    {
        // real request should be here
        return "response body";
    }
};
struct AuthResult
{
    std::string token;
    std::string userId;
};
AuthResult Login(const std::string& email, const std::string& password, HttpRequest& request)
{
    const auto response = request.Get("https://mysite.com/login?user=" + email + "&pw=" + password);
    return {/*ParseAuthResponse(response)*/};
}

// It's an example how you can test it using gmock library:

class MockHttpRequest : public HttpRequest
{
public:
    MOCK_METHOD1(Get, std::string(const std::string&));    // this allows us to use things like ON_CALL below
};

TEST(LoginUtils, Login_ValidData)
{
    const std::string validResponse = R"({"token":"AAAAABgh123","user":"1234567"})";

    testing::NiceMock<MockHttpRequest> request;    
    ON_CALL(request, Get(testing::_))                      // (if you need to check the argument use EXPECT_CALL and pass a checked value instead of testing::_)
        .WillByDefault(testing::Return(validResponse));    // this construction allows us to set the string which will be returned from Get()
    const auto result = Login("vlad", "pass", request);
    
    EXPECT_EQ("AAAAABgh123", result.token);
    EXPECT_EQ("1234567", result.userId);
}