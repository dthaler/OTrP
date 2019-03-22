/* Copyright (c) Microsoft Corporation.  All Rights Reserved. */
#include <stdio.h>
#include "../OTrPTamBrokerLib/OTrPTamBrokerLib.h"

int main(int argc, char** argv)
{
    int err;

    err = StartTamBroker();
    if (err != 0) {
        return err;
    }

    err = TamBrokerProcess();

    StopTamBroker();
    return err;
}