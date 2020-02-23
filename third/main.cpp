#include <codecvt>
#include <locale>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

bool intSigned(const std::wstring& s){
    size_t offset = 0;
    if( s[offset] == '-' )
        ++offset;
    return s.find_first_not_of(L"0123456789", offset) == std::wstring::npos;
}

int mini (int a, int b, int c){
    return(std::min(a, std::min(b,c)));
}

int dl_dist(std::wstring word1, std::wstring word2){

    int counter_1 = 0;
    int counter_2 = 0;
    int size_1 = 0;
    int size_2 = 0;
    while (word1[counter_1] != '\0')
        counter_1++;

    while (word2[counter_2] != '\0')
        counter_2++;

    if ( counter_1 < word1.size())
        size_1 = word1.size()/2;
    else
        size_1 = word1.size();

    if ( counter_2 < word2.size())
        size_2 = word2.size()/2;
    else
        size_2 = word2.size();

    int suppr_dist, insert_dist, subs_dist, val = 0;
    int* dist = new int[(size_1 + 1) * (size_2 + 1)];

    for( int i = 0 ; i < size_1 + 1 ; i++) {
        dist[(size_2 + 1) * i] = i;
    }
    for ( int j = 0 ; j < size_2 + 1 ; j++) {
        dist[j] = j;
    }
    for (int i = 1 ; i < size_1 + 1 ; i++){
        for (int j = 1 ; j < size_2 + 1 ; j++){
            suppr_dist = dist[(size_2 + 1) * (i - 1) + j] + 1;
            insert_dist = dist[(size_2 + 1) * i + j - 1] + 1;
            subs_dist = dist[(size_2 + 1) * (i - 1) + j - 1];

            if ( word1[i-1] != word2[j-1] ) {
                subs_dist += 1;
            }
            val = mini(suppr_dist, insert_dist, subs_dist);

            if ( ((i >= 2) && (j >= 2)) && ((word1[i-1] == word2[j-2]) && (word1[i-2] == word2[j-1]))) {
                val = std::min(dist[(size_2 + 1) * (i - 2) + j - 2] + 1, val);
            }
            dist[(size_2 + 1) * i + j] = val;
        }
    }

    int res = dist[(size_1 + 1) * (size_2 + 1) - 1];
    delete[] dist;
    return res;
}

std::vector <std::wstring> comparison (const std::vector <std::wstring>& _dict , const std::vector <std::wstring>& _inputWords ){
    std::vector < std::wstring > final;
    //std::string str_final = " ";
    for ( size_t i = 0; i < _inputWords.size() ; i++){
        for ( size_t j = 0 ; j < _dict.size(); j++){
            std::wstring str_1 = _inputWords[i];
            std::transform(str_1.begin(), str_1.end(), str_1.begin(), towlower);
            if ( dl_dist( str_1 , _dict[j]) == 0) {
                std::wstring str_final = L" ";
                str_final = _inputWords[i] + L" - ok";
                final.push_back(str_final);
                break;
            }

            if ( dl_dist( str_1 , _dict[j]) == 1 ) {
                std::wstring str_final = L" ";
                bool flag = false;
                std::vector <std::wstring> vect;
                vect.push_back(_dict[j]);
                //str_final = _inputWords[i] + L" -> " + _dict[j];
                for ( size_t z = j+1 ; z < _dict.size() ; z++ ){
                    if ( dl_dist( str_1 , _dict[z] ) == 1 ) {

                        vect.push_back(_dict[z]);
                    }
                    if (dl_dist( str_1 , _dict[z]) == 0){
                        str_final = _inputWords[i] + L" - ok";
                        flag = true;
                        break;
                    }
                }
                if ( flag == 1){
                    final.push_back(str_final);
                }
                else {
                    std::sort(vect.begin() , vect.end());
                    for ( size_t p = 0 ; p < vect.size() ; p++){
                        if ( p == 0) {
                            str_final = _inputWords[i] + L" -> " + vect[p];
                        }
                        else
                            str_final = str_final + L", " + vect[p];
                    }
                    final.push_back(str_final);
                }
                break;
            }

            if ( dl_dist( str_1 , _dict[j]) > 1){
                std::wstring str_final = L" ";
                std::vector <std::wstring> vect;
                for ( size_t z = j+1 ; z < _dict.size() ; z++ ){
                    if (dl_dist( str_1 , _dict[z]) > 1) {
                        if ( z + 1 == _dict.size()) {
                            if ( vect.size()!= 0){
                                std::sort(vect.begin() , vect.end());
                                for ( size_t p = 0 ; p < vect.size() ; p++){
                                    if ( p == 0) {
                                        str_final = _inputWords[i] + L" -> " + vect[p];
                                    }
                                    else
                                        str_final = str_final + L", " + vect[p];
                                }
                                final.push_back(str_final);
                                break;
                            }
                        }
                        continue;
                    }
                    else {
                        if (dl_dist(str_1, _dict[z]) == 1) {
                            if ( str_final == L" ") {
                                vect.push_back(_dict[z]);
                            }
                            else {
                                vect.push_back(_dict[z]);
                            }
                            if (  z + 1 == _dict.size()) {
                                std::sort(vect.begin() , vect.end());
                                for ( size_t p = 0 ; p < vect.size() ; p++){
                                    if ( p == 0) {
                                        str_final = _inputWords[i] + L" -> " + vect[p];
                                    }
                                    else
                                        str_final = str_final + L", " + vect[p];
                                }
                                final.push_back(str_final);
                                break;
                            }
                        }
                        else {
                            if ( dl_dist(str_1, _dict[z]) == 0 ){
                                str_final = _inputWords[i] + L" - ok";
                                final.push_back(str_final);
                                break;
                            }
                        }
                    }
                }
                if ( str_final == L" ") {
                    str_final = _inputWords[i] + L" -?" ;
                    final.push_back(str_final);
                    break;
                }
                else {
                    if ( str_final != L" " ) {
                        break;
                    }
                }
            }
        }
    }
    return final;
}

int main() {

    // setlocale(LC_ALL, "Russian");
    std::locale::global (std::locale("ru_RU.utf-8"));
    std::wcin.imbue(std::locale("ru_RU.utf-8"));
    std::wcout.imbue(std::locale("ru_RU.utf-8"));

    std::vector <std::wstring> result(0);
    std::vector <std::wstring> dict(0);
    std::vector <std::wstring> inputWords(0);
    int sizeDict = 0;
    int sizeInput = 0;
    std::wstring str;
    int flag_1 = 0;
    //int flag_2 = 0;

    while ( std::getline(std::wcin , str ,L'\n') && sizeDict != 1) {

        if (intSigned(str)) {
            sizeDict = std::stoi(str.c_str());
            sizeDict++; // увеличл на один чтоб вайл прекратил после слов
            flag_1 = 1;
        }

        if (flag_1 == 1 && str != L" " && intSigned(str) != 1) {
            std::transform(str.begin(), str.end(), str.begin(), towlower);
            dict.push_back(str);
            sizeDict--;
        }
    }

    while ( std::getline(std::wcin , str , L'\n') ) {
        //std::wstring workingStr;
        if ( str != L"EOF") {
            if ( str != (L" ") && intSigned(str) != 1) {
                sizeInput++;
                //inputWords.resize(sizeInput);
                inputWords.push_back(str);
            }
        }
        else {
            break;
        }
    }

    result = comparison(dict , inputWords);

    for ( size_t i = 0 ; i < result.size() ; i++) {
        std::wcout << result[i] << std::endl;
    }

    return 0;
}
