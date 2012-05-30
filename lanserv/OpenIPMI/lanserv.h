/*
 * lanserv.h
 *
 * MontaVista IPMI LAN server include file
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2003,2004,2005 MontaVista Software Inc.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * Lesser General Public License (GPL) Version 2 or the modified BSD
 * license below.  The following disclamer applies to both licenses:
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * GNU Lesser General Public Licence
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Modified BSD Licence
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *   3. The name of the author may not be used to endorse or promote
 *      products derived from this software without specific prior
 *      written permission.
 */

#ifndef __LANSERV_H
#define __LANSERV_H

#include <OpenIPMI/ipmi_auth.h>
#include <OpenIPMI/serv.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Restrictions: <=64 sessions
 */
#define SESSION_BITS_REQ	6 /* Bits required to hold a session. */
#define SESSION_MASK		0x3f

typedef struct session_s session_t;
typedef struct lan_data_s lan_data_t;

typedef struct integ_handlers_s
{
    int (*init)(lan_data_t *lan, session_t *session);
    void (*cleanup)(lan_data_t *lan, session_t *session);
    int (*add)(lan_data_t *lan, session_t *session,
	       unsigned char *pos,
	       unsigned int *data_len, unsigned int data_size);
    int (*check)(lan_data_t *lan, session_t *session, msg_t *msg);
} integ_handlers_t;

typedef struct conf_handlers_s
{
    int (*init)(lan_data_t *lan, session_t *session);
    void (*cleanup)(lan_data_t *lan, session_t *session);
    int (*encrypt)(lan_data_t *lan, session_t *session,
		   unsigned char **pos, unsigned int *hdr_left,
		   unsigned int *data_len, unsigned int *data_size);
    int (*decrypt)(lan_data_t *lan, session_t *session, msg_t *msg);
} conf_handlers_t;

typedef struct auth_handlers_s
{
    int (*init)(lan_data_t *lan, session_t *session);
    int (*set2)(lan_data_t *lan, session_t *session,
		unsigned char *data, unsigned int *data_len,
		unsigned int max_len);
    int (*check3)(lan_data_t *lan, session_t *session,
		  unsigned char *data, unsigned int *data_len);
    int (*set4)(lan_data_t *lan, session_t *session,
		unsigned char *data, unsigned int *data_len,
		unsigned int max_len);
} auth_handlers_t;

typedef struct auth_data_s
{
    unsigned char rand[16];
    unsigned char rem_rand[16];
    unsigned char role;
    unsigned char username_len;
    unsigned char username[16];
    unsigned char sik[20];
    unsigned char k1[20];
    unsigned char k2[20];
    unsigned int  akey_len;
    unsigned int  integ_len;
    void          *adata;
    const void    *akey;
    unsigned int  ikey_len;
    void          *idata;
    const void    *ikey;
    const void    *ikey2;
    unsigned int  ckey_len;
    void          *cdata;
    const void    *ckey;
} auth_data_t;

struct session_s
{
    unsigned int active : 1;
    unsigned int in_startup : 1;
    unsigned int rmcpplus : 1;

    int           handle; /* My index in the table. */

    uint32_t        recv_seq;
    uint32_t        xmit_seq;
    uint32_t        sid;
    unsigned char   userid;

    /* RMCP data */
    unsigned char   authtype;
    ipmi_authdata_t authdata;

    /* RMCP+ data */
    uint32_t        unauth_recv_seq;
    uint32_t        unauth_xmit_seq;
    uint32_t        rem_sid;
    unsigned int    auth;
    unsigned int    conf;
    unsigned int    integ;
    integ_handlers_t *integh;
    conf_handlers_t  *confh;
    auth_handlers_t  *authh;
    auth_data_t      auth_data;

    unsigned char priv;
    unsigned char max_priv;

    /* The number of seconds left before the session is shut down. */
    unsigned int time_left;

    /* Address of the message that started the sessions. */
    void *src_addr;
    int  src_len;
};

typedef struct lanparm_dest_data_s
{
    unsigned char type[4];
    unsigned char addr[13];
    unsigned char vlan[4];
} lanparm_dest_data_t;

