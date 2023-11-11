#pragma once

#include "Include.h"

class Algorithm
{
public:
	Algorithm() = default;
	Algorithm(const Algorithm& algorithm) = delete;
	Algorithm(const Algorithm&& algorithm) = delete;

	Algorithm& operator=(const Algorithm& algorithm) = delete;
	Algorithm& operator=(const Algorithm&& algorithm) = delete;

	virtual ~Algorithm() = default;

	virtual std::string crypt(const std::string& message) const = 0;
	virtual std::string decrypt(const std::string& message) const = 0;
};
