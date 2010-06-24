/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** Bluetooth configuration for dream (debug only)  */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/sco.h>

int vendor_setup_pcm(int sock) {
    /* Use vendor-specific HCI commands to set up SCO over HCI pr PCM */
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    /* HCI_VS_Write_SCO_Configuration_Island3
    * This command is used to configure the codec interface paramters and
    * includes configuration of the PCM clock rate which is relevant when BT
    * core is generating the clock. This command MUST be used by the host in
    * order to use PCM interface.
    * */
    hdr.opcode = 0xFD06;
    unsigned char cmd[] = {
        0x00, 0x08,         // clock rate: 2048 kHz
        0x01,               // BRF6300 is input (slave)
        0x40, 0x1f, 00, 00, // frame sync frequency: 8kHz
        0x01, 00,           // frame sync duty cycle: 1 PCM clock
        0x01,               // frame sync edge: falling
        0x00,               // frame sync polarity: active high
        0x00,               // reserved
        // CHANNEL 1
        0x10, 0x00,         // out sample size: 16 bits
        0x00, 0x00,         // out sample offset in frame: 0 PCM clock cycle
        0x00,               // out edge: rising
        0x0E, 0x00,         // in sample size: 14 bits
        0x01, 0x00,         // in sample offset in frame: 1 PCM clock cycle
        0x00,               // in edge: rising
        0x00,               // reserved
        // CHANNEL 2  (not used)
        0x00, 0x00,
        0x00, 0x00,
        0x00,
        0x00, 0x00,
        0x00, 0x00,
        0x00,
        0x00,
        };
    hdr.plen = sizeof(cmd);
    struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
    };
    int total_len = 1 + sizeof(hdr) + sizeof(cmd);
    errno = 0;
    rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
    }
    return 0;
}

int vendor_status(int sock) {
    /* Use vendor-specific HCI command to get system status */
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    /* HCI_VS_Get_System_Status */
    hdr.opcode = 0xFE1F;
    unsigned char cmd[] = {};
    hdr.plen = sizeof(cmd);
    struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
    };
    int total_len = 1 + sizeof(hdr) + sizeof(cmd);
    errno = 0;
    rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
    }
    return 0;
}

int vendor_sleep(int sock, int enable) {
    /* Use vendor-specific HCI command to go into deep sleep mode */
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    /* HCI_VS_Sleep_Mode_Configuration */
    hdr.opcode = 0xFD0C;
    unsigned char cmd[] = {
        0x01,   // big sleep (1 enable)
        enable ? 0x01 : 0x00,   // deep sleep (1 enable)
        0x00,   // deep sleep protocol mode: HCILL
        0xFF,   // reserved
        0xFF,   // output pull: don't change
        0xFF,   // input pull: don't change
        0x00,   // reserved
        0x00,   // deep sleep timeouut: 0
    };
    hdr.plen = sizeof(cmd);
    struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
    };
    int total_len = 1 + sizeof(hdr) + sizeof(cmd);
    errno = 0;
    rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
    }
    return 0;
}

int vendor_uart_baudrate(int sock, uint32_t rate) {
    /* Use vendor-specific HCI command to set uart baud rate */
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    printf("Setting baud rate to %d\n", rate);
    /* HCI_VS_Sleep_Mode_Configuration */
    hdr.opcode = 0xFF36;
    hdr.plen = sizeof(rate);
    struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &rate, sizeof(rate) },
    };
    int total_len = 1 + sizeof(hdr) + sizeof(rate);
    errno = 0;
    rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
    }
    return 0;
}

int vendor_setup_pcm2(int sock) {
   int rc;
   unsigned char type = HCI_COMMAND_PKT;
   hci_command_hdr hdr;
   // HCI_VS_Write_CODEC_Config_Enhanced_Island3
   hdr.opcode = 0xFD07;
   unsigned char cmd[] = {
       0x00,            // PCM clock shutdown: disabled
       0x00, 0x00,      // PCM clock start
       0x00, 0x00,      // PCM clock stop
       0x00,            // reserved
       // Channel 1
       0x04,            // din order: MSB first, don't swap bytes, shift sample
       0x04,            // dout order: MSB first, don't swap bytes, shift sample
       0x02,            // dout mode: Hi-Z when idle
       0x00,            // dout duplication: disabled
       0x00, 0x00, 0x00, 0x00, // tx_dup_value
       0x00,            // data quant: bitwise
       0x00,            // reserved
       // Channel 2
       0x00,            // din order
       0x00,            // dout order
       0x00,            // dout mode
       0x00,            // dout duplication
       0x00, 0x00, 0x00, 0x00, // tx_dup_value
       0x00,            // data quant
       0x00,            // reserved
    };
   hdr.plen = sizeof(cmd);
   struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
   };
   int total_len = 1 + sizeof(hdr) + sizeof(cmd);
   errno = 0;
   rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
   if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
   }
   return 0;
}

