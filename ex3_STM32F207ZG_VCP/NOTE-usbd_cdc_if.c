################################################################################
Author: armandp.rivero@supsi.ch
Date: 19.08.2022
################################################################################

ADD THE FOLLOWING CODE IN THE FILE "usbd_cdc_if.c" located in:
/STM32F207ZG_VCP/USB_DEVICE/App/usbd_cdc_if.c





/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern uint8_t bufferVCP_Rx[64];
/* USER CODE END PV */





/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  /* USER CODE BEGIN 6 */
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);

  memset (bufferVCP_Rx, '\0', 64);  // clear the buffer
  uint8_t len = (uint8_t)*Len;
  memcpy(bufferVCP_Rx, Buf, len);  // copy the data to the buffer
  memset(Buf, '\0', len);   // clear the Buf also

  return (USBD_OK);
  /* USER CODE END 6 */
}

