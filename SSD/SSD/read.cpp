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
        LBA = stoi(operation[1]);
        if (check_validation() == false) {
            throw ReadException();
        }
        do_action();
    }
private:
    bool check_validation() override {
        if ((LBA < 0) || (LBA > 99)) {
            return false;
        }
        return true;
    }
    void do_action() override {
        // TO Do
    }

    int LBA = 0;
    SSD_HW* ssd_hw;
};
