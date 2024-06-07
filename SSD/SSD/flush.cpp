#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include "Command.h"
#include "SSD_HW.h"
#include "SSD_WriteBuffer.cpp"

using namespace std;

class FlushException : public exception {
public:
    char const* what() const override {
        return "FLUSH :validation error!";
    }
};

class FlushCmd : public Command {
public:
    FlushCmd(SSD_HW* _ssd, SSD_WriteBuffer* _write_buffer)
        : ssd_hw{ _ssd }, write_buffer(_write_buffer) {};

    void execute(const vector<string>& operation) override {
        cmd_args = operation;

        if (check_validation() == false) {
            throw FlushException();
        }

        do_action();
    }

private:
    vector<string> cmd_args;
    SSD_HW* ssd_hw;
    SSD_WriteBuffer* write_buffer;

    bool check_validation() override {
        if (is_valid_args() == false) {
            return false;
        }
        if (is_matched_cmd() == false) {
            return false;
        }

        return true;
    }

    bool is_valid_args() {
        return (cmd_args.size() != 1)? false : true;
    }

    bool is_matched_cmd() {
        return (cmd_args[0] != "F")? false : true;
    }

    void do_action() override {
        write_buffer->flush();
    }
};
