/* apps/apps.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2001 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#ifndef HEADER_APPS_H
#define HEADER_APPS_H

#include "e_os.h"

#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/lhash.h>
#include <openssl/conf.h>
#include <openssl/txt_db.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
#ifndef OPENSSL_NO_OCSP
#include <openssl/ocsp.h>
#endif
#include <openssl/ossl_typ.h>

#ifndef OPENSSL_SYS_NETWARE
#include <signal.h>
#endif
#if defined(OPENSSL_SYSNAME_WIN32) || defined(OPENSSL_SYSNAME_WINCE)
#  define openssl_fdset(a,b) FD_SET((unsigned int)a, b)
#else
#  define openssl_fdset(a,b) FD_SET(a, b)
#endif


int app_RAND_load_file(const char *file, BIO *bio_e, int dont_warn);
int app_RAND_write_file(const char *file, BIO *bio_e);
/* When `file' is NULL, use defaults.
 * `bio_e' is for error messages. */
void app_RAND_allow_write_file(void);
long app_RAND_load_files(char *file); /* `file' is a list of files to read,
                                       * separated by LIST_SEPARATOR_CHAR
                                       * (see e_os.h).  The string is
                                       * destroyed! */

extern CONF *config;
extern char *default_config_file;
extern BIO *bio_in;
extern BIO *bio_out;
extern BIO *bio_err;
BIO* dup_bio_in();
BIO* dup_bio_out();
BIO* bio_open_default(const char* filename, const char* mode);
extern void unbuffer(FILE* fp);

/* Often used in calls to bio_open_default. */
#define RB(xformat)  ((xformat) == FORMAT_ASN1 ? "rb" : "r")
#define WB(xformat)  ((xformat) == FORMAT_ASN1 ? "wb" : "w")

/*
 * Common verification options.
 */
#define OPT_V_ENUM \
	OPT_V__FIRST=2000, \
	OPT_V_POLICY, OPT_V_PURPOSE, OPT_V_VERIFY_NAME, OPT_V_VERIFY_DEPTH, \
	OPT_V_ATTIME, OPT_V_VERIFY_HOSTNAME, OPT_V_VERIFY_EMAIL, \
	OPT_V_VERIFY_IP, OPT_V_IGNORE_CRITICAL, OPT_V_ISSUER_CHECKS, \
	OPT_V_CRL_CHECK, OPT_V_CRL_CHECK_ALL, OPT_V_POLICY_CHECK, \
	OPT_V_EXPLICIT_POLICY, OPT_V_INHIBIT_ANY, OPT_V_INHIBIT_MAP, \
	OPT_V_X509_STRICT, OPT_V_EXTENDED_CRL, OPT_V_USE_DELTAS, \
	OPT_V_POLICY_PRINT, OPT_V_CHECK_SS_SIG, OPT_V_TRUSTED_FIRST, \
	OPT_V_SUITEB_128_ONLY, OPT_V_SUITEB_128, OPT_V_SUITEB_192, \
	OPT_V_PARTIAL_CHAIN, \
	OPT_V__LAST

#define OPT_V_OPTIONS \
	{ "policy", OPT_V_POLICY, 's' }, \
	{ "purpose", OPT_V_PURPOSE, 's' }, \
	{ "verify_name", OPT_V_VERIFY_NAME, 's' }, \
	{ "verify_depth", OPT_V_VERIFY_DEPTH, 'p' }, \
	{ "attime", OPT_V_ATTIME, 'p' }, \
	{ "verify_hostname", OPT_V_VERIFY_HOSTNAME, 's' }, \
	{ "verify_email", OPT_V_VERIFY_EMAIL, 's' }, \
	{ "verify_ip", OPT_V_VERIFY_IP, 's' }, \
	{ "ignore_critical", OPT_V_IGNORE_CRITICAL, '-' }, \
	{ "issuer_checks", OPT_V_ISSUER_CHECKS, '-' }, \
	{ "crl_check", OPT_V_CRL_CHECK, '-' }, \
	{ "crl_check_all", OPT_V_CRL_CHECK_ALL, '-' }, \
	{ "policy_check", OPT_V_POLICY_CHECK, '-' }, \
	{ "explicit_policy", OPT_V_EXPLICIT_POLICY, '-' }, \
	{ "inhibit_any", OPT_V_INHIBIT_ANY, '-' }, \
	{ "inhibit_map", OPT_V_INHIBIT_MAP, '-' }, \
	{ "x509_strict", OPT_V_X509_STRICT, '-' }, \
	{ "extended_crl", OPT_V_EXTENDED_CRL, '-' }, \
	{ "use_deltas", OPT_V_USE_DELTAS, '-' }, \
	{ "policy_print", OPT_V_POLICY_PRINT, '-' }, \
	{ "check_ss_sig", OPT_V_CHECK_SS_SIG, '-' }, \
	{ "trusted_first", OPT_V_TRUSTED_FIRST, '-' }, \
	{ "suiteB_128_only", OPT_V_SUITEB_128_ONLY, '-' }, \
	{ "suiteB_128", OPT_V_SUITEB_128, '-' }, \
	{ "suiteB_192", OPT_V_SUITEB_192, '-' }, \
	{ "partial_chain", OPT_V_PARTIAL_CHAIN, '-' }

