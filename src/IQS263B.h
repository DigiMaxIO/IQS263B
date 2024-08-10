#ifndef CAPWHEEL2_H
#define CAPWHEEL2_H

#include <Arduino.h>
#include <Wire.h>

#define STOP true
#define RESTART false

// -------------------------------------------------------------- PUBLIC MACROS 

#define CAPWHEEL2_RETVAL  uint8_t
#define CAPWHEEL2_OK           0x00
#define CAPWHEEL2_INIT_ERROR   0xFF

#define CAPWHEEL2_DEVICE_ADDRESS             0x44

#define RDY_PIN A3


#define WHEEL1_THRESHOLD_SETTING 16 //16
#define WHEEL2_THRESHOLD_SETTING 16 //16
#define WHEEL3_THRESHOLD_SETTING 16 //16

//defgroup Cap Wheel 2 ( IQS263 ) registers 

#define CAPWHEEL2_DEVICE_INFO                0x00
#define CAPWHEEL2_SYS_FLAGS                  0x01
#define CAPWHEEL2_COORDINATES                0x02
#define CAPWHEEL2_TOUCH_BYTES                0x03
#define CAPWHEEL2_COUNTS                     0x04
#define CAPWHEEL2_LTA                        0x05
#define CAPWHEEL2_DELTAS                     0x06
#define CAPWHEEL2_MULTIPLIERS                0x07
#define CAPWHEEL2_COMPENSATION               0x08
#define CAPWHEEL2_PROX_SETTINGS              0x09
#define CAPWHEEL2_THRESHOLDS                 0x0A
#define CAPWHEEL2_TIMINGS_AND_TARGETS        0x0B
#define CAPWHEEL2_GESTURE_TIMERS             0x0C
#define CAPWHEEL2_ACTIVE_CHANNELS            0x0D
/** \} */

// Gesture Masks
#define CAPWHEEL2_TAP_MASK                   0x20
#define CAPWHEEL2_TOUCH_MASK                 0x02
#define CAPWHEEL2_PROX_MASK                  0x01


// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * @brief Initialization function.
 * @param capwheel2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPWHEEL2_RETVAL capwheel2_init();

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @returns    Data buffer setted to default values.
 *
 * @description This function executes default configuration for CapWheel2 click.
 */
uint8_t capwheel2_default_cfg();

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void capwheel2_i2c_write_no_wait(uint8_t reg, uint8_t *data_buf, uint8_t len);

/**
 * @brief Read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void capwheel2_i2c_read_no_wait(uint8_t reg, uint8_t *data_buf, uint8_t len);

/**
 * @brief Getingg state of INT pin.
 *
 * @param ctx  Click object.
 * @returns    1 for HIGH pin state, or 0 for LOW pin state.
 *
 * @description This function gets state of INT pin.
 */
uint8_t capwheel2_int_get();

/**
 * @brief Waiting for RDY (INT) pin.
 *
 * @param ctx  Click object.
 * @returns    0 if RDY pin went from HIGH to LOW state, or 1 if it did not go from HIGH to LOW state within 4,294,967,295(2^32 - 1) iterations.
 *
 * @description This function waits for RDY pin to transition from HIGH to LOW state.
 */
uint8_t capwheel2_wait_for_rdy();

/**
 * @brief Read wait function.
 *
 * 
 * @param ctx                       Click object.
 * @param register_address          Register address.
 * @param read_buffer               Buffer to store register byte(s).
 * @param len                       Number of the bytes to be read.
 * @returns                         0 if no error occured during setup, or 1 if error occured.
 *
 * @description This function reads data from the desired register.
 */
uint8_t capwheel2_i2c_read_wait(uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes);

/**
 * @brief Write wait function.
 *
 * @param ctx                       Click object.
 * @param register_address          Register address.
 * @param register_values           Buffer to store register value(s).
 * @param len                       Number of the bytes in data buf.
 * @returns                         0 if no error occured during setup, or 1 if error occured.
 *
 * @description This function sets register content.
 * @note This function waits for RDY pin to go from HIGH to LOW in order to get register contents
 */
uint8_t capwheel2_i2c_write_wait(uint8_t register_address, uint8_t * register_values, uint8_t n_bytes);

#endif  // _CAPWHEEL2_H_

// ------------------------------------------------------------------------- END
