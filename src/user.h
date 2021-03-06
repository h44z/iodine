/*
 * Copyright (c) 2006-2014 Erik Ekman <yarrick@kryo.se>,
 * 2006-2009 Bjorn Andersson <flex@kryo.se>,
 * 2015 Frekk van Blagh <frekk@frekkworks.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __USER_H__
#define __USER_H__

#include "window.h"
#include "server.h"

#define USERS 16

struct tun_user {
	char id;
	int active;
	int authenticated;
	int authenticated_raw;
	int disabled;
	time_t last_pkt;
	int seed;
	in_addr_t tun_ip;
	struct sockaddr_storage host;
	socklen_t hostlen;
	struct query q;
	/* TODO: multiple incoming query storage + handling */
	struct frag_buffer *incoming;
	struct frag_buffer *outgoing;
	int next_upstream_ack;
	struct encoder *encoder;
	char downenc;
	int downenc_bits;
	int fragsize;
	enum connection conn;
	int lazy;
	/*unsigned char qmemping_cmc[QMEMPING_LEN * 4];
	unsigned short qmemping_type[QMEMPING_LEN];
	int qmemping_lastfilled;
	unsigned char qmemdata_cmc[QMEMDATA_LEN * 4];
	unsigned short qmemdata_type[QMEMDATA_LEN];
	int qmemdata_lastfilled;*/
#ifdef DNSCACHE_LEN
	struct query dnscache_q[DNSCACHE_LEN];
	char dnscache_answer[DNSCACHE_LEN][4096];
	int dnscache_answerlen[DNSCACHE_LEN];
	int dnscache_lastfilled;
#endif
};

extern struct tun_user *users;
extern int created_users;

int user_sending(int user);
int all_users_waiting_to_send();
int user_active(int i);
int check_authenticated_user_and_ip(int userid, struct query *q);
int check_user_and_ip(int userid, struct query *q);

int init_users(in_addr_t, int);
const char* users_get_first_ip();
int find_user_by_ip(uint32_t);
int find_available_user();
void user_switch_codec(int userid, struct encoder *enc);
void user_set_conn_type(int userid, enum connection c);

#endif
