/**
 * d_a_npc_co1.cpp
 * NPC - Prince Komali (before Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_co1.h"
#include "res/Object/Co.h"

class daNpc_Co1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Co1_HIO_c();
    virtual ~daNpc_Co1_HIO_c() {
    }
    void genMessage(JORMContext* ctx) {
        UNUSED(ctx);
    }

public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ u8 field_0x0C[0x38 - 0x0C];
}; // Size: 0x38

static char* l_evn_tbl[] = {
    "Prl_Flw",
    "Contact",
    "Red_Ltr",
};

/* 000000EC-00000150       .text __ct__15daNpc_Co1_HIO_cFv */
daNpc_Co1_HIO_c::daNpc_Co1_HIO_c() {
    static u32 a_prm_tbl[] = { 0x20002328, 0xE000DCD8, 0x00000000, 0x00000000, 0x04000400, 0x42B60000,
                               0x000000FF, 0x00960000, 0x42200000, 0x41A00000, 0x02000040 };
    memcpy(&field_0x0C, a_prm_tbl, 0x2C);
    field_0x04 = -1;
    field_0x08 = -1;
}

/* 00000198-000001E4       .text nodeCallBack_Co1__FP7J3DNodei */
static BOOL nodeCallBack_Co1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Co1_c*>(j3dSys.getModel()->getUserArea())->nodeCo1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000334       .text nodeCo1Control__11daNpc_Co1_cFP7J3DNodeP8J3DModel */
void daNpc_Co1_c::nodeCo1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f);
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));
    if (jntNo == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mEyePos);
    }
    if (jntNo == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000370-00000410       .text init_CO1_0__11daNpc_Co1_cFv */
bool daNpc_Co1_c::init_CO1_0() {
    bool res = dComIfGs_isSymbol(1) == FALSE;
    if (res) {
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
        set_action(&daNpc_Co1_c::wait_action1, NULL);
    }
    return res;
}

/* 00000410-00000588       .text createInit__11daNpc_Co1_cFv */
bool daNpc_Co1_c::createInit() {
    for (int i = 0; i < 3; i++) {
        field_0x7F2[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x46;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x45;
    gravity = -4.5f;
    mLookAtPos = current.pos;
    field_0x81E = true;
    field_0x72C.setActorInfo2("Co1", this);
    mAnmNum = 0xB;

    bool init_success;
    switch (mSpecificType) {
        case 0:
            init_success = init_CO1_0();
            break;
        default:
            init_success = false;
            break;
    }

    if (init_success) {
        shape_angle = current.angle;
    } else {
        return false;
    }

    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00000588-000008E4       .text setMtx__11daNpc_Co1_cFb */
void daNpc_Co1_c::setMtx(bool) {
    /* Nonmatching */
}

/* 000008E4-000008F8       .text anmNum_toResID__11daNpc_Co1_cFi */
u32 daNpc_Co1_c::anmNum_toResID(int i_idx) {
    static const u32 a_bck_resID_tbl[] = { dRes_ID_CO_BCK_CO_WAIT01_e,  dRes_ID_CO_BCK_CO_WAIT02_e, dRes_ID_CO_BCK_CO_MIGAMAE_e, dRes_ID_CO_BCK_CO_OKIRU_e,
                                           dRes_ID_CO_BCK_CO_READ_e,    dRes_ID_CO_BCK_CO_TALK01_e, dRes_ID_CO_BCK_CO_TALK02_e,  dRes_ID_CO_BCK_CO_SWAIT01_e,
                                           dRes_ID_CO_BCK_CO_UKETORI_e, dRes_ID_CO_BCK_CO_OKIRU_e,  dRes_ID_CO_BCK_CO_MIGAMAE_e };
    return a_bck_resID_tbl[i_idx];
}

/* 000008F8-0000090C       .text anmNum_toResID_prl__11daNpc_Co1_cFi */
u32 daNpc_Co1_c::anmNum_toResID_prl(int i_idx) {
    static const u32 a_bck_resID_tbl[] = { dRes_ID_CO_BCK_COPEAL_WAIT01_e, dRes_ID_CO_BCK_COPEAL_WAIT02_e,  dRes_ID_CO_BCK_COPEAL_MIGAMAE_e,
                                           dRes_ID_CO_BCK_COPEAL_OKIRU_e,  dRes_ID_CO_BCK_COPEAL_READ_e,    dRes_ID_CO_BCK_COPEAL_TALK01_e,
                                           dRes_ID_CO_BCK_COPEAL_TALK02_e, dRes_ID_CO_BCK_COPEAL_SWAIT01_e, dRes_ID_CO_BCK_COPEAL_UKETORI_e,
                                           dRes_ID_CO_BCK_COPEAL_OKIRU_e,  dRes_ID_CO_BCK_COPEAL_MIGAMAE_e };
    return a_bck_resID_tbl[i_idx];
}

/* 0000090C-00000920       .text btpNum_toResID__11daNpc_Co1_cFi */
u32 daNpc_Co1_c::btpNum_toResID(int i_idx) {
    static const u32 a_btp_resID_tbl[] = { dRes_ID_CO_BTP_FUAN_e,   dRes_ID_CO_BTP_KIRI_e,  dRes_ID_CO_BTP_NIKO_e,   dRes_ID_CO_BTP_OKORI_e,
                                           dRes_ID_CO_BTP_NAGAME_e, dRes_ID_CO_BTP_OKIRU_e, dRes_ID_CO_BTP_MIGAMAE_e };

    return a_btp_resID_tbl[i_idx];
}

/* 00000920-00000A30       .text setBtp__11daNpc_Co1_cFbi */
bool daNpc_Co1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    int resID = btpNum_toResID(i_btpNum);
    field_0x6FC = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Co", resID));
    JUT_ASSERT(0x1CE, field_0x6FC != NULL);
    int initVal = field_0x700.init(model_data, field_0x6FC, 1, 2, 1.0f, 0, -1, i_modify, 0);
    bool o_retval = initVal == 1;
    if (o_retval) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00000A30-00000B30       .text setBtk__11daNpc_Co1_cFb */
bool daNpc_Co1_c::setBtk(bool i_modify) {
    J3DModelData* model_data = mpPearlMorf->getModel()->getModelData();
    m_prl_btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BTK_CO_PEAL_e);
    JUT_ASSERT(0x1EA, m_prl_btk != NULL);
    bool ret = field_0x6DC.init(model_data, m_prl_btk, 1, 2, 1.0f, 0, -1, i_modify, 0) == TRUE;
    if (ret) {
        field_0x6F0 = 0;
    }
    return ret;
}

/* 00000B30-00000B58       .text iniTexPttrnAnm__11daNpc_Co1_cFb */
bool daNpc_Co1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 00000B58-00000C44       .text plyTexPttrnAnm__11daNpc_Co1_cFv */
void daNpc_Co1_c::plyTexPttrnAnm() {
    field_0x6F0++;
    if (field_0x6F0 >= m_prl_btk->getFrameMax()) {
        field_0x6F0 = 0;
    }
    if (mBtpNum == 6 || mBtpNum == 5 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame++;
        if (mBlinkFrame >= field_0x6FC->getFrameMax()) {
            if (mBtpNum == 6 || mBtpNum == 5) {
                mBlinkFrame = field_0x6FC->getFrameMax();
            } else {
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000C44-00000C80       .text setAnm_tex__11daNpc_Co1_cFSc */
void daNpc_Co1_c::setAnm_tex(s8 i_param1) {
    if (mBtpNum != i_param1) {
        mBtpNum = i_param1;
        iniTexPttrnAnm(true);
    }
}

/* 00000C80-00000D64       .text setAnm_anm__11daNpc_Co1_cFPQ211daNpc_Co1_c9anm_prm_c */
BOOL daNpc_Co1_c::setAnm_anm(daNpc_Co1_c::anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->anmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->anmNum;
    u32 resID = anmNum_toResID(mAnmNum);
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, resID, -1, "Co");
    u32 prlResID = anmNum_toResID_prl(mAnmNum);
    dNpc_setAnmIDRes(mpPearlMorf, i_anmPrmP->loopMode, 0.0f, 0.0f, prlResID, -1, "Co");
    mFrame = 0.0f;
    field_0x809 = 0;
    mbMorfAnimStopped = false;
    return TRUE;
}

/* 00000D64-00000DD0       .text setAnm_NUM__11daNpc_Co1_cFii */
void daNpc_Co1_c::setAnm_NUM(int i_idx, int i_flag) {
    static anm_prm_c a_anm_prm_tbl[] = {
        { 0, 0, 8.0f, 1.0f, 2 }, { 1, 4, 8.0f, 1.0f, 2 }, { 2, 6, 8.0f, 1.0f, 0 }, { 3, 5, 8.0f, 1.0f, 0 },  { 4, 4, 8.0f, 1.0f, 2 },   { 5, 0, 8.0f, 1.0f, 2 },
        { 6, 3, 8.0f, 1.0f, 2 }, { 7, 4, 8.0f, 1.0f, 2 }, { 8, 0, 8.0f, 1.0f, 0 }, { 9, 5, 8.0f, -1.0f, 0 }, { 10, 6, 8.0f, -1.0f, 0 }, { 7, 0, 8.0f, 1.0f, 2 },
    };
    if (i_flag != 0) {
        setAnm_tex(a_anm_prm_tbl[i_idx].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_idx]);
}

/* 00000DD0-00000E50       .text setAnm__11daNpc_Co1_cFv */
bool daNpc_Co1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = { { -1, -1, 0.0f, 0.0f, -1 }, { 1, 4, 8.0f, 1.0f, 2 },    { -1, -1, 0.0f, 0.0f, -1 }, { 3, 5, 8.0f, 1.0f, 0 },
                                         { 7, 0, 8.0f, 1.0f, 2 },    { -1, -1, 0.0f, 0.0f, -1 }, { 4, 4, 8.0f, 1.0f, 2 },    { 10, 6, 8.0f, -1.0f, 0 } };
    if (a_anm_prm_tbl[mStatus].btpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStatus].btpNum);
    }
    if (a_anm_prm_tbl[mStatus].anmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00000E50-00000E54       .text chg_anmTag__11daNpc_Co1_cFv */
void daNpc_Co1_c::chg_anmTag() {
    return;
}

/* 00000E54-00000E58       .text control_anmTag__11daNpc_Co1_cFv */
void daNpc_Co1_c::control_anmTag() {
    return;
}

/* 00000E58-00000EF8       .text chg_anmAtr__11daNpc_Co1_cFUc */
void daNpc_Co1_c::chg_anmAtr(u8 i_param1) {
    if (i_param1 >= 14 || i_param1 == mAnmAtr) {
        return;
    }
    field_0x85F = 1;
    switch (i_param1) {
        case 3:
        case 4:
        case 5:
        case 7:
        case 11:
            field_0x85F = 0;
            break;
        case 13:
            set_target(1);
            break;
    }
    mAnmAtr = i_param1;
    setAnm_ATR(1);
}

/* 00000EF8-00000FF4       .text control_anmAtr__11daNpc_Co1_cFv */
void daNpc_Co1_c::control_anmAtr() {
    switch (mAnmAtr) {
        case 2:
            if (mbMorfAnimStopped) {
                setAnm_NUM(7, 1);
                mAnmAtr = 6;
            }
            break;
        case 3:
            if (mbMorfAnimStopped) {
                setAnm_NUM(4, 1);
                mAnmAtr = 10;
            }
            break;
        case 7:
            if (mbMorfAnimStopped) {
                setAnm_NUM(6, 1);
                mAnmAtr = 5;
            }
            break;
        case 8:
            if (mbMorfAnimStopped) {
                setAnm_NUM(7, 1);
                mAnmAtr = 6;
            }
            break;
        case 9:
            if (mbMorfAnimStopped) {
                setAnm_NUM(1, 1);
                mAnmAtr = 1;
            }
            break;
        case 13:
            break;
    }
}

/* 00000FF4-0000105C       .text setAnm_ATR__11daNpc_Co1_cFi */
void daNpc_Co1_c::setAnm_ATR(int i_param1) {
    static anm_prm_c a_anm_prm_tbl[] = {
        { 0, 0, 8.0f, 1.0f, 2 }, { 1, 4, 8.0f, 1.0f, 2 }, { 3, 5, 8.0f, 1.0f, 0 }, { 8, 0, 8.0f, 1.0f, 0 },   { 5, 0, 8.0f, 1.0f, 2 },
        { 6, 3, 8.0f, 1.0f, 2 }, { 7, 4, 8.0f, 1.0f, 2 }, { 2, 6, 8.0f, 1.0f, 0 }, { 10, 6, 8.0f, -1.0f, 0 }, { 9, 5, 8.0f, -1.0f, 0 },
        { 4, 4, 8.0f, 1.0f, 2 }, { 5, 4, 8.0f, 1.0f, 2 }, { 5, 0, 8.0f, 1.0f, 2 }, { 6, 3, 8.0f, 1.0f, 2 },
    };
    if (i_param1) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 0000105C-00001120       .text anmAtr__11daNpc_Co1_cFUs */
void daNpc_Co1_c::anmAtr(u16 i_param1) {
    switch (i_param1) {
        case 0x6:
            {
                if (field_0x863 == 0) {
                    mAnmAtr = -1;
                    chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                    field_0x863++;
                }
                u32 tagInfo = dComIfGp_getMesgAnimeTagInfo();
                dComIfGp_clearMesgAnimeTagInfo();
                if (tagInfo != 0xFF && mAnmTag != tagInfo) {
                    mAnmTag = tagInfo;
                    chg_anmTag();
                }
                break;
            }
        case 0xE:
            field_0x863 = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00001120-000011B8       .text eventOrder__11daNpc_Co1_cFv */
void daNpc_Co1_c::eventOrder() {
    if (mTalkOrder == 1 || mTalkOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mTalkOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mTalkOrder >= 3) {
        field_0x7F8 = mTalkOrder - 3;
        fopAcM_orderOtherEventId(this, field_0x7F2[field_0x7F8]);
    }
}

/* 000011B8-00001288       .text checkOrder__11daNpc_Co1_cFv */
void daNpc_Co1_c::checkOrder() {
    /* Nonmatching */
}

/* 00001288-000013AC       .text setCollision_SP___11daNpc_Co1_cFv */
void daNpc_Co1_c::setCollision_SP_() {
    /* Nonmatching */
}

/* 000013AC-000014B8       .text set_target__11daNpc_Co1_cFi */
void daNpc_Co1_c::set_target(int) {
    /* Nonmatching */
}

/* 000014B8-00001554       .text chk_talk__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chk_talk() {
    /* Nonmatching */
}

/* 00001554-00001594       .text chk_partsNotMove__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chk_partsNotMove() {
    /* Nonmatching */
}

/* 00001594-00001734       .text lookBack__11daNpc_Co1_cFv */
void daNpc_Co1_c::lookBack() {
    /* Nonmatching */
}

/* 00001734-000017EC       .text next_msgStatus__11daNpc_Co1_cFPUl */
u16 daNpc_Co1_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 000017EC-00001894       .text getMsg_CO1_0__11daNpc_Co1_cFv */
u32 daNpc_Co1_c::getMsg_CO1_0() {
    /* Nonmatching */
}

/* 00001894-000018D0       .text getMsg__11daNpc_Co1_cFv */
u32 daNpc_Co1_c::getMsg() {
    /* Nonmatching */
}

/* 000018D0-00001950       .text chkAttention__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chkAttention() {
    /* Nonmatching */
}

/* 00001950-00001A44       .text setAttention__11daNpc_Co1_cFb */
void daNpc_Co1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00001A44-00001A60       .text charDecide__11daNpc_Co1_cFi */
bool daNpc_Co1_c::charDecide(int) {
    /* Nonmatching */
}

/* 00001A60-00001A9C       .text eInit_MDR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eInit_MDR_() {
    /* Nonmatching */
}

/* 00001A9C-00001AC4       .text eInit_RED_LTR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eInit_RED_LTR_() {
    /* Nonmatching */
}

/* 00001AC4-00001B50       .text event_actionInit__11daNpc_Co1_cFi */
void daNpc_Co1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 00001B50-00001BA8       .text eMove_MDR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eMove_MDR_() {
    /* Nonmatching */
}

/* 00001BA8-00001C34       .text eMove_RED_LTR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eMove_RED_LTR_() {
    /* Nonmatching */
}

/* 00001C34-00001C84       .text event_action__11daNpc_Co1_cFv */
void daNpc_Co1_c::event_action() {
    /* Nonmatching */
}

/* 00001C84-00001D70       .text privateCut__11daNpc_Co1_cFi */
void daNpc_Co1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00001D70-00001D90       .text endEvent__11daNpc_Co1_cFv */
void daNpc_Co1_c::endEvent() {
    /* Nonmatching */
}

/* 00001D90-00001DC8       .text isEventEntry__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::isEventEntry() {
    /* Nonmatching */
}

/* 00001DC8-00001EC0       .text event_proc__11daNpc_Co1_cFi */
void daNpc_Co1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00001EC0-00001F6C       .text set_action__11daNpc_Co1_cFM11daNpc_Co1_cFPCvPvPv_iPv */
BOOL daNpc_Co1_c::set_action(ActionFunc, void*) {
    /* Nonmatching */
}

/* 00001F6C-00001FD4       .text setStt__11daNpc_Co1_cFSc */
void daNpc_Co1_c::setStt(s8) {
    /* Nonmatching */
}

/* 00001FD4-0000205C       .text wait_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::wait_1() {
    /* Nonmatching */
}