#define OPT_V_CASES \
	OPT_V__FIRST: case OPT_V__LAST: break; \
	case OPT_V_POLICY: \
	case OPT_V_PURPOSE: \
	case OPT_V_VERIFY_NAME: \
	case OPT_V_VERIFY_DEPTH: \
	case OPT_V_ATTIME: \
	case OPT_V_VERIFY_HOSTNAME: \
	case OPT_V_VERIFY_EMAIL: \
	case OPT_V_VERIFY_IP: \
	case OPT_V_IGNORE_CRITICAL: \
	case OPT_V_ISSUER_CHECKS: \
	case OPT_V_CRL_CHECK: \
	case OPT_V_CRL_CHECK_ALL: \
	case OPT_V_POLICY_CHECK: \
	case OPT_V_EXPLICIT_POLICY: \
	case OPT_V_INHIBIT_ANY: \
	case OPT_V_INHIBIT_MAP: \
	case OPT_V_X509_STRICT: \
	case OPT_V_EXTENDED_CRL: \
	case OPT_V_USE_DELTAS: \
	case OPT_V_POLICY_PRINT: \
	case OPT_V_CHECK_SS_SIG: \
	case OPT_V_TRUSTED_FIRST: \
	case OPT_V_SUITEB_128_ONLY: \
	case OPT_V_SUITEB_128: \
	case OPT_V_SUITEB_192: \
	case OPT_V_PARTIAL_CHAIN

/*
 * Common "extended"? options.
 */
#define OPT_X_ENUM \
	OPT_X__FIRST=1000, \
	OPT_X_KEY, OPT_X_CERT, OPT_X_CHAIN, OPT_X_CHAIN_BUILD, \
	OPT_X_CERTFORM, OPT_X_KEYFORM, \
	OPT_X__LAST

#define OPT_X_OPTIONS \
	{ "xkey", OPT_X_KEY, '<' }, \
	{ "xcert", OPT_X_CERT, '<' }, \
	{" xchain", OPT_X_CHAIN, '<' }, \
	{ "xchain_build", OPT_X_CHAIN_BUILD, '-' }, \
	{ "xcertform", OPT_X_CERTFORM, 'F' }, \
	{ "xkeyform", OPT_X_KEYFORM, 'F' }

#define OPT_X_CASES \
	OPT_X__FIRST: case OPT_X__LAST: break; \
	case OPT_X_KEY: \
	case OPT_X_CERT: \
	case OPT_X_CHAIN: \
	case OPT_X_CHAIN_BUILD: \
	case OPT_X_CERTFORM: \
	case OPT_X_KEYFORM

/*
 * Common SSL options.
 */
#define OPT_S_ENUM \
	OPT_S__FIRST=3000, \
	OPT_S_SIGALGS, OPT_S_CLIENT_SIGALGS, OPT_S_CURVES, OPT_S_NAMED_CURVE, \
	OPT_S_CIPHER, OPT_S_CERT, OPT_S_KEY, OPT_S_DHPARAM, \
	OPT_S__LAST

#define OPT_S_OPTIONS \
	{ "sigalgs", OPT_S_SIGALGS, 's' }, \
	{ "client_sigalgs", OPT_S_CLIENT_SIGALGS, 's' }, \
	{ "curves", OPT_S_CURVES, 's' }, \
	{ "named_curve", OPT_S_NAMED_CURVE, 's' }, \
	{ "cipher", OPT_S_CIPHER, 's' }, \
	{ "cert", OPT_S_CERT, '<' }, \
	{ "key", OPT_S_KEY, '<' }, \
	{ "dhparam", OPT_S_DHPARAM, '<' }

#define OPT_S_CASES \
	OPT_S__FIRST: case OPT_S__LAST: break; \
	case OPT_S_SIGALGS: \
	case OPT_S_CLIENT_SIGALGS: \
	case OPT_S_CURVES: \
	case OPT_S_NAMED_CURVE: \
	case OPT_S_CIPHER: \
	case OPT_S_CERT: \
	case OPT_S_KEY: \
	case OPT_S_DHPARAM

