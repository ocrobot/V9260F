#ifndef V9260F_H
#define V9260F_H

#include <Arduino.h>

#define ADDR_SystemConfigRegister       0x180
#define ADDR_MeteringControlRegister0   0x183
#define ADDR_MeteringControlRegister1   0x184
#define ADDR_AnalogControlRegister0     0x185
#define ADDR_AnalogControlRegister1     0x186
#define ADDR_AnalogControlRegister2     0x187
#define ADDR_ZZDCI                      0x123
#define ADDR_ZZDCU                      0x124
#define ADDR_WARTI                      0x12C
#define ADDR_WARTU						0x132
#define ADDR_WARTM						0x12D
#define ADDR_WBRTI						0x126
#define ADDR_WBRTU						0x12B
#define ADDR_WAPT 						0x12E
#define ADDR_WAQT 						0x130
#define ADDR_WWAPT						0x12F
#define ADDR_WWAQT						0x131
#define ADDR_WBPT 						0x127
#define ADDR_WBQT 						0x129
#define ADDR_WWBPT						0x128
#define ADDR_WWBQT						0x12A
#define ADDR_EGYHT						0x181 
#define ADDR_CTH  						0x182
#define ADDR_IDETTH						0x134
#define ADDR_BandPassFilter             0x125
#define ADDR_CKSUM    					0x133


class V9260F
{
    public:

        void begin(HardwareSerial& SerialData,uint8_t device_addr_number);   //初始化实例化串口
		void init();  //将所有配置写入寄存器
        void loop();   //数据动态更新服务
		
		//配置参数
		
		bool XTAL3P2M();   //外部晶振开关  0 = 6.5536Mhz(defaulet)   1 = 3.2726Mhz
 		void XTAL3P2M(bool sw);
		
		bool XTALLP();    //使用3.2768M时 必须为1  6.5536M 保持默认 0 
		void XTALLP(bool sw);
		
		
		//获取数据
		//直流分量
		int32_t DCU(); //电压直流分量
		int32_t DCI();
		int32_t DCM();//M 通道的直流分量
		int32_t DCIM(); //M通道 DCM的数据备份
		int32_t DCTM(); //M通道测量温度时的直流分量
		//频率数据
		int32_t FREQ(); //瞬时频率
		int32_t SAFREQ(); //频率秒平均值
		int32_t AFREQ(); //频率平均值
		
		//电压电流数据
		int32_t ARRTI();  //全波电流原始值
		int32_t ARRTU();  //全波电压有效值原始值
		int32_t ARRTM();  //M通道有效原始值
		int32_t BRRTU();  //基波电压有效原始值
		int32_t BRRTI();  //基波电流有效原始值
		int32_t ARTI();   //全波电流有效瞬时值
		int32_t ARTU();   //全波电压有效瞬时值
		int32_t ARTM();   //M通道电压有效瞬时值
		int32_t ARTIM();  //
		int32_t BRTU();   //基波电压有效瞬时值
		int32_t BRTI();   //基波电流有效瞬时值
		int32_t AARTU();  //全波电压有效平均值
		int32_t AARTI();  //全波电流有效平均值
		int32_t AARTM();  //M通道有效平均值
 		int32_t ABRTU();  //基波电压有效平均值
		int32_t ABRTI();  //基波电流有效平均值
		
		//有功无功寄存器
		//int32_t 
		//int32_t 
		//int32_t 
		//int32_t 
		//int32_t 

        void writeRegisterData(uint16_t Addr, uint32_t writeData, byte Device_addr);   //写入数据至寄存器
        uint32_t readRegisterData(uint16_t Addr, byte Device_addr);                 //从寄存器获取数据 uint32
        void readRegisterData(uint16_t Addr, byte Device_addr,byte *DataOutput);     //4字节数组传出
   
    private:
		//寄存器位读位写函数
		bool readBitData(uint32_t RegisterData,uint8_t RegisterAddr);
		void setBitData(uint32_t RegisterData,uint8_t RegisterAddr,bool sw);
	
	
	
	
        HardwareSerial *_Serial;
		
		uint32_t SystemConfigRegister = 0x01FB0004;  //0x180
		
		uint32_t MeteringControlRegister0 = 0x0E000000; //0x183
		uint32_t MeteringControlRegister1 = 0x0A0B0900; //0x184
		
		uint32_t AnalogControlRegister0 = 0xDF000440; //0x185
		uint32_t AnalogControlRegister1 = 0x30000000; //0x186
		uint32_t AnalogControlRegister2 = 0x0000000F; //0x187
		
		uint32_t BandPassFilter = 0x811D2BA7; //0x0125
		
		
		//校表寄存器
		//直流偏置
		int32_t ZZDCI = 0;  //0x123
		int32_t ZZDCU = 0;  //0x124
		//电压电流测量有效值校正
		int32_t WARTI = 0;
		int32_t WARTU = 0;
		int32_t WARTM = 0;
		int32_t WBRTI = 0;
		int32_t WBRTU = 0;
		//全波有功无功校正
		int32_t WAPT = 0;
		int32_t WAQT = 0;
		int32_t WWAPT = 0;
		int32_t WWAQT = 0;
		int32_t WBPT = 0;
		int32_t WBQT = 0;
		int32_t WWBPT = 0;
		int32_t WWBQT = 0;
		//门限值寄存器
		int32_t EGYHT = 0;
		int32_t CTH = 0;
		int32_t IDETTH = 0;
		
		
		
		uint8_t _device_addr_number = 0;
        //uint32_t Register[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        byte uchar_checksum(byte *data, byte dataSize);   //专用和校验计算
};



#endif
