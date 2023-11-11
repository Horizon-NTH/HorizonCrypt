#pragma once

#include "Include.h"
#include "RSA.h"

namespace hcrypt
{
	class RSA::Key
	{
	public:
		explicit Key(unsigned int size);

		void save(const std::string& publicFile, const std::string& privateFile) const;

	private:
		std::pair<mpz_class, mpz_class> m_public;
		mpz_class m_private;

		static std::string to_base64(const mpz_class& number);
	};
}
