#ifndef TEST_HPP
#define TEST_HPP

#include <unordered_map>

namespace test {

    class Log {
    public:
        class Info {
        public:
            int fails = 0;
            int attempts = 0;
        };

        static void log(const std::string & str, int fail) {
            auto resstr = std::string(fail ? ": FAIL" : ": OK");
            auto it = fails.find(str);

            std::cout << "testing: " << str << resstr << std::endl;

            if (it != fails.end()) {
                it->second.fails += fail;
                it->second.attempts++;
            }
            else {
                fails[str] = { fail, 1 };
            }
        }

        static void stats() {
            for (auto & it : fails) {
                std::cout << it.first << ": " << it.second.fails << " fails ";
                std::cout << it.second.attempts << " attempts"<< std::endl;
            }
        }

    private:
        static std::unordered_map<std::string, Info> fails;
    };

    std::unordered_map<std::string, Log::Info> Log::fails;

}

#endif // TEST_HPP
