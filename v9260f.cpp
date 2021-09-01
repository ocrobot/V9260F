#include "v9260f.h"



void V9260F::begin(HardwareSerial& SerialData,uint8_t device_addr_number)
{
    _Serial = &SerialData; 
	_device_addr_number = device_addr_number;
}

void V9260F::init()
{
	//默认参数配置
	writeRegisterData(ADDR_SystemConfigRegister, SystemConfigRegister, _device_addr_number);
	writeRegisterData(ADDR_MeteringControlRegister0, MeteringControlRegister0, _device_addr_number);
	writeRegisterData(ADDR_MeteringControlRegister1, MeteringControlRegister1, _device_addr_number);
	writeRegisterData(ADDR_AnalogControlRegister0, AnalogControlRegister0, _device_addr_number);
	writeRegisterData(ADDR_AnalogControlRegister1, AnalogControlRegister1, _device_addr_number);
	writeRegisterData(ADDR_AnalogControlRegister2, AnalogControlRegister2, _device_addr_number);
	
	writeRegisterData(ADDR_ZZDCI, ZZDCI, _device_addr_number);
	writeRegisterData(ADDR_ZZDCU, ZZDCU, _device_addr_number);
	writeRegisterData(ADDR_WARTI, WARTI, _device_addr_number);
	
	writeRegisterData(ADDR_WARTU, WARTU, _device_addr_number);
	writeRegisterData(ADDR_WARTM, WARTM, _device_addr_number);
	writeRegisterData(ADDR_WBRTI, WBRTI, _device_addr_number);
	writeRegisterData(ADDR_WBRTU, WBRTU, _device_addr_number);
	writeRegisterData(ADDR_WAPT, WAPT, _device_addr_number);
	writeRegisterData(ADDR_WAQT, WAQT, _device_addr_number);
	writeRegisterData(ADDR_WWAPT, WWAPT, _device_addr_number);
	writeRegisterData(ADDR_WWAQT, WWAQT, _device_addr_number);
	writeRegisterData(ADDR_WBPT, WBPT, _device_addr_number);
	writeRegisterData(ADDR_WBQT, WBQT, _device_addr_number);
	writeRegisterData(ADDR_WWBPT, WWBPT, _device_addr_number);
	writeRegisterData(ADDR_WWBQT, WWBQT, _device_addr_number);
	writeRegisterData(ADDR_EGYHT, EGYHT, _device_addr_number);
	writeRegisterData(ADDR_CTH, CTH, _device_addr_number);
	writeRegisterData(ADDR_IDETTH, IDETTH, _device_addr_number);
	writeRegisterData(ADDR_BandPassFilter, BandPassFilter, _device_addr_number);
	
	//校验数据计算
	uint32_t sum_check = 0xFFFFFFFF - 
						(
						SystemConfigRegister + 
						MeteringControlRegister0 + 
						MeteringControlRegister1 + 
						AnalogControlRegister0 + 
						AnalogControlRegister1 + 
						AnalogControlRegister2 +
						ZZDCI +
						ZZDCU +
						WARTI +
						WARTU +
						WARTM +
						WBRTI +
						WBRTU +
						WAPT +
						WAQT +
						WWAPT +
						WWAQT +
						WBPT +
						WBQT +
						WWBPT +
						WWBQT +
						EGYHT +
						CTH +
						IDETTH +
						BandPassFilter
						);
	writeRegisterData(ADDR_CKSUM, sum_check, _device_addr_number);
}




//配置功能
//0x0185  模拟控制寄存器

bool V9260F::XTAL3P2M()   //外部晶振开关  0 = 6.5536Mhz(defaulet)   1 = 3.2726Mhz
{
	uint8_t bitAddr = 19;
	return readBitData(AnalogControlRegister0,bitAddr);
}
void V9260F::XTAL3P2M(bool sw)
{
	uint8_t bitAddr = 19;
	setBitData(AnalogControlRegister0,bitAddr,sw);
}


bool V9260F::XTALLP()    //使用3.2768M时 必须为1  6.5536M 保持默认 0 
{
	uint8_t bitAddr = 18;
	return readBitData(AnalogControlRegister0,bitAddr);
}
void V9260F::XTALLP(bool sw)
{
	uint8_t bitAddr = 18;
	setBitData(AnalogControlRegister0,bitAddr,sw);
}












//获取数据响应



//频率数据

int32_t V9260F::FREQ()
{
	uint16_t dataAddr = 0x019A;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}

int32_t V9260F::SAFREQ()
{
	uint16_t dataAddr = 0x011D;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}


int32_t V9260F::AFREQ()
{
	uint16_t dataAddr = 0x011E;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}


//电压电流数据
int32_t V9260F::ARRTI()  //全波电流原始值
{
	uint16_t dataAddr = 0x0105;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARRTU()  //全波电压有效值原始值
{
	uint16_t dataAddr = 0x0104;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARRTM()  //M通道有效原始值
{
	uint16_t dataAddr = 0x0106;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::BRRTU()  //基波电压有效原始值
{
	uint16_t dataAddr = 0x0109;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::BRRTI()  //基波电流有效原始值
{
	uint16_t dataAddr = 0x010A;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARTI()  //全波电流有效瞬时值
{
	uint16_t dataAddr = 0x010E;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARTU()   //全波电压有效瞬时值
{
	uint16_t dataAddr = 0x010D;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARTM()   //M通道电压有效瞬时值
{
	uint16_t dataAddr = 0x010F;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ARTIM()  //
{
	uint16_t dataAddr = 0x00F8;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::BRTU()   //基波电压有效瞬时值
{
	uint16_t dataAddr = 0x0112;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::BRTI()   //基波电流有效瞬时值
{
	uint16_t dataAddr = 0x0113;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::AARTU()  //全波电压有效平均值
{
	uint16_t dataAddr = 0x011B;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::AARTI()  //全波电流有效平均值
{
	uint16_t dataAddr = 0x011C;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::AARTM()  //M通道有效平均值
{
	uint16_t dataAddr = 0x0117;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ABRTU()  //基波电压有效平均值
{
	uint16_t dataAddr = 0x0121;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
}
int32_t V9260F::ABRTI()  //基波电流有效平均值
{
	uint16_t dataAddr = 0x0122;
	uint32_t tempData = readRegisterData(dataAddr,_device_addr_number);
	return (int32_t)tempData;
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
  _Serial->write(printData, 8); //发送请求
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




bool V9260F::readBitData(uint32_t RegisterData,uint8_t RegisterAddr)
{
	uint32_t tempData = RegisterData;
	return bitRead(tempData,RegisterAddr);
}


void V9260F::setBitData(uint32_t RegisterData,uint8_t RegisterAddr,bool sw)
{
	uint32_t tempData = RegisterData;   //获取数据
	bitWrite(tempData,RegisterAddr,sw);  //修改bit数据
	RegisterData = tempData; //回写至寄存器缓存
}