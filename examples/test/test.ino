//#include <Arduino.h>
#include "v9260f.h"
V9260F v9260f;
void setup()
{ 
  digitalWrite(0,LOW);
  delay(200);
  digitalWrite(0,HIGH);
  //delay(2000);
  SerialUSB.begin(115200);

  Serial1.begin(2400, SERIAL_8O1);
  v9260f.begin(Serial1);
  
  //计量控制寄存器
  v9260f.writeRegisterData(0x0183, 0x0E000000, 0);
  //v9260f.writeRegisterData(0x0184, 0x430000, 0);    //0a0b0900
  v9260f.writeRegisterData(0x0184, 0x0a0b0900, 0);  //有效
  
  //模拟控制寄存器
  //v9260f.writeRegisterData(0x0185, 0x3d200440, 0);  //默认参数
  v9260f.writeRegisterData(0x0185, 0xDF000440, 0);
  v9260f.writeRegisterData(0x0186, 0x30000000, 0);
  //v9260f.writeRegisterData(0x0187, 0x00000000, 0);
  v9260f.writeRegisterData(0x0187, 0x0000000F, 0);
  //系统配置寄存器
  v9260f.writeRegisterData(0x0180, 0x01FB0004, 0);
  
  //带通滤波器
  v9260f.writeRegisterData(0x0125, 0x811D2BA7, 0);
  
  //
  //writeRegisterData(0x012c, 0xFBE93380, 0);
  
  //计算校验值
  //uint32_t sum_check = 0xFFFFFFFF - (0x3d200440 + 0x30000000 + 0x430000 + 0x811D2BA7);
  uint32_t sum_check = 0xFFFFFFFF - (0x0E000000 + 0x0a0b0900 + 0xDF000440 + 0x30000000 + 0x01FB0004 + 0x811D2BA7);
  //SerialUSB.println(sum_check,HEX);
  v9260f.writeRegisterData(0x0133, sum_check, 0);
  delay(100);
}

void loop()
{
  //byte data[4];
  uint16_t _addr = 0x11C;
  uint32_t data = v9260f.readRegisterData(_addr ,0);

  SerialUSB.print(_addr,HEX);
  SerialUSB.print(":");
  SerialUSB.print(data);
  SerialUSB.print(",");
  SerialUSB.println(data / 103452);
  /*
  SerialUSB.print(data[3],HEX);
  SerialUSB.print(",");
  SerialUSB.print(data[2],HEX);
  SerialUSB.print(",");
  SerialUSB.print(data[1],HEX);
  SerialUSB.print(",");
  SerialUSB.print(data[0],HEX);
  SerialUSB.println();
  */
  delay(1000);
}