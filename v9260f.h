#ifndef V9260F_H
#define V9260F_H

#include <Arduino.h>

class V9260F
{
    public:
        void begin(HardwareSerial& SerialData);   //初始化实例化串口
        void systemConfig();  
        void analogConfig0();
        void analogConfig1();
        void measureConfig0();
        void measureConfig1();
        void loop();   //数据动态更新服务


        void writeRegisterData(uint16_t Addr, uint32_t writeData, byte Device_addr);   //写入数据至寄存器
        uint32_t readRegisterData(uint16_t Addr, byte Device_addr);                 //从寄存器获取数据 uint32
        void readRegisterData(uint16_t Addr, byte Device_addr,byte *DataOutput);     //4字节数组传出
   
    private:
        HardwareSerial *_Serial;
        uint32_t Register[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        byte uchar_checksum(byte *data, byte dataSize);   //专用和校验计算
};



#endif
