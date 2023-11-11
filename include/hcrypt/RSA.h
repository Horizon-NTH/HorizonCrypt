#pragma once

#include "Include.h"
#include  "Algorithm.h"

namespace hcrypt
{
	class RSA final : public Algorithm
	{
	public:
		class Key;

		explicit RSA(unsigned int keySize = 4096);

		std::string crypt(const std::string& message) const override;
		std::string decrypt(const std::string& message) const override;

	private:
	};
}
