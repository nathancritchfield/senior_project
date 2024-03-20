/*
 * NRF24L01.c
 *
 *  Created on: Feb 17, 2024
 *      Author: nate_
 */

#include "NRF24L01.h"

uint8_t nrf_read_reg(uint8_t reg)
{
//    uint8_t command = NRF24_CMD_R_REGISTER | reg;
//    uint8_t status;
//
//    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(&hspi1, &command, 1, 100);
//    HAL_SPI_Receive(&hspi1, &status, 1, 100);
//    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
//
//    return status;
	uint8_t command = NRF24_CMD_R_REGISTER | reg;
	uint8_t status;
	uint8_t data;
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
	HAL_SPI_Receive(&hspi1, &data, 1, 2000);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
	return data;

}

void nrf_read_reg_multi (uint8_t reg, uint8_t *data, int size){
	/*
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);
    HAL_SPI_Receive(&hspi1, data, size, 1000);

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
    */

	uint8_t command = NRF24_CMD_R_REGISTER | reg;
	uint8_t status;
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
	for(int i = 0; i<size; i++)
		HAL_SPI_Receive(&hspi1, &data[i], 1, 2000);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
}

void nrf_write_reg(uint8_t reg, uint8_t value)
{
//	uint8_t buf[2];
//    buf[0] = NRF24_CMD_W_REGISTER | reg;
//    buf[1] = value;
//
//    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(&hspi1, buf, 2, 1000);
//    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

	uint8_t command = NRF24_CMD_W_REGISTER | reg;
	uint8_t status;
	uint8_t write_val = value;
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
	HAL_SPI_Transmit(&hspi1, &write_val, 1, 2000);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

}

void nrf_write_reg_multi(uint8_t reg, uint8_t *data, int size)
{
	uint8_t command = NRF24_CMD_W_REGISTER | reg;
	uint8_t status;
	//uint8_t write_val = value;
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &command, &status, 1, 2000);
	for (int i = 0; i <size; i++)
		HAL_SPI_Transmit(&hspi1, &data[i], 1, 2000);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

}

void nrf_send_cmd (uint8_t cmd){
    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);
}

void nrf_init(void){
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);

    nrf_write_reg(NRF24_REG_CONFIG, 0);

    nrf_write_reg(NRF24_REG_EN_AA, 0); //Turn off auto ack

    nrf_write_reg(NRF24_REG_EN_RXADDR, 0); //Not enabling any data pipe

    nrf_write_reg(NRF24_REG_SETUP_AW, 0x03); //5 bytes for TX/RX address

    nrf_write_reg(NRF24_REG_SETUP_RETR, 0); //No retransmission

    nrf_write_reg(NRF24_REG_RF_CH, 0); //

    nrf_write_reg(NRF24_REG_RF_SETUP, 0x0E); //Power = 0dB, data rate = 2Mbps

    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);

}

void nrf_tx_mode(uint8_t *addr, uint8_t channel){
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);

    nrf_write_reg(NRF24_REG_RF_CH, channel);
    nrf_write_reg_multi(NRF24_REG_TX_ADDR, addr, 5);

    uint8_t config = nrf_read_reg(NRF24_REG_CONFIG);
    config = config | (1<<1);
    nrf_write_reg(NRF24_REG_CONFIG, config);

    //testing that I added
    uint8_t test = 0;
    test = nrf_read_reg(NRF24_REG_RF_SETUP);
    uint8_t test2[5] = {0};
    nrf_read_reg_multi(NRF24_REG_TX_ADDR, test2, 5);

    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
}

uint8_t nrf_transmit(uint8_t *data){
	uint8_t cmd = 0;

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);

    //TX command
    cmd = NRF24_CMD_W_TX_PAYLOAD;
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);

    //TX data send
    HAL_SPI_Transmit(&hspi1, data, 32, 1000);


    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

    HAL_Delay(1);

    uint8_t fifo_status = nrf_read_reg(NRF24_REG_FIFO_STATUS);

    if((fifo_status & (1<<4)) && (!(fifo_status & (1<<3)))){
    	cmd = NRF24_CMD_FLUSH_TX;
    	nrf_send_cmd(cmd);

    	return 1;
    }

    return 0;


}

void nrf_rx_mode(uint8_t *addr, uint8_t channel){
    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_RESET);

    nrf_write_reg(NRF24_REG_RF_CH, channel);

    uint8_t enrxaddr = nrf_read_reg(NRF24_REG_EN_RXADDR);
    enrxaddr = enrxaddr | (1<<1);
    nrf_write_reg(NRF24_REG_EN_RXADDR, enrxaddr); //select data pipe 1
    nrf_write_reg_multi(NRF24_REG_RX_ADDR_P1, addr, 5); //Write the address

    nrf_write_reg(NRF24_REG_RX_PW_P1, 32); //Set to 32 bit payload

    uint8_t config = nrf_read_reg(NRF24_REG_CONFIG);
    config = config | (1<<1) | (1<<0);
    nrf_write_reg(NRF24_REG_CONFIG, config);


    HAL_GPIO_WritePin(NRF_CE_GPIO_Port, NRF_CE_Pin, GPIO_PIN_SET);
}

uint8_t is_data_availible(int pipenum){
	uint8_t status = nrf_read_reg(NRF24_REG_STATUS);

	if((status & (1<<6)) && (status & (pipenum<<1))){
		nrf_write_reg(NRF24_REG_STATUS,(1<<6));

		return 1;
	}
	return 0;
}

void nrf_receive(uint8_t *data){
	uint8_t cmd = 0;

    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_RESET);

    //TX command
    cmd = NRF24_CMD_R_RX_PAYLOAD;
    HAL_SPI_Transmit(&hspi1, &cmd, 1, 100);

    //TX data send
    HAL_SPI_Receive(&hspi1, data, 32, 1000);


    HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PIN_SET);

    HAL_Delay(1);

    cmd = NRF24_CMD_FLUSH_RX;
    nrf_send_cmd(cmd);


}
