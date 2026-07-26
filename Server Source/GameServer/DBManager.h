#ifndef __DB_MANAGER_H__
#define __DB_MANAGER_H__

#include <vector>
#include <string>
#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/thread.hpp>

#include "../ShareLib/queue_ts.h"
#include "../ShareLib/mysqldb.h"
#include "../ShareLib/MemoryPoolBase.h"
#include "../ShareLib/packetType/ptype_express_system.h"

#include "Character.h"

enum
{
	DB_PROC_EXIT = -1,

	DB_PROC_CHARACTER_LIST = 0,
	DB_PROC_CREATE_CHAR,
	DB_PROC_DELETE_CHAR,
	DB_PROC_CANCEL_DELETE_CHAR,
	DB_PROC_SELECT_CHAR,
	DB_PROC_SAVE_CHAR,

	DB_PROC_EXPRESS_EXIST,
	DB_PROC_EXPRESS_LIST,
	DB_PROC_EXPRESS_TAKE,
	DB_PROC_EXPRESS_TAKE_ALL,
	DB_PROC_EXPRESS_INPUT_ITEM,		// Ã¢°íNPC¿¡°Ô ¾ÆÀÌÅÛÀ» ÀÔ·Â
	DB_PROC_EXPRESS_INPUT_NAS,		// Ã¢°íNPC¿¡°Ô ³ª½º(µ·)À» ÀÔ·Â
	DB_PROC_EXPRESS_DELETE,			// ¾ÆÀÌÅÛ(¶Ç´Â µ·)À» À¯Àú°¡ ¼ö·ÉÇßÀ» °æ¿ì »èÁ¦ÇÔ
	DB_PROC_EXPRESS_DELETE_ALL,			// ¾ÆÀÌÅÛ(¶Ç´Â µ·)À» À¯Àú°¡ ¼ö·ÉÇßÀ» °æ¿ì »èÁ¦ÇÔ

	DB_PROC_QUERY,

	DB_PROC_MYSQL_PING,
	DB_PROC_SEND_ANY_INFO_AFTER_LOGIN,		// ·Î±×ÀÎ ÈÄ ÀÚµ¿À¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô º¸³¾ Á¤º¸¸¦ Ã³¸®ÇÔ

	DB_PROC_SEARCH_NICKNAME_FOR_EXPRESS,	// ½ÅºñÇÑ ¼®»óÀÇ ±¸½½
	DB_PROC_SEND_ITEM_TO_NICKNAME,				// ½ÅºñÇÑ ¼®»óÀÇ ±¸½½

	DB_PROC_DEL_CHARACTER_FOR_GM,			// gm ¸í·É¾î·Î Ä³¸¯ÅÍ¸¦ Áö¿ï¶§ »ç¿ë

	DB_PROC_QUERY_FOR_AUTH_DB,
	DB_PROC_QUERY_FOR_DATA_DB,

	DB_PROC_GET_CHAR_INDEX_BY_GPS,			// ÀÌ¸§À» ÅëÇØ¼­ char index¸¦ ¾òÀ½
	
	DB_PROC_INSERT_MAKETITLE_INFO,			// Á¦ÀÛ Å¸ÀÌÀ» Á¤º¸¸¦ ÀúÀå
};

