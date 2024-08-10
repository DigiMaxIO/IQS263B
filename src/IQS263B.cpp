#include "capwheel2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS


CAPWHEEL2_RETVAL capwheel2_init()
{
    Wire.begin();
    Wire.setClock(400000);
    pinMode(RDY_PIN, INPUT);
    return CAPWHEEL2_OK;
}

uint8_t capwheel2_default_cfg()
{
    uint8_t data_buffer[30];

    if(capwheel2_i2c_read_wait(CAPWHEEL2_DEVICE_INFO , &data_buffer[0], 2))
    {
        return 1;
    }

    if((data_buffer[0] != 0x3C ) && ( data_buffer[1] != 0x01))
    {
        return 1;
    }

    data_buffer[0] = 0x10; 

    if(capwheel2_i2c_write_wait(CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 1))
    {
        return 1;
    }

    data_buffer[0] = 0x00; 
    data_buffer[1] = 0x00; 
    data_buffer[2] = 0x00; 
    data_buffer[3] = 0x00;
    data_buffer[4] = 0x00; 

    if(capwheel2_i2c_write_wait(CAPWHEEL2_MULTIPLIERS, &data_buffer[0], 5))
    {
        return 1;
    }
    data_buffer[0] = 81; //0x51
    data_buffer[1] = 73; //0x49
    data_buffer[2] = 73; //0x49
    data_buffer[3] = 73; //0x49

    if(capwheel2_i2c_write_wait(CAPWHEEL2_COMPENSATION, &data_buffer[0], 4))
    {
        return 1;
    }
    data_buffer[0] = 0x22;  
    data_buffer[1] = 0x0B; 
    data_buffer[2] = 0x08; 
    data_buffer[3] = 0xB7;
    data_buffer[4] = 0x00;

    if(capwheel2_i2c_write_wait(CAPWHEEL2_PROX_SETTINGS, &data_buffer[0], 5))
    {
        return 1;
    }
    data_buffer[0] = 4;  
    data_buffer[1] = WHEEL1_THRESHOLD_SETTING; 
    data_buffer[2] = WHEEL2_THRESHOLD_SETTING; 
    data_buffer[3] = WHEEL3_THRESHOLD_SETTING; 
    data_buffer[4] = 3; 
    data_buffer[5] = 0;  
    data_buffer[6] = 20; 
    data_buffer[7] = 4;  

    if(capwheel2_i2c_write_wait(CAPWHEEL2_THRESHOLDS, &data_buffer[0], 8))
    {
        return 1;
    }
    data_buffer[0] = 0x00; 
    data_buffer[1] = 48;    
    data_buffer[2] = 64;   

    if(capwheel2_i2c_write_wait(CAPWHEEL2_TIMINGS_AND_TARGETS, &data_buffer[0], 3))
    {
        return 1;
    }
    data_buffer[0] = 20;
    data_buffer[1] = 81; 
    data_buffer[2] = 51; 

    if(capwheel2_i2c_write_wait(CAPWHEEL2_GESTURE_TIMERS, &data_buffer[0], 3))
    {
        return 1;
    }
    data_buffer[0] = 0x0F;

    if(capwheel2_i2c_write_wait(CAPWHEEL2_ACTIVE_CHANNELS, &data_buffer[0], 1))
    {
        return 1;
    }
    data_buffer[0] = 0x10;

    if(capwheel2_i2c_write_wait(CAPWHEEL2_PROX_SETTINGS, &data_buffer[0], 1))
    {
        return 1;
    }
    do
    {
        if(capwheel2_i2c_read_wait(CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 1) )
        {
            return 1;
        }
    }
    while((data_buffer[0] & 0x04) == 0x04);

    if (capwheel2_i2c_read_wait(CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 2))
    {
        return 1;
    }

    if(((data_buffer[0] & 0xA4) == 0x00))
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

void capwheel2_i2c_write_no_wait(uint8_t reg, uint8_t *data_buf, uint8_t len)
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[0] = reg;
    
    for (cnt = 1; cnt <= len; cnt++)
    {
        tx_buf[cnt] = data_buf[cnt - 1]; 
    }
    
    Wire.beginTransmission(CAPWHEEL2_DEVICE_ADDRESS);
    Wire.write(tx_buf, len + 1);
    Wire.endTransmission();
}

void capwheel2_i2c_read_no_wait(uint8_t reg, uint8_t *data_buf, uint8_t len)
{
  //Counter variable for loading array
  uint8_t i = 0; 
  //Select Device and start comms
  Wire.beginTransmission(CAPWHEEL2_DEVICE_ADDRESS);
  //Specify memory address to start reading data
  Wire.write(reg);
  //Complete selection
  Wire.endTransmission(RESTART); //Restart comms for reading next
  //Request bytes
  do{
    Wire.requestFrom(CAPWHEEL2_DEVICE_ADDRESS, len);
  }while(Wire.available() == 0);
  //Load bytes into array
  while(Wire.available())
  {
    data_buf[i] = Wire.read();
    i++;
  }

}

uint8_t capwheel2_int_get()
{
    return digitalRead(RDY_PIN);
}

uint8_t capwheel2_wait_for_rdy()
{
    uint32_t aux_counter = 0;

    while((capwheel2_int_get() == 0) && (aux_counter < 4294967295))
    {
        aux_counter++;
    }
    if(aux_counter == 4294967295)
    {
        return 1;
    }

    aux_counter = 0;
    while((capwheel2_int_get() == 1) && (aux_counter < 4294967295))
    {
        aux_counter++;
    }
    if(aux_counter == 4294967295)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

uint8_t capwheel2_i2c_read_wait(uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes)
{
    if(capwheel2_wait_for_rdy())
    {
       return 1;
    }

    capwheel2_i2c_read_no_wait(register_address, read_buffer, n_bytes);
    
    return 0;
}

uint8_t capwheel2_i2c_write_wait(uint8_t register_address, uint8_t * register_values, uint8_t n_bytes)
{  
    if(capwheel2_wait_for_rdy())
    {
       return 1;
    }

    capwheel2_i2c_write_no_wait(register_address, register_values, n_bytes);
    
    
    return 0;
}

// ------------------------------------------------------------------------- END

