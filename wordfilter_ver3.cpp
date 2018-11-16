#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <math.h>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

char wordfilter(wchar_t *input,wchar_t *filter,wchar_t *repl){
    wchar_t *pch;
    double START,END;
    long m = 0;
    START = clock();
    wstring wsInput = input;                                                                 //將字串使用wstring進行處理
    wstring::size_type uPos = 0;                                                             //宣告欲過濾字之定位
    vector<wstring> foo;
    foo.reserve(150000);
    if(wsInput.size()!=0 && wcslen(filter)!=0 && pch!=NULL){
        pch = wcstok(filter,L" ");                                                           //將過濾文庫之字串以空白進行切割
        while(pch !=NULL){
            foo.push_back(pch);                                                              //將切割後的過濾字放入記憶體陣列中
            pch = wcstok(NULL,L" ");
            m++;
        }
        vector<wstring>::iterator irr;
        for (irr = foo.begin();irr!=foo.end();irr++){                                       //過濾字陣列掃描
            if(wsInput.length() >= (*irr).length()){                                        //當輸入之句子長度大於過濾字長度時執行下列動作
                uPos = wsInput.find(*irr);                                                  //將輸入之句子中第一個與過濾字相同的文字位子紀錄並作為定位點
                while(uPos != wstring::npos){                                               //在定位點不等於尾端位置時持續執行
                    wsInput.replace(uPos,(*irr).length(),repl);                             //利用定位點將欲過濾之句子過濾掉
                    uPos = wsInput.find(*irr);                                              //在句子中持續尋找重複之欲過濾字
                    m++;
                }
                m++;                                                                         //將搜尋之步驟累計作為時間複雜度之評估
            }
        }
    }
    END = clock();
    wcout << endl << wsInput << endl;                                                        //句子過濾後之結果
    cout << "時間複雜度" << m << " " << endl;
    cout << endl << "進行運算所花費的時間：" << (END-START) / CLOCKS_PER_SEC << " S" << endl;  //計算過濾時所花費時間
    cout << "實際花費記憶體空間" << foo.size() << endl;                                        //計算實際使用之記憶體
    cout << "預留之記憶體空間大小" << foo.capacity() << endl;                                  //計算預留記憶體空間
    foo.clear() ;                                                                            //過濾結束後釋放已使用之記憶體空間
    return 0;
}

char deleteword(wchar_t *del,wchar_t *filter){
    wchar_t *pch;
    fstream file;
    wofstream outfile("filter.txt");
    if(wcslen(del)!=0 && wcslen(filter)!=0){
        vector<wstring> foo;
        foo.reserve(150000);
        pch = wcstok(filter,L" ");
        while(pch !=NULL){
            foo.push_back(pch);
            pch = wcstok(NULL,L" ");
        }
        vector<wstring>::iterator irr;
        for(irr = foo.begin();irr !=foo.end();irr++){
            if(*irr == del){
                foo.erase(irr);                                                              //將與輸入之欲刪除字相同之過濾字刪除掉
                irr--;                                                                       //避免欲刪除之過濾字為文庫最後文字而導致iterator錯誤
            }
        }
        for(irr = foo.begin();irr !=foo.end();irr++){
            outfile << *irr << " ";                                                          //將過濾字存回文件中
        }
        foo.clear();
    }
    return 0;
}

int main() {
    int choose = 0;
    wchar_t filter[1000000] = L"";
    wchar_t repl[] = L"*";
    wchar_t input[10000] = L"";
    wchar_t change[100] = L"";
    wchar_t del[100] = L"";
    cout << "選擇1為新增過濾字 選擇2為刪除過濾字 選擇3為輸入句子: " << endl;
    while (cin >> choose){
        cin.ignore();
        wfstream file;
        file.open("filter.txt",ios::in);                                                     //將檔案開啟為輸出模式
        file.read(filter,sizeof(filter));                                                    //將檔案暫存進字串中
        file.close();                                                                        //關閉檔案
        switch(choose){
            case 1:
                cout << "欲增加過濾字: " << endl;
                file.open("filter.txt",ios::out|ios::app);                                   //將文件開啟為輸入模式
                wcin.get(change,sizeof(change))  ;                                           //輸入欲加入之過濾字
                wcin.ignore();
                file.write(change,wcslen(change)+1);                                         //將輸入之過濾字寫入文件中
                file.close();
                break;
            case 2:
                cout << "欲刪除過濾字: " << endl;
                wcin.get(del,sizeof(del))  ;                                                 //輸入欲刪除之過濾字
                cin.ignore();
                deleteword(del,filter);                                                      //過濾字刪除之副程式
                break;
            case 3:
                cout << "輸入句子: " << endl;
                wcin.get(input,sizeof(input))  ;                                             //輸入欲文字過濾之句子
                cin.ignore();
                wordfilter(input,filter,repl);                                               //文字過濾之副程式
                break;
            default:
                cout << "請輸入1~3中任一數字" << endl;
                choose = 0;
                break;
        }
        cout << "選擇1為新增過濾字 選擇2為刪除過濾字 選擇3為輸入句子: " << endl;
    }
    return 0;
}