enum
{
	CHAR_SAVE_TYPE_TCHAR,
	CHAR_SAVE_TYPE_TCHAR_GUILD_POINT,
	CHAR_SAVE_TYPE_TCHAR_QUEST,
	CHAR_SAVE_TYPE_TCHAR_AFFINITY,
	CHAR_SAVE_TYPE_TCHAR_ASSIST,
	CHAR_SAVE_TYPE_TCHAR_ASSIST_ABS_TIME,
	CHAR_SAVE_TYPE_TCHAR_INVEN,
	CHAR_SAVE_TYPE_TCHAR_GAMIGO_HACK_DELETE,
	CHAR_SAVE_TYPE_TCHAR_STASH,
	CHAR_SAVE_TYPE_TCHAR_QUICK_SLOT,
	CHAR_SAVE_TYPE_TCHAR_MEMPOS,
	CHAR_SAVE_TYPE_TCHAR_CASH_ITEM_DATE,
	CHAR_SAVE_TYPE_TCHAR_PD_DATA,
	CHAR_SAVE_TYPE_TCHAR_PET_PRE,
	CHAR_SAVE_TYPE_TCHAR_PET,
	CHAR_SAVE_TYPE_TCHAR_PET_NAME,
	CHAR_SAVE_TYPE_TCHAR_PET_TEMP_DELETE,
	CHAR_SAVE_TYPE_TCHAR_APET_PRE,
	CHAR_SAVE_TYPE_TCHAR_APET,
	CHAR_SAVE_TYPE_TCHAR_APET_OWNER,
	CHAR_SAVE_TYPE_TCHAR_APET_INVEN,
	CHAR_SAVE_TYPE_TCHAR_APET_AI,
	CHAR_SAVE_TYPE_TCHAR_APET_TEMP_DELETE,
	CHAR_SAVE_TYPE_TCHAR_CHARACTER_FACTORY,
	CHAR_SAVE_TYPE_TCHAR_MESSENGER_OPT,
	CHAR_SAVE_TYPE_TCHAR_FRIEND,
	CHAR_SAVE_TYPE_TCHAR_BLOCK_FRIEND,
	CHAR_SAVE_TYPE_TCHAR_WAR_GROUND,
	CHAR_SAVE_TYPE_TCHAR_EVENT_GOMDORI,

	CHAR_SAVE_TYPE_TIMER_ITEM,
	CHAR_SAVE_TYPE_TCHAR_PET_STASH,
	CHAR_SAVE_TYPE_TCHAR_PET_STASH_INFO,
	CHAR_SAVE_TYPE_TCHAR_SKILL_COOLTIME,
	CHAR_SAVE_TYPE_TCHAR_WEAR_ITEM,
	CHAR_SAVE_TYPE_RVR_INFO,
	CHAR_SAVE_TYPE_GPS_INFO,
	CHAR_SAVE_TYPE_ITEM_COLLECTION_INFO,

#ifdef PREMIUM_CHAR
	CHAR_SAVE_TYPE_PREMIUM_CHAR_INFO,
#endif
	//PASSIVE_SYSTEM
	CHAR_SAVE_TYPE_TCHAR_CHARACTER_PASSIVE, //new 16-08-2022

	CHAR_SAVE_TYPE_INVENTORY_OPTIONS,
	CHAR_SAVE_TYPE_TCHAR_MAX,
};

// Dirty flags for conditional saves — only save subsystems that actually changed
// On disconnect, all flags are force-set so everything is saved
enum eSaveDirtyFlags
{
	SAVE_DIRTY_CHAR          = (1 << 0),   // main t_characters (exp, level, hp, position, skills, nas, etc.)
	SAVE_DIRTY_GUILD_POINT   = (1 << 1),   // guild exp/fame
	SAVE_DIRTY_QUEST         = (1 << 2),   // quest data
	SAVE_DIRTY_AFFINITY      = (1 << 3),   // affinity
	SAVE_DIRTY_ASSIST        = (1 << 4),   // buffs/debuffs + abs time
	SAVE_DIRTY_INVEN         = (1 << 5),   // inventory items
	SAVE_DIRTY_STASH         = (1 << 6),   // warehouse/stash
	SAVE_DIRTY_QUICKSLOT     = (1 << 7),   // quick slot layout
	SAVE_DIRTY_MEMPOS        = (1 << 8),   // saved positions
	SAVE_DIRTY_PET           = (1 << 9),   // all pet data (pet + apet)
	SAVE_DIRTY_FACTORY       = (1 << 10),  // character factory
	SAVE_DIRTY_MESSENGER     = (1 << 11),  // messenger/friends/block
	SAVE_DIRTY_WARGROUND     = (1 << 12),  // war ground stats
	SAVE_DIRTY_TIMER_ITEM    = (1 << 13),  // timer items
	SAVE_DIRTY_PET_STASH     = (1 << 14),  // pet stash
	SAVE_DIRTY_SKILL_COOL    = (1 << 15),  // skill cooldowns
	SAVE_DIRTY_WEAR_ITEM     = (1 << 16),  // wear item info
	SAVE_DIRTY_RVR           = (1 << 17),  // RvR info
	SAVE_DIRTY_GPS           = (1 << 18),  // GPS info
	SAVE_DIRTY_COLLECTION    = (1 << 19),  // item collection
	SAVE_DIRTY_PREMIUM       = (1 << 20),  // premium char
	SAVE_DIRTY_PASSIVE       = (1 << 21),  // passive system
	SAVE_DIRTY_INVEN_OPTIONS = (1 << 22),  // inventory options
	SAVE_DIRTY_CASH_ITEM     = (1 << 23),  // cash item date
	SAVE_DIRTY_PD_DATA       = (1 << 24),  // personal dungeon
	SAVE_DIRTY_ALL           = 0xFFFFFFFF, // force save everything (disconnect)
};

