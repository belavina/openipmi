/*
 * ipmi_auth.h
 *
 * MontaVista IPMI interface for authorization
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


#ifndef _IPMI_AUTH_H
#define _IPMI_AUTH_H

/* Data is provided to the authorization code as an array of these items, a
   "scatter-gather" list.  The algorithm will go through the item in the
   array until "data" is NULL. */
typedef struct ipmi_auth_sg_s
{
    void *data; /* NULL to terminate. */
    int  len;
} ipmi_auth_sg_t;

/* A handle for an authorization algorithm to use. */
typedef struct ipmi_authdata_s *ipmi_authdata_t;

typedef struct ipmi_auth_s
{
    /* Initialize the authorization engine and return a handle for it.
       You must pass this handle into the other authorization
       calls.  Return 0 on success or an errno on failure. */
    int (*authcode_init)(unsigned char *password, ipmi_authdata_t *handle);

    /* Generate a 16-byte authorization code and put it into
       "output". Returns 0 on success and an errno on failure.  */
    int (*authcode_gen)(ipmi_authdata_t handle,
			ipmi_auth_sg_t  data[],
			void            *output);

    /* Check that the 16-byte authorization code given in "code" is valid.
       This will return 0 if it is valid or EINVAL if not. */
    int (*authcode_check)(ipmi_authdata_t handle,
			  ipmi_auth_sg_t  data[],
			  void            *code);

    /* Free the handle.  You MUST call this when you are done with the
       handle. */
    void (*authcode_cleanup)(ipmi_authdata_t handle);
} ipmi_auth_t;

#define IPMI_USERNAME_MAX	16
#define IPMI_PASSWORD_MAX	16

/* Standard IPMI authentication algorithms. */
#define IPMI_AUTHTYPE_NONE	0
#define IPMI_AUTHTYPE_MD2	1
#define IPMI_AUTHTYPE_MD5	2
#define IPMI_AUTHTYPE_STRAIGHT	4

/* This is a table of authentication algorithms. */
#define MAX_IPMI_AUTHS		6
extern ipmi_auth_t ipmi_auths[MAX_IPMI_AUTHS];

/* IPMI privilege levels */
#define IPMI_PRIVILEGE_CALLBACK		1
#define IPMI_PRIVILEGE_USER		2
#define IPMI_PRIVILEGE_OPERATOR		3
#define IPMI_PRIVILEGE_ADMIN		4

#endif /* _IPMI_AUTH_H */