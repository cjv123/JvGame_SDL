#ifndef _JVG_H
#define _JVG_H
#include "ini.h"

class JvGame;
class JvState;
class JvCamera;
class JvSave;
class JvJoystick;
class JvSound;


/**
*�������һЩȫ�ֺ�����ȫ�ֶ���
*/
class JvG
{
public:
	/**
	 *����ȫ������
	 *@param JvGame* jvGame,JvGame��ָ��
	 *@param unsigned int Width,��Ļ��
	 *@param unsigned int Height,��Ļ��
	 *@return void
	 */
	static void setGameData(JvGame* JvGameP,unsigned int Width,
		unsigned int Height);

	/**
	 *��������
	 *@param JvState* StateP,����������stateָ��
	 *@return void
	 */
	static void switchState(JvState* StateP);

	static void playMusic(const char* filename,float Volume=1.0f);
	static void play(const char* filename,float Volume=1.0f,bool Looped=false);
	static void stopMusic();
	
	/*JvGameָ��*/
	static JvGame* jvGameP;

	/*��Ļ��*/
	static unsigned int width;

	/*��Ļ��*/
	static unsigned int height;
	
	/*��ǰ����ָ��*/
	static JvState* stateP;

	/*֡��*/
	static unsigned int frameRate;
	
	/*ÿ֡������ʱ��(��)*/
	static double elapsed;

	/*����elapsed*/
	static double maxElapsed;

	/*ʱ������*/
	static double timeScale;

	/*��ǰ�������ָ��*/
	static JvCamera* camera;

	/*�����豸*/
	static JvJoystick* joystick;

	static JvSave* save;

	static JvSound* sound;

	static bool pause;

	static mINI::INIStructure ini;
};

#endif