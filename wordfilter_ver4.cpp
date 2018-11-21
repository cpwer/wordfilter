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
#include <map>

using namespace std;

char wordfilter(wchar_t *input,wchar_t *filter){
    wchar_t *pch;
    double START,END;
    long m = 0;
    int i = 0;
    START = clock();

    wstring wsInput = input;                                                                 //將字串使用wstring進行處理
    wstring ws;
    wstring::size_type uPos = 0;                                                             //宣告句子定位點
    map<wstring, wstring> mapfoo;                                                            //dictionary tree宣告
    map<wstring, wstring>::iterator iter;
    if(wsInput.size()!=0 && wcslen(filter)!=0 && pch!=NULL){
        pch = wcstok(filter,L" ");                                                           //將filter.txt的字切割放入tree
       while(pch !=NULL){
            mapfoo.insert(pair<wstring, wstring>(pch,L"*"));                                 //dictionary tree中key為關鍵字 value為取代字與判斷
            pch = wcstok(NULL,L" ");
        }
    }
    for (uPos = 0; uPos < wsInput.length();uPos++){                                          //逐字搜尋完整之輸入句子
        for (i = 0; i<16 ;i++){                                                              //從1位元比對到最高15位元比對
            ws.assign(wsInput,uPos,i);                                                       //要與dictionary tree中key比對的字
            iter = mapfoo.find(ws);                                                          //找出比對字與key相符的位置
            if ((*iter).second == L"*"){                                                     //如果相符則取value之值驗證
                wsInput.replace(uPos,ws.size(),(*iter).second);                              //將相符字視為欲過濾字進行取代
            }
            m++;                                                                             //過濾執行時的時間複雜度
       }
    }

    END = clock();
    wcout << endl << wsInput << endl;                                                        //句子過濾後之結果
    cout << "時間複雜度" << m << " " << endl;
    cout << endl << "進行運算所花費的時間：" << (END-START) / CLOCKS_PER_SEC << " S" << endl;  //計算過濾時所花費時間
    cout << "實際花費記憶體空間" << mapfoo.size() << endl;                                     //計算實際使用之記憶體
    cout << "總共花費記憶體空間" << mapfoo.max_size() << endl;
    mapfoo.clear() ;                                                                         //過濾結束後釋放已使用之記憶體空間
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
    wchar_t input[10000] = L"";
    wchar_t change[100] = L"";
    wchar_t del[100] = L"";
    wstring lim;

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
                lim = change;
                if(lim.size()<16){                                                           //判斷位元是否超過15
                    file.write(change,wcslen(change)+1);                                     //將輸入之過濾字寫入文件中
                    file.close();
                }
                else{
                    cout << "請輸入英文15字以內 中文7字以內 " << endl;                          //如果超過則新增失敗
                }
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
                wordfilter(input,filter);                                                    //文字過濾之副程式
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