int vendor_coexist(int sock, int enable) {
    /* Use vendor-specific HCI command to set up WIFI coexistance*/
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    /* HCI_VS_Write_Wlan_Configuration */
    hdr.opcode = 0xFD1D;
    unsigned char cmd[] = {
        0x04,     // enable: SG2.0
        0x01,     // polarity: active high
        0xE9, 0x05, // priority: TDD, page, page scan, inquiry, inquiry scan, sniff, SCO/eSCO
        0x00, 0x00, // connection handle select
        0x00,     // connection handle: disable
        0x00,     // frequency mask: disable
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // freq mask: dont change
        0x04,     // wlan0 mux: IO14
        0x01,     // wlan0 input pull: enabled
        0x00,     // wlan1 mux: IO4
        0x01,     // wlan1 input pull: enabled
        0x02,     // wlan2 mux: IO3
        0x01,     // wlan2 input pull: enabled
        0x00,     // wlan3 mux: PA_OFF on IO1
        0xFF,     // wlan3 input pull: don't cahnge
        enable? 0x00 : 0x01,     // wlan interface: enable/disable
    };
    hdr.plen = sizeof(cmd);
    struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
    };
    int total_len = 1 + sizeof(hdr) + sizeof(cmd);
    errno = 0;
    rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
    }
    return 0;
}

int setup_loopback1(int sock) {
   int rc;
   unsigned char type = HCI_COMMAND_PKT;
   hci_command_hdr hdr;
   // HCI_VS_Set_PCM_Loopback_Configuration_Island3 (0xFD04)
   hdr.opcode = 0xFD04;
   unsigned char cmd[] = {
       0xFF, 0x00,      // delay: 255 frame's
   };
   hdr.plen = sizeof(cmd);
   struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
   };
   int total_len = 1 + sizeof(hdr) + sizeof(cmd);
   errno = 0;
   rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
   if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
   }
   return 0;
}

int setup_loopback2(int sock, int on) {
   int rc;
   unsigned char type = HCI_COMMAND_PKT;
   hci_command_hdr hdr;
   // HCI_VS_Set_PCM_Loopback_Enable (0xFE28)
   hdr.opcode = 0xFE28;
   printf("loopback %s\n", on ? "ON" : "OFF");
   unsigned char cmd[] = {
       on ? 0x01 : 0x00,  // enable
   };
   hdr.plen = sizeof(cmd);
   struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
   };
   int total_len = 1 + sizeof(hdr) + sizeof(cmd);
   errno = 0;
   rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
   if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
   }
   return 0;
}


int write_voice_setting(int sock) {
   int rc;
   unsigned char type = HCI_COMMAND_PKT;
   hci_command_hdr hdr;
   // HCI_Write_Voice_Setting (0x0026)
   hdr.opcode = 0x0026;
   unsigned char cmd[] = {
       0x00, 0x00,
   };
   hdr.plen = sizeof(cmd);
   struct iovec iov[] = {
       { &type, 1 },
       { &hdr, sizeof(hdr) },
       { &cmd, sizeof(cmd) },
   };
   int total_len = 1 + sizeof(hdr) + sizeof(cmd);
   errno = 0;
   rc = writev(sock, iov, sizeof(iov)/sizeof(iov[0]));
   if (rc != total_len) {
       printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
            total_len, rc, strerror(errno), errno);
       return -1;
   }
   return 0;
}

