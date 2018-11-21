# wordfilter

wordfilter_ver4.cpp 為codeblocks原始碼

cmake_built 為CMake建置之c++專案

wordfilter測試結果與分析.PDF 舊版本過濾器報告

filter.txt 關鍵字文庫本

測試用句子.txt 測試使用之10句句子

wordfilter修改與新增.PDF 最新修改報告

此為C++撰寫的文字過濾器，以一個名為”filter.txt”文件檔案作為需過慮之關鍵字文庫進行文字過濾之功能，並在exe執行檔中以輸入1~3來選擇操作功能，1為新增過濾字進入到”filter.txt”文件中，2為刪除”filter.txt”文件中的過濾字，3為執行輸入需進行過濾之句子。

Filter.txt文件為題目所要求之test case，其內涵網路所搜索之大陸敏感字、髒話、自訂義之文字以及約139K個20萬-40萬隨機之數字串，約140K個不完全重複之過濾字，由於在字串變數宣告時不得大於1M大小之限制，使得文件最大僅能容下1M之容量，最大包含約150K之過濾字，故僅放入140K過濾字以免程式崩潰。

測試用句子.txt是用來測試程式執行所使用的句子文件，僅含10句涉及一些敏感字與特定文字的文件，不同句子分別測試連續敏感字，中英混雜，純英句子不同狀況下其文字過濾器的效能狀況。

******************11/21新增***********************

新增wordfilter修改與新增.PDF 

codeblocks原始碼 updata為wordfilter_ver4.cpp 

cmake_built更新為wordfilter_ver4之專案

本次Wordfilter按照要求使用 dictionary tree  之結構修改其程式碼，使其時間複雜度不因filter.txt的大小影響，進而大幅縮小其時間複雜度。
