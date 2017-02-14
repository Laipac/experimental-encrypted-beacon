
#include <stdint.h>
#include "app_error.h"
#include "nrf_nvic.h"
#include "softdevice_handler.h"

#include "radio_notify.h"

/**@brief Function for initializing Radio Notification Software Interrupts.
 */
uint32_t radio_notification_init(uint32_t irq_priority, uint8_t notification_type, uint8_t notification_distance)
{
    uint32_t err_code;

    err_code = sd_nvic_ClearPendingIRQ(SWI1_IRQn);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_nvic_SetPriority(SWI1_IRQn, irq_priority);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_nvic_EnableIRQ(SWI1_IRQn);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Configure the event
    return sd_radio_notification_cfg_set(notification_type, notification_distance);
}