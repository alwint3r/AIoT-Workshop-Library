#include "DeviceIdentity.h"

DeviceIdentity::DeviceIdentity() : id_("")
{
}

DeviceIdentity::DeviceIdentity(std::string id) : id_(id)
{
}

DeviceIdentityBuilder::DeviceIdentityBuilder(std::string prefix) : id_(prefix)
{
}

DeviceIdentityBuilder *DeviceIdentityBuilder::macAddress(std::string mac)
{
    std::string temp = "";
    for (auto &c : mac)
    {
        if (c == ':')
        {
            continue;
        }

        append(c);
    }

    id_.append(temp);

    return this;
}

DeviceIdentityBuilder *DeviceIdentityBuilder::append(std::string text)
{
    id_.append(text);

    return this;
}

DeviceIdentityBuilder *DeviceIdentityBuilder::append(char c)
{
    id_.push_back(c);

    return this;
}

DeviceIdentity DeviceIdentityBuilder::build()
{
    return DeviceIdentity(std::move(id_));
}
