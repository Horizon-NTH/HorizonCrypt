#include "../include/hcrypt/RSAKey.h"

#include <ranges>

hcrypt::RSA::Key::Key(const unsigned size)
{
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_class p, q;
	const mp_bitcnt_t b(size / 2);
	mpz_urandomb(p.get_mpz_t(), state, b);
	mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
	mpz_urandomb(q.get_mpz_t(), state, b);
	mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());
	mpz_class n = p * q, lambda_n, phi_q(q - 1), phi_p(p - 1), e(65537), is_coprime;
	mpz_lcm(lambda_n.get_mpz_t(), phi_p.get_mpz_t(), phi_q.get_mpz_t());
	mpz_gcd(is_coprime.get_mpz_t(), e.get_mpz_t(), lambda_n.get_mpz_t());
	while (is_coprime != 1 || e <= 2 || e >= lambda_n)
	{
		mpz_urandomb(e.get_mpz_t(), state, size);
		mpz_nextprime(e.get_mpz_t(), e.get_mpz_t());
		mpz_gcd(is_coprime.get_mpz_t(), e.get_mpz_t(), lambda_n.get_mpz_t());
	}
	mpz_class d;
	mpz_invert(d.get_mpz_t(), e.get_mpz_t(), lambda_n.get_mpz_t());
    m_public = {n ,e};
    m_private = d;
}

void hcrypt::RSA::Key::save(const std::string& publicFile, const std::string& privateFile) const
{
	{
		std::ofstream stream(publicFile);
		if (stream.is_open())
		{
			stream << "----- BEGIN PUBLIC KEY-----" << std::endl
				<< to_base64(m_public.first) << std::endl
				<< to_base64(m_public.second) << std::endl
				<< "-----END PUBLIC KEY-----" << std::endl;
		}
		else
		{
			throw std::runtime_error(("ERROR WHILE LOADING FILE :: " + publicFile).c_str());
		}
	}
	{
		std::ofstream stream(privateFile);
		if (stream.is_open())
		{
			stream << "-----BEGIN RSA PRIVATE KEY-----" << std::endl
				<< to_base64(m_private) << std::endl
				<< "-----END RSA PRIVATE KEY-----" << std::endl;
		}
		else
		{
			throw std::runtime_error(("ERROR WHILE LOADING FILE :: " + privateFile).c_str());
		}
	}
}

std::string hcrypt::RSA::Key::to_base64(const mpz_class& number)
{
    std::string binary_str = number.get_str(2);

    while (binary_str.length() % 6 != 0)
    {
        binary_str.insert(0, "0");
    }

    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_str;
    for (int i = 0; i < binary_str.length(); i += 6)
    {
        if (!(i % 64) && i != 0 && i != binary_str.length())
            base64_str += '\n';
        std::bitset<6> bits(binary_str.substr(i, 6));
        base64_str += base64_chars[bits.to_ulong()];
    }

    return base64_str;
}
