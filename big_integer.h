#pragma once
#include<string>
#include<iostream>

class big_integer
{
public:
	big_integer();
	big_integer(std::string number);
	big_integer(const big_integer& copy);
	big_integer(big_integer&& other) noexcept;
	big_integer(int number);
	big_integer& operator= (const big_integer& other);
	big_integer& operator= (big_integer&& other) noexcept;
	big_integer operator+ (const big_integer& right) const;
	big_integer operator* (const big_integer& right);
	friend big_integer operator* (const int left, big_integer& right);
	std::string get() const;
	//~big_integer();
private:
	std::string data_;
};

std::ostream& operator<< (std::ostream& left, const big_integer& right);