#ifndef _SSL_H
#define _SSL_H

#include <mbedtls/ssl.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>

#include "main.h"

typedef mbedtls_ssl_context proxenet_ssl_context_t;
typedef mbedtls_x509_crt proxenet_ssl_cert_t;
typedef mbedtls_x509_buf proxenet_ssl_buf_t;

typedef struct __ssl_atom_t {
		proxenet_ssl_context_t     context;
		proxenet_ssl_cert_t        cert;
                proxenet_ssl_cert_t        ca;
		mbedtls_ctr_drbg_context   ctr_drbg;
		mbedtls_entropy_context    entropy;
		mbedtls_rsa_context        rsa;
		mbedtls_pk_context         pkey;
                mbedtls_ssl_config         conf;
		bool                       is_valid;
} ssl_atom_t;

typedef struct __ssl_context_t {
		bool         use_ssl;
		ssl_atom_t   client;
		ssl_atom_t   server;
} ssl_context_t;

#include "socket.h"
#include "utils.h"

int proxenet_ssl_init_server_context(ssl_atom_t* server, char* hostname);
int proxenet_ssl_init_client_context(ssl_atom_t* client, char* hostname);

void proxenet_ssl_wrap_socket(proxenet_ssl_context_t* s, sock_t* sock);
int proxenet_ssl_handshake(proxenet_ssl_context_t* s);

void proxenet_ssl_finish(ssl_atom_t* ssl);
void proxenet_ssl_free_structs(ssl_atom_t* ssl);

ssize_t proxenet_ssl_read(proxenet_ssl_context_t *s, void *n, size_t l);
ssize_t proxenet_ssl_write(proxenet_ssl_context_t *s, void *n, size_t l);

#endif /* _SSL_H */
