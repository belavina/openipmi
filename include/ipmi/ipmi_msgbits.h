/*
 * ipmi_msgbits.h
 *
 * MontaVista IPMI interface, values used for messages.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2 of
 *  the License, or (at your option) any later version.
 *
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
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _IPMI_MSGBITS_H
#define _IPMI_MSGBITS_H

#define MAX_IPMI_DATA_SIZE 36

/* Timeout to wait for IPMI responses, in milliseconds. */
#define IPMI_RSP_TIMEOUT 5000

/*
 * IPMI commands
 */
/* Sensor/Event netfn (0x04) */
#define IPMI_GET_DEVICE_SDR_INFO_CMD		0x20
#define IPMI_GET_DEVICE_SDR_CMD			0x21
#define IPMI_RESERVE_DEVICE_SDR_REPOSITORY_CMD	0x22
#define IPMI_GET_SENSOR_READING_FACTORS_CMD	0x23
#define IPMI_SET_SENSOR_HYSTERESIS_CMD		0x24
#define IPMI_GET_SENSOR_HYSTERESIS_CMD		0x25
#define IPMI_SET_SENSOR_THRESHOLD_CMD		0x26
#define IPMI_GET_SENSOR_THRESHOLD_CMD		0x27
#define IPMI_SET_SENSOR_EVENT_ENABLE_CMD	0x28
#define IPMI_GET_SENSOR_EVENT_ENABLE_CMD	0x29
#define IPMI_REARM_SENSOR_EVENTS_CMD		0x2a
#define IPMI_GET_SENSOR_EVENT_STATUS_CMD	0x2b
#define IPMI_GET_SENSOR_READING_CMD		0x2d
#define IPMI_SET_SENSOR_TYPE_CMD		0x2e
#define IPMI_GET_SENSOR_TYPE_CMD		0x2f

/* App netfn (0x06) */
#define IPMI_GET_DEVICE_ID_CMD			0x01
#define IPMI_BROADCAST_GET_DEVICE_ID_CMD	0x01
#define IPMI_COLD_RESET_CMD			0x02
#define IPMI_WARM_RESET_CMD			0x03
#define IPMI_GET_SELF_TEST_RESULTS_CMD		0x04
#define IPMI_MANUFACTURING_TEST_ON_CMD		0x05
#define IPMI_SET_ACPI_POWER_STATE_CMD		0x06
#define IPMI_GET_ACPI_POWER_STATE_CMD		0x07
#define IPMI_GET_DEVICE_GUID_CMD		0x08
#define IPMI_ENABLE_MESSAGE_CHANNEL_RCV_CMD	0x32
#define IPMI_SEND_MSG_CMD			0x34
#define IPMI_READ_EVENT_MSG_BUFFER_CMD		0x35
#define IPMI_GET_SYSTEM_GUID_CMD		0x37
#define IPMI_GET_SESSION_CHALLENGE_CMD		0x39
#define IPMI_ACTIVATE_SESSION_CMD		0x3a
#define IPMI_CLOSE_SESSION_CMD			0x3c
#define IPMI_GET_CHANNEL_INFO_CMD		0x42

/* Storage netfn (0x0a) */
#define IPMI_GET_SDR_REPOSITORY_INFO_CMD	0x20
#define IPMI_GET_SDR_REPOSITORY_ALLOC_INFO_CMD	0x21
#define IPMI_RESERVE_SDR_REPOSITORY_CMD		0x22
#define IPMI_GET_SDR_CMD			0x23
#define IPMI_ADD_SDR_CMD			0x24
#define IPMI_PARTIAL_ADD_SDR_CMD		0x25
#define IPMI_DELETE_SDR_CMD			0x26
#define IPMI_CLEAR_SDR_REPOSITORY_CMD		0x27
#define IPMI_GET_SDR_REPOSITORY_TIME_CMD	0x28
#define IPMI_SET_SDR_REPOSITORY_TIME_CMD	0x29
#define IPMI_ENTER_SDR_REPOSITORY_UPDATE_CMD	0x2a
#define IPMI_EXIT_SDR_REPOSITORY_UPDATE_CMD	0x2b
#define IPMI_RUN_INITIALIZATION_AGENT_CMD	0x2c

#define IPMI_GET_SEL_INFO_CMD			0x40
#define IPMI_GET_SEL_ALLOCATION_INFO_CMD	0x41
#define IPMI_RESERVE_SEL_CMD			0x42
#define IPMI_GET_SEL_ENTRY_CMD			0x43
#define IPMI_ADD_SEL_ENTRY_CMD			0x44
#define IPMI_PARTIAL_ADD_SEL_ENTRY_CMD		0x45
#define IPMI_DELETE_SEL_ENTRY_CMD		0x46
#define IPMI_CLEAR_SEL_CMD			0x47
#define IPMI_GET_SEL_TIME_CMD			0x48
#define IPMI_SET_SEL_TIME_CMD			0x49
#define IPMI_GET_AUXILIARYLOG_STATUS_CMD	0x5a
#define IPMI_SET_AUXILIARYLOG_STATUS_CMD	0x5b

/*
 * NetFNs
 */
#define IPMI_CHASSIS_NETFN	0x00
#define IPMI_BRIDGE_NETFN	0x02
#define IPMI_SENSOR_EVENT_NETFN	0x04
#define IPMI_APP_NETFN		0x06
#define IPMI_FIRMWARE_NETFN	0x08
#define IPMI_STORAGE_NETFN	0x0a
#define IPMI_TRANSPORT_NETFN	0x0c

#endif /* _IPMI_MSGBITS_H */