/*
 * Option parsing.
 */
extern const char OPT_HELP_STR[];
extern const char OPT_MORE_STR[];
typedef struct options_st {
	const char* name;
	int retval;
	/* value type:
	 *   - no value, (also the value zero)
	 *   n number, p positive number, u unsigned,
	 *   s string, < input file, > output file,
	 *   f der/pem format, F any format identifier */
	int valtype;
	const char* helpstr;
} OPTIONS;

typedef struct opt_pair_st {
	const char* name;
	int retval;
} OPT_PAIR;

extern char* opt_progname(const char *argv0);
extern char* opt_getprog(void);
extern char* opt_init(int ac, char** av, const OPTIONS* o);
extern int opt_next();
extern int opt_format(const char *s, int onlyderpem, int* result);
extern int opt_int(const char* arg, int* result);
extern int opt_ulong(const char* arg, unsigned long* result);
extern int opt_long(const char* arg, long* result);
extern int opt_pair(const char* arg, const OPT_PAIR* pairs, int* result);
extern int opt_cipher(const char* name, const EVP_CIPHER** cipherp);
extern int opt_md(const char* name, const EVP_MD** mdp);
extern char* opt_arg(void);
extern char* opt_flag(void);
extern char* opt_unknown(void);
extern char* opt_reset(void);
extern char** opt_rest(void);
extern int opt_num_rest(void);
extern int opt_verify(int i, X509_VERIFY_PARAM* vpm);
extern void printhelp(const char**);
extern void opt_help(const OPTIONS* list);

typedef struct args_st
	{
	char **data;
	int count;
	} ARGS;

#define PW_MIN_LENGTH 4
typedef struct pw_cb_data
	{
	const void *password;
	const char *prompt_info;
	} PW_CB_DATA;

int password_callback(char *buf, int bufsiz, int verify,
	PW_CB_DATA *cb_data);

int setup_ui_method(void);
void destroy_ui_method(void);

int chopup_args(ARGS *arg,char *buf, int *argc, char **argv[]);
#ifdef HEADER_X509_H
int dump_cert_text(BIO *out, X509 *x);
void print_name(BIO *out, const char *title, X509_NAME *nm, unsigned long lflags);
#endif
int set_cert_ex(unsigned long *flags, const char *arg);
int set_name_ex(unsigned long *flags, const char *arg);
int set_ext_copy(int *copy_type, const char *arg);
int copy_extensions(X509 *x, X509_REQ *req, int copy_type);
int app_passwd(BIO *err, char *arg1, char *arg2, char **pass1, char **pass2);
int add_oid_section(BIO *err, CONF *conf);
X509 *load_cert(BIO *err, const char *file, int format,
	const char *pass, ENGINE *e, const char *cert_descrip);
X509_CRL *load_crl(const char *infile, int format);
int load_cert_crl_http(const char *url, BIO *err,
					X509 **pcert, X509_CRL **pcrl);
EVP_PKEY *load_key(BIO *err, const char *file, int format, int maybe_stdin,
	const char *pass, ENGINE *e, const char *key_descrip);
EVP_PKEY *load_pubkey(BIO *err, const char *file, int format, int maybe_stdin,
	const char *pass, ENGINE *e, const char *key_descrip);
STACK_OF(X509) *load_certs(BIO *err, const char *file, int format,
	const char *pass, ENGINE *e, const char *cert_descrip);
STACK_OF(X509_CRL) *load_crls(BIO *err, const char *file, int format,
	const char *pass, ENGINE *e, const char *cert_descrip);
X509_STORE *setup_verify(BIO *bp, char *CAfile, char *CApath);
#ifndef OPENSSL_NO_ENGINE
ENGINE *setup_engine(BIO *err, const char *engine, int debug);
#endif

#ifndef OPENSSL_NO_OCSP
OCSP_RESPONSE *process_responder(BIO *err, OCSP_REQUEST *req,
				 const char *host, const char *path,
				 const char *port, int use_ssl,
				 const STACK_OF(CONF_VALUE) *headers,
				 int req_timeout);
#endif

/* Functions defined in ca.c and also used in ocsp.c */
int unpack_revinfo(ASN1_TIME **prevtm, int *preason, ASN1_OBJECT **phold,
			ASN1_GENERALIZEDTIME **pinvtm, const char *str);

#define DB_type         0
#define DB_exp_date     1
#define DB_rev_date     2
#define DB_serial       3       /* index - unique */
#define DB_file         4       
#define DB_name         5       /* index - unique when active and not disabled */
#define DB_NUMBER       6

