package com.redcarrottt.sc.bt;

import com.redcarrottt.sc.P2PClient;

public class BtP2PClient extends P2PClient {
    @Override
    protected boolean discoverImpl() {
        // TODO:
        return false;
    }

    @Override
    protected boolean connectImpl() {
        // TODO:
        return false;
    }

    @Override
    protected boolean disconnectImpl() {
        // TODO:
        return false;
    }

    // Constructor
    public BtP2PClient(String targetMacAddr) {
        this.mTargetMacAddr = targetMacAddr;
    }

    // Attributes
    private String mTargetMacAddr;
}