enum
{
	EXPRESS_SENDER_TYPE_MARBLE,				// ½ÅºñÇÑ ¼®»óÀÇ ±¸½½
	EXPRESS_SENDER_TYPE_WEAR_INVENTORY,		// ÀåÂø ÀÎº¥Åä¸®
};

typedef std::vector<std::vector<std::string> > save_char_queryt_t;

struct CreateCharacterInfo : public MemoryPoolBaseWithMutex<CreateCharacterInfo>
{
	int				m_index;
	time_t			m_tExtendCharacterSlotTime;
#ifdef HANARO_EVENT
	std::string		m_hanaroCode;
#endif
	std::string		m_name;
	unsigned char	m_job;
	unsigned char	m_hairstyle;
	unsigned char	m_facestyle;

	int				m_str;
	int				m_dex;
	int				m_int;
	int				m_con;
	int				m_dbHP;
	int				m_dbMP;

	int				m_level;
	unsigned char	m_job2;
	int				m_statpt_str;
	int				m_statpt_dex;
	int				m_statpt_con;
	int				m_statpt_int;
	int				m_statpt_remain;

	int				m_etcEvent;
};

struct SaveCharacter
{
};
//////////////////////////////////////////////////////////////////////////
class DBProcess;

class DBManager
{
public:
	DBManager();
	~DBManager();

	static DBManager* instance();

	bool Init(int count = 2 /*thread count*/);
	void MySQLPing();
	void JoinAll();

	void PushCharacterList(CDescriptor* desc);
	void PushCreateChar(CDescriptor* desc, CreateCharacterInfo* cinfo);
	void PushDeleteCharacter(CDescriptor* desc, int char_index, int guildoutdate);
	void PushCancelDeleteCharacter(CDescriptor* desc, int char_index);
	void PushSelectCharacter(CDescriptor* desc, int char_index, void* guild);
	void PushSaveCharacter(CDescriptor* desc, save_char_queryt_t* save_data, bool disconnect);

	void PushExpressExist(CDescriptor* desc, int send_type);
	void PushExpressList(CDescriptor* desc, int pageIndex);
	void PushExpressTake(CDescriptor* desc, expressIndex_t expressIndex);
	void PushExpressTakeAll(CDescriptor* desc, int pageIndex);
	void PushExpressInputItem(CDescriptor* desc, ExpressSystemItemInfo* itemInfo, bool contentsFlag);
	void PushExpressInputNas(CDescriptor* desc, unsigned int nas, int send_type, std::string sender, bool contentsFlag);
	void PushExpressInputItemNotConnectUser(int charIndex, ExpressSystemItemInfo* itemInfo, bool contentsFlag);
	void PushExpressInputNasNotConnectUser(int charIndex, unsigned int nas, int send_type, std::string sender, bool contentsFlag);
	void PushExpressDelete(CDescriptor* desc, expressIndex_t expressIndex, bool send_flag = false);
	void PushExpressDeleteAll(CDescriptor* desc, int pageIndex, bool send_flag = false);
	void PushExpressSearchNickName(CDescriptor* desc, const char* nickName);
	void PushExpressSendItemToNickName(CDescriptor* desc, ExpressSystemItemInfo* itemInfo, std::string receiver, int sender_type);

	void pushQuery(int userIndex, std::string& query);

	void pushSendAnyInfoAfterLogin(CDescriptor* desc);

	void SaveCharacterInfo(CDescriptor* d, bool disconnect);

	void pushDelCharForGM(CDescriptor* desc, std::string& del_charname);

	void pushQueryForAuthDB(int userIndex, std::string& query);
	void pushQueryForDataDB(int userIndex, std::string& query);

	void pushGetCharIndexByGPS(CDescriptor* desc, std::string& name, int itemVindex);

