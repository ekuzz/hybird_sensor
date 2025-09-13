#include <Wire.h>
#include <MLX90393.h> 

MLX90393 mlx0;
MLX90393 mlx1;
MLX90393 mlx2;
MLX90393 mlx3;
MLX90393 mlx4;

MLX90393::txyz data0 = {0,0,0,0};
MLX90393::txyz data1 = {0,0,0,0};
MLX90393::txyz data2 = {0,0,0,0};
MLX90393::txyz data3 = {0,0,0,0};
MLX90393::txyz data4 = {0,0,0,0};

uint8_t mlx0_i2c = 0x0C;
uint8_t mlx1_i2c = 0x13;
uint8_t mlx2_i2c = 0x12;
uint8_t mlx3_i2c = 0x10;
uint8_t mlx4_i2c = 0x11;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(5); }

  Wire1.begin();
  Wire1.setClock(400000);
  delay(10);
  
  mlx0.begin(mlx0_i2c, -1, Wire1);
  mlx1.begin(mlx1_i2c, -1, Wire1);
  mlx2.begin(mlx2_i2c, -1, Wire1);
  mlx3.begin(mlx3_i2c, -1, Wire1);
  mlx4.begin(mlx4_i2c, -1, Wire1);

  mlx0.startBurst(0xF);
  mlx1.startBurst(0xF);
  mlx2.startBurst(0xF);
  mlx3.startBurst(0xF);
  mlx4.startBurst(0xF);
}

void loop() {
  mlx0.readBurstData(data0);
  mlx1.readBurstData(data1);
  mlx2.readBurstData(data2);
  mlx3.readBurstData(data3);
  mlx4.readBurstData(data4);

  // 手动打包成 float 数组，避免结构体导致的字节偏差
 float all_data[20] = {
  data0.t, data0.x, data0.y, data0.z,
  data1.t, data1.x, data1.y, data1.z,
  data2.t, data2.x, data2.y, data2.z,
  data3.t, data3.x, data3.y, data3.z,
  data4.t, data4.x, data4.y, data4.z
  };

  uint8_t buffer[80];
  memcpy(buffer, all_data, 80);

  Serial.write(0xAA);
  Serial.write(0x55);
  Serial.write(buffer, 80);
  Serial.write("\r\n");


  delayMicroseconds(500);
}

