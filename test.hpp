/*

  react LGPL Source Code
  Copyright (C) 2014 Edward Knyshov

  This file is part of the react LGPL Source Code (react Source Code).

  react Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  react Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with react Source Code. If not, see <http://www.gnu.org/licenses/>

*/

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
