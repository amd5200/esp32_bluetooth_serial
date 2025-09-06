/*
 * ESP32 藍牙串口透傳程序
 * 功能: 藍牙 <-> 串口 雙向透傳
 * 鮑率: 115200
 */

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  
  // 初始化藍牙
  SerialBT.begin("ESP32_BT_Server"); // 藍牙設備名稱
  
  Serial.println("ESP32 藍牙串口橋接器已啟動");
  Serial.println("藍牙設備名稱: ESP32_BT_Server");
  Serial.println("開始透傳模式...");
}

void loop() {
  // 將藍牙接收的數據轉發到串口
  if (SerialBT.available()) {
    String bluetoothData = SerialBT.readString();
    Serial.print(bluetoothData); // 直接轉發，不添加額外字符
  }
  
  // 將串口接收的數據轉發到藍牙
  if (Serial.available()) {
    String serialData = Serial.readString();
    SerialBT.print(serialData); // 直接轉發，不添加額外字符
  }
}

/*
 * ==================== 使用說明 ====================
 * 
 * 1. 硬件連接:
 *    - ESP32通過USB連接到電腦
 *    - 手機或其他藍牙設備連接ESP32的藍牙
 * 
 * 2. 功能說明:
 *    - 藍牙接收到的數據 -> 直接轉發到串口 -> 電腦可接收
 *    - 電腦通過串口發送的數據 -> 直接轉發到藍牙 -> 手機可接收
 * 
 * 3. 測試方法:
 *    - 在電腦上打開串口監視器（鮑率115200）
 *    - 手機連接藍牙設備"ESP32_Bridge"
 *    - 手機發送訊息，電腦串口監視器會顯示
 *    - 電腦串口監視器發送訊息，手機會收到
 * 
 * 4. 注意事項:
 *    - 確保串口監視器設定為115200鮑率
 *    - 藍牙和串口之間是完全透明傳輸
 *    - 沒有額外的數據處理或格式化
 */