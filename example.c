/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  *                   Called by the main after system initialization
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables */
lis2duxs12_object_t *pLis2duxs120; /* pointer referencing the LIS2DUXS12 object instance */
lis2duxs12_axes_t gAccData; /* This variable store the acceleratometer measurement (unit: deg mg) */
/** ########## Step 1 ##########
  * The init of LIS2DUXS12 is triggered by the applicative code

  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* Retrieve and store the LIS2DUXS12 object pointer */
  pLis2duxs120 = MX_LIS2DUXS12_getobject();
  /* Initialize the LIS2DUXS12 device 0 */
  if (lis2duxs12_drv_init(pLis2duxs120, MX_LIS2DUXS12) != 0)
  {
    PRINTF("[ERROR] Step 1: LIS2DUXS12 sensor init error\r\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: LIS2DUXS12 sensor init completed\r\n");
  /* LIS2DUXS12 device 0: enable the accelerometer feature */
  if (lis2duxs12_drv_acc_enable(pLis2duxs120) != 0)
  {
    PRINTF("[ERROR] Enabling the ACC feature failed\r\n");
    goto _app_init_exit;
  }
    PRINTF("[INFO] Enabling ACC feature SUCCESS\r\n");
  return_status = EXEC_STATUS_INIT_OK;
  
_app_init_exit:
  return return_status;
}

/**
  * ########## Step 2 ##########
  * Gets the values from LIS2DUXS12.
  * The values are displayed on the terminal.
  * output: EXEC_STATUS_OK if OK, EXEC_STATUS_ERROR in case of error
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* LIS2DUXS12 device 0: get the acceleration value and print it */
  if (lis2duxs12_drv_acc_get_axes(pLis2duxs120, &gAccData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading acceleration error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: ACC X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)gAccData.x_axis,
         (int32_t)gAccData.y_axis, (int32_t)gAccData.z_axis);
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
}

/** ########## Step 3 ##########
  * In this example, app_deinit is never called and is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  lis2duxs12_drv_deinit(pLis2duxs120);

  return EXEC_STATUS_OK;
}
