# NPC 3696 Cash Exchange - Complete Implementation

## Problem Fixed
NPC 3696 was showing default quest dialog instead of Cash Exchange UI.

## Root Causes Addressed
1. **UI order issue**: NPC 3696 check was too late in `OpenQuest()` - FIXED
2. **XML not loaded**: CashExchangeUI XML was not loaded in UIWindowDeclare - FIXED

## Changes Made

### 1. Client UI Logic (UIQuestNew.cpp)
- Moved NPC 3696 handler to line 298 (top of `OpenQuest()`)
- Finds `"CashExchangeUI"` window and shows it
- Returns early to bypass all quest dialog logic

### 2. UI System Registration (UIWindowDeclare.cpp)
- Added `#include <Engine/Contents/function/CashExchangeUI.h>` 
- Added UI initialization at line 285-287:
  ```cpp
  m_apUIs[UI_CASHEXCHANGE] = new CCashExchangeUI;
  LoadXML("CashExchangeUI.xml", m_apUIs[UI_CASHEXCHANGE]);
  ```

### 3. Server Side (doFuncQuest.cpp - already done)
- NPC 3696 special case sends empty quest list

## Build Status
✅ Successfully compiled