/* 0000205C-00002114       .text wait_2__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::wait_2() {
    /* Nonmatching */
}

/* 00002114-00002150       .text wakeup__11daNpc_Co1_cFv */
void daNpc_Co1_c::wakeup() {
    /* Nonmatching */
}

/* 00002150-0000234C       .text talk_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::talk_1() {
    /* Nonmatching */
}

/* 0000234C-000023BC       .text toru_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::toru_1() {
    /* Nonmatching */
}

/* 000023BC-000023F8       .text read_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::read_1() {
    /* Nonmatching */
}

/* 000023F8-00002458       .text modoru__11daNpc_Co1_cFv */
void daNpc_Co1_c::modoru() {
    /* Nonmatching */
}

/* 00002458-000025DC       .text wait_action1__11daNpc_Co1_cFPv */
BOOL daNpc_Co1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 000025DC-0000271C       .text demo__11daNpc_Co1_cFv */
bool daNpc_Co1_c::demo() {
    /* Nonmatching */
}

/* 0000271C-000027AC       .text shadowDraw__11daNpc_Co1_cFv */
void daNpc_Co1_c::shadowDraw() {
    /* Nonmatching */
}

/* 000027AC-0000295C       .text _draw__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_draw() {
    /* Nonmatching */
}

/* 0000295C-00002B08       .text _execute__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_execute() {
    /* Nonmatching */
}

