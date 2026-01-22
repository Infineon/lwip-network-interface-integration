/*
 * (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
 * Technologies AG. All rights reserved.
 * This software, associated documentation and materials ("Software") is
 * owned by Infineon Technologies AG or one of its affiliates ("Infineon")
 * and is protected by and subject to worldwide patent protection, worldwide
 * copyright laws, and international treaty provisions. Therefore, you may use
 * this Software only as provided in the license agreement accompanying the
 * software package from which you obtained this Software. If no license
 * agreement applies, then any use, reproduction, modification, translation, or
 * compilation of this Software is prohibited without the express written
 * permission of Infineon.
 *
 * Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
 * THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
 * SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
 * Infineon reserves the right to make changes to the Software without notice.
 * You are responsible for properly designing, programming, and testing the
 * functionality and safety of your intended application of the Software, as
 * well as complying with any legal requirements related to its use. Infineon
 * does not guarantee that the Software will be free from intrusion, data theft
 * or loss, or other breaches ("Security Breaches"), and Infineon shall have
 * no liability arising out of any Security Breaches. Unless otherwise
 * explicitly approved by Infineon, the Software may not be used in any
 * application where a failure of the Product or any consequences of the use
 * thereof can reasonably be expected to result in personal injury.
 */

#pragma once

#include "whd_wifi_api.h"
#include "cy_result.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
* \addtogroup group_lwip_network_interface_integration lwip-network-interface-integration
* \{
*
* \defgroup group_wifimwcore_eapol_functions EAPOL Functions
*/

/**
* \addtogroup group_wifimwcore_eapol_functions
* \{
* * Provides functions that the application or library can use to register and deregister.
* * These APIs are generally used by the enterprise security library.
*/

/**
 * EAPOL packet handler function pointer type; on receiving the EAPOL data, the WHD will send the data to the Wi-Fi Middleware Core.
 * The buffer should be freed by the EAPOL handler.
 *
 * @param[in] whd_iface  WHD interface.
 * @param[in] buffer     Buffer received from the WHD.
 *
 */
typedef void (*cy_wifimwcore_eapol_packet_handler_t) (whd_interface_t whd_iface, whd_buffer_t buffer);

/**
 *
 * This API allows registering the callback functions to receive EAPOL packets
 * from the WHD. If the callback is registered, and the received packet is an EAPOL packet,
 * it will be redirected to the registered callback. Passing "NULL"
 * as the handler will deregister the previously registered callback.
 *
 * @param[in] eapol_packet_handler : Callback function to be invoked when EAPOL packets are received from the WHD.
 *
 * @return CY_RSLT_SUCCESS if the registration was successful; returns \ref generic_lwip_whd_port_defines otherwise.
 *
 */
cy_rslt_t cy_wifimwcore_eapol_register_receive_handler(cy_wifimwcore_eapol_packet_handler_t eapol_packet_handler);

/** \} group_wifimwcore_eapol_functions */
#ifdef __cplusplus
}
#endif
/** \} group_lwip_network_interface_integration */
