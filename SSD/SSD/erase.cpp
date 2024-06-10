#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include "Command.h"
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
    void execute(const vector<string>& operation) override {
        cmd_args = operation;

        if (check_validation() == false) {
            throw EraseException();
        }

        LBA = get_address(operation[1]);
        SIZE = get_erase_size(LBA, stoi(operation[2]));

        do_action();
    }

private:
    const int max_address_num = 99;
    const int min_address_num = 0;
    const int max_size_num = 10;
    const int min_size_num = 1;
    int LBA = 0;
    int SIZE = 0;
    vector<string> cmd_args;
    SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance();

    bool check_validation() override {
        if (is_valid_args() == false) return false;
        if (is_matched_cmd() == false) return false;
        if (is_valid_address() == false) return false;
        if (is_address_in_range() == false) return false;
        if (is_valid_size() == false) return false;

        return true;
    }

    bool is_valid_args() {
        if (cmd_args.size() != 3) return false;
        return true;
    }

    bool is_matched_cmd() {
        if (cmd_args[0] != "E") return false;
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
        if (address < min_address_num) return false;
        if (address > max_address_num) return false;
        return true;
    }

    bool is_valid_size() {
        for (char ch : cmd_args[2]) {
            if (!isdigit(ch)) return false;
        }
        return true;
    }

    bool is_size_in_range() {
        int size = 0;
        try {
            size = stoi(cmd_args[2]);
        }
        catch (exception e) {
            return false;
        }
        if (size < min_size_num) return false;
        if (size > max_size_num) return false;
        return true;
    }

    int get_address(string oper) {
        int address = 0;
        try {
            address = stoi(oper);
        }
        catch (exception e) {
            throw EraseException();
        }
        return address;
    }

    int get_erase_size(int address, int size) {
        int resize = size;
        if (address + size - 1 > max_address_num) {
            resize = size - (address + size - max_address_num - 1);
        }
        return resize;
    }

    void do_action() override {
        write_buffer->erase(LBA, SIZE);
    }
};