static int vendor_specific_sco_setup(int hcifd, int over_hci) {
    /* Use vendor-specific HCI commands to set up SCO over HCI or PCM */
    int rc;
    unsigned char type = HCI_COMMAND_PKT;
    hci_command_hdr hdr;
    /* HCI_VS_Write_SCO_Configuration.
     * Once this command is issued, it is valid for all new SCO channels
     * created. It is used to determine the following paramters
     * SCO Connection type - Host (voice over HCI) or Codec
     * TX packet length used for flow control calculations
     * TX Buffer max latency determines how much time the data can be in the TX
     * buffer before being flushed out. Applicable only if flow control is
     * disabled.
     */
    hdr.opcode = 0xFE10;
    hdr.plen = 0x05;
    struct hci_sco_t {
        unsigned char conn_type;
        unsigned char packet_size;
        unsigned char max_latency[2];
        unsigned char bad_crc;
    } __attribute__((packed)) hci_sco;
    hci_sco.packet_size = 0x00; /* packet size--keep current setting */
    hci_sco.max_latency[0] = 0x00;
    hci_sco.max_latency[1] = 0x00; /* max latency--keep current setting */
    hci_sco.bad_crc     = 0xFF; /* bad CRC handling--keep current setting */
    struct iovec iov[3] = {
        { &type, 1 },
        { &hdr, sizeof(hdr) },
        { &hci_sco, sizeof(hci_sco) }
    };
    int total_len = 1 + sizeof(hdr) + sizeof(hci_sco);
    printf("Setting Vendor-specific SCO over %s.\n",
         (over_hci ? "HCI" : "PCM"));
    errno = 0;
    hci_sco.conn_type = (unsigned char)(over_hci ? 0x01 : 0x00);
    rc = writev(hcifd, iov, sizeof(iov)/sizeof(iov[0]));
    if (rc != total_len) {
        printf("Can't write %d bytes (wrote %d) to HCI socket: %s (%d)!\n",
             total_len, rc, strerror(errno), errno);
        return -1;
    }
    return 0;
}

int get_hci_sock() {
    int sock = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI);
    struct sockaddr_hci addr;
    int opt;

    if(sock < 0) {
        printf("Can't create raw socket!\n");
        return -1;
    }

    opt = 1;
    printf("Setting data direction.\n");
    if (setsockopt(sock, SOL_HCI, HCI_DATA_DIR, &opt, sizeof(opt)) < 0) {
        printf("Error setting data direction\n");
        return -1;
    }

    /* Bind socket to the HCI device */
    addr.hci_family = AF_BLUETOOTH;
    addr.hci_dev = 0;  // hci0
    printf("Binding to HCI device.\n");
    if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        printf("Can't attach to device hci0. %s(%d)\n",
             strerror(errno),
             errno);
        return -1;
    }
    return sock;
}

static const int num_devices = 3;
static const char device_names[3][20] = {
    "moto",
    "jabra250",
    "jabra125",
};
static const bdaddr_t device_addrs[3] = {
    {0xE1, 0x9C, 0x97, 0x2E, 0x0B, 0x00},
    {0x5E, 0x88, 0x26, 0xA4, 0x07, 0x00},
    {0xE3, 0xFD, 0x93, 0x8F, 0x16, 0x00},
};

void print_bdaddr(const bdaddr_t* bdaddr) {
    uint8_t* b = (uint8_t*)bdaddr;
    printf("%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\n",
            b[5], b[4], b[3], b[2], b[1], b[0]);
}

const bdaddr_t* get_remote_address(char* name) {
    int i;
    for (i=0; i<num_devices; i++) {
        if (strcmp(name, device_names[i]) == 0) {
            printf("Using ");
            print_bdaddr(&device_addrs[i]);
            return &device_addrs[i];
        }
    }
    printf("Unknown device: %s\n", name);
    for (i=0; i<num_devices; i++) {
        printf("%s ", device_names[i]);
        print_bdaddr(&device_addrs[i]);
    }
    exit(1);
}

