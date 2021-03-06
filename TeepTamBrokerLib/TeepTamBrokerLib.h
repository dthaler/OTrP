// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    int TeepHandleMessage(
        _In_ void* sessionHandle,
        _In_z_ const char* mediaType,
        _In_reads_(messageLength) const char *message,
        int messageLength);

    int TeepHandleConnect(_In_ void* sessionHandle, _In_z_ const char* acceptMediaType);

    int StartTamBroker(_In_z_ const char* manifestDirectory, int simulated_tee);
    void StopTamBroker(void);

    int TamBrokerProcess(_In_z_ const wchar_t* tamUri);

#ifdef __cplusplus
};
#endif
