#pragma once
#include <stdexcept>

#include "SSD_HW.h"
#include "Command.h"

class WriteException : public std::exception {
public:
	char const* what() const override {
		return "WRITE :validation error!";
	}
};

class WriteCmd : public Command {
	// Command을(를) 통해 상속됨
public:
	WriteCmd(SSD_HW* _ssd) : ssd_hw{ _ssd } {};

	void execute(const std::vector<std::string>& operation) override
	{
		cmd_arg = operation;
		if (check_validation() == false) {
			throw WriteException();
		}
		do_action();
	}

private:
	const int MIN_ADDR_NUM = 0;
	const int MAX_ADDR_NUM = 99;
	SSD_HW* ssd_hw;
	std::vector<std::string> cmd_arg;

	int write_address = -1;
	unsigned int write_data = 0;

	void do_action() override
	{
		ssd_hw->write(write_address, write_data);
	}

	bool check_validation() override
	{
		if (is_less_arg_count_3()) return false;
		if (is_not_matched_cmd_char()) return false;

		if (is_valid_address_arg() == false) return false;
		if (is_valid_data_arg() == false) return false;
		return true;
	}

	bool is_less_arg_count_3()
	{
		return cmd_arg.size() < 3;
	}
	bool is_not_matched_cmd_char()
	{
		return cmd_arg.at(0) != "W";
	}
	bool is_valid_address_arg()
	{
		if (is_valid_decimal_string(cmd_arg.at(1)) == false) return false;
		try {
			write_address = std::stoi(cmd_arg.at(1));
			if (write_address < MIN_ADDR_NUM) return false;
			if (write_address > MAX_ADDR_NUM) return false;
		}
		catch (std::exception e) {
			return false;
		}
		return true;
	}
	bool is_valid_data_arg()
	{
		if (cmd_arg.at(2).length() != 10) return false;
		if (cmd_arg.at(2)[0] != '0' || cmd_arg.at(2)[1] != 'x') return false;
		if (is_valid_hex_string(cmd_arg.at(2).substr(2)) == false) return false;
		try {
			write_data = std::stoi(cmd_arg.at(2), 0, 16);
		}
		catch (std::exception e) {
			return false;
		}
		return true;
	}
	bool is_valid_decimal_string(const std::string& decimalString) {
		for (char ch : decimalString) {
			if (!std::isdigit(ch)) {
				return false;
			}
		}
		return true;
	}
	bool is_valid_hex_string(const std::string& hexString) {
		for (char ch : hexString) {
			if (!std::isxdigit(ch)) {
				return false;
			}
		}
		return true;
	}
};