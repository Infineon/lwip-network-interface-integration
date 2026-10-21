# lwIP Network Interface Integration Library - Seamlessly Connect lwIP TCP/IP Stack with Wi-Fi and Ethernet Drivers

# Overview

The lwIP network interface integration library is an integration layer that links the lwIP TCP/IP stack with the underlying Wi-Fi Host Driver (WHD) and Ethernet driver on Infineon platforms. It interacts with FreeRTOS, the lwIP TCP/IP stack, mbed TLS for security, WHD, and the Ethernet driver, and contains the code that binds these components together. This eliminates the complexity of binding FreeRTOS, lwIP, mbed TLS, WHD, and Ethernet drivers together, enabling developers to quickly bring up network connectivity on PSOC&trade;, XMC&trade;, and PSOC&trade; Edge devices using the ModusToolbox&trade; software environment. The ModusToolbox&trade; Wi-Fi and Ethernet code examples download this library automatically.

This library is the equivalent of the now-deprecated *Wi-Fi middleware core* library. *Wi-Fi middleware core* users can follow the [porting guide](./porting_guide.md) to migrate their applications to the *lwIP network interface integration* library.

# Features

- **Wi-Fi and Ethernet interface support**: Provides a unified API to add, remove, and manage both Wi-Fi (STA and SoftAP) and Ethernet network interfaces through `cy_network_add_nw_interface` and `cy_network_remove_nw_interface`.
- **DHCP and static IP configuration**: Supports dynamic IP address assignment via DHCP as well as user-provided static IP configuration, with DHCP renew capability through `cy_network_dhcp_renew`. Includes a built-in DHCP server for SoftAP mode.
- **IPv4 and IPv6 address management**: Retrieve IPv4 addresses, IPv6 link-local addresses, gateway IP/MAC addresses, and subnet masks using dedicated API functions (`cy_network_get_ip_address`, `cy_network_get_ipv6_address`, `cy_network_get_gateway_ip_address`, `cy_network_get_netmask_address`).
- **Network activity monitoring and IP change callbacks**: Register callbacks for IP address changes (`cy_network_register_ip_change_cb`) and network Tx/Rx activity events (`cy_network_activity_register_cb`) to integrate with power management and application logic.
- **Network diagnostics**: Built-in ICMP ping support via `cy_network_ping` for connectivity testing, and true random number generation using hardware TRNG via `cy_network_random_number_generate` (not available on XMC4xxx devices).
- **D-cache and Rx polling support**: Supports D-cache enablement on XMC7000 devices and Rx polling method for XMC4700/XMC4800 devices for optimized Ethernet performance.
- **Memory footprint optimization**: For devices with limited flash and RAM, provides a documented set of tunable lwIP and mbed TLS configuration parameters that can be enabled or disabled to conserve code memory, static RAM, and heap memory. See the "Optimization of lwIP network interface integration" section of the [Reference Manual](https://infineon.github.io/lwip-network-interface-integration/api_reference_manual/html/index.html).

# When to Use

Use this library when developing IoT applications on Infineon PSOC&trade; 6, PSOC&trade; 64, XMC&trade; 7200, XMC&trade; 4700/4800, or PSOC&trade; Edge E84 platforms that require TCP/IP network connectivity over Wi-Fi or Ethernet. Typical scenarios include:

- Building Wi-Fi-connected IoT applications using PSOC&trade; 6 kits (e.g., [CY8CPROTO-062-4343W](https://www.infineon.com/cms/en/product/evaluation-boards/cy8cproto-062-4343w/), [CY8CKIT-062S2-43012](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-43012/)) with the lwIP network stack and FreeRTOS.
- Developing Ethernet-based industrial or IoT applications on XMC&trade; kits (e.g., [KIT-XMC72-EVK](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc72_evk/), [KIT_XMC47_RELAX_V1](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc47_relax_v1/), [KIT_XMC48_RELAX_ECAT_V1](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc48_relax_ecat_v1/)).
- Migrating from the deprecated *Wi-Fi middleware core* library to the new *lwIP network interface integration* library (see the [porting guide](./porting_guide.md) for API mapping).
- Any ModusToolbox&trade; project that requires a standardized abstraction layer between the lwIP stack and the underlying hardware network drivers.

## Supported Platforms

This library and its features are supported on Infineon Wi-Fi- and Ethernet-capable device families:

- **PSOC&trade; 6** with CYW4343W / CYW43012 / CYW4373 / CYW43439 / CYW43022 / CYW955513 connectivity
- **PSOC&trade; 64** secure MCUs
- **XMC7200** with CYW43xxx connectivity (Wi-Fi and Ethernet)
- **XMC4700 / XMC4800** (Ethernet)
- **PSOC&trade; Edge E84**

The set of validated kits grows over time; see [RELEASE.md](./RELEASE.md) for the specific kits validated in each release.

### Supported software and tools

This version of the library was validated for compatibility with the following software and tools:

| Software and tools                                           | Version |
| :---                                                         | :---    |
| ModusToolbox&trade; software environment                     | 3.9     |
| ModusToolbox&trade; Device Configurator                      | 5.90    |
| GCC compiler                                                 | 14.2.1  |
| IAR compiler                                                 | 9.50.2  |
| Arm&reg; compiler 6                                          | 6.22    |
| LLVM compiler                                                | 22.1.0  |

# How to Use

## 1. Add the library dependency

Add the appropriate core library using the ModusToolbox&trade; **Library Manager** (available in the ModusToolbox&trade; for VS Code extension and the Eclipse IDE), or by creating the corresponding `.mtb` file in the application's `deps` folder:

- **For Wi-Fi applications**, create a `wifi-core-freertos-lwip-mbedtls.mtb` file:

    ```
    https://github.com/Infineon/wifi-core-freertos-lwip-mbedtls#latest-v4.X#$$ASSET_REPO$$/wifi-core-freertos-lwip-mbedtls/latest-v4.X
    ```

- **For Ethernet applications**, create an `ethernet-core-freertos-lwip-mbedtls.mtb` file:

    ```
    https://github.com/Infineon/ethernet-core-freertos-lwip-mbedtls#latest-v4.X#$$ASSET_REPO$$/ethernet-core-freertos-lwip-mbedtls/latest-v4.X
    ```

Then run `make getlibs` to fetch all required libraries.

## Dependencies

The lwIP network interface integration library depends on the following:

- [lwIP FreeRTOS integration](https://github.com/Infineon/lwip-freertos-integration) - Provides the FreeRTOS OS-abstraction port required by lwIP.
- [lwIP](https://savannah.nongnu.org/projects/lwip/) - Lightweight open-source TCP/IP stack.

These dependencies are fetched automatically when you include the `wifi-core-freertos-lwip-mbedtls` (Wi-Fi) or `ethernet-core-freertos-lwip-mbedtls` (Ethernet) core library and run `make getlibs`.

## 2. Initialize the network stack and bring up an interface

```c
#include "cy_network_mw_core.h"

cy_network_interface_context *iface_ctx;

/* Step 1: Initialize the network stack */
cy_rslt_t result = cy_network_init();

/* Step 2: Add a network interface (Wi-Fi STA example) */
result = cy_network_add_nw_interface(CY_NETWORK_WIFI_STA_INTERFACE, 0,
                                     whd_iface, mac_address,
                                     NULL /* NULL for DHCP, or pass static IP */,
                                     &iface_ctx);

/* Step 3: Bring up the network (starts DHCP if no static IP was provided) */
result = cy_network_ip_up(iface_ctx);

/* Step 4: Retrieve the assigned IP address */
cy_nw_ip_address_t ip_addr;
cy_network_get_ip_address(iface_ctx, &ip_addr);
```

## 3. Register for IP change notifications (optional)

```c
void my_ip_change_handler(cy_network_interface_context *iface, void *user_data)
{
    /* Handle IP address change */
}

cy_network_register_ip_change_cb(iface_ctx, my_ip_change_handler, NULL);
```

## 4. Tear down the network

```c
cy_network_ip_down(iface_ctx);
cy_network_remove_nw_interface(iface_ctx);
cy_network_deinit();
```

## Enabling debug logs

By default, all debug log messages are disabled. To enable them, add the `ENABLE_CONNECTIVITY_MIDDLEWARE_LOGS` macro to the `DEFINES` in your Makefile:

```
DEFINES+=ENABLE_CONNECTIVITY_MIDDLEWARE_LOGS
```

Then call `cy_log_init()` provided by the *cy-log* module (part of the *connectivity-utilities* library). See the [Connectivity Utilities Reference Manual](https://infineon.github.io/connectivity-utilities/api_reference_manual/html/group__logging__utils.html) for cy-log details.

## Troubleshooting

- **DHCP timeout**: Ensure the network cable is connected (Ethernet) or Wi-Fi credentials are correct and the AP is reachable. The default DHCP timeout is 15 seconds.
- **Interface not found**: Verify the correct `cy_network_hw_interface_type_t` enum value and interface index are used.
- **Build errors with XMC devices**: Ensure the appropriate COMPONENT defines (e.g., `COMPONENT_XMC47XX`) are set in the build configuration.

# Release Notes and Changelog

- [RELEASE.md](./RELEASE.md) - Detailed release notes for all versions
- [Porting Guide](./porting_guide.md) - Migration guide from Wi-Fi middleware core to lwIP network interface integration

# License

This library is provided under Infineon software license terms. It integrates the third-party lwIP TCP/IP stack and depends on the FreeRTOS-based `lwip-freertos-integration` library; when fetched, it also pulls the `wifi-core-freertos-lwip-mbedtls` or `ethernet-core-freertos-lwip-mbedtls` core assets. These third-party components are governed by their own respective license terms. You are responsible for reviewing and accepting all applicable third-party license terms.

- [LICENSE](./LICENSE.txt)

# Copyright

(c) 2026, Infineon Technologies AG, or an affiliate of Infineon
Technologies AG.  All rights reserved.
