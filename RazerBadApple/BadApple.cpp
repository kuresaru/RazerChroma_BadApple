#include <iostream>

#include <windows.h>
#include <libloaderapi.h>
#include <tchar.h>

#include "MyRazer.h"
#include "SamplesData.h"

HMODULE m_hModule;

CREATEEFFECT CreateEffect = NULL;
CREATEKEYBOARDEFFECT CreateKeyboardEffect = NULL;
CREATEMOUSEEFFECT CreateMouseEffect = NULL;
CREATEHEADSETEFFECT CreateHeadsetEffect = NULL;
CREATEMOUSEPADEFFECT CreateMousematEffect = NULL;
CREATEKEYPADEFFECT CreateKeypadEffect = NULL;
CREATECHROMALINKEFFECT CreateChromaLinkEffect = NULL;
SETEFFECT SetEffect = NULL;
DELETEEFFECT DeleteEffect = NULL;
//QUERYDEVICE QueryDevice = NULL;

RZEFFECTID EffectId1 = GUID_NULL;

const ChromaSDK::Keyboard::RZKEY Key_Pixel_Map[52] = {
    ChromaSDK::Keyboard::RZKEY_F1,
    ChromaSDK::Keyboard::RZKEY_F2,
    ChromaSDK::Keyboard::RZKEY_F3,
    ChromaSDK::Keyboard::RZKEY_F4,
    ChromaSDK::Keyboard::RZKEY_F5,
    ChromaSDK::Keyboard::RZKEY_F6,
    ChromaSDK::Keyboard::RZKEY_F7,
    ChromaSDK::Keyboard::RZKEY_F8,
    ChromaSDK::Keyboard::RZKEY_F9,
    ChromaSDK::Keyboard::RZKEY_2,
    ChromaSDK::Keyboard::RZKEY_3,
    ChromaSDK::Keyboard::RZKEY_4,
    ChromaSDK::Keyboard::RZKEY_5,
    ChromaSDK::Keyboard::RZKEY_6,
    ChromaSDK::Keyboard::RZKEY_7,
    ChromaSDK::Keyboard::RZKEY_8,
    ChromaSDK::Keyboard::RZKEY_9,
    ChromaSDK::Keyboard::RZKEY_0,
    ChromaSDK::Keyboard::RZKEY_OEM_2,
    ChromaSDK::Keyboard::RZKEY_W,
    ChromaSDK::Keyboard::RZKEY_E,
    ChromaSDK::Keyboard::RZKEY_R,
    ChromaSDK::Keyboard::RZKEY_T,
    ChromaSDK::Keyboard::RZKEY_Y,
    ChromaSDK::Keyboard::RZKEY_U,
    ChromaSDK::Keyboard::RZKEY_I,
    ChromaSDK::Keyboard::RZKEY_O,
    ChromaSDK::Keyboard::RZKEY_P,
    ChromaSDK::Keyboard::RZKEY_OEM_4,
    ChromaSDK::Keyboard::RZKEY_S,
    ChromaSDK::Keyboard::RZKEY_D,
    ChromaSDK::Keyboard::RZKEY_F,
    ChromaSDK::Keyboard::RZKEY_G,
    ChromaSDK::Keyboard::RZKEY_H,
    ChromaSDK::Keyboard::RZKEY_J,
    ChromaSDK::Keyboard::RZKEY_K,
    ChromaSDK::Keyboard::RZKEY_L,
    ChromaSDK::Keyboard::RZKEY_OEM_7,
    ChromaSDK::Keyboard::RZKEY_Z,
    ChromaSDK::Keyboard::RZKEY_X,
    ChromaSDK::Keyboard::RZKEY_C,
    ChromaSDK::Keyboard::RZKEY_V,
    ChromaSDK::Keyboard::RZKEY_B,
    ChromaSDK::Keyboard::RZKEY_N,
    ChromaSDK::Keyboard::RZKEY_M,
    ChromaSDK::Keyboard::RZKEY_OEM_9,
    ChromaSDK::Keyboard::RZKEY_OEM_10,
    ChromaSDK::Keyboard::RZKEY_OEM_11,
};

int main()
{
    // º”‘ÿdll
	m_hModule = ::LoadLibrary(CHROMASDKDLL);
	if (m_hModule == NULL)
	{
		std::wcout << _T("LoadLibraryError\r\n");
		return 1;
	}

    // ÃÓ–¥≥Ã–Ú–≈œ¢
    ChromaSDK::APPINFOTYPE appInfo = {};
    _tcscpy_s(appInfo.Title, 256, _T("BadApple≤‚ ‘≥Ã–Ú"));
    _tcscpy_s(appInfo.Description, 1024, _T("Hello Bug!!"));
    _tcscpy_s(appInfo.Author.Name, 256, _T("ƒ∫π‚–°‘≥wzt"));
    _tcscpy_s(appInfo.Author.Contact, 256, _T("https://www.scraft.top"));

    //appInfo.SupportedDevice = 
    //    0x01 | // Keyboards
    //    0x02 | // Mice
    //    0x04 | // Headset
    //    0x08 | // Mousepads
    //    0x10 | // Keypads
    //    0x20   // ChromaLink devices
    //    ;
    appInfo.SupportedDevice = (0x01);
    appInfo.Category = 1;

    // ’“µΩ◊¢≤·∫Ø ˝÷∏’Î
    INITSDK InitSDK = (INITSDK)::GetProcAddress(m_hModule, "InitSDK");
    if (InitSDK == NULL)
    {
        std::wcout << _T("LoadLibraryError\r\n");
        return 1;
    }
    // ◊¢≤·≥Ã–Ú
    RZRESULT rzResult = InitSDK(&appInfo);
    if (rzResult != RZRESULT_SUCCESS)
    {
        std::wcout << _T("RegisterError\r\n");
        return 1;
    }
    CreateEffect = (CREATEEFFECT)::GetProcAddress(m_hModule, "CreateEffect");
    CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)::GetProcAddress(m_hModule, "CreateKeyboardEffect");
    CreateMouseEffect = (CREATEMOUSEEFFECT)::GetProcAddress(m_hModule, "CreateMouseEffect");
    CreateMousematEffect = (CREATEMOUSEPADEFFECT)::GetProcAddress(m_hModule, "CreateMousepadEffect");
    CreateKeypadEffect = (CREATEKEYPADEFFECT)::GetProcAddress(m_hModule, "CreateKeypadEffect");
    CreateHeadsetEffect = (CREATEHEADSETEFFECT)::GetProcAddress(m_hModule, "CreateHeadsetEffect");
    CreateChromaLinkEffect = (CREATECHROMALINKEFFECT)::GetProcAddress(m_hModule, "CreateChromaLinkEffect");
    SetEffect = (SETEFFECT)GetProcAddress(m_hModule, "SetEffect");
    DeleteEffect = (DELETEEFFECT)GetProcAddress(m_hModule, "DeleteEffect");

	std::wcout << _T("Init OK\r\n");

    ::CoCreateGuid(&EffectId1);
    ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE CustomKey = {};

    ::system("pause");
    std::wcout << _T("Start Play\r\n");
    for (int frame = 0; frame < 5478; frame++)
    {
        for (int i = 0; i < 52; i++)
        {
            CustomKey.Key[HIBYTE(Key_Pixel_Map[i])][LOBYTE(Key_Pixel_Map[i])] = 0x01000000 | samples_data[frame][i];
        }
        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY, &CustomKey, &EffectId1);

        SetEffect(EffectId1);
        Sleep(40);

        DeleteEffect(EffectId1);
    }

    std::wcout << _T("Finish\r\n");

	return 0;
}
