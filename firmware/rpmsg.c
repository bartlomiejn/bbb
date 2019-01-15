#include <string.h>
#include "rpmsg.h"

void rpmsg_setup(void)
{
    status = &resource_table.rpmsg_vdev.status;
    while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK));
    pru_rpmsg_init(
        &rpmsg_transport,
        &resource_table.rpmsg_vring0,
        &resource_table.rpmsg_vring1,
        TO_ARM_HOST_SYS_EVENT,
        FROM_ARM_HOST_SYS_EVENT
    );
    while (pru_rpmsg_channel(
        RPMSG_NS_CREATE,
        &rpmsg_transport,
        CHAN_NAME,
        CHAN_DESC,
        CHAN_PORT
    ) != PRU_RPMSG_SUCCESS);
}

/// Attempts to receive a message over RPMsg.
uint8_t rpmsg_get_from_arm(void)
{
    return pru_rpmsg_receive(
        &rpmsg_transport,
        &rpmsg_src,
        &rpmsg_dst,
        rpmsg_receive_buf,
        &rpmsg_receive_len
    );
}

/// Sends message to ARM over RPMsg
void rpmsg_send_to_arm(char *message)
{
    pru_rpmsg_send(
        &rpmsg_transport,
        rpmsg_dst,
        rpmsg_src,
        message,
        strlen(message)
    );
}