void sco_setup(char *device_name) {
    struct sockaddr_sco sco_addr;
    int sco_sock;

    sco_sock = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_SCO);
    if (sco_sock < 0) {
        printf("Could not create SCO socket\n");
        return;
    }

    /* Bind to local address */
    memset(&sco_addr, 0, sizeof(sco_addr));
    sco_addr.sco_family = AF_BLUETOOTH;
    hci_devba(0, &sco_addr.sco_bdaddr);
    printf("Local BDADDR is: ");
    print_bdaddr(&sco_addr.sco_bdaddr);
    printf("Binding...\n");
    if (bind(sco_sock, (struct sockaddr *) &sco_addr, sizeof(sco_addr)) < 0) {
        printf("Could not bind SCO socket\n");
        return;
    }

    memset(&sco_addr, 0, sizeof(sco_addr));
    sco_addr.sco_family = AF_BLUETOOTH;
    memcpy(&sco_addr.sco_bdaddr, get_remote_address(device_name), sizeof(bdaddr_t));
    printf("Connecting SCO socket...\n");
    print_bdaddr(&sco_addr.sco_bdaddr);
    if(connect(sco_sock, (struct sockaddr *)&sco_addr, sizeof(sco_addr)) < 0) {
        printf("Could not connect to SCO socket\n");
        return;
    }

    printf("SCO socket connected\n");

    struct sco_options opts;
    struct sco_conninfo conninfo;

    socklen_t len = sizeof(opts);

    if (getsockopt(sco_sock, SOL_SCO, SCO_OPTIONS, &opts, &len) < 0) {
        printf("Couldn't not get SCO socket options\n");
        return;
    }
    printf("SCO MTU: %d\n", opts.mtu);

    len = sizeof(conninfo);
    if (getsockopt(sco_sock, SOL_SCO, SCO_CONNINFO, &conninfo, &len) < 0) {
        printf("Couldn't get SCO connection options\n");
        return;
    }
    printf("SCO HCI handle: %d\n", conninfo.hci_handle);
    printf("SCO HCI device class: %02x%02x%02x\n",
              conninfo.dev_class[0],
              conninfo.dev_class[1],
              conninfo.dev_class[2]);
}



int main(int argc, char **argv) {
    if (argc == 1) {
        goto usage;
    }

    if (argc >= 2 && strcmp(argv[1], "pcm_setup") == 0 ) {
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        if (vendor_specific_sco_setup(sock, 0 /* set up over PCM */) < 0) {
            printf("Could not set up SCO\n");
            return -1;
        }
        sleep(1);
        if (vendor_setup_pcm(sock) < 0) {
            printf("Could not setup up PCM\n");
            return -1;
        }
        sleep(1);
    } else if (argc >= 2 && strcmp(argv[1], "pcm_setup2") == 0 ) {
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        if (vendor_setup_pcm2(sock) < 0) {
            printf("Could not setup up PCM\n");
            return -1;
        }
        sleep(1);
    } else if (argc >= 2 && strcmp(argv[1], "loopback") == 0 ) {
        int enable = 1;
        if (argc > 2) {
            if (strcmp(argv[2], "off") == 0) {
                enable = 0;
            }
        }
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        setup_loopback1(sock);
        setup_loopback2(sock, enable);
        sleep(1);
    } else if (argc >= 2 && strcmp(argv[1], "sleep") == 0 ) {
        int enable = 1;
        if (argc > 2) {
            if (strcmp(argv[2], "off") == 0) {
                enable = 0;
            }
        }
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        vendor_sleep(sock, enable);
        sleep(1);
    } else if (argc >= 2 && strcmp(argv[1], "coed") == 0 ) {
        int enable = 1;
        if (argc > 2) {
            if (strcmp(argv[2], "off") == 0) {
                enable = 0;
            }
        }
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        vendor_coexist(sock, enable);
        sleep(1);
    } else if (argc >= 3 && strcmp(argv[1], "rate") == 0 ) {
        uint32_t rate = atoi(argv[2]);
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        vendor_uart_baudrate(sock, rate);
        sleep(1);
    } else if (argc >= 2 && strcmp(argv[1], "vs_status") == 0 ) {
        int sock = get_hci_sock();
        if (sock < 0) {
            printf("Could not open hci socket\n");
            return -1;
        }
        vendor_status(sock);
        sleep(1);
    } else if (argc >= 3 && strcmp(argv[1], "sco_setup") == 0 ) {
        sco_setup(argv[2]);
        sleep(100000000);
    } else {
usage:
        printf("Usage:\n");
        printf("\tbtconfig sleep [on|off]\n");
        printf("\tbtconfig vs_status\n");
        printf("\tbtconfig pcm_setup\n");
        printf("\tbtconfig pcm_setup2\n");
        printf("\tbtconfig sco_setup DEVICE_ALIAS\n");
        printf("\tbtconfig loopback [on|off]\n");
        printf("\tbtconfig coed [on|off]\n");
        printf("\tbtconfig rate RATE\n");
        printf("\n");
        return 0;
    }

    return 0;
}
