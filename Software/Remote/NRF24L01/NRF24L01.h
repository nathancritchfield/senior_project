/*
 * NRF24L01.h
 *
 *  Created on: Feb 17, 2024
 *      Author: nate_
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "stm32g0xx_hal.h"
#include"spi.h"

void nrf_init(void);
void nrf_tx_mode(uint8_t *addr, uint8_t channel);
uint8_t nrf_transmit(uint8_t *data);
void nrf_rx_mode(uint8_t *addr, uint8_t channel);
uint8_t is_data_availible(int pipenum);
void nrf_receive(uint8_t *data);

int nrf_send_adc(uint32_t adc_val);

//void nrf_read_reg_multi (uint8_t reg, uint8_t *data, int size);
//void nrf_write_reg(uint8_t reg, uint8_t value);

//Command Definitions
#define NRF24_CMD_R_REGISTER	 		0x00
#define NRF24_CMD_W_REGISTER	 		0x20
#define NRF24_CMD_R_RX_PAYLOAD			0x61
#define NRF24_CMD_W_TX_PAYLOAD			0xA0
#define NRF24_CMD_FLUSH_TX				0xE1
#define NRF24_CMD_FLUSH_RX				0xE2
#define NRF24_CMD_REUSE_TX_PL			0xE3
#define NRF24_CMD_R_RX_PL_WID			0x60
#define NRF24_CMD_W_ACK_PAYLOAD			0xA8
#define NRF24_CMD_W_TX_PAYLOAD_NOACK	0xB0
#define NRF24_CMD_NOP					0xFF

//Register Definitions
#define NRF24_REG_CONFIG			 	0x00
#define NRF24_REG_EN_AA				 	0x01
#define NRF24_REG_EN_RXADDR			 	0x02
#define NRF24_REG_SETUP_AW			 	0x03
#define NRF24_REG_SETUP_RETR		 	0x04
#define NRF24_REG_RF_CH				 	0x05
#define NRF24_REG_RF_SETUP			 	0x06
#define NRF24_REG_STATUS			 	0x07


#define NRF24_REG_RX_ADDR_P1			0x0B

#define NRF24_REG_TX_ADDR				0x10

#define NRF24_REG_RX_PW_P1				0x12

#define NRF24_REG_FIFO_STATUS			0x17

// Data types
typedef enum {
	CMD_SEND_ADC = 0
} NRF24_CMD_t;

#endif /* NRF24L01_H_ */
