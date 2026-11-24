#ifndef D_A_NPC_CO1_H
#define D_A_NPC_CO1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Co1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x00 */ s8 anmNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    }; // Size: 0x10

    typedef BOOL (daNpc_Co1_c::*ActionFunc)(void*);

    void nodeCo1Control(J3DNode*, J3DModel*);
    bool init_CO1_0();
    bool createInit();
    void setMtx(bool);
    u32 anmNum_toResID(int);
    u32 anmNum_toResID_prl(int);
    u32 btpNum_toResID(int);
    bool setBtp(bool, int);
    void setBtk(bool);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    void setCollision_SP_();
    void set_target(int);
    bool chk_talk();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_CO1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    bool charDecide(int);
    void eInit_MDR_();
    void eInit_RED_LTR_();
    void event_actionInit(int);
    void eMove_MDR_();
    void eMove_RED_LTR_();
    void event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    void wakeup();
    BOOL talk_1();
    BOOL toru_1();
    BOOL read_1();
    void modoru();
    BOOL wait_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_prl_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_R_jnt_num;
    /* 0x6CF */ u8 field_0x6CF[0x6D0 - 0x6CF];
    /* 0x6D0 */ mDoExt_McaMorf* field_0x6D0;
    /* 0x6D4 */ J3DAnmTextureSRTKey* field_0x6D4;
    /* 0x6D8 */ s8 m_prl_jnt_num;
    /* 0x6D9 */ u8 field_0x6D9[0x6DC - 0x6D9];
    /* 0x6DC */ mDoExt_btkAnm field_0x6DC;
    /* 0x6F0 */ u8 field_0x6F0;
    /* 0x6F1 */ u8 field_0x6F1[0x6F4 - 0x6F1];
    /* 0x6F4 */ J3DModel* field_0x6F4;
    /* 0x6F8 */ u32 field_0x6F8;
    /* 0x6FC */ J3DAnmTexPattern* field_0x6FC;
    /* 0x700 */ mDoExt_btpAnm field_0x700;
    /* 0x714 */ u8 field_0x714;
    /* 0x715 */ u8 field_0x715[0x716 - 0x715];
    /* 0x716 */ u16 field_0x716;
    /* 0x718 */ ActionFunc mCurrActionFunc;
    /* 0x724 */ u8 field_0x724[0x72C - 0x724];
    /* 0x72C */ dNpc_EventCut_c field_0x72C;
    /* 0x798 */ u8 field_0x798[0x79C - 0x798];
    /* 0x79C */ cXyz field_0x79C;
    /* 0x7A8 */ csXyz field_0x7A8;
    /* 0x7AE */ u8 field_0x7AE[0x7B0 - 0x7AE];
    /* 0x7B0 */ cXyz mEyePos;
    /* 0x7BC */ cXyz mLookAtPos;
    /* 0x7C8 */ u8 field_0x7C8[0x7D4 - 0x7C8];
    /* 0x7D4 */ f32 mFrame;
    /* 0x7D8 */ u8 field_0x7D8[0x7EC - 0x7D8];
    /* 0x7EC */ s16 field_0x7EC;
    /* 0x7EE */ s16 field_0x7EE;
    /* 0x7F0 */ s16 field_0x7F0;
    /* 0x7F2 */ u16 field_0x7F2[3];
    /* 0x7F8 */ s16 field_0x7F8;
    /* 0x7FA */ u8 field_0x7FA[0x7FC - 0x7FA];
    /* 0x7FC */ u16 field_0x7FC;
    /* 0x7FE */ u8 field_0x7FE[0x802 - 0x7FE];
    /* 0x802 */ s16 field_0x802;
    /* 0x804 */ s16 field_0x804;
    /* 0x806 */ u8 field_0x806[0x808 - 0x806];
    /* 0x808 */ u8 mbMorfAnimStopped;
    /* 0x809 */ u8 field_0x809;
    /* 0x80A */ u8 field_0x80A;
    /* 0x80B */ u8 field_0x80B;
    /* 0x80C */ u8 field_0x80C[0x80D - 0x80C];
    /* 0x80D */ u8 field_0x80D;
    /* 0x80E */ u8 field_0x80E[0x80F - 0x80E];
    /* 0x80F */ u8 field_0x80F;
    /* 0x810 */ u8 field_0x810;
    /* 0x811 */ u8 field_0x811;
    /* 0x812 */ u8 field_0x812[0x813 - 0x812];
    /* 0x813 */ u8 field_0x813;
    /* 0x814 */ u8 field_0x814[0x815 - 0x814];
    /* 0x815 */ u8 field_0x815;
    /* 0x816 */ u8 field_0x816[0x818 - 0x816];
    /* 0x818 */ int field_0x818;
    /* 0x81C */ u8 field_0x81C;
    /* 0x81D */ u8 field_0x81D;
    /* 0x81E */ bool field_0x81E;
    /* 0x81F */ u8 mbInDemo;
    /* 0x820 */ cXyz field_0x820;
    /* 0x82C */ csXyz field_0x82C;
    /* 0x832 */ u8 field_0x832[0x834 - 0x832];
    /* 0x834 */ f32 field_0x834;
    /* 0x838 */ u8 field_0x838[0x840 - 0x838];
    /* 0x840 */ cXyz field_0x840;
    /* 0x84C */ f32 field_0x84C;
    /* 0x850 */ s16 field_0x850;
    /* 0x852 */ u8 field_0x852[0x854 - 0x852];
    /* 0x854 */ u8 field_0x854;
    /* 0x855 */ s8 field_0x855;
    /* 0x856 */ u8 field_0x856;
    /* 0x857 */ u8 field_0x857;
    /* 0x858 */ s8 mBtpNum;
    /* 0x859 */ s8 field_0x859;
    /* 0x85A */ u8 field_0x85A[0x85C - 0x85A];
    /* 0x85C */ u8 field_0x85C;
    /* 0x85D */ s8 field_0x85D;
    /* 0x85E */ u8 field_0x85E;
    /* 0x85F */ u8 field_0x85F;
    /* 0x860 */ u8 field_0x860;
    /* 0x861 */ u8 mSpecificType;
    /* 0x862 */ u8 field_0x862;
    /* 0x863 */ u8 field_0x863;
}; // Size: 0x864

#endif /* D_A_NPC_CO1_H */
