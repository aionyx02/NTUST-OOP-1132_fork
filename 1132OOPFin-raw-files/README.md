# 113 學年度 物件導向程式設計期末專案

本專案採用單元測試導向的方式進行實作與評分。學生需實作對應邏輯以通過助教提供之 `case.h` 測資。可搭配 Visual Studio 或 CMake 系統建構與執行。

## 專案結構說明

```
.
├── solution/         # 助教的正確解答，請勿修改此資料夾
├── resources/        # 提供給學生的程式碼框架與必要檔案
├── uploads/          # OJ 評測時使用的測資覆蓋資料夾
```

- `solution/`：每題目提供完整參考解與測資。助教可於本機使用 CMake 編譯測試。
- `resources/`：提供給學生的程式檔案、資料檔與部分標頭，禁止修改指定檔案。
- `uploads/`：模擬 OJ 評測環境的資料夾，會由平台自動複製對應測資與評測入口。

## 助教端解答編譯與測試

進行解答驗證與測試：

```sh
cmake -S ./solution/ -B .temp/solution -G "Visual Studio 16 2019"
cd .temp/solution
cmake --build . --config Debug
ctest -C Debug
```

## 模擬學生 OJ 評測流程

於根目錄執行以下命令：

```sh
cmake -S uploads/001 -B .temp/001 -D INPUT_DIR:STRING=<包含原始碼的資料夾>
cmake --build .temp/001 --parallel
```

- `-S` 參數可以使用 001 以外的資料夾，但不支援 002
- `-B` 參數隨意設定編譯用的資料夾，下一步驟的 `cmake --build` 對應到即可
- `INPUT_DIR` 參數指定學生上傳的原始碼目錄。
- 若未指定，預設使用 `solution/` 資料夾下對應解答。
- 編譯完成後，可以直接進入編譯資料夾，使用 `ctest -C Debug` 查看是否通過所有測試。