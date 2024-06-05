
#include "TestShellFixture.h"

// 표준 출력을 재지향하여 캡처하는 클래스
class OutputRedirector {
public:
    OutputRedirector() : old_cout_buf(std::cout.rdbuf()) {
        std::cout.rdbuf(buffer.rdbuf());
    }

    ~OutputRedirector() {
        std::cout.rdbuf(old_cout_buf);
    }

    std::string getOutput() {
        return buffer.str();
    }

private:
    std::stringstream buffer;
    std::streambuf* old_cout_buf;
};

TEST_F(TestShellFixture, HelpCommand) {
    OutputRedirector redirector;
    std::string expected_msg;
    for (auto& test_func : shell.test_func_map) {
        expected_msg += test_func.first + " : " + test_func.second.description + "\n";
    }
    shell.TestExecute("help");

    EXPECT_EQ(redirector.getOutput(), expected_msg);
}
