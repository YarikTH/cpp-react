#ifndef TEST_HPP
#define TEST_HPP

#include <unordered_map>

namespace test {

    class Log {
    public:
        class Info {
        public:
            int failes = 0;
            int attempts = 0;
        };

        static void log(const std::string & str, int fail) {
            auto resstr = std::string(fail ? ": FAIL" : ": OK");
            auto it = failes.find(str);

            std::cout << "testing: " << str << resstr << std::endl;

            if (it != failes.end()) {
                it->second.failes += fail;
                it->second.attempts++;
            }
            else {
                failes[str] = { fail, 1 };
            }
        }

        static void stats() {
            for (auto & it : failes) {
                std::cout << it.first << ": " << it.second.failes << " failes ";
                std::cout << it.second.attempts << " attempts"<< std::endl;
            }
        }

    private:
        static std::unordered_map<std::string, Info> failes;
    };

    std::unordered_map<std::string, Log::Info> Log::failes;

}

#endif // TEST_HPP
