#include "v9260f.h"

V9260F v9260f;
uint8_t Device_addr = 0; //设备地址( 对应板载的4颗芯片的位置  取值0-3)
void setup()
{

  SerialUSB.begin(115200);    //调试串口
  Serial1.begin(2400, SERIAL_8O1);  //与计量芯片通讯串口
  v9260f.begin(Serial1, Device_addr);
  /*传感器芯片配置*/

  /*传感器芯片配置结束*/
  v9260f.init();  //写入芯片配置参数

}

void loop()
{
  SerialUSB.print(v9260f.ARRTI());  //电流传感器原始值
  SerialUSB.print(","); 

  /*
     关于校准，一般按照总量程10%进行校准，例如 100A量程，则在10A下校准， 10A量程则在1A下校准
     首先将环接入交流源表，测量1A的adc值（等待一段时间，约1分钟，取i一段数据的平均值，记录），如下面的87551584
     除以1A 也就是1000ma，获得每毫安的adc值，再跟adc进行计算就获得了电流值
  */
  float lbs = 87551584 / 1000.0;   //校准计算

  SerialUSB.println(v9260f.ABRTI() / lbs );  //电流值

}