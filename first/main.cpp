#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

class Backpack{
private:
    unsigned long** A;
    unsigned long long backpack_weight;
    int n_o_d;
    std::vector<unsigned long > weight;
    std::vector<unsigned long > cost;
    std::vector <int> count;
    std::vector < int > rez_vect_w_p;
    std::vector <int > rez_1;

    int nod_search(unsigned long long a, unsigned long long b){
        if(a != 0 && b != 0){
            while (a != b) {
                if (a > b) {
                    a = a - b;
                } else {
                    b = b - a;
                }
            }
            return a;
        }else if( a == 0 && b != 0){
            return b;
        }else if( b == 0 && a != 0){
            return a;
        }
        return 1;
    }

    void all_to_nod(){
        int x = nod_search(backpack_weight, weight[0]);
        for(size_t i = 1; i < weight.size(); ++i)
            x = nod_search(x,weight[i]);
        n_o_d = x;
    }

    void table (){
        backpack_weight /= n_o_d;
        for (size_t i = 0; i < weight.size(); ++i){
            weight[i] /= n_o_d;
        }
        unsigned long k = 0;
        unsigned long n = 0;
        unsigned long s = 0;
        k = weight.size();
        A = new unsigned long*[k+1];
        for(int i = 0; i < k+1; ++i){
            A[i] = new unsigned long[backpack_weight+1];
        }
        for(s = 0; s <= k; ++s){
            for(n = 0; n <= backpack_weight; ++n) {
                A[s][n] = 0;
            }
        }
        for( s = 1; s <= k ; ++s)
        {
            for( n = 1; n <= backpack_weight ; ++n)
            {
                if( weight[s-1] > n ){
                    A[s][n] = A[s-1][n];
                }else {
                    A[s][n] = std::max(A[s-1][n], A[s-1][n - weight[s-1]] + cost[s-1]);
                }
            }
        }
    }

    void rezult_1( int s , int n , unsigned long **A) {
        if (A[s][n] == 0){
            return;
        }
        else if (A[s-1][n] == A[s][n])
            rezult_1(s-1, n, A);
        else if(A[s-1][n] != A[s][n])
        {
            rezult_1( s-1, n-weight[s - 1],A);
            //std::cout << s << std::endl;
            rez_1.push_back(s);
        }
    }

    void print_rezult_1 (){
        int k = 0 ;
        k = weight.size();
        rezult_1(k,backpack_weight,A);
    }

    void rezult_2( int s , int n , unsigned long **A) {
        if (A[s][n] == 0){
            return;
        }
        else if (A[s-1][n] == A[s][n])
            rezult_2(s-1, n, A);
        else if(A[s-1][n] != A[s][n])
        {
            rezult_2( s-1, n-weight[s - 1],A);
            count.push_back(s-1);
        }
    }

    void w_p(){
        int k = 0 ;
        k = weight.size();
        rezult_2(k,backpack_weight,A);
        int weight_1 = 0;
        int cost_1 = 0;
        for ( size_t i = 0 ; i < count.size() ; i++){
            weight_1 += weight[count[i]];
            cost_1 += cost[count[i]];
        }
        // std::cout << weight_1 * n_o_d << ' ' << cost_1 << std::endl;
        rez_vect_w_p.push_back(weight_1 * n_o_d);
        rez_vect_w_p.push_back(cost_1);
    }

public:

    Backpack(unsigned long long _weight , std::vector<unsigned long >& _weight1 , std::vector<unsigned long >& _cost){
        backpack_weight = _weight;
        A = nullptr;
        n_o_d = 0;
        weight = _weight1;
        cost = _cost;
    }

    ~Backpack(){
        if(A != nullptr){
            for(int i = 0; i < weight.size() + 1; ++i){
                delete[] A[i];
            }
            delete[] A;
        }
    }

    void create(){
        all_to_nod();
        table();
        print_rezult_1();
        w_p();
    }

    std::vector <int> back_w_p(){
        return rez_vect_w_p;
    }

    std::vector <int> back_rez(){
        return rez_1;
    }

};

int main() {
    std::string str;
    int counter = 0;

    std::vector <unsigned long> p(0);// стоимость
    std::vector <unsigned long> w(0);
    std::vector <int> w_p;
    std::vector <int> rezult;
    unsigned long long W = 0; // вместимость рюкзака
    int flag = 0;

    while ( std::getline(std::cin , str) && str !="EOF") {
        unsigned long long a = 0;
        unsigned long long b = 0;
        std::string strTest;
        std::string strExp;
        int counterPr = 0;
        int position = 0;

        for (unsigned int h = 0; h < str.size(); h++) {
            if (str[h] == ' ') {
                counterPr++;
            }
            if ( counterPr > 2 || str[h] == '\0') {
                break;
            }
        }

        for (unsigned int ii = 0; ii < str.size(); ii++) {
            if (str[ii] == ' ') {
                position = ii;
                break;
            }
            strTest += str[ii];
        }

        for (unsigned int j = position + 1; j < str.size(); j++) {
            if (str[j] == ' ') {
                break;
            }
            if (str[j] == '\0') {
                break;
            }
            strExp += str[j];
        }


        b = std::atoi(strExp.c_str());
        a = std::atoi(strTest.c_str());

        if (counterPr == 0 && str != " ") {
            counter++;

            W = a;
        }
        else {
            if ( W <= 0)
                std::cout << "error" << std::endl;
        }

        if ( counter == 1 && counterPr == 1 ) {
            p.push_back(b);
            w.push_back(a);
        }
        else {
            if ( W <= 0)
                std::cout << "error" << std::endl;
        }
    }

    Backpack bcp (W,w,p);

    bcp.create();
    w_p = bcp.back_w_p();
    rezult = bcp.back_rez();

    std::cout << w_p[0] << ' ' << w_p[1] << std::endl;
    for ( size_t i = 0; i < rezult.size(); i++ ){
        std::cout << rezult[i] << std::endl;
    }

    return 0;
}
