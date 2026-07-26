// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.DatabaseUpdate
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class DatabaseUpdate
  {
    public static void tnpc_Update(tnpc npc)
    {
      try
      {
        using (MySqlConnection mySqlConnection = new MySqlConnection(mySQL.ConnectionString))
        {
          MySqlCommand mySqlCommand = new MySqlCommand();
          mySqlConnection.Open();
          mySqlCommand.Connection = mySqlConnection;
          string str = "INSERT INTO t_npc (a_index, a_enable ,a_name ,a_family ,a_skillmaster ,a_flag ,a_flag1 ,a_state_flag ,a_level ,a_exp ,a_prize ,a_sight ,a_size ,a_move_area ,a_attack_area ,a_skill_point ,a_sskill_master ,a_str ,a_dex ,a_int ,a_con ,a_attack ,a_magic ,a_defense ,a_resist ,a_attacklevel ,a_defenselevel ,a_hp ,a_mp ,a_attackType ,a_attackSpeed ,a_recover_hp ,a_recover_mp ,a_walk_speed ,a_run_speed ,a_skill0 ,a_skill1 ,a_skill2 ,a_skill3 ,a_item_0 ,a_item_1 ,a_item_2 ,a_item_3 ,a_item_4 ,a_item_5 ,a_item_6 ,a_item_7 ,a_item_8 ,a_item_9 ,a_item_10 ,a_item_11 ,a_item_12 ,a_item_13 ,a_item_14 ,a_item_15 ,a_item_16 ,a_item_17 ,a_item_18 ,a_item_19 ,a_item_percent_0 ,a_item_percent_1 ,a_item_percent_2 ,a_item_percent_3 ,a_item_percent_4 ,a_item_percent_5 ,a_item_percent_6 ,a_item_percent_7 ,a_item_percent_8 ,a_item_percent_9 ,a_item_percent_10 ,a_item_percent_11 ,a_item_percent_12 ,a_item_percent_13 ,a_item_percent_14 ,a_item_percent_15 ,a_item_percent_16 ,a_item_percent_17 ,a_item_percent_18 ,a_item_percent_19 ,a_minplus ,a_maxplus ,a_probplus ,a_product0 ,a_product1 ,a_product2 ,a_product3 ,a_product4 ,a_file_smc ,a_motion_walk ,a_motion_idle ,a_motion_dam ,a_motion_attack ,a_motion_die ,a_motion_run ,a_motion_idle2 ,a_motion_attack2 ,a_scale ,a_attribute ,a_fireDelayCount ,a_fireDelay0 ,a_fireDelay1 ,a_fireDelay2 ,a_fireDelay3 ,a_fireEffect0 ,a_fireEffect1 ,a_fireEffect2 ,a_fireObject ,a_fireSpeed ,a_aitype ,a_aiflag ,a_aileader_flag ,a_ai_summonHp ,a_aileader_idx ,a_aileader_count ,a_crafting_category ,a_productIndex ,a_hit ,a_dodge ,a_magicavoid ,a_job_attribute ,a_npc_choice_trigger_count ,a_npc_choice_trigger_ids ,a_npc_kill_trigger_count ,a_npc_kill_trigger_ids ,a_createprob ,a_socketprob_0 ,a_socketprob_1 ,a_socketprob_2 ,a_socketprob_3 ,a_jewel_0 ,a_jewel_1 ,a_jewel_2 ,a_jewel_3 ,a_jewel_4 ,a_jewel_5 ,a_jewel_6 ,a_jewel_7 ,a_jewel_8 ,a_jewel_9 ,a_jewel_10 ,a_jewel_11 ,a_jewel_12 ,a_jewel_13 ,a_jewel_14 ,a_jewel_15 ,a_jewel_16 ,a_jewel_17 ,a_jewel_18 ,a_jewel_19 ,a_jewel_percent_0 ,a_jewel_percent_1 ,a_jewel_percent_2 ,a_jewel_percent_3 ,a_jewel_percent_4 ,a_jewel_percent_5 ,a_jewel_percent_6 ,a_jewel_percent_7 ,a_jewel_percent_8 ,a_jewel_percent_9 ,a_jewel_percent_10 ,a_jewel_percent_11 ,a_jewel_percent_12 ,a_jewel_percent_13 ,a_jewel_percent_14 ,a_jewel_percent_15 ,a_jewel_percent_16 ,a_jewel_percent_17 ,a_jewel_percent_18 ,a_jewel_percent_19 ,a_zone_flag ,a_extra_flag ,a_rvr_value ,a_rvr_grade ,a_bound ,a_lifetime)VALUES (@index, @enable ,@name ,@family ,@skillmaster ,@flag ,@flag1 ,@state_flag ,@level ,@exp ,@prize ,@sight ,@size ,@move_area ,@attack_area ,@skill_point ,@sskill_master ,@str ,@dex ,@int ,@con ,@attack ,@magic ,@defense ,@resist ,@attacklevel ,@defenselevel ,@hp ,@mp ,@attackType ,@attackSpeed ,@recover_hp ,@recover_mp ,@walk_speed ,@run_speed ,@skill0 ,@skill1 ,@skill2 ,@skill3 ,@item_0 ,@item_1 ,@item_2 ,@item_3 ,@item_4 ,@item_5 ,@item_6 ,@item_7 ,@item_8 ,@item_9 ,@item_10 ,@item_11 ,@item_12 ,@item_13 ,@item_14 ,@item_15 ,@item_16 ,@item_17 ,@item_18 ,@item_19 ,@item_percent_0 ,@item_percent_1 ,@item_percent_2 ,@item_percent_3 ,@item_percent_4 ,@item_percent_5 ,@item_percent_6 ,@item_percent_7 ,@item_percent_8 ,@item_percent_9 ,@item_percent_10 ,@item_percent_11 ,@item_percent_12 ,@item_percent_13 ,@item_percent_14 ,@item_percent_15 ,@item_percent_16 ,@item_percent_17 ,@item_percent_18 ,@item_percent_19 ,@minplus ,@maxplus ,@probplus ,@product0 ,@product1 ,@product2 ,@product3 ,@product4 ,@file_smc ,@motion_walk ,@motion_idle ,@motion_dam ,@motion_attack ,@motion_die ,@motion_run ,@motion_idle2 ,@motion_attack2 ,@scale ,@attribute ,@fireDelayCount ,@fireDelay0 ,@fireDelay1 ,@fireDelay2 ,@fireDelay3 ,@fireEffect0 ,@fireEffect1 ,@fireEffect2 ,@fireObject ,@fireSpeed ,@aitype ,@aiflag ,@aileader_flag ,@ai_summonHp ,@aileader_idx ,@aileader_count ,@crafting_category ,@productIndex ,@hit ,@dodge ,@magicavoid ,@job_attribute ,@npc_choice_trigger_count ,@npc_choice_trigger_ids ,@npc_kill_trigger_count ,@npc_kill_trigger_ids ,@createprob ,@socketprob_0 ,@socketprob_1 ,@socketprob_2 ,@socketprob_3 ,@jewel_0 ,@jewel_1 ,@jewel_2 ,@jewel_3 ,@jewel_4 ,@jewel_5 ,@jewel_6 ,@jewel_7 ,@jewel_8 ,@jewel_9 ,@jewel_10 ,@jewel_11 ,@jewel_12 ,@jewel_13 ,@jewel_14 ,@jewel_15 ,@jewel_16 ,@jewel_17 ,@jewel_18 ,@jewel_19 ,@jewel_percent_0 ,@jewel_percent_1 ,@jewel_percent_2 ,@jewel_percent_3 ,@jewel_percent_4 ,@jewel_percent_5 ,@jewel_percent_6 ,@jewel_percent_7 ,@jewel_percent_8 ,@jewel_percent_9 ,@jewel_percent_10 ,@jewel_percent_11 ,@jewel_percent_12 ,@jewel_percent_13 ,@jewel_percent_14 ,@jewel_percent_15 ,@jewel_percent_16 ,@jewel_percent_17 ,@jewel_percent_18 ,@jewel_percent_19 ,@zone_flag ,@extraflag ,@rvr_value ,@rvr_grade ,@bound ,@lifetime )";
          mySqlCommand.CommandText = str;
          mySqlCommand.Prepare();
          mySqlCommand.Parameters.AddWithValue("@index", (object) npc.index);
          mySqlCommand.Parameters.AddWithValue("@enable", (object) npc.enable);
          mySqlCommand.Parameters.AddWithValue("@name", (object) npc.name);
          mySqlCommand.Parameters.AddWithValue("@family", (object) npc.family);
          mySqlCommand.Parameters.AddWithValue("@skillmaster", (object) npc.skillmaster);
          mySqlCommand.Parameters.AddWithValue("@flag", (object) npc.flag);
          mySqlCommand.Parameters.AddWithValue("@flag1", (object) npc.flag1);
          mySqlCommand.Parameters.AddWithValue("@state_flag", (object) npc.stateflag);
          mySqlCommand.Parameters.AddWithValue("@level", (object) npc.level);
          mySqlCommand.Parameters.AddWithValue("@exp", (object) npc.exp);
          mySqlCommand.Parameters.AddWithValue("@prize", (object) npc.prize);
          mySqlCommand.Parameters.AddWithValue("@sight", (object) npc.sight);
          mySqlCommand.Parameters.AddWithValue("@size", (object) npc.size);
          mySqlCommand.Parameters.AddWithValue("@move_area", (object) npc.movearea);
          mySqlCommand.Parameters.AddWithValue("@attack_area", (object) npc.attackarea);
          mySqlCommand.Parameters.AddWithValue("@skill_point", (object) npc.skillpoint);
          mySqlCommand.Parameters.AddWithValue("@sskill_master", (object) npc.sskillmaster);
          mySqlCommand.Parameters.AddWithValue("@str", (object) npc.str);
          mySqlCommand.Parameters.AddWithValue("@dex", (object) npc.dex);
          mySqlCommand.Parameters.AddWithValue("@int", (object) npc.INT);
          mySqlCommand.Parameters.AddWithValue("@con", (object) npc.con);
          mySqlCommand.Parameters.AddWithValue("@attack", (object) npc.attack);
          mySqlCommand.Parameters.AddWithValue("@magic", (object) npc.magic);
          mySqlCommand.Parameters.AddWithValue("@defense", (object) npc.defense);
          mySqlCommand.Parameters.AddWithValue("@resist", (object) npc.resist);
          mySqlCommand.Parameters.AddWithValue("@attacklevel", (object) npc.attacklevel);
          mySqlCommand.Parameters.AddWithValue("@defenselevel", (object) npc.defenselevel);
          mySqlCommand.Parameters.AddWithValue("@hp", (object) npc.hp);
          mySqlCommand.Parameters.AddWithValue("@mp", (object) npc.mp);
          mySqlCommand.Parameters.AddWithValue("@attackType", (object) npc.attacktype);
          mySqlCommand.Parameters.AddWithValue("@attackSpeed", (object) npc.attackspeed);
          mySqlCommand.Parameters.AddWithValue("@recover_hp", (object) npc.recoverhp);
          mySqlCommand.Parameters.AddWithValue("@recover_mp", (object) npc.recovermp);
          mySqlCommand.Parameters.AddWithValue("@walk_speed", (object) npc.walkspeed);
          mySqlCommand.Parameters.AddWithValue("@run_speed", (object) npc.runspeed);
          mySqlCommand.Parameters.AddWithValue("@skill0", (object) npc.skill0);
          mySqlCommand.Parameters.AddWithValue("@skill1", (object) npc.skill1);
          mySqlCommand.Parameters.AddWithValue("@skill2", (object) npc.skill2);
          mySqlCommand.Parameters.AddWithValue("@skill3", (object) npc.skill3);
          mySqlCommand.Parameters.AddWithValue("@item_0", (object) npc.drop0);
          mySqlCommand.Parameters.AddWithValue("@item_1", (object) npc.drop1);
          mySqlCommand.Parameters.AddWithValue("@item_2", (object) npc.drop2);
          mySqlCommand.Parameters.AddWithValue("@item_3", (object) npc.drop3);
          mySqlCommand.Parameters.AddWithValue("@item_4", (object) npc.drop4);
          mySqlCommand.Parameters.AddWithValue("@item_5", (object) npc.drop5);
          mySqlCommand.Parameters.AddWithValue("@item_6", (object) npc.drop6);
          mySqlCommand.Parameters.AddWithValue("@item_7", (object) npc.drop7);
          mySqlCommand.Parameters.AddWithValue("@item_8", (object) npc.drop8);
          mySqlCommand.Parameters.AddWithValue("@item_9", (object) npc.drop9);
          mySqlCommand.Parameters.AddWithValue("@item_10", (object) npc.drop10);
          mySqlCommand.Parameters.AddWithValue("@item_11", (object) npc.drop11);
          mySqlCommand.Parameters.AddWithValue("@item_12", (object) npc.drop12);
          mySqlCommand.Parameters.AddWithValue("@item_13", (object) npc.drop13);
          mySqlCommand.Parameters.AddWithValue("@item_14", (object) npc.drop14);
          mySqlCommand.Parameters.AddWithValue("@item_15", (object) npc.drop15);
          mySqlCommand.Parameters.AddWithValue("@item_16", (object) npc.drop16);
          mySqlCommand.Parameters.AddWithValue("@item_17", (object) npc.drop17);
          mySqlCommand.Parameters.AddWithValue("@item_18", (object) npc.drop18);
          mySqlCommand.Parameters.AddWithValue("@item_19", (object) npc.drop19);
          mySqlCommand.Parameters.AddWithValue("@item_percent_0", (object) npc.droprate0);
          mySqlCommand.Parameters.AddWithValue("@item_percent_1", (object) npc.droprate1);
          mySqlCommand.Parameters.AddWithValue("@item_percent_2", (object) npc.droprate2);
          mySqlCommand.Parameters.AddWithValue("@item_percent_3", (object) npc.droprate3);
          mySqlCommand.Parameters.AddWithValue("@item_percent_4", (object) npc.droprate4);
          mySqlCommand.Parameters.AddWithValue("@item_percent_5", (object) npc.droprate5);
          mySqlCommand.Parameters.AddWithValue("@item_percent_6", (object) npc.droprate6);
          mySqlCommand.Parameters.AddWithValue("@item_percent_7", (object) npc.droprate7);
          mySqlCommand.Parameters.AddWithValue("@item_percent_8", (object) npc.droprate8);
          mySqlCommand.Parameters.AddWithValue("@item_percent_9", (object) npc.droprate9);
          mySqlCommand.Parameters.AddWithValue("@item_percent_10", (object) npc.droprate10);
          mySqlCommand.Parameters.AddWithValue("@item_percent_11", (object) npc.droprate11);
          mySqlCommand.Parameters.AddWithValue("@item_percent_12", (object) npc.droprate12);
          mySqlCommand.Parameters.AddWithValue("@item_percent_13", (object) npc.droprate13);
          mySqlCommand.Parameters.AddWithValue("@item_percent_14", (object) npc.droprate14);
          mySqlCommand.Parameters.AddWithValue("@item_percent_15", (object) npc.droprate15);
          mySqlCommand.Parameters.AddWithValue("@item_percent_16", (object) npc.droprate16);
          mySqlCommand.Parameters.AddWithValue("@item_percent_17", (object) npc.droprate17);
          mySqlCommand.Parameters.AddWithValue("@item_percent_18", (object) npc.droprate18);
          mySqlCommand.Parameters.AddWithValue("@item_percent_19", (object) npc.droprate19);
          mySqlCommand.Parameters.AddWithValue("@minplus", (object) npc.minplus);
          mySqlCommand.Parameters.AddWithValue("@maxplus", (object) npc.maxplus);
          mySqlCommand.Parameters.AddWithValue("@probplus", (object) npc.probplus);
          mySqlCommand.Parameters.AddWithValue("@product0", (object) npc.product0);
          mySqlCommand.Parameters.AddWithValue("@product1", (object) npc.product1);
          mySqlCommand.Parameters.AddWithValue("@product2", (object) npc.product2);
          mySqlCommand.Parameters.AddWithValue("@product3", (object) npc.product3);
          mySqlCommand.Parameters.AddWithValue("@product4", (object) npc.product4);
          mySqlCommand.Parameters.AddWithValue("@file_smc", (object) npc.filesmc);
          mySqlCommand.Parameters.AddWithValue("@motion_walk", (object) npc.motionwalk);
          mySqlCommand.Parameters.AddWithValue("@motion_idle", (object) npc.motionidle);
          mySqlCommand.Parameters.AddWithValue("@motion_dam", (object) npc.motiondam);
          mySqlCommand.Parameters.AddWithValue("@motion_attack", (object) npc.motionattack);
          mySqlCommand.Parameters.AddWithValue("@motion_die", (object) npc.motiondie);
          mySqlCommand.Parameters.AddWithValue("@motion_run", (object) npc.motionrun);
          mySqlCommand.Parameters.AddWithValue("@motion_idle2", (object) npc.motionidle2);
          mySqlCommand.Parameters.AddWithValue("@motion_attack2", (object) npc.motionattack2);
          mySqlCommand.Parameters.AddWithValue("@scale", (object) npc.scale);
          mySqlCommand.Parameters.AddWithValue("@attribute", (object) npc.attribute);
          mySqlCommand.Parameters.AddWithValue("@fireDelayCount", (object) npc.firedelaycount);
          mySqlCommand.Parameters.AddWithValue("@fireDelay0", (object) npc.firedelay0);
          mySqlCommand.Parameters.AddWithValue("@fireDelay1", (object) npc.firedelay1);
          mySqlCommand.Parameters.AddWithValue("@fireDelay2", (object) npc.firedelay2);
          mySqlCommand.Parameters.AddWithValue("@fireDelay3", (object) npc.firedelay3);
          mySqlCommand.Parameters.AddWithValue("@fireEffect0", (object) npc.fireeffect0);
          mySqlCommand.Parameters.AddWithValue("@fireEffect1", (object) npc.fireeffect1);
          mySqlCommand.Parameters.AddWithValue("@fireEffect2", (object) npc.fireeffect2);
          mySqlCommand.Parameters.AddWithValue("@fireObject", (object) npc.fireobject);
          mySqlCommand.Parameters.AddWithValue("@fireSpeed", (object) npc.firespeed);
          mySqlCommand.Parameters.AddWithValue("@aitype", (object) npc.aitype);
          mySqlCommand.Parameters.AddWithValue("@aiflag", (object) npc.aiflag);
          mySqlCommand.Parameters.AddWithValue("@aileader_flag", (object) npc.aileaderflag);
          mySqlCommand.Parameters.AddWithValue("@ai_summonHp", (object) npc.aisummonhp);
          mySqlCommand.Parameters.AddWithValue("@aileader_idx", (object) npc.aileaderidx);
          mySqlCommand.Parameters.AddWithValue("@aileader_count", (object) npc.aileadercount);
          mySqlCommand.Parameters.AddWithValue("@crafting_category", (object) npc.craftingcategory);
          mySqlCommand.Parameters.AddWithValue("@productIndex", (object) npc.productindex);
          mySqlCommand.Parameters.AddWithValue("@hit", (object) npc.hit);
          mySqlCommand.Parameters.AddWithValue("@dodge", (object) npc.dodge);
          mySqlCommand.Parameters.AddWithValue("@magicavoid", (object) npc.magicavoid);
          mySqlCommand.Parameters.AddWithValue("@job_attribute", (object) npc.jobattribute);
          mySqlCommand.Parameters.AddWithValue("@npc_choice_trigger_count", (object) npc.npcchoicetriggercount);
          mySqlCommand.Parameters.AddWithValue("@npc_choice_trigger_ids", (object) npc.npcchoicetriggerids);
          mySqlCommand.Parameters.AddWithValue("@npc_kill_trigger_count", (object) npc.npckilltriggercount);
          mySqlCommand.Parameters.AddWithValue("@npc_kill_trigger_ids", (object) npc.npckilltriggerids);
          mySqlCommand.Parameters.AddWithValue("@createprob", (object) npc.createprob);
          mySqlCommand.Parameters.AddWithValue("@socketprob_0", (object) npc.socketprob0);
          mySqlCommand.Parameters.AddWithValue("@socketprob_1", (object) npc.socketprob1);
          mySqlCommand.Parameters.AddWithValue("@socketprob_2", (object) npc.socketprob2);
          mySqlCommand.Parameters.AddWithValue("@socketprob_3", (object) npc.socketprob3);
          mySqlCommand.Parameters.AddWithValue("@jewel_0", (object) npc.jewel0);
          mySqlCommand.Parameters.AddWithValue("@jewel_1", (object) npc.jewel1);
          mySqlCommand.Parameters.AddWithValue("@jewel_2", (object) npc.jewel2);
          mySqlCommand.Parameters.AddWithValue("@jewel_3", (object) npc.jewel3);
          mySqlCommand.Parameters.AddWithValue("@jewel_4", (object) npc.jewel4);
          mySqlCommand.Parameters.AddWithValue("@jewel_5", (object) npc.jewel5);
          mySqlCommand.Parameters.AddWithValue("@jewel_6", (object) npc.jewel6);
          mySqlCommand.Parameters.AddWithValue("@jewel_7", (object) npc.jewel7);
          mySqlCommand.Parameters.AddWithValue("@jewel_8", (object) npc.jewel8);
          mySqlCommand.Parameters.AddWithValue("@jewel_9", (object) npc.jewel9);
          mySqlCommand.Parameters.AddWithValue("@jewel_10", (object) npc.jewel0);
          mySqlCommand.Parameters.AddWithValue("@jewel_11", (object) npc.jewel1);
          mySqlCommand.Parameters.AddWithValue("@jewel_12", (object) npc.jewel2);
          mySqlCommand.Parameters.AddWithValue("@jewel_13", (object) npc.jewel3);
          mySqlCommand.Parameters.AddWithValue("@jewel_14", (object) npc.jewel4);
          mySqlCommand.Parameters.AddWithValue("@jewel_15", (object) npc.jewel5);
          mySqlCommand.Parameters.AddWithValue("@jewel_16", (object) npc.jewel6);
          mySqlCommand.Parameters.AddWithValue("@jewel_17", (object) npc.jewel7);
          mySqlCommand.Parameters.AddWithValue("@jewel_18", (object) npc.jewel8);
          mySqlCommand.Parameters.AddWithValue("@jewel_19", (object) npc.jewel9);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_0", (object) npc.jeweldrop0);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_1", (object) npc.jeweldrop1);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_2", (object) npc.jeweldrop2);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_3", (object) npc.jeweldrop3);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_4", (object) npc.jeweldrop4);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_5", (object) npc.jeweldrop5);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_6", (object) npc.jeweldrop6);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_7", (object) npc.jeweldrop7);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_8", (object) npc.jeweldrop8);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_9", (object) npc.jeweldrop9);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_10", (object) npc.jeweldrop10);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_11", (object) npc.jeweldrop11);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_12", (object) npc.jeweldrop12);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_13", (object) npc.jeweldrop13);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_14", (object) npc.jeweldrop14);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_15", (object) npc.jeweldrop15);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_16", (object) npc.jeweldrop16);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_17", (object) npc.jeweldrop17);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_18", (object) npc.jeweldrop18);
          mySqlCommand.Parameters.AddWithValue("@jewel_percent_19", (object) npc.jeweldrop19);
          mySqlCommand.Parameters.AddWithValue("@zone_flag", (object) npc.zoneflag);
          mySqlCommand.Parameters.AddWithValue("@extraflag", (object) npc.extraflag);
          mySqlCommand.Parameters.AddWithValue("@rvr_value", (object) npc.rvrvalue);
          mySqlCommand.Parameters.AddWithValue("@rvr_grade", (object) npc.rvrgrade);
          mySqlCommand.Parameters.AddWithValue("@bound", (object) npc.bound);
          mySqlCommand.Parameters.AddWithValue("@lifetime", (object) npc.lifetime);
          mySqlCommand.ExecuteNonQuery();
          mySqlConnection.Close();
        }
      }
      catch (MySqlException ex)
      {
        int num = (int) MessageBox.Show(ex.Message.ToString());
      }
    }

    public static void tattkpet_Update(t_attkpet attkpet)
    {
      try
      {
        using (MySqlConnection mySqlConnection = new MySqlConnection(mySQL.ConnectionString))
        {
          MySqlCommand mySqlCommand = new MySqlCommand();
          mySqlConnection.Open();
          mySqlCommand.Connection = mySqlConnection;
          string str = "INSERT INTO t_attack_pet (a_index, a_enable ,a_type ,a_name ,a_str ,a_con ,a_dex ,a_int ,a_item_idx ,a_maxFaith ,a_maxStm ,a_maxHP ,a_maxMP ,a_recoverHP ,a_recoverMP ,a_delay ,a_AISlot ,a_after_dead ,a_attack ,a_defence ,a_Mattack ,a_Mdefence ,a_hitpoint ,a_avoidpoint ,a_Mavoidpoint ,a_attackSpeed ,a_deadly ,a_critical ,a_awful ,a_normal ,a_week ,a_bagic_skill1 ,a_bagic_skill2 ,a_flag ,a_trans_type ,a_trans_start ,a_trans_end ,a_smcFileName_1 ,a_ani_idle1_1 ,a_ani_idle2_1 ,a_ani_attack1_1 ,a_ani_attack2_1 ,a_ani_damage_1 ,a_ani_die_1 ,a_ani_walk_1 ,a_ani_run_1 ,a_ani_levelup_1 ,a_mount_1 ,a_summon_skill_1 ,a_speed_1 ,a_smcFileName_2 ,a_ani_idle1_2 ,a_ani_idle2_2 ,a_ani_attack1_2 ,a_ani_attack2_2 ,a_ani_damage_2 ,a_ani_die_2 ,a_ani_walk_2 ,a_ani_run_2 ,a_ani_levelup_2 ,a_summon_skill_2 ,a_speed_2 ,)VALUES (@index, @enable ,@type ,@name ,@str ,@con ,@dex ,@intel ,@itemidx ,@maxFaith ,@maxStm ,@maxHP ,@maxMP ,@recoverHP ,@recoverMP ,@delay ,@AISlot ,@afterDead ,@attack ,@defense ,@mAttack ,@mDefense ,@hitPoint ,@avoidPoint ,@mavoidPoint ,@attackSpeed ,@Deadly ,@Critical ,@awful ,@strong ,@normal ,@weak ,@bagicSkill1 ,@bagicSkill2 ,@flag ,@transType ,@transStart ,@transEnd ,@smcFileName1 ,@aniIdle1 ,@aniIdle2 ,@aniAttack1 ,@aniAttack2 ,@aniDamage1 ,@aniDie1 ,@aniWalk1 ,@aniRun1 ,@aniLevelup1 ,@mount1 ,@summonSkill1 ,@speed1 ,@smcFileName2 ,@aniIdle1_2 ,@aniIdle2_2 ,@aniAttack1_2 ,@aniAttack2_2 ,@aniDamage1_2 ,@aniDie1_2 ,@aniWalk1_2 ,@aniRun1_2 ,@aniLevelup1_2 ,@mount1_2 ,@summonSkill1_2 ,@speed1_2 ,)";
          mySqlCommand.CommandText = str;
          mySqlCommand.Prepare();
          mySqlCommand.Parameters.AddWithValue("@index", (object) attkpet.index);
          mySqlCommand.Parameters.AddWithValue("@enable", (object) attkpet.enable);
          mySqlCommand.Parameters.AddWithValue("@type", (object) attkpet.type);
          mySqlCommand.Parameters.AddWithValue("@name", (object) attkpet.name);
          mySqlCommand.Parameters.AddWithValue("@str", (object) attkpet.str);
          mySqlCommand.Parameters.AddWithValue("@con", (object) attkpet.con);
          mySqlCommand.Parameters.AddWithValue("@dex", (object) attkpet.dex);
          mySqlCommand.Parameters.AddWithValue("@intel", (object) attkpet.intel);
          mySqlCommand.Parameters.AddWithValue("@itemidx", (object) attkpet.itemidx);
          mySqlCommand.Parameters.AddWithValue("@maxFaith", (object) attkpet.maxFaith);
          mySqlCommand.Parameters.AddWithValue("@maxStm", (object) attkpet.maxStm);
          mySqlCommand.Parameters.AddWithValue("@maxHP", (object) attkpet.maxHP);
          mySqlCommand.Parameters.AddWithValue("@maxMP", (object) attkpet.maxMP);
          mySqlCommand.Parameters.AddWithValue("@recoverHP", (object) attkpet.recoverHP);
          mySqlCommand.Parameters.AddWithValue("@recoverMP", (object) attkpet.recoverMP);
          mySqlCommand.Parameters.AddWithValue("@delay", (object) attkpet.delay);
          mySqlCommand.Parameters.AddWithValue("@AISlot", (object) attkpet.AISlot);
          mySqlCommand.Parameters.AddWithValue("@afterDead", (object) attkpet.afterDead);
          mySqlCommand.Parameters.AddWithValue("@attack", (object) attkpet.attack);
          mySqlCommand.Parameters.AddWithValue("@defense", (object) attkpet.defense);
          mySqlCommand.Parameters.AddWithValue("@mAttack", (object) attkpet.mAttack);
          mySqlCommand.Parameters.AddWithValue("@mDefense", (object) attkpet.mDefense);
          mySqlCommand.Parameters.AddWithValue("@hitPoint", (object) attkpet.hitPoint);
          mySqlCommand.Parameters.AddWithValue("@avoidPoint", (object) attkpet.avoidPoint);
          mySqlCommand.Parameters.AddWithValue("@mavoidPoint", (object) attkpet.mavoidPoint);
          mySqlCommand.Parameters.AddWithValue("@attackSpeed", (object) attkpet.attackSpeed);
          mySqlCommand.Parameters.AddWithValue("@Deadly", (object) attkpet.Deadly);
          mySqlCommand.Parameters.AddWithValue("@Critical", (object) attkpet.Critical);
          mySqlCommand.Parameters.AddWithValue("@awful", (object) attkpet.awful);
          mySqlCommand.Parameters.AddWithValue("@strong", (object) attkpet.strong);
          mySqlCommand.Parameters.AddWithValue("@normal", (object) attkpet.normal);
          mySqlCommand.Parameters.AddWithValue("@weak", (object) attkpet.weak);
          mySqlCommand.Parameters.AddWithValue("@bagicSkill1", (object) attkpet.bagicSkill1);
          mySqlCommand.Parameters.AddWithValue("@bagicSkill2", (object) attkpet.bagicSkill2);
          mySqlCommand.Parameters.AddWithValue("@flag", (object) attkpet.flag);
          mySqlCommand.Parameters.AddWithValue("@transType", (object) attkpet.transType);
          mySqlCommand.Parameters.AddWithValue("@transStart", (object) attkpet.transStart);
          mySqlCommand.Parameters.AddWithValue("@transEnd", (object) attkpet.transEnd);
          mySqlCommand.Parameters.AddWithValue("@smcFileName1", (object) attkpet.smcFileName1);
          mySqlCommand.Parameters.AddWithValue("@aniIdle1", (object) attkpet.aniIdle1);
          mySqlCommand.Parameters.AddWithValue("@aniIdle2", (object) attkpet.aniIdle2);
          mySqlCommand.Parameters.AddWithValue("@aniAttack1", (object) attkpet.aniAttack1);
          mySqlCommand.Parameters.AddWithValue("@aniAttack2", (object) attkpet.aniAttack2);
          mySqlCommand.Parameters.AddWithValue("@aniDamage1", (object) attkpet.aniDamage1);
          mySqlCommand.Parameters.AddWithValue("@aniDie1", (object) attkpet.aniDie1);
          mySqlCommand.Parameters.AddWithValue("@aniWalk1", (object) attkpet.aniWalk1);
          mySqlCommand.Parameters.AddWithValue("@aniRun1", (object) attkpet.aniRun1);
          mySqlCommand.Parameters.AddWithValue("@aniLevelup1", (object) attkpet.aniLevelup1);
          mySqlCommand.Parameters.AddWithValue("@mount1", (object) attkpet.mount1);
          mySqlCommand.Parameters.AddWithValue("@summonSkill1", (object) attkpet.summonSkill1);
          mySqlCommand.Parameters.AddWithValue("@speed1", (object) attkpet.speed1);
          mySqlCommand.Parameters.AddWithValue("@smcFileName2", (object) attkpet.smcFileName2);
          mySqlCommand.Parameters.AddWithValue("@aniIdle1_2", (object) attkpet.aniIdle1_2);
          mySqlCommand.Parameters.AddWithValue("@aniIdle2_2", (object) attkpet.aniIdle2_2);
          mySqlCommand.Parameters.AddWithValue("@aniAttack1_2", (object) attkpet.aniAttack1_2);
          mySqlCommand.Parameters.AddWithValue("@aniAttack2_2", (object) attkpet.aniAttack2_2);
          mySqlCommand.Parameters.AddWithValue("@aniDamage1_2", (object) attkpet.aniDamage1_2);
          mySqlCommand.Parameters.AddWithValue("@aniDie1_2", (object) attkpet.aniDie1_2);
          mySqlCommand.Parameters.AddWithValue("@aniWalk1_2", (object) attkpet.aniWalk1_2);
          mySqlCommand.Parameters.AddWithValue("@aniRun1_2", (object) attkpet.aniRun1_2);
          mySqlCommand.Parameters.AddWithValue("@aniLevelup1_2", (object) attkpet.aniLevelup1_2);
          mySqlCommand.Parameters.AddWithValue("@mount1_2", (object) attkpet.mount1_2);
          mySqlCommand.Parameters.AddWithValue("@summonSkill1_2", (object) attkpet.summonSkill1_2);
          mySqlCommand.Parameters.AddWithValue("@speed1_2", (object) attkpet.speed1_2);
          mySqlCommand.ExecuteNonQuery();
          mySqlConnection.Close();
        }
      }
      catch (MySqlException ex)
      {
        int num = (int) MessageBox.Show(ex.Message.ToString());
      }
    }
  }
}
