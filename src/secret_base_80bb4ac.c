#include "global.h"
#include "event_data.h"
#include "vars.h"

extern u8 gUnknown_020387DC;
extern u16 gSpecialVar_0x8004;
extern u16 gScriptResult;

void sub_80BB4AC(struct SecretBaseRecord *record) { // 080bb4ac
    u16 i;
    u16 j;
    record->sbr_field_0 = 0;
    for (i=0; i<7; i++)
        record->sbr_field_2[i] = 0xff;
    for (i=0; i<4; i++)
        record->trainerId[i] = 0x00;
    record->sbr_field_e = 0;
    record->sbr_field_10 = 0;
    record->sbr_field_11 = 0;
    record->sbr_field_1_0 = 0;
    record->gender = 0;
    record->sbr_field_1_5 = 0;
    record->sbr_field_1_6 = 0;
    for (i=0; i<16; i++) {
        record->decorations[i] = 0;
        record->sbr_field_22[i] = 0;
    }
    for (i=0; i<6; i++) {
        for (j=0; j<4; j++) {
            record->partyMoves[i * 4 + j] = 0;
        }
        record->partyPersonality[i] = 0;
        record->partyEVs[i] = 0;
        record->partySpecies[i] = 0;
        record->partyHeldItems[i] = 0;
        record->partyLevels[i] = 0;
    }
}

void ResetSecretBase(u8 idx) { // 80bb594
    sub_80BB4AC(&(gSaveBlock1.secretBases[idx]));
}

void ResetSecretBases(void) { // 080bb5b4
    u16 i;
    for (i=0; i<20; i++)
        ResetSecretBase(i);
}

void sub_80BB5D0(void) { // 080bb5d0
    gUnknown_020387DC = gSpecialVar_0x8004;
}

void sub_80BB5E4(void) { // 80bb5e4
    u16 idx;
    gScriptResult = 0;
    for (idx=0; idx<20; idx++) {
        if (gUnknown_020387DC == gSaveBlock1.secretBases[idx].sbr_field_0) {
            gScriptResult = 1;
            VarSet(0x4054, idx);
            return;
        }
    }
}
