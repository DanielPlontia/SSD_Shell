#include <vector>
#include <string>
#include <stdexcept>
#include "Command.h"
#include "SSD_HW.h"

using namespace std;


class ReadException : public std::exception {
public:
    char const* what() const override {
        return "READ :validation error!";
    }
};

class ReadCmd : public Command {
public:
    ReadCmd(SSD_HW* _ssd) : ssd_hw{ _ssd } {};
    void execute(const std::vector<std::string>& operation) override {
        cmd_arg = operation;
        if (check_validation() == false) {
            throw ReadException();
        }
        LBA = stoi(operation[1]);
        do_action();
    }
private:
    bool check_validation() override {
        if (check_args() == false) return false;
        if (check_cmd() == false) return false;
        if (check_address_value() == false) return false;
        if (check_address_range() == false) return false;

        return true;
    }
    bool check_args() {
        if (cmd_arg.size() != 2) return false;
        return true;
    }
    bool check_cmd() {
        if (cmd_arg[0] != "R") return false;
        return true;
    }
    bool check_address_value() {
        for (char ch : cmd_arg[1]) {
            if (!std::isdigit(ch)) {
                return false;
            }
        }
        return true;
    }
    bool check_address_range() {
        if ((stoi(cmd_arg[1]) < min_num) || (stoi(cmd_arg[1]) > max_num)) return false;
        return true;
    }
    void do_action() override {
        ssd_hw->read(LBA);
    }

    int LBA = 0;
    const int max_num = 99;
    const int min_num = 0;
    std::vector<std::string> cmd_arg;
    SSD_HW* ssd_hw;
};