	void pushMakeTitleInfo(CDescriptor* desc, int char_index, int v_index, char color, char background_color, char effect, std::string name, int* option_index, int* option_level);

private:
	void _SaveCharaterQuery(std::vector<std::string> & vec, CPC* pChar, int table_no);
	void _SaveGuildPointQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveQuestQuery(std::vector<std::string> & vec, CPC* pChar, int table_no);
	void _SaveAffinityQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveAssistQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveAssistABSTimeQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharInvenQuery(std::vector<std::string> & vec, CPC* pChar,int table_no);
	void _SaveCharcterStashQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterQuickSlotQuery(std::vector<std::string> & vec, CPC* pChar, int table_no);
	void _SaveCharacterMemposQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterCashItemDateQuery(std::vector<std::string> & vec, CPC* pChar, int descriptorUserIndex);
	void _SaveCharacterPersonalDungeonQuery(std::vector<std::string> & vec, CPC* pChar, int table_no);

	void _SaveCharacterPetPreQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterPetQuery(std::vector<std::string> & vec, CPC* pChar, CPet* pet);
	void _SaveCharacterPetNameQuery(std::vector<std::string> & vec, CPC* pChar, CPet* pet);
	void _SaveCharacterPetTempDeleteQuery(std::vector<std::string> & vec, CPC* pChar);

	void _SaveCharacterAttackPetPreQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterAttackPetQuery(std::vector<std::string> & vec, CPC* pChar, CAPet* apet);
	void _SaveCharacterAttackPetInvenQuery(std::vector<std::string> & vec, CPC* pChar, CAPet* apet);
	void _SaveCharacterAttackPetAIQuery(std::vector<std::string> & vec, CPC* pChar, CAPet* apet);
	void _SaveCharacterAttackPetTempDeleteQuery(std::vector<std::string> & vec, CPC* pChar);

