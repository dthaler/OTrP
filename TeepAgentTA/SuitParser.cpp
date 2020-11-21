/* Copyright (c) Microsoft Corporation.  All Rights Reserved. */
#include <openenclave/enclave.h>
#include <stdlib.h>
extern "C" {
#include "jansson.h"
#include "../TeepCommonTALib/common.h"
#include "../TeepCommonTALib/teep_protocol.h"
#include "../TeepCommonTALib/suit_manifest.h"
};
#include "qcbor/qcbor_decode.h"
#include "SuitParser.h"

// Parse a SUIT_Common out of a decode context and try to install it.
teep_error_code_t TryProcessSuitCommon(QCBORDecodeContext* context, uint16_t mapEntryCount)
{
    QCBORItem item;
    teep_error_code_t errorCode = TEEP_ERR_SUCCESS;
    for (int mapEntryIndex = 0; mapEntryIndex < mapEntryCount; mapEntryIndex++) {
        QCBORDecode_GetNext(context, &item);
        if (errorCode != TEEP_ERR_SUCCESS) {
            continue;
        }
        suit_common_label_t label = (suit_common_label_t)item.label.int64;
        switch (label) {
        case SUIT_COMMON_LABEL_DEPENDENCIES:
        case SUIT_COMMON_LABEL_COMPONENTS:
        case SUIT_COMMON_LABEL_SEQUENCE:
            // Not yet implemented.
            errorCode = TEEP_ERR_INTERNAL_ERROR;
            break;
        default:
            errorCode = TEEP_ERR_ILLEGAL_PARAMETER;
        }
    }
    return errorCode;
}

// Parse a SUIT_Manifest out of a decode context and try to install it.
teep_error_code_t TryProcessSuitManifest(QCBORDecodeContext* context, uint16_t mapEntryCount)
{
    QCBORItem item;
    teep_error_code_t errorCode = TEEP_ERR_SUCCESS;
    for (int mapEntryIndex = 0; mapEntryIndex < mapEntryCount; mapEntryIndex++) {
        QCBORDecode_GetNext(context, &item);
        if (errorCode != TEEP_ERR_SUCCESS) {
            continue;
        }
        suit_manifest_label_t label = (suit_manifest_label_t)item.label.int64;
        switch (label) {
        case SUIT_MANIFEST_LABEL_VERSION:
            if (item.uDataType != QCBOR_TYPE_INT64 || item.val.int64 != SUIT_MANIFEST_VERSION_VALUE) {
                REPORT_TYPE_ERROR("suit-manifest-version", QCBOR_TYPE_INT64, item);
                return TEEP_ERR_ILLEGAL_PARAMETER;
            }
            break;
        case SUIT_MANIFEST_LABEL_SEQUENCE_NUMBER:
            if (item.uDataType != QCBOR_TYPE_UINT64) {
                REPORT_TYPE_ERROR("suit-manifest-sequence-number", QCBOR_TYPE_UINT64, item);
                return TEEP_ERR_ILLEGAL_PARAMETER;
            }
            break;
        case SUIT_MANIFEST_LABEL_COMMON:
            if (item.uDataType != QCBOR_TYPE_MAP) {
                REPORT_TYPE_ERROR("suit-manifest-common", QCBOR_TYPE_MAP, item);
                return TEEP_ERR_ILLEGAL_PARAMETER;
            }
            errorCode = TryProcessSuitCommon(context, item.val.uCount);
            break;
        case SUIT_MANIFEST_LABEL_REFERENCE_URI:
            errorCode = TEEP_ERR_INTERNAL_ERROR;
            break;
        default:
            errorCode = TEEP_ERR_ILLEGAL_PARAMETER;
        }
    }
    return errorCode;
}

// Parse a SUIT_Envelope out of a decode context and try to install it.
teep_error_code_t TryProcessSuitEnvelope(QCBORDecodeContext* context, size_t mapEntryCount)
{
    QCBORItem item;
    teep_error_code_t errorCode = TEEP_ERR_SUCCESS;
    for (size_t mapEntryIndex = 0; mapEntryIndex < mapEntryCount; mapEntryIndex++) {
        QCBORDecode_GetNext(context, &item);
        if (errorCode != TEEP_ERR_SUCCESS) {
            continue;
        }
        suit_envelope_label_t label = (suit_envelope_label_t)item.label.int64;
        switch (label) {
        case SUIT_ENVELOPE_LABEL_AUTHENTICATION_WRAPPER:
            if (item.uDataType != QCBOR_TYPE_BYTE_STRING) {
                REPORT_TYPE_ERROR("suit-authentication-wrapper", QCBOR_TYPE_BYTE_STRING, item);
                return TEEP_ERR_ILLEGAL_PARAMETER;
            }
            // TODO: process authentication wrapper
            break;
        case SUIT_ENVELOPE_LABEL_MANIFEST:
            if (item.uDataType != QCBOR_TYPE_BYTE_STRING) {
                REPORT_TYPE_ERROR("suit-manifest", QCBOR_TYPE_BYTE_STRING, item);
                return TEEP_ERR_ILLEGAL_PARAMETER;
            }
            errorCode = TryProcessSuitManifest(context, item.val.uCount);
            break;
        default:
            errorCode = TEEP_ERR_ILLEGAL_PARAMETER;
            break;
        }
    }
    return errorCode;
}
