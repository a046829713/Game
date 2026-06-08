# CMAKE 最低版本要求 (建議 3.10 以上)
cmake_minimum_required(VERSION 3.10)

# 專案名稱 (您可以自行更改 "MyGame")
project(MyGameT C)

# --- 自動尋找原始檔 ---
# 使用 file(GLOB ...) 指令來自動尋找所有在專案根目錄下的 .c 檔案
file(GLOB SOURCES "*.c")

# --- 建立可執行檔 ---
# *** 修正點：必須先建立目標 ***
# 使用上面找到的所有原始檔 (SOURCES) 來建立一個可執行檔。
# 執行檔的名稱會是您在 project() 中設定的名稱，也就是 "MyGame"。
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 設定標頭檔路徑 ---
# *** 修正點：在建立目標之後，才能設定它的屬性 ***
# 告訴編譯器要去哪裡尋找 .h 檔案。
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

# --- (可選，但強烈建議) 設定編譯選項 ---
# 加上這些旗標 (flags) 可以讓編譯器提供更嚴格的警告，幫助您寫出更穩健的程式碼。
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -std=c11")

# --- 輸出提示訊息 ---
# 執行 cmake 時會在終端機顯示的訊息，方便您確認。
message(STATUS "專案名稱: ${PROJECT_NAME}")
message(STATUS "找到的原始檔: ${SOURCES}")
message(STATUS "可執行檔將會被建立在 build 資料夾中。")
