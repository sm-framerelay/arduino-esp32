// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef __ESP_WIFI_TYPES_H__
#define __ESP_WIFI_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include "rom/queue.h"
#include "esp_err.h"
#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WIFI_MODE_NULL = 0,  /**< null mode */
    WIFI_MODE_STA,       /**< WiFi station mode */
    WIFI_MODE_AP,        /**< WiFi soft-AP mode */
    WIFI_MODE_APSTA,     /**< WiFi station + soft-AP mode */
    WIFI_MODE_MAX
} wifi_mode_t;

typedef enum {
    WIFI_IF_STA = 0,     /**< ESP32 station interface */
    WIFI_IF_AP,          /**< ESP32 soft-AP interface */
    WIFI_IF_MAX
} wifi_interface_t;

typedef enum {
    WIFI_COUNTRY_CN = 0, /**< country China, channel range [1, 14] */
    WIFI_COUNTRY_JP,     /**< country Japan, channel range [1, 14] */
    WIFI_COUNTRY_US,     /**< country USA, channel range [1, 11] */
    WIFI_COUNTRY_EU,     /**< country Europe, channel range [1, 13] */
    WIFI_COUNTRY_MAX
} wifi_country_t;

typedef enum {
    WIFI_AUTH_OPEN = 0,      /**< authenticate mode : open */
    WIFI_AUTH_WEP,           /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,       /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,      /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,  /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_MAX
} wifi_auth_mode_t;

enum {
    WIFI_REASON_UNSPECIFIED              = 1,
    WIFI_REASON_AUTH_EXPIRE              = 2,
    WIFI_REASON_AUTH_LEAVE               = 3,
    WIFI_REASON_ASSOC_EXPIRE             = 4,
    WIFI_REASON_ASSOC_TOOMANY            = 5,
    WIFI_REASON_NOT_AUTHED               = 6,
    WIFI_REASON_NOT_ASSOCED              = 7,
    WIFI_REASON_ASSOC_LEAVE              = 8,
    WIFI_REASON_ASSOC_NOT_AUTHED         = 9,
    WIFI_REASON_DISASSOC_PWRCAP_BAD      = 10,
    WIFI_REASON_DISASSOC_SUPCHAN_BAD     = 11,
    WIFI_REASON_IE_INVALID               = 13,
    WIFI_REASON_MIC_FAILURE              = 14,
    WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT   = 15,
    WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT = 16,
    WIFI_REASON_IE_IN_4WAY_DIFFERS       = 17,
    WIFI_REASON_GROUP_CIPHER_INVALID     = 18,
    WIFI_REASON_PAIRWISE_CIPHER_INVALID  = 19,
    WIFI_REASON_AKMP_INVALID             = 20,
    WIFI_REASON_UNSUPP_RSN_IE_VERSION    = 21,
    WIFI_REASON_INVALID_RSN_IE_CAP       = 22,
    WIFI_REASON_802_1X_AUTH_FAILED       = 23,
    WIFI_REASON_CIPHER_SUITE_REJECTED    = 24,

    WIFI_REASON_BEACON_TIMEOUT           = 200,
    WIFI_REASON_NO_AP_FOUND              = 201,
    WIFI_REASON_AUTH_FAIL                = 202,
    WIFI_REASON_ASSOC_FAIL               = 203,
    WIFI_REASON_HANDSHAKE_TIMEOUT        = 204,
};

typedef enum {
    WIFI_SECOND_CHAN_NONE = 0,  /**< the channel width is HT20 */
    WIFI_SECOND_CHAN_ABOVE,     /**< the channel width is HT40 and the second channel is above the primary channel */
    WIFI_SECOND_CHAN_BELOW,     /**< the channel width is HT40 and the second channel is below the primary channel */
} wifi_second_chan_t;

typedef struct {
    char *ssid;          /**< SSID of AP */
    uint8_t *bssid;      /**< MAC address of AP */
    uint8_t channel;     /**< channel, scan the specific channel */
    bool show_hidden;    /**< enable to scan AP whose SSID is hidden */
} wifi_scan_config_t;

