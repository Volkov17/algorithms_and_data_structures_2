#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <list>
#include <algorithm>


std::vector <int> decToBinary(int n)
{
    std::vector<int> arr;
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0 ; j--) {
        arr.push_back(binaryNum[j]);
    }
    return arr;
}


int main() {

    std::vector <std::string> steps(0);
    std::vector <std::string> steps__1 (0);
    int number , number_1 = 0;
    std::cin >> number;
    //std::bitset<sizeof(int)*8> bst(number);


    number_1 = number;
    while (number != 0) {
        if (number % 2 == 0) {
            number = number / 2;
            steps.push_back("dbl");
        }
        if (number == 1) {
            number -= 1;
            steps.push_back("inc");
        }
        if (number % 2 == 1) {
            std::vector<int> bt = decToBinary(number + 1);
            std::vector<int> bt_1 = decToBinary (number - 1);

            int a = 0;
            int b = 0;

            for (size_t i = 0; i < bt.size(); i++) {
                if (bt[i] == 1) {
                    a += 1;
                }
            }

            for (size_t i = 0; i < bt_1.size(); i++) {
                if (bt_1[i] == 1) {
                    b += 1;
                }
            }

            if (a < b) {
                number += 1;
                steps.push_back("dec");
            }

            if (a == b) {
                std::vector<int> bt_new = decToBinary(number + 1);
                std::vector<int> bt_new_1 = decToBinary(number - 1);

                int itlen = bt_new.size() / 2;

                for (int i = itlen; i <= bt_new.size() - 1; i++) {
                    if (bt_new[i] > bt_new_1[i]) {
                        steps.push_back("dec");
                        number += 1;
                        break;
                    }
                    if ((bt_new[i] < bt_new_1[i]) || (bt_new_1.size() < bt_new.size())) {
                        steps.push_back("inc");
                        number -= 1;
                        break;
                    }
                }
            }

            if (a > b) {
                number -= 1;
                steps.push_back("inc");
            }
        }
    }

    while (number_1 != 0) {
        if (number_1 % 2 == 0) {
            number_1 = number_1 / 2;
            steps__1.push_back("dbl");
        }

        if (number_1 == 1) {
            number_1 -= 1;
            steps__1.push_back("inc");
        }
        if (number_1 % 2 == 1) {
            std::vector<int> bt = decToBinary(number_1 + 1);
            std::vector<int>bt_1 = decToBinary(number_1 - 1);
            int a = 0;
            int b = 0;

            for (size_t i = 0; i < bt.size(); i++) {
                if (bt[i] == 1) {
                    a += 1;
                }
            }
            for (size_t i = 0; i < bt_1.size(); i++) {
                if (bt_1[i] == 1) {
                    b = b + 1;
                }
            }

            if (a < b) {
                number_1 += 1;
                steps__1.push_back("dec");
            }

            if (a > b) {
                number_1 -= 1;
                steps__1.push_back("inc");
            }

            if (a == b) {
                number_1 -= 1;
                steps__1.push_back("inc");
            }
        }
    }

    std::reverse(steps.begin(), steps.end());
    std::reverse(steps__1.begin(), steps__1.end());

    if (steps.size() >= steps__1.size()) {
        for (size_t i = 0; i < steps__1.size(); i++) {
            std::cout << steps__1[i] << std::endl;
        }
    }

    if (steps.size() < steps__1.size()) {
        for (size_t i = 0; i < steps.size(); i++) {
            std::cout << steps[i] << std::endl;
        }
    }
    
    return 0;
}
