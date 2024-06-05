#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "Command.h"
#include "SSD_HW.h"

using namespace std;

class ReadException : public exception {
public:
    char const* what() const override {
        return "READ :validation error!";
    }
};

class ReadCmd : public Command {
public:
    ReadCmd(SSD_HW* _ssd) : ssd_hw{ _ssd } {};

    void execute(const vector<string>& operation) override {
        cmd_args = operation;

        if (check_validation() == false) {
            throw ReadException();
        }

        LBA = stoi(operation[1]);

        do_action();
    }

private:
    const int max_num = 99;
    const int min_num = 0;
    int LBA = 0;
    vector<string> cmd_args;
    SSD_HW* ssd_hw;

    bool check_validation() override {
        if (is_valid_args() == false) return false;
        if (is_matched_cmd() == false) return false;
        if (is_valid_address() == false) return false;
        if (is_address_in_range() == false) return false;

        return true;
    }
    bool is_valid_args() {
        if (cmd_args.size() != 2) return false;
        return true;
    }
    bool is_matched_cmd() {
        if (cmd_args[0] != "R") return false;
        return true;
    }
    bool is_valid_address() {
        for (char ch : cmd_args[1]) {
            if (!isdigit(ch)) return false;
        }
        return true;
    }
    bool is_address_in_range() {
        int address = 0;
        try {
            address = stoi(cmd_args[1]);
        }
        catch (exception e) {
            return false;
        }
        if (address < min_num) return false;
        if (address > max_num) return false;
        return true;
    }
    void do_action() override {
        ssd_hw->read(LBA);
    }
};