/* 00002B08-00002B6C       .text _delete__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_delete() {
    /* Nonmatching */
}

/* 00002B6C-00002B8C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002B8C-00002CAC       .text _create__11daNpc_Co1_cFv */
cPhs_State daNpc_Co1_c::_create() {
    /* Nonmatching */
}

/* 00003150-000033C0       .text create_Anm__11daNpc_Co1_cFv */
J3DModelData* daNpc_Co1_c::create_Anm() {
    /* Nonmatching */
}

/* 000033C0-00003578       .text create_prl_Anm__11daNpc_Co1_cFv */
J3DModelData* daNpc_Co1_c::create_prl_Anm() {
    /* Nonmatching */
}

/* 00003578-00003634       .text create_itm_Mdl__11daNpc_Co1_cFv */
bool daNpc_Co1_c::create_itm_Mdl() {
    /* Nonmatching */
}

/* 00003634-000037C8       .text CreateHeap__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::CreateHeap() {
    /* Nonmatching */
}

/* 000037C8-000037E8       .text daNpc_Co1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Co1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_create();
}

/* 000037E8-00003808       .text daNpc_Co1_Delete__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Delete(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_delete();
}

/* 00003808-00003828       .text daNpc_Co1_Execute__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Execute(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_execute();
}

/* 00003828-00003848       .text daNpc_Co1_Draw__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Draw(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_draw();
}

/* 00003848-00003850       .text daNpc_Co1_IsDelete__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_IsDelete(daNpc_Co1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Co1_Method = {
    (process_method_func)daNpc_Co1_Create,
    (process_method_func)daNpc_Co1_Delete,
    (process_method_func)daNpc_Co1_Execute,
    (process_method_func)daNpc_Co1_IsDelete,
    (process_method_func)daNpc_Co1_Draw,
};

actor_process_profile_definition g_profile_NPC_CO1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_CO1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Co1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_CO1_e,
    /* Actor SubMtd */ &l_daNpc_Co1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