typedef struct lanparm_data_s lanparm_data_t;
struct lanparm_data_s
{
    unsigned int set_in_progress : 2;
    void (*commit)(lan_data_t *lan); /* Called when the commit occurs. */
    unsigned int auth_type_support : 6; /* Read-only */
    unsigned int ip_addr_src : 4;
    unsigned int bmc_gen_arp_ctl : 2;
    unsigned int garp_interval : 8;
    unsigned int num_destinations : 4; /* Read-only */
    lanparm_dest_data_t dest[16];

    unsigned char auth_type_enables[5];
    unsigned char ip_addr[4];
    unsigned char mac_addr[6];
    unsigned char subnet_mask[4];
    unsigned char ipv4_hdr_parms[3];
    unsigned char primary_rmcp_port[2];
    unsigned char secondary_rmcp_port[2];
    unsigned char default_gw_ip_addr[4];
    unsigned char default_gw_mac_addr[6];
    unsigned char backup_gw_ip_addr[4];
    unsigned char backup_gw_mac_addr[6];
    unsigned char community_string[18];

    unsigned char vlan_id[2];
    unsigned char vlan_priority;
    unsigned int  num_cipher_suites : 4;
    unsigned char cipher_suite_entry[17];
    unsigned char max_priv_for_cipher_suite[9];

    /* Tells what has changed, so the commit can do something about it. */
    struct {
	unsigned int ip_addr_src : 1;
	unsigned int bmc_gen_arp_ctl : 1;
	unsigned int garp_interval : 1;
	unsigned int auth_type_enables : 1;
	unsigned int ip_addr : 1;
	unsigned int mac_addr : 1;
	unsigned int subnet_mask : 1;
	unsigned int ipv4_hdr_parms : 1;
	unsigned int primary_rmcp_port : 1;
	unsigned int secondary_rmcp_port : 1;
	unsigned int default_gw_ip_addr : 1;
	unsigned int default_gw_mac_addr : 1;
	unsigned int backup_gw_ip_addr : 1;
	unsigned int backup_gw_mac_addr : 1;
	unsigned int community_string : 1;
	unsigned int vlan_id : 1;
	unsigned int vlan_priority : 1;
	unsigned int max_priv_for_cipher_suite : 1;
	unsigned char dest_type[16];
	unsigned char dest_addr[16];
	unsigned char dest_vlan[16];
    } changed;
};

struct lan_data_s
{
    bmc_data_t *bmcinfo;

    unsigned char *guid;

    channel_t channel;

    /* The amount of time in seconds before a session will be shut
       down if there is no activity. */
    unsigned int default_session_timeout;

    unsigned char *bmc_key;

    void *user_info;

    /* Set by the user code, used to actually send a raw message out
       the UDP socket */
    void (*send_out)(lan_data_t *lan,
		     struct iovec *data, int vecs,
		     void *addr, int addr_len);

    /* Generate 'size' bytes of random data into 'data'. */
    int (*gen_rand)(lan_data_t *lan, void *data, int size);

    int debug;

    /* Don't fill in the below in the user code. */

    /* session 0 is not used. */
    session_t sessions[MAX_SESSIONS+1];

    /* Used to make the sid somewhat unique. */
    uint32_t sid_seq;

    ipmi_authdata_t challenge_auth;
    unsigned int next_challenge_seq;

    lanparm_data_t lanparm;
    lanparm_data_t lanparm_rollback;

    lanserv_addr_t *lan_addrs;
    int num_lan_addrs;
};


void handle_asf(lan_data_t *lan,
		unsigned char *data, int len,
		void *from_addr, int from_len);

void ipmi_handle_lan_msg(lan_data_t *lan,
			 unsigned char *data, int len,
			 void *from_addr, int from_len);

/* Read in a configuration file and fill in the lan and address info. */
int lanserv_read_config(bmc_data_t   *bmc,
			FILE         *f,
			int          *line,
			unsigned int channel_num);

/* Call this periodically to time things.  time_since_last is the
   number of seconds since the last call to this. */
void ipmi_lan_tick(lan_data_t *lan, unsigned int time_since_last);

int ipmi_lan_init(lan_data_t *lan);

#ifdef __cplusplus
}
#endif

#endif /* __LANSERV_H */
