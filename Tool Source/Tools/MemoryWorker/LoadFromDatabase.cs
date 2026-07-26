// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.LoadFromDatabase
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class LoadFromDatabase
  {
    public static string LoadFromDatabaseSQL = "";
    private string language = ExportLodHandle.connection.Settings.Language;

    public void tPets_Import()
    {
      AllLists.tpet_MenuData.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_attack_pet ORDER BY a_index";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
      {
        t_attkpet tAttkpet = new t_attkpet();
        tAttkpet.index = Convert.ToInt32(row["a_index"]);
        tAttkpet.enable = Convert.ToInt32(row["a_enable"]);
        tAttkpet.name = Convert.ToString(row["a_name"]);
        tAttkpet.type = Convert.ToInt32(row["a_type"]);
        tAttkpet.str = Convert.ToInt32(row["a_str"]);
        tAttkpet.con = Convert.ToInt32(row["a_con"]);
        tAttkpet.dex = Convert.ToInt32(row["a_dex"]);
        tAttkpet.intel = Convert.ToInt32(row["a_int"]);
        tAttkpet.itemidx = Convert.ToInt32(row["a_item_idx"]);
        tAttkpet.maxFaith = Convert.ToInt32(row["a_maxFaith"]);
        tAttkpet.maxStm = Convert.ToInt32(row["a_maxStm"]);
        tAttkpet.maxHP = Convert.ToInt32(row["a_maxHP"]);
        tAttkpet.maxMP = Convert.ToInt32(row["a_maxMP"]);
        tAttkpet.recoverHP = Convert.ToInt32(row["a_recoverHP"]);
        tAttkpet.recoverMP = Convert.ToInt32(row["a_recoverMP"]);
        tAttkpet.delay = Convert.ToInt32(row["a_delay"]);
        tAttkpet.AISlot = Convert.ToInt32(row["a_AISlot"]);
        tAttkpet.afterDead = Convert.ToInt32(row["a_after_dead"]);
        tAttkpet.attack = Convert.ToInt32(row["a_attack"]);
        tAttkpet.defense = Convert.ToInt32(row["a_defence"]);
        tAttkpet.mAttack = Convert.ToInt32(row["a_Mattack"]);
        tAttkpet.mDefense = Convert.ToInt32(row["a_Mdefence"]);
        tAttkpet.hitPoint = Convert.ToInt32(row["a_hitpoint"]);
        tAttkpet.avoidPoint = Convert.ToInt32(row["a_avoidpoint"]);
        tAttkpet.mavoidPoint = Convert.ToInt32(row["a_Mavoidpoint"]);
        tAttkpet.attackSpeed = Convert.ToInt32(row["a_attackSpeed"]);
        tAttkpet.Deadly = Convert.ToInt32(row["a_deadly"]);
        tAttkpet.Critical = Convert.ToInt32(row["a_critical"]);
        tAttkpet.awful = Convert.ToInt32(row["a_awful"]);
        tAttkpet.strong = Convert.ToInt32(row["a_strong"]);
        tAttkpet.normal = Convert.ToInt32(row["a_normal"]);
        tAttkpet.weak = Convert.ToInt32(row["a_week"]);
        tAttkpet.bagicSkill1 = Convert.ToInt32(row["a_bagic_skill1"]);
        tAttkpet.bagicSkill2 = Convert.ToInt32(row["a_bagic_skill2"]);
        tAttkpet.flag = Convert.ToInt32(row["a_flag"]);
        tAttkpet.transType = Convert.ToInt32(row["a_trans_type"]);
        tAttkpet.transStart = Convert.ToInt32(row["a_trans_start"]);
        tAttkpet.transEnd = Convert.ToInt32(row["a_trans_end"]);
        tAttkpet.smcFileName1 = Convert.ToString(row["a_smcFileName_1"]).Replace('/', '\\');
        tAttkpet.aniIdle1 = Convert.ToString(row["a_ani_idle1_1"]);
        tAttkpet.aniIdle1_2 = Convert.ToString(row["a_ani_idle2_1"]);
        tAttkpet.aniAttack1 = Convert.ToString(row["a_ani_attack1_1"]);
        tAttkpet.aniAttack1_2 = Convert.ToString(row["a_ani_attack2_1"]);
        tAttkpet.aniDamage1 = Convert.ToString(row["a_ani_damage_1"]);
        tAttkpet.aniDie1 = Convert.ToString(row["a_ani_die_1"]);
        tAttkpet.aniWalk1 = Convert.ToString(row["a_ani_walk_1"]);
        tAttkpet.aniRun1 = Convert.ToString(row["a_ani_run_1"]);
        tAttkpet.aniLevelup1 = Convert.ToString(row["a_ani_levelup_1"]);
        tAttkpet.mount1 = Convert.ToInt32(row["a_mount_1"]);
        tAttkpet.summonSkill1 = Convert.ToInt32(row["a_summon_skill_1"]);
        tAttkpet.speed1 = Convert.ToInt32(row["a_speed_1"]);
        tAttkpet.smcFileName2 = Convert.ToString(row["a_smcFileName_2"]).Replace('/', '\\');
        tAttkpet.aniIdle2 = Convert.ToString(row["a_ani_idle1_2"]);
        tAttkpet.aniIdle2_2 = Convert.ToString(row["a_ani_idle2_2"]);
        tAttkpet.aniAttack2 = Convert.ToString(row["a_ani_attack1_2"]);
        tAttkpet.aniAttack2_2 = Convert.ToString(row["a_ani_attack2_2"]);
        tAttkpet.aniDamage1_2 = Convert.ToString(row["a_ani_damage_2"]);
        tAttkpet.aniDie1_2 = Convert.ToString(row["a_ani_die_2"]);
        tAttkpet.aniWalk1_2 = Convert.ToString(row["a_ani_walk_2"]);
        tAttkpet.aniRun1_2 = Convert.ToString(row["a_ani_run_2"]);
        tAttkpet.aniLevelup1_2 = Convert.ToString(row["a_ani_levelup_2"]);
        tAttkpet.mount1_2 = Convert.ToInt32(row["a_mount_2"]);
        tAttkpet.summonSkill1_2 = Convert.ToInt32(row["a_summon_skill_2"]);
        AllLists.tpet_MenuData.Add(tAttkpet);
        AllLists.tpet_Menu.Add(tAttkpet.index.ToString() + " - " + tAttkpet.name.ToString());
      }
    }

    public void tPets_Evolution_Import()
    {
      AllLists.tpet_ev_MenuData.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_attack_pet_ev ORDER BY a_pet_index";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
        AllLists.tpet_ev_MenuData.Add(new BigpetEv()
        {
          APetIdx = Convert.ToInt32(row["a_pet_index"]),
          Level = Convert.ToInt32(row["a_level"]),
          Stemina = Convert.ToInt32(row["a_stemina"]),
          Faith = Convert.ToInt32(row["a_faith"]),
          a_stat1 = Convert.ToInt32(row["a_stat1"]),
          a_stat2 = Convert.ToInt32(row["a_stat2"]),
          a_ev_pet_index = Convert.ToInt32(row["a_ev_pet_index"]),
          a_order = Convert.ToInt32(row["a_order"])
        });
    }

    public void tPets_Exp_Import()
    {
      AllLists.tpet_exp_MenuData.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_attack_pet_exp ORDER BY a_pet_index";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
        AllLists.tpet_exp_MenuData.Add(new BigpetExp()
        {
          a_pet_index = Convert.ToInt32(row["a_pet_index"]),
          a_max_acc_param1 = Convert.ToInt32(row["a_max_acc_param1"]),
          a_max_acc_param2 = Convert.ToInt32(row["a_max_acc_param2"]),
          a_acc_rate_param1 = Convert.ToInt32(row["a_acc_rate_param1"]),
          a_acc_rate_param2 = Convert.ToInt32(row["a_acc_rate_param2"]),
          a_cooltime = Convert.ToInt32(row["a_cooltime"]),
          a_cooltime_rate = Convert.ToInt32(row["a_cooltime_rate"])
        });
    }

    public void treward_Import()
    {
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_reward_head";
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT ";
      LoadFromDatabase.LoadFromDatabaseSQL += "c.a_reward_idx, c.a_desc, c.a_rand_type,";
      LoadFromDatabase.LoadFromDatabaseSQL += "i.a_item_idx, i.a_item_flag, i.a_item_plus, i.a_item_option, i.a_item_num";
      LoadFromDatabase.LoadFromDatabaseSQL += "FROM ";
      LoadFromDatabase.LoadFromDatabaseSQL += "t_catalog c,  t_ct_item i \t";
      LoadFromDatabase.LoadFromDatabaseSQL += " WHERE ";
      LoadFromDatabase.LoadFromDatabaseSQL += "i.a_ctid = c.a_ctid";
      LoadFromDatabase.LoadFromDatabaseSQL += "   \t";
      LoadFromDatabase.LoadFromDatabaseSQL += "     ORDER BY";
      LoadFromDatabase.LoadFromDatabaseSQL += "        c.a_ctid, i.a_ctid";
      LoadFromDatabase.LoadFromDatabaseSQL += ")";
      DataTable fromQuery = mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL);
      AllLists.treward_head_MenuData.Clear();
      AllLists.tnpc_Menu.Clear();
      AllLists.treward_data_MenuData.Clear();
      foreach (DataRow row in (InternalDataCollectionBase) fromQuery.Rows)
      {
        treward_head trewardHead = new treward_head();
        trewardHead.idx = Convert.ToInt32(row["a_reward_idx"]);
        trewardHead.desc = Convert.ToString(row["a_desc"]);
        trewardHead.randtype = Convert.ToInt32(row["a_rand_type"]);
        AllLists.treward_head_MenuData.Add(trewardHead);
        AllLists.tnpc_Menu.Add(trewardHead.idx.ToString() + " - " + trewardHead.desc.ToString());
      }
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_reward_data";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
        AllLists.treward_data_MenuData.Add(new treward_data()
        {
          PrimaryKey = Convert.ToInt32(row["a_primarykey"]),
          RewardID = Convert.ToInt32(row["a_reward_idx"]),
          Type = Convert.ToInt32(row["a_type"]),
          ItemID = Convert.ToInt32(row["a_idx"]),
          Value1 = Convert.ToInt32(row["a_value_1"]),
          Value2 = Convert.ToInt32(row["a_value_2"]),
          Value3 = Convert.ToInt32(row["a_value_3"]),
          JobFlag = Convert.ToInt32(row["a_job_flag"]),
          MinLevel = Convert.ToInt32(row["a_level_mini"]),
          MaxLevel = Convert.ToInt32(row["a_level_maxi"]),
          Prob = Convert.ToInt32(row["a_prob"])
        });
    }

    public void tnpc_Import()
    {
      AllLists.tnpc_MenuData.Clear();
      AllLists.tnpc_Menu.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_npc";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
      {
        tnpc tnpc = new tnpc()
        {
          index = Convert.ToInt32(row["a_index"]),
          enable = Convert.ToInt32(row["a_enable"]),
          name = Convert.ToString(row["a_name"]),
          family = Convert.ToInt32(row["a_family"]),
          skillmaster = Convert.ToInt32(row["a_skillmaster"]),
          flag = Convert.ToInt32(row["a_flag"]),
          flag1 = Convert.ToInt32(row["a_flag1"]),
          stateflag = Convert.ToInt32(row["a_state_flag"]),
          level = Convert.ToInt32(row["a_level"]),
          exp = Convert.ToInt32(row["a_exp"]),
          prize = Convert.ToInt32(row["a_prize"]),
          sight = Convert.ToInt32(row["a_sight"]),
          size = Convert.ToSingle(row["a_size"]),
          movearea = Convert.ToInt32(row["a_move_area"]),
          attackarea = Convert.ToSingle(row["a_attack_area"]),
          skillpoint = Convert.ToInt32(row["a_skill_point"]),
          sskillmaster = Convert.ToInt32(row["a_sskill_master"]),
          str = Convert.ToInt32(row["a_str"]),
          dex = Convert.ToInt32(row["a_dex"]),
          INT = Convert.ToInt32(row["a_int"]),
          con = Convert.ToInt32(row["a_con"]),
          attack = Convert.ToInt32(row["a_attack"]),
          magic = Convert.ToInt32(row["a_magic"]),
          defense = Convert.ToInt32(row["a_defense"]),
          resist = Convert.ToInt32(row["a_resist"]),
          attacklevel = Convert.ToInt32(row["a_attacklevel"]),
          defenselevel = Convert.ToInt32(row["a_defenselevel"]),
          hp = Convert.ToInt64(row["a_hp"]),
          mp = Convert.ToInt32(row["a_mp"]),
          attacktype = Convert.ToInt32(row["a_attackType"]),
          attackspeed = Convert.ToInt32(row["a_attackSpeed"]),
          recoverhp = Convert.ToInt32(row["a_recover_hp"]),
          recovermp = Convert.ToInt32(row["a_recover_mp"]),
          walkspeed = Convert.ToSingle(row["a_walk_speed"]),
          runspeed = Convert.ToSingle(row["a_run_speed"]),
          skill0 = Convert.ToString(row["a_skill0"]),
          skill1 = Convert.ToString(row["a_skill1"]),
          skill2 = Convert.ToString(row["a_skill2"]),
          skill3 = Convert.ToString(row["a_skill3"]),
          drop0 = Convert.ToInt32(row["a_item_0"]),
          drop1 = Convert.ToInt32(row["a_item_1"]),
          drop2 = Convert.ToInt32(row["a_item_2"]),
          drop3 = Convert.ToInt32(row["a_item_3"]),
          drop4 = Convert.ToInt32(row["a_item_4"]),
          drop5 = Convert.ToInt32(row["a_item_5"]),
          drop6 = Convert.ToInt32(row["a_item_6"]),
          drop7 = Convert.ToInt32(row["a_item_7"]),
          drop8 = Convert.ToInt32(row["a_item_8"]),
          drop9 = Convert.ToInt32(row["a_item_9"]),
          drop10 = Convert.ToInt32(row["a_item_10"]),
          drop11 = Convert.ToInt32(row["a_item_11"]),
          drop12 = Convert.ToInt32(row["a_item_12"]),
          drop13 = Convert.ToInt32(row["a_item_13"]),
          drop14 = Convert.ToInt32(row["a_item_14"]),
          drop15 = Convert.ToInt32(row["a_item_15"]),
          drop16 = Convert.ToInt32(row["a_item_16"]),
          drop17 = Convert.ToInt32(row["a_item_17"]),
          drop18 = Convert.ToInt32(row["a_item_18"]),
          drop19 = Convert.ToInt32(row["a_item_19"]),
          droprate0 = Convert.ToInt32(row["a_item_percent_0"]),
          droprate1 = Convert.ToInt32(row["a_item_percent_1"]),
          droprate2 = Convert.ToInt32(row["a_item_percent_2"]),
          droprate3 = Convert.ToInt32(row["a_item_percent_3"]),
          droprate4 = Convert.ToInt32(row["a_item_percent_4"]),
          droprate5 = Convert.ToInt32(row["a_item_percent_5"]),
          droprate6 = Convert.ToInt32(row["a_item_percent_6"]),
          droprate7 = Convert.ToInt32(row["a_item_percent_7"]),
          droprate8 = Convert.ToInt32(row["a_item_percent_8"]),
          droprate9 = Convert.ToInt32(row["a_item_percent_9"]),
          droprate10 = Convert.ToInt32(row["a_item_percent_10"]),
          droprate11 = Convert.ToInt32(row["a_item_percent_11"]),
          droprate12 = Convert.ToInt32(row["a_item_percent_12"]),
          droprate13 = Convert.ToInt32(row["a_item_percent_13"]),
          droprate14 = Convert.ToInt32(row["a_item_percent_14"]),
          droprate15 = Convert.ToInt32(row["a_item_percent_15"]),
          droprate16 = Convert.ToInt32(row["a_item_percent_16"]),
          droprate17 = Convert.ToInt32(row["a_item_percent_17"]),
          droprate18 = Convert.ToInt32(row["a_item_percent_18"]),
          droprate19 = Convert.ToInt32(row["a_item_percent_19"]),
          minplus = Convert.ToInt32(row["a_minplus"]),
          maxplus = Convert.ToInt32(row["a_maxplus"]),
          probplus = Convert.ToInt32(row["a_probplus"]),
          product0 = Convert.ToInt32(row["a_product0"]),
          product1 = Convert.ToInt32(row["a_product1"]),
          product2 = Convert.ToInt32(row["a_product2"]),
          product3 = Convert.ToInt32(row["a_product3"]),
          product4 = Convert.ToInt32(row["a_product4"]),
          filesmc = Convert.ToString(row["a_file_smc"]),
          motionwalk = Convert.ToString(row["a_motion_walk"]),
          motionidle = Convert.ToString(row["a_motion_idle"]),
          motiondam = Convert.ToString(row["a_motion_dam"]),
          motionattack = Convert.ToString(row["a_motion_attack"]),
          motiondie = Convert.ToString(row["a_motion_die"]),
          motionrun = Convert.ToString(row["a_motion_run"]),
          motionidle2 = Convert.ToString(row["a_motion_idle2"]),
          motionattack2 = Convert.ToString(row["a_motion_attack2"]),
          scale = Convert.ToSingle(row["a_scale"]),
          attribute = Convert.ToInt32(row["a_attribute"]),
          firedelaycount = Convert.ToInt32(row["a_fireDelayCount"]),
          firedelay0 = Convert.ToSingle(row["a_fireDelay0"]),
          firedelay1 = Convert.ToSingle(row["a_fireDelay1"]),
          firedelay2 = Convert.ToSingle(row["a_fireDelay2"]),
          firedelay3 = Convert.ToSingle(row["a_fireDelay3"]),
          fireeffect0 = Convert.ToString(row["a_fireEffect0"]),
          fireeffect1 = Convert.ToString(row["a_fireEffect1"]),
          fireeffect2 = Convert.ToString(row["a_fireEffect2"]),
          fireobject = Convert.ToInt32(row["a_fireObject"]),
          firespeed = Convert.ToSingle(row["a_fireSpeed"]),
          aitype = Convert.ToInt32(row["a_aitype"]),
          aiflag = Convert.ToInt32(row["a_aiflag"]),
          aileaderflag = Convert.ToInt32(row["a_aileader_flag"]),
          aisummonhp = Convert.ToInt32(row["a_ai_summonHp"]),
          aileaderidx = Convert.ToInt32(row["a_aileader_idx"]),
          aileadercount = Convert.ToInt32(row["a_aileader_count"]),
          npcchoicetriggercount = Convert.ToInt32(row["a_npc_choice_trigger_count"]),
          npcchoicetriggerids = Convert.ToString(row["a_npc_choice_trigger_ids"])
        };
        tnpc.npcchoicetriggercount = Convert.ToInt32(row["a_npc_kill_trigger_count"]);
        tnpc.npckilltriggerids = Convert.ToString(row["a_npc_kill_trigger_ids"]);
        tnpc.createprob = Convert.ToInt32(row["a_createprob"]);
        tnpc.socketprob0 = Convert.ToInt32(row["a_socketprob_0"]);
        tnpc.socketprob1 = Convert.ToInt32(row["a_socketprob_1"]);
        tnpc.socketprob2 = Convert.ToInt32(row["a_socketprob_2"]);
        tnpc.socketprob3 = Convert.ToInt32(row["a_socketprob_3"]);
        tnpc.jewel0 = Convert.ToInt32(row["a_jewel_0"]);
        tnpc.jewel1 = Convert.ToInt32(row["a_jewel_1"]);
        tnpc.jewel2 = Convert.ToInt32(row["a_jewel_2"]);
        tnpc.jewel3 = Convert.ToInt32(row["a_jewel_3"]);
        tnpc.jewel4 = Convert.ToInt32(row["a_jewel_4"]);
        tnpc.jewel5 = Convert.ToInt32(row["a_jewel_5"]);
        tnpc.jewel6 = Convert.ToInt32(row["a_jewel_6"]);
        tnpc.jewel7 = Convert.ToInt32(row["a_jewel_7"]);
        tnpc.jewel8 = Convert.ToInt32(row["a_jewel_8"]);
        tnpc.jewel9 = Convert.ToInt32(row["a_jewel_9"]);
        tnpc.jewel10 = Convert.ToInt32(row["a_jewel_10"]);
        tnpc.jewel11 = Convert.ToInt32(row["a_jewel_11"]);
        tnpc.jewel12 = Convert.ToInt32(row["a_jewel_12"]);
        tnpc.jewel13 = Convert.ToInt32(row["a_jewel_13"]);
        tnpc.jewel14 = Convert.ToInt32(row["a_jewel_14"]);
        tnpc.jewel15 = Convert.ToInt32(row["a_jewel_15"]);
        tnpc.jewel16 = Convert.ToInt32(row["a_jewel_16"]);
        tnpc.jewel17 = Convert.ToInt32(row["a_jewel_17"]);
        tnpc.jewel18 = Convert.ToInt32(row["a_jewel_18"]);
        tnpc.jewel19 = Convert.ToInt32(row["a_jewel_19"]);
        tnpc.jeweldrop0 = Convert.ToInt32(row["a_jewel_percent_0"]);
        tnpc.jeweldrop1 = Convert.ToInt32(row["a_jewel_percent_1"]);
        tnpc.jeweldrop2 = Convert.ToInt32(row["a_jewel_percent_2"]);
        tnpc.jeweldrop3 = Convert.ToInt32(row["a_jewel_percent_3"]);
        tnpc.jeweldrop4 = Convert.ToInt32(row["a_jewel_percent_4"]);
        tnpc.jeweldrop5 = Convert.ToInt32(row["a_jewel_percent_5"]);
        tnpc.jeweldrop6 = Convert.ToInt32(row["a_jewel_percent_6"]);
        tnpc.jeweldrop7 = Convert.ToInt32(row["a_jewel_percent_7"]);
        tnpc.jeweldrop8 = Convert.ToInt32(row["a_jewel_percent_8"]);
        tnpc.jeweldrop9 = Convert.ToInt32(row["a_jewel_percent_9"]);
        tnpc.jeweldrop10 = Convert.ToInt32(row["a_jewel_percent_10"]);
        tnpc.jeweldrop11 = Convert.ToInt32(row["a_jewel_percent_11"]);
        tnpc.jeweldrop12 = Convert.ToInt32(row["a_jewel_percent_12"]);
        tnpc.jeweldrop13 = Convert.ToInt32(row["a_jewel_percent_13"]);
        tnpc.jeweldrop14 = Convert.ToInt32(row["a_jewel_percent_14"]);
        tnpc.jeweldrop15 = Convert.ToInt32(row["a_jewel_percent_15"]);
        tnpc.jeweldrop16 = Convert.ToInt32(row["a_jewel_percent_16"]);
        tnpc.jeweldrop17 = Convert.ToInt32(row["a_jewel_percent_17"]);
        tnpc.jeweldrop18 = Convert.ToInt32(row["a_jewel_percent_18"]);
        tnpc.jeweldrop19 = Convert.ToInt32(row["a_jewel_percent_19"]);
        tnpc.zoneflag = Convert.ToInt64(row["a_zone_flag"]);
        tnpc.extraflag = Convert.ToInt64(row["a_extra_flag"]);
        tnpc.rvrvalue = Convert.ToInt32(row["a_rvr_value"]);
        tnpc.rvrgrade = Convert.ToInt32(row["a_rvr_grade"]);
        tnpc.bound = Convert.ToInt32(row["a_bound"]);
        tnpc.lifetime = Convert.ToInt32(row["a_lifetime"]);
        AllLists.tnpc_MenuData.Add(tnpc);
        AllLists.tnpc_Menu.Add(tnpc.index.ToString() + " - " + tnpc.name.ToString());
      }
    }

    public void tItemCollection_Import()
    {
      AllLists.tItemCollect_MenuData.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_item_collection ORDER BY a_theme";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
      {
        tItemCollection tItemCollection = new tItemCollection();
        tItemCollection.a_theme = Convert.ToInt32(row["a_theme"]);
        tItemCollection.a_category = Convert.ToInt32(row["a_category"]);
        if (this.language == "THA")
        {
          tItemCollection.a_theme_string = Convert.ToString(row["a_theme_string_tld"]);
          tItemCollection.a_descr_string = Convert.ToString(row["a_desc_string_tld"]);
        }
        else
        {
          tItemCollection.a_theme_string = Convert.ToString(row["a_theme_string"]);
          tItemCollection.a_descr_string = Convert.ToString(row["a_desc_string"]);
        }
        tItemCollection.a_enable = Convert.ToBoolean(row["a_enable"]);
        tItemCollection.a_id = Convert.ToInt32(row["a_id"]);
        tItemCollection.a_row = Convert.ToInt32(row["a_row"]);
        tItemCollection.a_col = Convert.ToInt32(row["a_col"]);
        tItemCollection.a_need1_type = Convert.ToInt32(row["a_need1_type"]);
        tItemCollection.a_need1_index = Convert.ToInt32(row["a_need1_index"]);
        tItemCollection.a_need1_num = Convert.ToInt32(row["a_need1_num"]);
        tItemCollection.a_need2_type = Convert.ToInt32(row["a_need2_type"]);
        tItemCollection.a_need2_index = Convert.ToInt32(row["a_need2_index"]);
        tItemCollection.a_need2_num = Convert.ToInt32(row["a_need2_num"]);
        tItemCollection.a_need3_type = Convert.ToInt32(row["a_need3_type"]);
        tItemCollection.a_need3_index = Convert.ToInt32(row["a_need3_index"]);
        tItemCollection.a_need3_num = Convert.ToInt32(row["a_need3_num"]);
        tItemCollection.a_need4_type = Convert.ToInt32(row["a_need4_type"]);
        tItemCollection.a_need4_index = Convert.ToInt32(row["a_need4_index"]);
        tItemCollection.a_need4_num = Convert.ToInt32(row["a_need4_num"]);
        tItemCollection.a_need5_type = Convert.ToInt32(row["a_need5_type"]);
        tItemCollection.a_need5_index = Convert.ToInt32(row["a_need5_index"]);
        tItemCollection.a_need5_num = Convert.ToInt32(row["a_need5_num"]);
        tItemCollection.a_need6_type = Convert.ToInt32(row["a_need6_type"]);
        tItemCollection.a_need6_index = Convert.ToInt32(row["a_need6_index"]);
        tItemCollection.a_need6_num = Convert.ToInt32(row["a_need6_num"]);
        tItemCollection.a_result_type = Convert.ToInt32(row["a_result_type"]);
        tItemCollection.a_result_index = Convert.ToInt32(row["a_result_index"]);
        tItemCollection.a_result_num = Convert.ToInt32(row["a_result_num"]);
        AllLists.tItemCollect_MenuData.Add(tItemCollection);
        AllLists.tItemCollect_Menu.Add(tItemCollection.a_theme.ToString() + " - " + tItemCollection.a_theme_string.ToString());
      }
    }
  }
}
