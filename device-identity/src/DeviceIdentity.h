#ifndef DEVICE_IDENTITY_H_
#define DEVICE_IDENTITY_H_

#include <string>

class DeviceIdentity
{
public:
    DeviceIdentity();

    DeviceIdentity(std::string id);

    const std::string &get() const
    {
        return id_;
    }

private:
    std::string id_;
};

class DeviceIdentityBuilder
{
public:
    DeviceIdentityBuilder(std::string prefix);

    DeviceIdentityBuilder *append(std::string text);
    DeviceIdentityBuilder *append(char c);
    DeviceIdentityBuilder *macAddress(std::string macAddress);

    DeviceIdentity build();

private:
    std::string id_;
};

#endif