	void _SaveCharacterFactoryQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterMessengerOPTQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterMessengerFriendQuery(std::vector<std::string> & vec, CPC* pChar, int table_no);
	void _SaveCharacterMessengerBlockFriendQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterRoyalRumbleQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterEventGomdoriQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveTimerItemQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterPetStashDeleteQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterPetStashQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterSkillCoolTimeQuery(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterRVRInfo(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterGPSInfo(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterItemCollectionInfo(std::vector<std::string> & vec, CPC* pChar);
	void _SaveCharacterInventoryOptions(std::vector<std::string>& vec, CPC* ch);

#ifdef PREMIUM_CHAR
	void _SaveCharacterPremiumCharInfo(std::vector<std::string> & vec, CPC* pChar);
#endif
	//PASSIVE_SYSTEM
	void _SaveCharacterPassiveQuery(std::vector<std::string>& vec, CPC* pChar); //new 16-08-2022

private:
	int						thread_count_;
	boost::thread_group		thread_group_;
	DBProcess*				db_process_;

	bool					stop_flag_;
};

//////////////////////////////////////////////////////////////////////////

class DBProcess
{
public:
	friend class DBManager;

	typedef std::pair<int, boost::any> type_t;

	typedef boost::tuple<LONGLONG, int/*user_index*/, int, unsigned int> charlist_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, CreateCharacterInfo*> createchar_t;
	typedef boost::tuple<LONGLONG, int/*m_index*/, int/*char_index*/, time_t, int> delchar_t;
	typedef boost::tuple<LONGLONG, int, int> canceldelchar_t;
	typedef boost::tuple<LONGLONG, int/*m_index*/, int/*char_index*/, int/*m_playmode*/, std::string/*m_proSite*/, std::string/*user_id*/, void*/*guild*/> selectchar_t;
	typedef boost::tuple<LONGLONG, int/*m_index*/, int/*charIndex*/, std::string/*id*/, std::string/*charName*/, bool/*disconnect flag*/, save_char_queryt_t*> savechar_t;

	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, int/*send_type*/> expressexist_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, int/*page index*/> expresslist_t;
	typedef boost::tuple<LONGLONG, int/*m_index*/, int/*char_index*/, expressIndex_t> expresstake_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, int/*page index*/> expresstakeall_t;
	typedef boost::tuple<LONGLONG, int/*char_index*/, ExpressSystemItemInfo*, bool> expressinputitem_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, unsigned int/*nas*/, int/*send_type*/, std::string/*sender*/, bool> expressinputnas_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, expressIndex_t, bool/*send_flag*/> expressdelete_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, int/*page index*/, bool/*send_flag*/> expressdeleteall_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/> sendanyinfoafterlogin_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, std::string/*nickName*/> expresssearchnickname_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*charIndex*/,ExpressSystemItemInfo*, std::string/*receiver*/, int/*sender_type*/> expresssenditemtonickname_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, std::string/*del_char_name*/> delcharforgm_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, std::string/*search_char_name*/, int/*itemVIndex*/> getcharindexbyGPS_t;
	typedef boost::tuple<LONGLONG, int/*user_index*/, int/*char_index*/, int/*virtual_index*/, char /*color*/, char /*background_color*/, char /*effect*/, std::string /*name*/, int*/*option_index*/, int*/*option_level*/> title_make_t;

	typedef std::string query_t;

public:
	DBProcess();

	~DBProcess()
	{
		char_db_.close();
		data_db_.close();
#ifdef USE_TENTER_BILLING
		catal_db_.close();
#endif

#ifdef STASH_PASSWORD
		auth_db_.close();
#endif
	}

	bool Connect();
	void Run();

	//////////////////////////////////////////////////////////////////////////
	void CharacterList(boost::any& argv);
	void CreateChar(boost::any& argv);
	void DeleteChar(boost::any& argv);
	void CancelDeleteChar(boost::any& argv);
	void SelectChar(boost::any& argv); // DBProcess_SelectChar.cpp ¿¡ À§Ä¡
	void SaveChar(boost::any& argv); // DBProcess_SaveChar.cpp ¿¡ À§Ä¡

	void ExpressExist(boost::any& argv);
	void ExpressList(boost::any& argv);
	void ExpressTake(boost::any& argv);
	void ExpressTakeAll(boost::any& argv);
	void ExpressInputItem(boost::any& argv);
	void ExpressInputNas(boost::any& argv);
	void ExpressDelete(boost::any& argv);
	void ExpressDeleteAll(boost::any& argv);
	void ExpressSearchNickName(boost::any& argv);
	void ExpressSendItemToNickName(boost::any& argv);

	void QueryProcess(boost::any& argv);
	void sendAnyInfoAfterLogin(boost::any& argv);

	void DelCharForGM(boost::any& argv);

	void QueryProcessForAuthDB(boost::any& argv);
	void QueryProcessForDataDB(boost::any& argv);

	void getCharIndexByGPS(boost::any& argv);

	void InsertMakeTitleInfo(boost::any& argv);
	static std::vector<PassiveData> GetCurrentCharacterPassiveData(int charIndex);

private:
	void SendMessageToClient(LONGLONG& seq_index, int userIndex, CNetMsg::SP& msg);
	void excute_query(std::vector<std::string>& vec); // DBProcess_SaveChar.cpp ¿¡ À§Ä¡
	bool excute_query_commi_and_rollback(std::vector<std::string>& vec); // DBProcess_SaveChar.cpp ¿¡ À§Ä¡
	void PromotionGive(int m_index, CPC* pChar, int partner_id, bool lucky);
	void getItemByExpress(ExpressSystemItemInfo* info, MYSQL_RES *result);
	void select_rvr_info_query(CPC* pChar);		// ÀúÀåµÇ¾îÁø °á»ç´ë Á¤º¸ °¡Á®¿À±â

	void FixItemUsedTime(CItem* pItem);

	void MySQLPing();

private:
	queue_ts<type_t>	queue_;

	bool		is_connect;
	mysqldb		char_db_;
	mysqldb		data_db_;
	mysqldb&	castle_db_;
	mysqldb&	charingame_db_;

#ifdef USE_TENTER_BILLING
	mysqldb		catal_db_;
#endif

	mysqldb&	trigger_db_;

#ifdef STASH_PASSWORD
	mysqldb		auth_db_;
#endif

	std::vector<std::string> a_item_idx_str;
	std::vector<std::string> a_plus_str;
	std::vector<std::string> a_wear_pos_str;
	std::vector<std::string> a_flag_str;
	std::vector<std::string> a_serial_str;
	std::vector<std::string> a_count_str;
	std::vector<std::string> a_used_str;
	std::vector<std::string> a_used2_str;

	std::vector<std::string> a_item_option_str[ITEMS_PER_ROW];
	std::vector<std::string> a_item_origin_str[ITEMS_PER_ROW];

	std::vector<std::string> a_socket_str;

#ifdef DURABILITY
	std::vector<std::string> a_now_durability_str;
	std::vector<std::string> a_max_durability_str;
#endif

	std::vector<std::string> a_mempos_comment;

};

#endif
