/* Copyright (c) Microsoft Corporation.  All Rights Reserved. */
#pragma once

#define OTRP_JSON_MEDIA_TYPE "application/otrp+json"
#define TEEP_JSON_MEDIA_TYPE "application/teep+json"
#define TEEP_CBOR_MEDIA_TYPE "application/teep+cbor"

int OTrPHandleJsonMessage(void* sessionHandle, const char* message, unsigned int messageLength);
int TeepHandleJsonMessage(void* sessionHandle, const char* message, unsigned int messageLength);
int TeepHandleCborMessage(void* sessionHandle, const char* message, unsigned int messageLength);
void HexPrintBuffer(const void* buffer, int length);

char *DecodeJWS(const json_t *jws, const json_t *jwk);

json_t* CreateNewJwkRS256(void);
json_t* CreateNewJwkR1_5(void);
json_t* CreateNewJwk(const char* alg);
json_t* CopyToJweKey(json_t* jwk1, const char* alg);

const unsigned char* GetDerCertificate(json_t* jwk, size_t *pCertificateSize);

typedef enum {
    TEEP_QUERY_REQUEST       = 1,
    TEEP_QUERY_RESPONSE      = 2,
    TEEP_TRUSTED_APP_INSTALL = 3,
    TEEP_TRUSTED_APP_DELETE  = 4,
    TEEP_SUCCESS             = 5,
    TEEP_ERROR               = 6,
} teep_message_type_t;

typedef enum {
    TEEP_ERR_SUCCESS                    = 0,
    TEEP_ERR_ILLEGAL_PARAMETER          = 1,
    TEEP_ERR_UNSUPPORTED_EXTENSION      = 2,
    TEEP_ERR_REQUEST_SIGNATURE_FAILED   = 3,
    TEEP_ERR_UNSUPPORTED_MSG_VERSION    = 4,
    TEEP_ERR_UNSUPPORTED_CRYPTO_ALG     = 5,
    TEEP_ERR_BAD_CERTIFICATE            = 6,
    TEEP_ERR_UNSUPPORTED_CERTIFICATE    = 7,
    TEEP_ERR_CERTIFICATE_REVOKED        = 8,
    TEEP_ERR_CERTIFICATE_EXPIRED        = 9,
    TEEP_ERR_INTERNAL_ERROR             = 10,
    TEEP_ERR_RESOURCE_FULL              = 11,
    TEEP_ERR_TA_NOT_FOUND               = 12,
    TEEP_ERR_TA_ALREADY_INSTALLED       = 13,
    TEEP_ERR_TA_UNKNOWN_FORMAT          = 14,
    TEEP_ERR_TA_DECRYPTION_FAILED       = 15,
    TEEP_ERR_TA_DECOMPRESSION_FAILED    = 16,
    TEEP_ERR_MANIFEST_PROCESSING_FAILED = 17,
    TEEP_ERR_PD_PROCESSING_FAILED       = 18
} teep_error_code_t;

typedef enum {
    TEEP_ATTESTATION    = 1,
    TEEP_TRUSTED_APPS   = 2,
    TEEP_EXTENSIONS     = 4,
    TEEP_SUIT_COMMANDS  = 8
} teep_data_items_t;

typedef enum {
    TEEP_LABEL_SUPPORTED_CIPHER_SUITES = 1,
    TEEP_LABEL_CHALLENGE               = 2,
    TEEP_LABEL_VERSIONS                = 3,
    TEEP_LABEL_OCSP_DATA               = 4,
    TEEP_LABEL_SELECTED_CIPHER_SUITE   = 5,
    TEEP_LABEL_SELECTED_VERSION        = 6,
    TEEP_LABEL_EVIDENCE                = 7,
    TEEP_LABEL_TA_LIST                 = 8,
    TEEP_LABEL_EXT_LIST                = 9,
    TEEP_LABEL_MANIFEST_LIST           = 10,
    TEEP_LABEL_MSG                     = 11,
    TEEP_LABEL_ERR_MSG                 = 12,
    TEEP_LABEL_EVIDENCE_FORMAT         = 13
} teep_label_t;

typedef enum {
    SUIT_ENVELOPE_LABEL_DELEGATION = 1,
    SUIT_ENVELOPE_LABEL_AUTHENTICATION_WRAPPER = 2,
    SUIT_ENVELOPE_LABEL_MANIFEST = 3
} suit_envelope_label_t;

typedef enum {
    SUIT_MANIFEST_LABEL_VERSION = 1,
    SUIT_MANIFEST_LABEL_SEQUENCE_NUMBER = 2,
    SUIT_MANIFEST_LABEL_COMMON = 3,
    SUIT_MANIFEST_LABEL_REFERENCE_URI = 4,
} suit_manifest_label_t;

typedef enum {
    SUIT_COMMON_LABEL_DEPENDENCIES = 1,
    SUIT_COMMON_LABEL_COMPONENTS = 2,
    SUIT_COMMON_LABEL_SEQUENCE = 4,
} suit_common_label_t;

#define SUIT_MANIFEST_VERSION_VALUE 1

#define UNIQUE_ID_LEN 16
