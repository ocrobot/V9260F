#include "v9260f.h"

void V9260F::begin(HardwareSerial& SerialData)
{
    _Serial = &SerialData; 
}






void V9260F::writeRegisterData(uint16_t Addr, uint32_t writeData, byte Device_addr)
{
  byte printData[8];  //数据包长度
  printData[0] = 0XFE;
  printData[1] =  ((Addr >> 8) << 4) + (Device_addr << 2) + B10;
  printData[2] = Addr & 0xff;
  printData[3] = writeData;
  printData[4] = writeData >> 8;
  printData[5] = writeData >> 16;
  printData[6] = writeData >> 24;
  printData[7] = uchar_checksum(printData, 7); //校验值
  Serial1.write(printData, 8); //发送请求
  delay(400);
  //消息应答
  byte tempReadData[4];
  for (byte a = 0; a < 4; a++)
  {
    tempReadData[a] = _Serial->read();
    //SerialUSB.print(tempReadData[a], HEX);
    //SerialUSB.print(",");
  }
  //SerialUSB.println();
}


//获取4字节数组，方便拆分获取细节数据
void V9260F::readRegisterData(uint16_t Addr, byte Device_addr,byte *DataOutput)
{
  byte printData[8];  //数据包长度
  printData[0] = 0XFE;
  printData[1] =  ((Addr >> 8) << 4) + (Device_addr << 2) + B01;
  printData[2] = Addr & 0xff;
  printData[3] = 1;
  printData[4] = 0;
  printData[5] = 0;
  printData[6] = 0;
  printData[7] = uchar_checksum(printData, 7); //校验值
  _Serial->write(printData, 8); //发送请求
  delay(400);
  //获取数据响应
  byte tempReadData[8];
  for (byte a = 0; a < 8; a++)
  {
    tempReadData[a] = _Serial->read();
  }
  DataOutput[0] = tempReadData[3];
  DataOutput[1] = tempReadData[4];
  DataOutput[2] = tempReadData[5];
  DataOutput[3] = tempReadData[6];
}


//直接获取UINT32
uint32_t V9260F::readRegisterData(uint16_t Addr, byte Device_addr)
{
  byte printData[8];  //数据包长度
  printData[0] = 0XFE;
  printData[1] =  ((Addr >> 8) << 4) + (Device_addr << 2) + B01;
  printData[2] = Addr & 0xff;
  printData[3] = 1;
  printData[4] = 0;
  printData[5] = 0;
  printData[6] = 0;
  printData[7] = uchar_checksum(printData, 7); //校验值
  _Serial->write(printData, 8); //发送请求
  delay(400);
  //获取数据响应
  byte tempReadData[8];
  for (byte a = 0; a < 8; a++)
  {
    tempReadData[a] = _Serial->read();
  }
  //DataOutput[0] = tempReadData[3];
  //DataOutput[1] = tempReadData[4];
  //DataOutput[2] = tempReadData[5];
  //DataOutput[3] = tempReadData[6];
  uint32_t data = ((uint32_t)tempReadData[6] << 24) +((uint32_t)tempReadData[5] << 16) +((uint32_t)tempReadData[4] << 8) + (uint32_t)tempReadData[3];
  return data;
}


byte V9260F::uchar_checksum(byte *data, byte dataSize)
{
  byte tempData = 0;
  for (uint16_t a = 0; a < dataSize; a++)   //先累加
  {
    tempData = tempData + data[a];
  }
  tempData = ~tempData;   //再取反
  tempData = tempData + 0x33; //再加0x33
  return tempData;
}