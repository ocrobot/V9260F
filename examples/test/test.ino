#include "v9260f.h"

V9260F v9260f;
HardwareSerial Serial3(PC11, PC10);   // 通讯调试串口
uint8_t Device_addr = 0; //设备地址
void setup()
{ 

  SerialUSB.begin(115200);

  Serial3.begin(2400, SERIAL_8O1);
  v9260f.begin(Serial3);
  
  //计量控制寄存器
  v9260f.writeRegisterData(0x0183, 0x0E000000, Device_addr);
  //v9260f.writeRegisterData(0x0184, 0x430000, Device_addr);    //0a0b0900
  v9260f.writeRegisterData(0x0184, 0x0a0b0900, Device_addr);  //有效(神秘参数)
  
  //模拟控制寄存器
  //v9260f.writeRegisterData(0x0185, 0x3d200440, 0);  //默认参数
  v9260f.writeRegisterData(0x0185, 0xDF000440, Device_addr);
  v9260f.writeRegisterData(0x0186, 0x30000000, Device_addr);
  //v9260f.writeRegisterData(0x0187, 0x00000000, 0);
  v9260f.writeRegisterData(0x0187, 0x0000000F, Device_addr);
  //系统配置寄存器
  v9260f.writeRegisterData(0x0180, 0x01FB0004, Device_addr);
  
  //带通滤波器
  v9260f.writeRegisterData(0x0125, 0x811D2BA7, Device_addr);
  
  //
  //writeRegisterData(0x012c, 0xFBE93380, 0);
  
  //计算校验值
  //uint32_t sum_check = 0xFFFFFFFF - (0x3d200440 + 0x30000000 + 0x430000 + 0x811D2BA7);
  uint32_t sum_check = 0xFFFFFFFF - (0x0E000000 + 0x0a0b0900 + 0xDF000440 + 0x30000000 + 0x01FB0004 + 0x811D2BA7);
  //SerialUSB.println(sum_check,HEX);
  v9260f.writeRegisterData(0x0133, sum_check, Device_addr);
  delay(100);
}

void loop()
{
  //byte data[4];
  uint16_t _addr = 0x11C;
  
  int32_t Data = v9260f.readRegisterData(_addr ,Device_addr);

  SerialUSB.print(_addr,HEX);
  SerialUSB.print(":");
  SerialUSB.print(Data);
  SerialUSB.print(",");
  SerialUSB.println(Data / 103452);
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