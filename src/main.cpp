#include <capwheel2.h>

static uint8_t data_buffer[30];

static uint16_t channel_0_counts;
static uint16_t channel_1_counts;
static uint16_t channel_2_counts;
static uint16_t channel_3_counts;

void application_init(void);
void application_task(void);
void capwheel2_get_channel_counts_task();
void capwheel2_get_gesture_task();
void capwheel2_get_wheel_coords();
void capwheel2_get_channels_task();
void capwheel2_get_channels_halt();
void capwheel2_get_channels_touch();

void setup() 
{
  application_init( );
}

void loop() 
{
  application_task( );
}


void capwheel2_get_channels_touch()
{
    switch (data_buffer[0])
    {
        case 0x00 :
        {
            Serial.println(">     |     |     |     <   \r\n" );
            break;
        }
        case 0x01 :
        {
            Serial.println(">     |     |     | CH0 <   \r\n" );
            break;
        }
        case 0x02 :
        {
            Serial.println(">     |     | CH1 |     <   \r\n" );
            break;
        }
        case 0x03 :
        {
            Serial.println(">     |     | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x04 :
        {
            Serial.println(">     | CH2 |     |     <   \r\n" );
            break;
        }
        case 0x05 :
        {
            Serial.println(">     | CH2 |     | CH0 <   \r\n" );
            break;
        }
        case 0x06 :
        {
            Serial.println(">     | CH2 | CH1 |     <   \r\n" );
            break;
        }
        case 0x07 :
        {
            Serial.println(">     | CH2 | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x08 :
        {
            Serial.println("> CH3 |     |     |     <   \r\n" );
            break;
        }
        case 0x09 :
        {
            Serial.println("> CH3 |     |     | CH0 <   \r\n" );
            break;
        }
        case 0x0A :
        {
            Serial.println("> CH3 |     | CH1 |     <   \r\n" );
            break;
        }
        case 0x0B :
        {
            Serial.println("> CH3 |     | CH1 | CH0 <   \r\n" );
            break;
        }
        case 0x0C :
        {
            Serial.println("> CH3 | CH2 |     |     <   \r\n" );
            break;
        }
        case 0x0D :
        {
            Serial.println("> CH3 | CH2 |     | CH0 <   \r\n" );
            break;
        }
        case 0x0E :
        {
            Serial.println("> CH3 | CH2 | CH1 |     <   \r\n" );
            break;
        }
        case 0x0F :
        {
            Serial.println("> CH3 | CH2 | CH1 | CH0 <   \r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void capwheel2_get_channels_halt()
{
    switch(data_buffer[1])
    {
        case 0x00 :
        {
            Serial.println(">     |     |     |     <\r\n" );
            break;
        }
        case 0x01 :
        {
            Serial.println(">     |     |     | CH0 <\r\n" );
            break;
        }
        case 0x02 :
        {
            Serial.println(">     |     | CH1 |     <\r\n" );
            break;
        }
        case 0x03 :
        {
            Serial.println(">     |     | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x04 :
        {
            Serial.println(">     | CH2 |     |     <\r\n" );
            break;
        }
        case 0x05 :
        {
            Serial.println(">     | CH2 |     | CH0 <\r\n" );
            break;
        }
        case 0x06 :
        {
            Serial.println(">     | CH2 | CH1 |     <\r\n" );
            break;
        }
        case 0x07 :
        {
            Serial.println(">     | CH2 | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x08 :
        {
            Serial.println("> CH3 |     |     |     <\r\n" );
            break;
        }
        case 0x09 :
        {
            Serial.println("> CH3 |     |     | CH0 <\r\n" );
            break;
        }
        case 0x0A :
        {
            Serial.println("> CH3 |     | CH1 |     <\r\n" );
            break;
        }
        case 0x0B :
        {
            Serial.println("> CH3 |     | CH1 | CH0 <\r\n" );
            break;
        }
        case 0x0C :
        {
            Serial.println("> CH3 | CH2 |     |     <\r\n" );
            break;
        }
        case 0x0D :
        {
            Serial.println("> CH3 | CH2 |     | CH0 <\r\n" );
            break;
        }
        case 0x0E :
        {
            Serial.println("> CH3 | CH2 | CH1 |     <\r\n" );
            break;
        }
        case 0x0F :
        {
            Serial.println("> CH3 | CH2 | CH1 | CH0 <\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void capwheel2_get_channels_task()
{
    if(capwheel2_i2c_read_wait(CAPWHEEL2_TOUCH_BYTES, &data_buffer[0], 2))
    {
        Serial.print("RDY ERROR - RESET SYSTEM");
        while(1);
    }

    Serial.println(" ");
    Serial.println(">      TOUCH BYTES      <\r\n" );
    capwheel2_get_channels_touch( );
    Serial.println(">      HALT  BYTES      <\r\n" );
    capwheel2_get_channels_halt( );
    delay(150);
}

void capwheel2_get_wheel_coords()
{
    //check if touch is active on any channels except for CH0 which is proximity
    if(capwheel2_i2c_read_wait(CAPWHEEL2_TOUCH_BYTES, &data_buffer[0], 2))
    {
        Serial.print("RDY ERROR - RESET SYSTEM");
        while(1);
    }
    if(data_buffer[0] != 0x00 && data_buffer[0] != 0x01)
    {
      if(capwheel2_i2c_read_wait(CAPWHEEL2_COORDINATES, &data_buffer[0], 3))
      {
        Serial.print("RDY ERROR - RESET SYSTEM");
        while(1);
      }
      uint8_t relative_position = (int16_t)(data_buffer[1]  | data_buffer[2]<<8);	
      Serial.print("Coords: "); Serial.print(data_buffer[0]); Serial.print(" Rel: "); Serial.println(relative_position);
    }
    //delay(25);
}

void capwheel2_get_gesture_task()
{
    if(capwheel2_i2c_read_wait(CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 2))
    {
        Serial.print("RDY ERROR - RESET SYSTEM");
        while(1);
    }

    if((data_buffer[1] & CAPWHEEL2_TAP_MASK ) == CAPWHEEL2_TAP_MASK)
    {
        Serial.println("> TAP\r\n" );
    }
    else if((data_buffer[1] & CAPWHEEL2_TOUCH_MASK ) == CAPWHEEL2_TOUCH_MASK)
    {
        Serial.println("> TOUCH\r\n" );
    }
    else if((data_buffer[1] & CAPWHEEL2_PROX_MASK ) == CAPWHEEL2_PROX_MASK)
    {
        Serial.println("> PROX\r\n" );
    }
    delay(800);
}

void capwheel2_get_channel_counts_task()
{
    if(capwheel2_i2c_read_wait(CAPWHEEL2_COUNTS, &data_buffer[0], 10))
    {
        Serial.print("RDY ERROR - RESET SYSTEM");
        while(1);
    }
    channel_0_counts = data_buffer[3];
    channel_0_counts <<= 8;
    channel_0_counts |= data_buffer[2];
    channel_1_counts = data_buffer[5];
    channel_1_counts <<= 8;
    channel_1_counts |= data_buffer[4];
    channel_2_counts = data_buffer[7];
    channel_2_counts <<= 8;
    channel_2_counts |= data_buffer[6];
    channel_3_counts = data_buffer[9];
    channel_3_counts <<= 8;
    channel_3_counts |= data_buffer[8];

    Serial.print("> Channel 0  counts : %u \r\n"); Serial.println(channel_0_counts);
    Serial.print("> Channel 1  counts : %u \r\n"); Serial.println(channel_1_counts);
    Serial.print("> Channel 2  counts : %u \r\n"); Serial.println(channel_2_counts);
    delay(150);
}


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init(void)
{
    Serial.begin(115200);
    while(!Serial){;}
    Serial.println("---- Application Init ----");
    capwheel2_init();
    if(capwheel2_default_cfg() == 1)
    {
      Serial.println("CapWheel Config Failed");
      while(1);
    }
}

void application_task(void)
{
    //capwheel2_get_channels_task();
    capwheel2_get_wheel_coords();
}
