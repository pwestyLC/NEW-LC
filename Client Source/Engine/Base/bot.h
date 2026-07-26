#ifndef BotH
#define BotH

#include <string.h>

#define SYMBOL_NO_STR 0
#define SYMBOL_UP_REG 1
#define SYMBOL_DO_REG 2

#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define LEVEL_5 5

class ChatBot {
public:

	struct Translite {
		char RUS;
		char ENG;
	};

	struct RegulationList
	{
		int  LenText;
		char Text[32];
		int Type;
	};

	RegulationList m_RegulationList[512];
	int CountRegulationList;

	void AddInRegulationList(char *strText, int Type){

		m_RegulationList[CountRegulationList].LenText = strlen(strText);
		strcpy(m_RegulationList[CountRegulationList].Text, strText);
		m_RegulationList[CountRegulationList].Type = Type;

		CountRegulationList ++;
	}


	Translite m_Translite[33];
	int CountTranslite;


	void TransliteAdd(char SybmolRUS, char SymbolENG) {

		m_Translite[CountTranslite].RUS = SybmolRUS;
		m_Translite[CountTranslite].ENG = SymbolENG;

		CountTranslite++;
	}



	void TransliteAdd_2(char SybmolRUS, char SymbolENG) {

		m_Translite_2[CountTranslite_2].RUS = SybmolRUS;
		m_Translite_2[CountTranslite_2].ENG = SymbolENG;

		CountTranslite_2++;
	}

	Translite m_Translite_2[33];
	int CountTranslite_2;

	struct Violation {

		int IdRegulationText;
		int Position;
		int Type;

	};

	int CountViolation;

	Violation m_Violation[32];

	char GetRegulationSymbol(int IndexRegul, int IndexSymbol) {		
		if (m_RegulationList[IndexRegul].LenText < IndexSymbol) return NULL;
		return m_RegulationList[IndexRegul].Text[IndexSymbol];
	}

	bool GetViolation() {
		return isViolation;
	}

	bool isViolation;

	void ClearViolation() {
		isViolation = false;
		CountViolation = 0;
	}


	bool EditShift(char *str) {

		int len = strlen(str);
		if (len < 1) return false;
		int w = 0;
		for  (int i = 0; i < len; i++)
		{
			w = i + 1;
			if (w < len)
				if (str[i] == str[w]) { this->WipeString(str, i); if (str[w - 1] == '\0') break; i--; }
		}

		return true;
	}

	int CheckViolation(char *str) {

		int len = strlen(str);
		if (len < 1) return false;

    	for (int i = 0; i < CountRegulationList; i++)	
			for (int w = 0; w < len; w++)		
				for (int k = 0; k < m_RegulationList[i].LenText; k++)				
					if (str[w] == m_RegulationList[i].Text[k]) 
					{
						/*int v;
						for (v = 0; ((w < len) && (str[w + v] == GetRegulationSymbol(i, k + v))); v++);
						w += v;*/
						
						if (k == (m_RegulationList[i].LenText - 1)) {
							isViolation = true;
							m_Violation[CountViolation].IdRegulationText = i;
							m_Violation[CountViolation].Position = w - (m_RegulationList[i].LenText - 1);
							CountViolation++;
						}

						if ((w + 1) == len) break;
						w++;

					} else 			
						break;

					return CountViolation;
	}

