

Append run 1:
md5_append(&state, (const md5_byte_t *)word, strlen(word));


const md5_byte_t *p = data;
int left = nbytes;
int offset = (state.count[0] >> 3) & 63;
md5_word_t nbits = (md5_word_t)(nbytes << 3);

/* Update the message length. */
state.count[1] += nbytes >> 29;
state.count[0] += nbits;

/* Process a final partial block. */
memcpy(state.buf, p, left);



Append run 2:
pms = state
static const md5_byte_t pad[64] = {
0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
md5_append(pms, pad, ((55 - (pms->count[0] >> 3)) & 63) + 1);


const md5_byte_t *p = data;
int left = nbytes;
int offset = (pms->count[0] >> 3) & 63; // equal to length of the string
md5_word_t nbits = (md5_word_t)(nbytes << 3);

/* Update the message length. */
pms->count[1] += nbytes >> 29;
pms->count[0] += nbits;

/* Process an initial partial block. */
int copy = nbytes;

memcpy(pms->buf + offset, p, copy);





Append run 3:
pms = state
// data is calculated before the call to append 2
md5_byte_t data[8];
for (i = 0; i < 8; ++i) {
	data[i] = (md5_byte_t)(pms->count[i >> 2] >> ((i & 3) << 3));
}
md5_append(pms, data, 8);



const md5_byte_t *p = data;
int left = nbytes;
int offset = (pms->count[0] >> 3) & 63; // equals to ((string length * 8) / 8) + ((56 - string length) * 8) / 8
md5_word_t nbits = (md5_word_t)(nbytes << 3);

/* Update the message length. */
pms->count[1] += nbytes >> 29;
pms->count[0] += nbits;

/* Process an initial partial block. */
int copy = nbytes);

memcpy(pms->buf + offset, p, copy);

p += copy;
left -= copy;
md5_process(pms, pms->buf);

/* Process a final partial block. */
memcpy(pms->buf, p, left);