#ifndef MSG_COMMANDS_H
#define MSG_COMMANDS_H

enum msgRequestState{
    REQUEST_IDLE = 0,
    REQUEST = 1,
    CONFIRMED = 2,
    ACK_REQUEST = 3,
    ACK_CONFIRMED = 4,
    WAITING = 5
};

enum msgCommands{
    MsgAck = 0,
    ConnectionRequest = 1,
    DockingModeOn = 5,
    DockingModeOff = 6,
    SimulatinCommand = 7,
    RestToDefault = 8,
    SystemStandby = 9,
    JBsetupCommand = 10,
    DL2setupCommand = 11,
    ALLsetupCommand = 12,
    ALIsetupCommand = 13,
    AUCLsetupCommand = 14,
    OCFsetupCommand = 15,
    CUsetupCommand = 16,
    SetupReceivedConfirmationCommand = 17,
    CalibrationCommand = 18,
    SendMeConfigurationCommand = 19,
    FitnessConfirmCommand = 20,
    CalibrationPointCommand = 21,
    DataForManualCalibrationCommand = 22,
    DataForSemiAutoCalibrationCommand = 23,
    CurrentCalibrationpoints = 24,
    CalibrationCoeffitients = 25,
    AuxStatesCommand = 26,
    CalibrationPointAccepted = 27,
    CalibrationPointRejected = 28,
    DataForTempCalibrationCommand = 29,
    DataForTiltCalibrationCommand = 30,
    ValidityForSemiAutoCalibrationCommand = 31,
    QualityFactorDataCommand = 32,
    UpdateAvailable = 33
};

enum diagnosticsMsgCommands{
    SelfTestData = 9,
    CommunicationDiagnostics = 10,
    StartSelfTest = 11,
    StartDiagnosticsTest = 12
};
#endif
