#pragma once

#include <vector>
#include <string>
#include "Command.h"
#include "SSD_HW.h"
#include <stdexcept>
#include "SSD_WriteBuffer.cpp"

using namespace std;

class EraseException : public exception {
public:
    char const* what() const override {
        return "ERASE :validation error!";
    }
};

class EraseCmd : public Command {
public:
    EraseCmd(SSD_HW* _ssd, SSD_WriteBuffer* _write_buffer)
        : ssd_hw{ _ssd }, write_buffer(_write_buffer) {};

    void execute(const vector<string>& operation) override {
        cmd_args = operation;

        if (check_validation() == false) {
            throw EraseException();
        }

        LBA = stoi(operation[1]);
        SIZE = stoi(operation[2]);

        do_action();
    }

private:
    bool check_validation() override {
        if (check_args() == false) {
            return false;
        }
        if (check_cmd() == false) {
            return false;
        }
        if (check_address() == false) {
            return false;
        }
        if (check_address_range() == false) {
            return false;
        }
        if (check_size() == false) {
            return false;
        }

        return true;
    }

    bool check_args() {
        if (cmd_args.size() != 3) {
            return false;
        }
        else {
            return true;
        }
    }

    bool check_cmd() {
        if (cmd_args[0] != "E") {
            return false;
        }
        else {
            return true;
        }
    }

    bool check_address() {
        for (char arg : cmd_args[1]) {
            if (!isdigit(arg)) {
                return false;
            }
        }
        return true;
    }

    bool check_address_range() {
        int address = stoi(cmd_args[1]);

        if (address < 0) {
            return false;
        }
        if (address > 99) {
            return false;
        }
        return true;
    }

    bool check_size() {
        for (char arg : cmd_args[2]) {
            if (!isdigit(arg)) {
                return false;
            }
        }
        return true;
    }

    bool is_size_in_range() {
        int address = stoi(cmd_args[1]);
        int size = stoi(cmd_args[2]);

        if (size < 1) {
            return false;
        }
        if (size > 10) {
            return false;
        }
        if (address + size - 1 > 99) {
            size -= (address + size - 100);
        }

        return true;
    }

    void do_action() override {
        for (int i = LBA; i < LBA+SIZE; i++) {
            ssd_hw->write(LBA, 0x00000000);
        }
    }

    int LBA = 0;
    int SIZE = 0;
    vector<string> cmd_args;
    SSD_HW* ssd_hw;
    SSD_WriteBuffer* write_buffer;
};
