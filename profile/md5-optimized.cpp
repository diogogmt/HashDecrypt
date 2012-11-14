Append run 1:

const md5_byte_t *p = data;
int left = nbytes;
int offset = (pms->count[0] >> 3) & 63;
md5_word_t nbits = (md5_word_t)(nbytes << 3);

/* Update the message length. */
pms->count[1] += nbytes >> 29;
pms->count[0] += nbits;

/* Process a final partial block. */
memcpy(pms->buf, p, left);



Append run 2:


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