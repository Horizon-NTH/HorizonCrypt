#include "../include/hcrypt/RSA.h"
#include "../include/hcrypt/RSAKey.h"

hcrypt::RSA::RSA(const unsigned int keySize)
{
	Key key(keySize);
	key.save("test.pub", "test.pem");
}

std::string hcrypt::RSA::crypt(const std::string& message) const
{
	return {};
}

std::string hcrypt::RSA::decrypt(const std::string& message) const
{
	return {};
}