typedef struct {
    uint8_t bssid[6];                     /**< MAC address of AP */
    uint8_t ssid[32];                     /**< SSID of AP */
    uint8_t primary;                      /**< channel of AP */
    wifi_second_chan_t second;            /**< second channel of AP */
    int8_t  rssi;                         /**< signal strength of AP */
    wifi_auth_mode_t authmode;            /**< authmode of AP */
} wifi_ap_record_t;

typedef enum {
    WIFI_PS_NONE,    /**< No power save */
    WIFI_PS_MODEM,   /**< Modem power save */
    WIFI_PS_LIGHT,   /**< Light power save */
    WIFI_PS_MAC,     /**< MAC power save */
} wifi_ps_type_t;

#define WIFI_PROTOCOL_11B         1
#define WIFI_PROTOCOL_11G         2
#define WIFI_PROTOCOL_11N         4

typedef enum {
    WIFI_BW_HT20 = 0, /* Bandwidth is HT20 */
    WIFI_BW_HT40,     /* Bandwidth is HT40 */
} wifi_bandwidth_t;

typedef struct {
    char ssid[32];              /**< SSID of ESP32 soft-AP */
    char password[64];          /**< Password of ESP32 soft-AP */
    uint8_t ssid_len;           /**< Length of SSID. If softap_config.ssid_len==0, check the SSID until there is a termination character; otherwise, set the SSID length according to softap_config.ssid_len. */
    uint8_t channel;            /**< Channel of ESP32 soft-AP */
    wifi_auth_mode_t authmode;  /**< Auth mode of ESP32 soft-AP. Do not support AUTH_WEP in soft-AP mode */
    uint8_t ssid_hidden;        /**< Broadcast SSID or not, default 0, broadcast the SSID */
    uint8_t max_connection;     /**< Max number of stations allowed to connect in, default 4, max 4 */
    uint16_t beacon_interval;   /**< Beacon interval, 100 ~ 60000 ms, default 100 ms */
} wifi_ap_config_t;

typedef struct {
    char ssid[32];         /**< SSID of target AP*/
    char password[64];     /**< password of target AP*/
    bool bssid_set;        /**< whether set MAC address of target AP or not. Generally, station_config.bssid_set needs to be 0; and it needs to be 1 only when users need to check the MAC address of the AP.*/
    uint8_t bssid[6];     /**< MAC address of target AP*/
} wifi_sta_config_t;

typedef union {
    wifi_ap_config_t  ap;  /**< configuration of AP */
    wifi_sta_config_t sta; /**< configuration of STA */
} wifi_config_t;

typedef struct {
    uint8_t mac[6];  /**< mac address of sta that associated with ESP32 soft-AP */
}wifi_sta_info_t;

#define ESP_WIFI_MAX_CONN_NUM  (8+2)       /**< max number of sta the eSP32 soft-AP can connect */
typedef struct {
    wifi_sta_info_t sta[ESP_WIFI_MAX_CONN_NUM]; /**< station list */
    uint8_t         num; /**< number of station that associated with ESP32 soft-AP */
}wifi_sta_list_t;

typedef enum {
    WIFI_STORAGE_FLASH,  /**< all configuration will strore in both memory and flash */
    WIFI_STORAGE_RAM,    /**< all configuration will only store in the memory */
} wifi_storage_t;

/**
  * @brief     Vendor IE type
  *
  */
typedef enum {
    WIFI_VND_IE_TYPE_BEACON,
    WIFI_VND_IE_TYPE_PROBE_REQ,
    WIFI_VND_IE_TYPE_PROBE_RESP,
    WIFI_VND_IE_TYPE_ASSOC_REQ,
    WIFI_VND_IE_TYPE_ASSOC_RESP,
} wifi_vendor_ie_type_t;

/**
  * @brief     Vendor IE index
  *
  */
typedef enum {
    WIFI_VND_IE_ID_0,
    WIFI_VND_IE_ID_1,
} wifi_vendor_ie_id_t;


#ifdef __cplusplus
}
#endif


#endif /* __ESP_WIFI_TYPES_H__ */