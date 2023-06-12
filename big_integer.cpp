#include "big_integer.h"

big_integer::big_integer()
	:data_{ "0" }
{}

big_integer::big_integer(std::string number)
	:data_{ number }
{}

big_integer::big_integer(const big_integer& copy)
	:data_{ copy.data_ }
{}

big_integer::big_integer(big_integer&& other) noexcept
	:data_{ std::exchange(other.data_, "")}
{}

big_integer::big_integer(int number)
	:data_{ std::to_string(number) }
{}

big_integer& big_integer::operator= (const big_integer& other)
{
	if (this == &other) {
		return *this;
	}
	data_ = other.data_;
	return *this;
}
big_integer& big_integer::operator= (big_integer&& other) noexcept
{
	if (this == &other) {
		return *this;
	}
	data_ = std::exchange(other.data_, "");
	return *this;
}

big_integer big_integer::operator+ (const big_integer& right) const{
	int left_size = data_.size();
	int right_size = right.data_.size();
	unsigned min = (left_size < right_size ? left_size : right_size);
	unsigned max = (left_size > right_size ? left_size : right_size);
	int tmp_sum = 0;
	int perenos = 0;
	std::string result("");//������ ������ ��� ����������
	for (int i = 0; i < max || perenos > 0; i++) {//  �������� �� ������� ����� ������ �������� �����
		if (i < min) {//���� ����������� ����� ����������
			tmp_sum = static_cast<int>(data_[left_size - 1 - i]) + static_cast<int>(right.data_[right_size - 1 - i]) + perenos - 96;
		}
		else if ( i < left_size) {//���������� �� �������� �����
			tmp_sum = static_cast<int>(data_[left_size - 1 - i]) + perenos - 48; // 48 - �������� ��� ���� � �������
		}
		else if ( i < right_size) {
			tmp_sum = static_cast<int>(right.data_[right_size - 1 - i]) + perenos - 48;
		}
		else {//����� ����� ����� ������� ����� ���������(perenos > 0)
			tmp_sum = 1;
		}
		if (tmp_sum >= 10) {
			perenos = 1;
			tmp_sum -= 10;
		}
		else {
			perenos = 0;
		}
		result = std::to_string(tmp_sum) + result;// ��������� � ������ ������ ����� �� ��������
	}
	return big_integer(result);
}

big_integer big_integer::operator* (const big_integer& right) {
	int left_size = data_.size();
	int right_size = right.data_.size();
	int perenos = 0;
	int tmp = 0;
	int tmp_perenos = 0;
	std::string result(left_size+right_size,'0');
	for (int i = left_size-1; i >= 0; i--) {
		for (int j = right_size-1; j >= 0 ; j--) { // �������� ��������� �� 1�� �����.
			tmp = (data_[i] - 48) * (right.data_[j] - 48) + (result[i + j + 1] - 48); // 48 - �������� ��� ���� � �������
			if (tmp > 9) { // ��������� ������� �������
				perenos = (tmp - (tmp % 10)) / 10;
				tmp -= perenos * 10;
			}
			else {
				perenos = 0;
			}
			result[i + j + 1] = tmp+48;

			tmp = result[i + j] - 48 + perenos;
			if (tmp > 9) { //���� �� �������� ���� ��� �������
				tmp_perenos = (tmp - (tmp % 10)) / 10;
				tmp -= tmp_perenos * 10;
			}
			else {
				tmp_perenos = 0;
			}
			result[i + j] = tmp + 48;// ��������� ������� �������
			if (tmp_perenos > 0) { // ������ 3� ��������� ���� �� �����
				result[i + j - 1] += tmp_perenos;
			}
		}
	}
	if (result.front() == '0') { // ������� ���� � ������ 
		result.erase(0, 1);
	}
	return big_integer(result);
}

big_integer operator* (const int left, big_integer& right) {
	return right * big_integer(left);
}

std::string big_integer::get() const {
	return data_;
}

std::ostream& operator<< (std::ostream& left, const big_integer& right) {
	left << right.get();
	return left;
}

//big_integer::~big_integer() {
//	std::cout << " destructor " << std::endl;
//}