#define DB_TYPE_REV	'R'
#define DB_TYPE_EXP	'E'
#define DB_TYPE_VAL	'V'

typedef struct db_attr_st
	{
	int unique_subject;
	} DB_ATTR;
typedef struct ca_db_st
	{
	DB_ATTR attributes;
	TXT_DB *db;
	} CA_DB;

BIGNUM *load_serial(char *serialfile, int create, ASN1_INTEGER **retai);
int save_serial(char *serialfile, char *suffix, BIGNUM *serial, ASN1_INTEGER **retai);
int rotate_serial(char *serialfile, char *new_suffix, char *old_suffix);
int rand_serial(BIGNUM *b, ASN1_INTEGER *ai);
CA_DB *load_index(char *dbfile, DB_ATTR *dbattr);
int index_index(CA_DB *db);
int save_index(const char *dbfile, const char *suffix, CA_DB *db);
int rotate_index(const char *dbfile, const char *new_suffix, const char *old_suffix);
void free_index(CA_DB *db);
#define index_name_cmp_noconst(a, b) \
	index_name_cmp((const OPENSSL_CSTRING *)CHECKED_PTR_OF(OPENSSL_STRING, a), \
	(const OPENSSL_CSTRING *)CHECKED_PTR_OF(OPENSSL_STRING, b))
int index_name_cmp(const OPENSSL_CSTRING *a, const OPENSSL_CSTRING *b);
int parse_yesno(const char *str, int def);

X509_NAME *parse_name(char *str, long chtype, int multirdn);
void policies_print(BIO *out, X509_STORE_CTX *ctx);
int bio_to_mem(unsigned char **out, int maxlen, BIO *in);
int pkey_ctrl_string(EVP_PKEY_CTX *ctx, char *value);
int init_gen_str(BIO *err, EVP_PKEY_CTX **pctx,
			const char *algname, ENGINE *e, int do_param);
int do_X509_sign(BIO *err, X509 *x, EVP_PKEY *pkey, const EVP_MD *md,
			STACK_OF(OPENSSL_STRING) *sigopts);
int do_X509_REQ_sign(BIO *err, X509_REQ *x, EVP_PKEY *pkey, const EVP_MD *md,
			STACK_OF(OPENSSL_STRING) *sigopts);
int do_X509_CRL_sign(BIO *err, X509_CRL *x, EVP_PKEY *pkey, const EVP_MD *md,
			STACK_OF(OPENSSL_STRING) *sigopts);
#ifndef OPENSSL_NO_PSK
extern char *psk_key;
#endif
#ifndef OPENSSL_NO_JPAKE
void jpake_client_auth(BIO *out, BIO *conn, const char *secret);
void jpake_server_auth(BIO *out, BIO *conn, const char *secret);
#endif

#ifndef OPENSSL_NO_TLSEXT
unsigned char *next_protos_parse(unsigned short *outlen, const char *in);
#endif  /* ndef OPENSSL_NO_TLSEXT */

void print_cert_checks(BIO *bio, X509 *x,
				const char *checkhost,
				const char *checkemail,
				const char *checkip);

void store_setup_crl_download(X509_STORE *st);

#define FORMAT_UNDEF    0
#define FORMAT_ASN1     1
#define FORMAT_TEXT     2
#define FORMAT_PEM      3
#define FORMAT_NETSCAPE 4
#define FORMAT_PKCS12   5
#define FORMAT_SMIME    6
#define FORMAT_ENGINE   7
#define FORMAT_IISSGC	8	/* XXX this stupid macro helps us to avoid
				 * adding yet another param to load_*key() */
#define FORMAT_PEMRSA	9	/* PEM RSAPubicKey format */
#define FORMAT_ASN1RSA	10	/* DER RSAPubicKey format */
#define FORMAT_MSBLOB	11	/* MS Key blob format */
#define FORMAT_PVK	12	/* MS PVK file format */
#define FORMAT_HTTP	13	/* Download using HTTP */
#define FORMAT_NSS	14	/* NSS keylog format */

#define EXT_COPY_NONE	0
#define EXT_COPY_ADD	1
#define EXT_COPY_ALL	2

#define NETSCAPE_CERT_HDR	"certificate"

#define APP_PASS_LEN	1024

#define SERIAL_RAND_BITS	64

int app_isdir(const char *);
int raw_read_stdin(void *,int);
int raw_write_stdout(const void *,int);

#define TM_START	0
#define TM_STOP		1
double app_tminterval (int stop,int usertime);

#define OPENSSL_NO_SSL_INTERN

#endif