	ChatBot() {
		
		CountTranslite = 0;
		CountRegulationList = 0;
		CountTranslite_2 = 0;
		strcpy(SymbolUpRegister,   "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿabcdefghijklmnopqrstuvwxyz");
		strcpy(SymbolDownRegister, "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßABCDEFGHIJKLMNOPQRSTUVWXYZ");
		strcpy(AllSymbol, "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
		CountAllSymbol  = strlen(AllSymbol);
		CountUpSymbol   = strlen(SymbolUpRegister);
		CountDownSymbol = strlen(SymbolDownRegister);

		// Èäåàëüíûå â íèæíåì ðåãèñòðå
		TransliteAdd('à', 'a');
		TransliteAdd('î', 'o');
		TransliteAdd('å', 'e');
		TransliteAdd('ó', 'y');
		TransliteAdd('ê', 'k');
		TransliteAdd('ð', 'p');
		TransliteAdd('õ', 'x');
		TransliteAdd('ñ', 'c');

		// Â âåðõíåì
		TransliteAdd('â', 'b');
		TransliteAdd('í', 'h');
		TransliteAdd('ò', 't');
		TransliteAdd('ì', 'm');

		//AddInRegulationList("õóé", 1);



		TransliteAdd_2('à', 'a');
		TransliteAdd_2('á', 'b');
		TransliteAdd_2('ñ', 'c');
		TransliteAdd_2('ä', 'd');
		TransliteAdd_2('å', 'e');
		TransliteAdd_2('ô', 'f');
		TransliteAdd_2('ã', 'g');
		TransliteAdd_2('õ', 'h');
		TransliteAdd_2('è', 'i');
		TransliteAdd_2('æ', 'j');
		TransliteAdd_2('ê', 'k');
		TransliteAdd_2('ë', 'l');
		TransliteAdd_2('ì', 'm');
		TransliteAdd_2('í', 'n');
		TransliteAdd_2('î', 'o');
		TransliteAdd_2('ï', 'p');
		TransliteAdd_2('ê', 'q');
		TransliteAdd_2('ð', 'r');
		TransliteAdd_2('ñ', 's');
		TransliteAdd_2('ò', 't');
		TransliteAdd_2('â', 'u');
		TransliteAdd_2('â', 'v');
		TransliteAdd_2('â', 'w');
		TransliteAdd_2('ê', 'x');
		TransliteAdd_2('ó', 'y');
		TransliteAdd_2('ó', 'y');
		TransliteAdd_2('ç', 'z');
	}



	bool CheckSymbolRUS(char Symbol) {

		for (int i = 0; i < CountDownSymbol; i++)
			if (SymbolUpRegister[i] == Symbol) return true;

		return false;
	}

	bool EditSymbolToChar(char *str) {

		int len = strlen(str);
		if (len < 1) return false;

		char SymbolRus;
		char _tmp[256];
		strcpy(_tmp, str);

		for (int w = 0; w < 34;  w++)
		{
			strcpy(str, _tmp);
			SymbolRus = GetUpSymbol(w);

			for (int i = 0; i < len; i++)	
				if ((!CheckSymbolRUS(str[i]) && (str[i] != ' ')))
					str[i] = SymbolRus;

		//	std::cout << "\n" << str;

			DeleteAllSymbol(str);
			CheckViolation(str);
			if (this->GetViolation()) return GetViolation();
		}

		return false;
	}

	bool CheckMsg(const char *Msg) {

		ClearViolation();

		if (strlen(Msg) > 250) return false;



		char tmp[256];
		char str[256];
		char tmp2[256];

		strcpy(str, Msg);
		strcpy(tmp2, Msg);
	
		//std::cout << "\nÈñõîäíàÿ ñòðîêà: " << str;

		// Ïåðåâåäåì â íèæíåþ ñòðîêó
		EditInDownRegister(tmp2);
		TransliteChangeMethod1(tmp2);
		EditShift(tmp2);
		EditSymbolToChar(tmp2);

		if (this->GetViolation()) return GetViolation();

		EditInDownRegister(str);
		DeleteAllSymbol(str);


		strcpy(tmp, str);
		EditShift(str);
		EditShift(tmp);

		TransliteChangeMethod1(str); 
		CheckViolation(str);

		if (this->GetViolation()) return GetViolation();

		TransliteChangeMethod1337(tmp);
		CheckViolation(tmp);

		if (this->GetViolation()) return GetViolation();

	//	std::cout << "\nÏîñëå ïðîâåðîê: " << str;	
	//	std::cout << "\nÏîñëå ïðîâåðîê 1337: " << tmp;


	//	for (int i = 0; i < CountViolation; i++)	
	//		std::cout << "\nÍàðóøåíèå ïðàâèë [" << i + 1 << "] â ïîçèöèè: " << m_Violation[i].Position << " çàïðåùåííîå ñëîâî: " << m_RegulationList[m_Violation[i].IdRegulationText].Text;
     	
		return GetViolation();
	}


	char AllSymbol[256];
	int CountAllSymbol;

	struct RegisterInfo {
		int Type;
		int Index;
	};


	char TransliteSymbolRus(char Symbol) {
		
		for (int i = 0; i < CountTranslite; i++)
			if (Symbol == m_Translite[i].ENG) return m_Translite[i].RUS;
		
		return Symbol;
	}

	char TransliteSymbolRus1337(char Symbol) {

		for (int i = 0; i < CountTranslite_2; i++)
			if (Symbol == m_Translite_2[i].ENG) return m_Translite_2[i].RUS;

		return Symbol;
	}


	bool TransliteChangeMethod1337(char *str) {
		int len = strlen(str);
		if (len < 1) return false;
		for (int i = 0; i < len; i++)
			str[i] = TransliteSymbolRus1337(str[i]);

		return true;
	}

	bool TransliteChangeMethod1(char *str) {
		int len = strlen(str);
		if (len < 1) return false;
		for (int i = 0; i < len; i++)
			str[i] = TransliteSymbolRus(str[i]);

		return true;
	}

	 bool DeleteAllSymbol(char* str) {
	
		int len = strlen(str);
		if (len < 1) return false;

		for (int i = 0; i < len; i++) 
			if (!CheckSymbol(str[i])) { WipeString(str, i); len = strlen(str); i--; }

		return true;
	}

	// Ñäâèã ñòðîêè ñ çàòåðàíèåì 
	bool WipeString(char *str, int IndexByte)
	{
		int len = strlen(str);
		if (len < 1) return false;
		if ((IndexByte == len) || (IndexByte < 0)) return false;
		
		for (int i = IndexByte; i < len; i++)	
		 str[i] = str[i + 1];
		
		str[len] = '\0';
		return true;
	}

	bool CheckSymbol(char Symbol) {

		for (int i = 0; i < CountAllSymbol; i++)
			if (AllSymbol[i] == Symbol) return true;
		
		return false;
	}

    bool CheckStr(const char* str) {

		char valid[] = " /_[]1234567890àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@";
		int lenvalid = strlen(valid);

		int len = strlen(str);

		if (len < 1) return false;

		bool isA = false;

		for (int i = 0; i < len; i++) {

			isA = false;

			for (size_t w = 0; w < lenvalid; w++)
			{
				if (str[i] == valid[w]) {
					isA = true;
					break;
				}
			}

			if (!isA) return false;
		}

		return true;
	}

	bool EditInDownRegister(char *Str) {

		int StrLen = strlen(Str);
		if (StrLen < 1) return false;

		char cBuf;
		for  (int i = 0; i < StrLen; i++)		{
			cBuf = GetUpSymbol(IndexSymbol(Str[i]));
			if (cBuf != NULL) Str[i] = cBuf;
		}

		return true;
	}

	bool EditInUpRegister(char *Str) {

		int StrLen = strlen(Str);
		if (StrLen < 1) return false;

		char cBuf;
		for (int i = 0; i < StrLen; i++)		{
			cBuf = GetDownSymbol(IndexSymbol(Str[i]));
			if (cBuf != NULL) Str[i] = cBuf;
		}

		return true;
	}

	char GetDownSymbol(RegisterInfo m_RegisterInfo) {
		if (m_RegisterInfo.Type == SYMBOL_UP_REG) return GetDownSymbol(m_RegisterInfo.Index);
		return NULL;
	}

	char GetUpSymbol(RegisterInfo m_RegisterInfo) {
		if (m_RegisterInfo.Type == SYMBOL_DO_REG) return GetUpSymbol(m_RegisterInfo.Index);
		return NULL;
	}

	char GetUpSymbol(int Index)
	{
		return SymbolUpRegister[Index];
	}

	char GetDownSymbol(int Index)
	{
		return SymbolDownRegister[Index];
	}


	RegisterInfo IndexSymbol(char Symbol) {
		
		RegisterInfo Result;
		Result.Type  = SYMBOL_NO_STR;
		Result.Index = -1;
		for (int i = 0; i < CountDownSymbol; i++)
		{
			if (Symbol == SymbolUpRegister[i])
			{
				Result.Type = SYMBOL_UP_REG;
				Result.Index = i;
				return Result;
			}

			if (Symbol == SymbolDownRegister[i])
			{
				Result.Type  = SYMBOL_DO_REG;
				Result.Index = i;
				return Result;
			}
		}

		return Result;
	}

	int CountDownSymbol;
	int CountUpSymbol;

    char SymbolDownRegister[256];
	char SymbolUpRegister[256];

};


#endif
