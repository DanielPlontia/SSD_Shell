#include <vector>
#include <string>
#include <stdexcept>
#include "Command.h"
#include "SSD_HW.h"

using namespace std;

class ReadException : public std::exception {
public:
    char const* what() const override {
        "READ :validation error!";
    }
};

class ReadCmd : public Command {
public:
    void execute(const std::vector<std::string>& operation) {
        LBA = stoi(operation[1]);
        if (check_validation() == false) {
            throw ReadException();
        }
        do_action();
    }
private:
    bool check_validation() {
        if ((LBA < 0) || (LBA > 99)) {
            return false;
        }
        return true;
    }
    void do_action() {
        // TO Do
    }

    int LBA;
};
