#ifndef TEST_HPP
#define TEST_HPP

#include <unordered_map>

namespace test {

    class Log {
    public:
        static void log(const std::string & str, int fail) {
            auto resstr = std::string(fail ? ": FAIL" : ": OK");
            auto it = failes.find(str);

            std::cout << "testing: " << str << resstr << std::endl;

            if (it != failes.end()) {
                it->second += fail;
            }
            else {
                failes[str] = fail;
            }
        }

        static void stats() {
            for (auto & it : failes) {
                std::cout << it.first << ": " << it.second << " fail(es)" << std::endl;
            }
        }

    private:
        static std::unordered_map<std::string, int> failes;
    };

    std::unordered_map<std::string, int> Log::failes;

}

#endif // TEST_HPP
